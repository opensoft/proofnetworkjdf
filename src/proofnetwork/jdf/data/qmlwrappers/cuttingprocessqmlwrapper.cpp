#include "cuttingprocessqmlwrapper.h"
#include "cutblockqmlwrapper.h"
#include "mediaqmlwrapper.h"

#include "proofnetwork/jdf/data/cuttingprocess.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class CuttingProcessQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CuttingProcessQmlWrapper)
    void updateCutingParams();
    void updateMedia();

    CuttingParamsQmlWrapper *cuttingParams = nullptr;
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

CuttingParamsQmlWrapper *CuttingProcessQmlWrapper::cuttingParams() const
{
    Q_D(const CuttingProcessQmlWrapper);
    return d->cuttingParams;
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
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CuttingProcess, quint32, amount)

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
    connect(cuttingProcess.data(), &CuttingProcess::amountChanged,
            this, &CuttingProcessQmlWrapper::amountChanged);
    connect(cuttingProcess.data(), &CuttingProcess::cuttingParamsChanged,
            d->lambdaConnectContext, [d](){d->updateCutingParams();});
    connect(cuttingProcess.data(), &CuttingProcess::mediaChanged,
            d->lambdaConnectContext, [d](){d->updateMedia();});

    CuttingProcessSP oldCuttingProcess = qSharedPointerCast<CuttingProcess>(old);
    if (oldCuttingProcess) {
        if (cuttingProcess->id() != oldCuttingProcess->id())
            emit idChanged(cuttingProcess->id());
        if (cuttingProcess->pressSheetWidth() != oldCuttingProcess->pressSheetWidth())
            emit pressSheetWidthChanged(cuttingProcess->pressSheetWidth());
        if (cuttingProcess->pressSheetHeight() != oldCuttingProcess->pressSheetHeight())
            emit pressSheetHeightChanged(cuttingProcess->pressSheetHeight());
        if (cuttingProcess->amount() != oldCuttingProcess->amount())
            emit amountChanged(cuttingProcess->amount());
    }

    d->updateCutingParams();
    d->updateMedia();
}

void CuttingProcessQmlWrapperPrivate::updateCutingParams()
{
    Q_Q(CuttingProcessQmlWrapper);
    CuttingProcessSP cutProcess = entity<CuttingProcess>();
    if (cuttingParams == nullptr)
        cuttingParams = cutProcess->cuttingParams()->toQmlWrapper(q);
    else
        cuttingParams->setEntity(cutProcess->cuttingParams());

    emit q->cuttingParamsChanged(cuttingParams);
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
