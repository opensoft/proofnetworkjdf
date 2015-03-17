#include "cuttingprocessqmlwrapper.h"

#include "componentqmlwrapper.h"
#include "mediaqmlwrapper.h"

#include "proofnetwork/jdf/data/cuttingprocess.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class CuttingProcessQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CuttingProcessQmlWrapper)
    void updateComponent();
    void updateCutingParams();
    void updateMedia();

    ComponentQmlWrapper *component = nullptr;
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

ComponentQmlWrapper *CuttingProcessQmlWrapper::component() const
{
    Q_D(const CuttingProcessQmlWrapper);
    return d->component;
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

void CuttingProcessQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(CuttingProcessQmlWrapper);
    Q_UNUSED(old);
    CuttingProcessSP cuttingProcess = d->entity<CuttingProcess>();
    Q_ASSERT(cuttingProcess);

    connect(cuttingProcess.data(), &CuttingProcess::componentChanged,
            d->lambdaConnectContext, [d](){d->updateComponent();});
    connect(cuttingProcess.data(), &CuttingProcess::cuttingParamsChanged,
            d->lambdaConnectContext, [d](){d->updateCutingParams();});
    connect(cuttingProcess.data(), &CuttingProcess::mediaChanged,
            d->lambdaConnectContext, [d](){d->updateMedia();});

    d->updateComponent();
    d->updateCutingParams();
    d->updateMedia();
}

void CuttingProcessQmlWrapperPrivate::updateComponent()
{
    Q_Q(CuttingProcessQmlWrapper);
    CuttingProcessSP cutProcess = entity<CuttingProcess>();
    if (component == nullptr)
        component = cutProcess->component()->toQmlWrapper(q);
    else
        component->setEntity(cutProcess->component());

    emit q->componentChanged(component);
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
