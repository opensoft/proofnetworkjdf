#include "cuttingparamsqmlwrapper.h"

#include "cutblockqmlwrapper.h"

#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/cutblock.h"

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class CuttingParamsQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CuttingParamsQmlWrapper)
    void updateCutBlocks();
    void updateParts();

    static CutBlockQmlWrapper *cutBlockAt(QQmlListProperty<CutBlockQmlWrapper> *property, int index);
    static int cutBlocksCount(QQmlListProperty<CutBlockQmlWrapper> *property);

    static CuttingParamsQmlWrapper *partAt(QQmlListProperty<CuttingParamsQmlWrapper> *property, int index);
    static int partsCount(QQmlListProperty<CuttingParamsQmlWrapper> *property);

    QList<CutBlockQmlWrapper *> cutBlocks;
    QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper> qmlCutBlocksList;

    QList<CuttingParamsQmlWrapper *> parts;
    QQmlListProperty<Proof::Jdf::CuttingParamsQmlWrapper> qmlPartsList;
};

}
}

using namespace Proof;
using namespace Proof::Jdf;

CuttingParamsQmlWrapper::CuttingParamsQmlWrapper(const CuttingParamsSP &cuttingParams, QObject *parent)
    : AbstractResourceQmlWrapper(cuttingParams, *new CuttingParamsQmlWrapperPrivate, parent)
{
    setupEntity();
}

CuttingParamsQmlWrapper::~CuttingParamsQmlWrapper()
{
}

QQmlListProperty<CutBlockQmlWrapper> CuttingParamsQmlWrapper::cutBlocks()
{
    Q_D(CuttingParamsQmlWrapper);
    return d->qmlCutBlocksList;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(CuttingParams)

QQmlListProperty<CuttingParamsQmlWrapper> CuttingParamsQmlWrapper::parts()
{
    Q_D(CuttingParamsQmlWrapper);
    return d->qmlPartsList;
}

void CuttingParamsQmlWrapperPrivate::updateParts()
{
    Q_Q(CuttingParamsQmlWrapper);
    CuttingParamsSP cuttingParams = entity<CuttingParams>();
    for (CuttingParamsQmlWrapper *wrapper : parts)
        wrapper->deleteLater();

    parts.clear();
    for (const CuttingParamsSP &part : cuttingParams->parts())
        parts << part->toQmlWrapper(q);

    qmlPartsList = QQmlListProperty<Proof::Jdf::CuttingParamsQmlWrapper>(q, &parts,
                                                                        &CuttingParamsQmlWrapperPrivate::partsCount,
                                                                        &CuttingParamsQmlWrapperPrivate::partAt);
    emit q->partsChanged(qmlPartsList);
}

CuttingParamsQmlWrapper *CuttingParamsQmlWrapperPrivate::partAt(QQmlListProperty<CuttingParamsQmlWrapper> *property, int index)
{
    return static_cast<QList<CuttingParamsQmlWrapper *> *>(property->data)->at(index);
}

int CuttingParamsQmlWrapperPrivate::partsCount(QQmlListProperty<CuttingParamsQmlWrapper> *property)
{
    return static_cast<QList<CuttingParamsQmlWrapper *> *>(property->data)->count();
}

void CuttingParamsQmlWrapperPrivate::updateCutBlocks()
{
    Q_Q(CuttingParamsQmlWrapper);
    CuttingParamsSP cuttingParam = entity<CuttingParams>();
    for (CutBlockQmlWrapper *wrapper : cutBlocks)
        wrapper->deleteLater();

    cutBlocks.clear();
    for (const CutBlockSP &cutBlock : cuttingParam->cutBlocks())
        cutBlocks << cutBlock->toQmlWrapper(q);

    qmlCutBlocksList = QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>(q, &cutBlocks,
                                                                        &CuttingParamsQmlWrapperPrivate::cutBlocksCount,
                                                                        &CuttingParamsQmlWrapperPrivate::cutBlockAt);
    emit q->cutBlocksChanged(qmlCutBlocksList);
}

CutBlockQmlWrapper *CuttingParamsQmlWrapperPrivate::cutBlockAt(QQmlListProperty<CutBlockQmlWrapper> *property, int index)
{
    return static_cast<QList<CutBlockQmlWrapper *> *>(property->data)->at(index);
}

int CuttingParamsQmlWrapperPrivate::cutBlocksCount(QQmlListProperty<CutBlockQmlWrapper> *property)
{
    return static_cast<QList<CutBlockQmlWrapper *> *>(property->data)->count();
}

void CuttingParamsQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(CuttingParamsQmlWrapper);
    CuttingParamsSP cuttingParams = d->entity<CuttingParams>();
    Q_ASSERT(cuttingParams);

    connect(cuttingParams.data(), &CuttingParams::cutBlocksChanged,
            d->lambdaConnectContext, [d](){d->updateCutBlocks();});
    connect(cuttingParams.data(), &CuttingParams::partsChanged,
            d->lambdaConnectContext, [d](){d->updateParts();});

    d->updateCutBlocks();
    d->updateParts();

    CuttingParamsSP oldCuttingParams = qSharedPointerCast<CuttingParams>(old);
    if (oldCuttingParams) {
        bool equal = true;
        for( int i = 0; i < cuttingParams->cutBlocks().count(); ++i ) {
            if (cuttingParams->cutBlocks()[i]->blockName() != cuttingParams->cutBlocks()[i]->blockName()) {
                equal = false;
                break;
            }
        }
        if (!equal)
            emit cutBlocksChanged(cuttingParams->toQmlWrapper()->cutBlocks());
    }
}
