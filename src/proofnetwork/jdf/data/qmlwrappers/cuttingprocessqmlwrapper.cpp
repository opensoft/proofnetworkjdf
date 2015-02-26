#include "cuttingprocessqmlwrapper.h"
#include "cutblockqmlwrapper.h"
#include "mediaqmlwrapper.h"

#include "proofnetwork/jdf/data/cuttingprocess.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class CuttingProcessQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CuttingProcessQmlWrapper)
    void updateCutBlocks();
    void updateMedia();

    static CutBlockQmlWrapper *cutBlockAt(QQmlListProperty<CutBlockQmlWrapper> *property, int index);
    static int cutBlocksCount(QQmlListProperty<CutBlockQmlWrapper> *property);

    QList<CutBlockQmlWrapper *> cutBlocks;
    QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper> qmlCutBlocksList;
    MediaQmlWrapper *media = nullptr;
};

}
}

using namespace Proof;
using namespace Proof::Jdf;

CuttingProcessQmlWrapper::CuttingProcessQmlWrapper(const CuttingProcessSP &cuttingProcess, QObject *parent)
    : NetworkDataEntityQmlWrapper(cuttingProcess, *new CuttingProcessQmlWrapperPrivate, parent)
{
    setupEntity();
}

CuttingProcessQmlWrapper::~CuttingProcessQmlWrapper()
{
}

QQmlListProperty<CutBlockQmlWrapper> CuttingProcessQmlWrapper::cutBlocks()
{
    Q_D(CuttingProcessQmlWrapper);
    return d->qmlCutBlocksList;
}

MediaQmlWrapper *CuttingProcessQmlWrapper::media() const
{
    Q_D(const CuttingProcessQmlWrapper);
    return d->media;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(CuttingProcess)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CuttingProcess, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CuttingProcess, double, pressSheetWidth)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CuttingProcess, double, pressSheetHeight)

void CuttingProcessQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(CuttingProcessQmlWrapper);
    CuttingProcessSP cuttingProcess = d->entity<CuttingProcess>();
    Q_ASSERT(cuttingProcess);

    connect(cuttingProcess.data(), &CuttingProcess::idChanged,
            this, &CuttingProcessQmlWrapper::idChanged);
    connect(cuttingProcess.data(), &CuttingProcess::pressSheetWidthChanged,
            this, &CuttingProcessQmlWrapper::pressSheetWidthChanged);
    connect(cuttingProcess.data(), &CuttingProcess::pressSheetHeightChanged,
            this, &CuttingProcessQmlWrapper::pressSheetHeightChanged);
    connect(cuttingProcess.data(), &CuttingProcess::cutBlocksChanged,
            d->lambdaConnectContext, [d](){d->updateCutBlocks();});
    connect(cuttingProcess.data(), &CuttingProcess::mediaChanged,
            d->lambdaConnectContext, [d](){d->updateMedia();});

    d->updateCutBlocks();

    CuttingProcessSP oldCuttingProcess = qSharedPointerCast<CuttingProcess>(old);
    if (oldCuttingProcess) {
        if (cuttingProcess->id() != oldCuttingProcess->id())
            emit idChanged(cuttingProcess->id());
        if (cuttingProcess->pressSheetWidth() != oldCuttingProcess->pressSheetWidth())
            emit pressSheetWidthChanged(cuttingProcess->pressSheetWidth());
        if (cuttingProcess->pressSheetHeight() != oldCuttingProcess->pressSheetHeight())
            emit pressSheetHeightChanged(cuttingProcess->pressSheetHeight());
        if (cuttingProcess->id() != oldCuttingProcess->id())
            emit idChanged(cuttingProcess->id());

        bool equal = true;
        for( int i=0; i < cuttingProcess->cutBlocks().count(); ++i )
        {
            if (cuttingProcess->cutBlocks()[i]->id() != cuttingProcess->cutBlocks()[i]->id()) {
                equal = false;
                break;
            }
        }
        if (!equal)
            emit cutBlocksChanged(cuttingProcess->toQmlWrapper()->cutBlocks());

    }

    d->updateMedia();
}

void CuttingProcessQmlWrapperPrivate::updateCutBlocks()
{
    Q_Q(CuttingProcessQmlWrapper);
    CuttingProcessSP cutProcess = entity<CuttingProcess>();
    for (CutBlockQmlWrapper *wrapper : cutBlocks)
        wrapper->deleteLater();

    cutBlocks.clear();
    for (const CutBlockSP &cutBlock : cutProcess->cutBlocks())
        cutBlocks << cutBlock->toQmlWrapper(q);

    qmlCutBlocksList = QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>(q, &cutBlocks,
                                                                                     &CuttingProcessQmlWrapperPrivate::cutBlocksCount,
                                                                                     &CuttingProcessQmlWrapperPrivate::cutBlockAt);
    emit q->cutBlocksChanged(qmlCutBlocksList);
}

void CuttingProcessQmlWrapperPrivate::updateMedia()
{
    Q_Q(CuttingProcessQmlWrapper);
    CuttingProcessSP cutProcess = entity<CuttingProcess>();
    if (media == nullptr)
        media = cutProcess->media()->toQmlWrapper(q);
    else
        media->setEntity(cutProcess->media());
    emit q->mediaChanged(media);
}

CutBlockQmlWrapper *CuttingProcessQmlWrapperPrivate::cutBlockAt(QQmlListProperty<CutBlockQmlWrapper> *property, int index)
{
    return static_cast<QList<CutBlockQmlWrapper *> *>(property->data)->at(index);
}

int CuttingProcessQmlWrapperPrivate::cutBlocksCount(QQmlListProperty<CutBlockQmlWrapper> *property)
{
    return static_cast<QList<CutBlockQmlWrapper *> *>(property->data)->count();
}
