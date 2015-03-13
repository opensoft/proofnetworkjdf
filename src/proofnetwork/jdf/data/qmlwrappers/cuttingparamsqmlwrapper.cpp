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

    static CutBlockQmlWrapper *cutBlockAt(QQmlListProperty<CutBlockQmlWrapper> *property, int index);
    static int cutBlocksCount(QQmlListProperty<CutBlockQmlWrapper> *property);

    QList<CutBlockQmlWrapper *> cutBlocks;
    QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper> qmlCutBlocksList;
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

void CuttingParamsQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(CuttingParamsQmlWrapper);
    CuttingParamsSP cuttingParams = d->entity<CuttingParams>();
    Q_ASSERT(cuttingParams);

    connect(cuttingParams.data(), &CuttingParams::cutBlocksChanged,
            d->lambdaConnectContext, [d](){d->updateCutBlocks();});

    d->updateCutBlocks();

    CuttingParamsSP oldCuttingParams = qSharedPointerCast<CuttingParams>(old);
    if (oldCuttingParams) {
        bool equal = true;
        for( int i=0; i < cuttingParams->cutBlocks().count(); ++i )
        {
            if (cuttingParams->cutBlocks()[i]->id() != cuttingParams->cutBlocks()[i]->id()) {
                equal = false;
                break;
            }
        }
        if (!equal)
            emit cutBlocksChanged(cuttingParams->toQmlWrapper()->cutBlocks());
    }
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

