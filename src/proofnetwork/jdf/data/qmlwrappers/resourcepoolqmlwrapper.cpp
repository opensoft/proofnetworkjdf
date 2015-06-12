#include "resourcepoolqmlwrapper.h"

#include "componentqmlwrapper.h"
#include "cuttingparamsqmlwrapper.h"
#include "mediaqmlwrapper.h"
#include "foldingparamsqmlwrapper.h"
#include "laminatingintentqmlwrapper.h"

#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/laminatingintent.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class ResourcePoolQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ResourcePoolQmlWrapper)
    void updateComponent();
    void updateCutingParams();
    void updateMedia();
    void updateFoldingParams();
    void updateLaminatingIntent();

    QList<ComponentQmlWrapper *> components;
    QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> qmlComponentsList;
    static ComponentQmlWrapper *componentAt(QQmlListProperty<ComponentQmlWrapper> *property, int index);
    static int componentsCount(QQmlListProperty<ComponentQmlWrapper> *property);

    CuttingParamsQmlWrapper *cuttingParams = nullptr;
    MediaQmlWrapper *media = nullptr;
    FoldingParamsQmlWrapper *foldingParams = nullptr;
    LaminatingIntentQmlWrapper *laminatingIntent = nullptr;
};

}
}

using namespace Proof;
using namespace Proof::Jdf;

ResourcePoolQmlWrapper::ResourcePoolQmlWrapper(const ResourcePoolSP &resourcePool, QObject *parent)
    : NetworkDataEntityQmlWrapper(resourcePool, *new ResourcePoolQmlWrapperPrivate, parent)
{
    setupEntity();
}

ResourcePoolQmlWrapper::~ResourcePoolQmlWrapper()
{
}

QQmlListProperty<ComponentQmlWrapper> ResourcePoolQmlWrapper::components() const
{
    Q_D(const ResourcePoolQmlWrapper);
    return d->qmlComponentsList;
}

CuttingParamsQmlWrapper *ResourcePoolQmlWrapper::cuttingParams() const
{
    Q_D(const ResourcePoolQmlWrapper);
    return d->cuttingParams;
}

MediaQmlWrapper *ResourcePoolQmlWrapper::media() const
{
    Q_D(const ResourcePoolQmlWrapper);
    return d->media;
}

FoldingParamsQmlWrapper *ResourcePoolQmlWrapper::foldingParams() const
{
    Q_D(const ResourcePoolQmlWrapper);
    return d->foldingParams;
}

LaminatingIntentQmlWrapper *ResourcePoolQmlWrapper::laminatingIntent() const
{
    Q_D(const ResourcePoolQmlWrapper);
    return d->laminatingIntent;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(ResourcePool)

void ResourcePoolQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(ResourcePoolQmlWrapper);
    Q_UNUSED(old);
    ResourcePoolSP cuttingProcess = d->entity<ResourcePool>();
    Q_ASSERT(cuttingProcess);

    connect(cuttingProcess.data(), &ResourcePool::componentsChanged,
            d->lambdaConnectContext, [d](){d->updateComponent();});
    connect(cuttingProcess.data(), &ResourcePool::cuttingParamsChanged,
            d->lambdaConnectContext, [d](){d->updateCutingParams();});
    connect(cuttingProcess.data(), &ResourcePool::mediaChanged,
            d->lambdaConnectContext, [d](){d->updateMedia();});

    d->updateComponent();
    d->updateCutingParams();
    d->updateMedia();
    d->updateFoldingParams();
}

void ResourcePoolQmlWrapperPrivate::updateComponent()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP resourcePool = entity<ResourcePool>();
    for (ComponentQmlWrapper *wrapper : components)
        wrapper->deleteLater();

    components.clear();
    for (const ComponentSP &component : resourcePool->components())
        components << component->toQmlWrapper(q);

    qmlComponentsList = QQmlListProperty<Proof::Jdf::ComponentQmlWrapper>(q, &components,
                                                                          &ResourcePoolQmlWrapperPrivate::componentsCount,
                                                                          &ResourcePoolQmlWrapperPrivate::componentAt);
    emit q->componentsChanged(qmlComponentsList);
}

void ResourcePoolQmlWrapperPrivate::updateCutingParams()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP cutProcess = entity<ResourcePool>();
    if (cuttingParams == nullptr)
        cuttingParams = cutProcess->cuttingParams()->toQmlWrapper(q);
    else
        cuttingParams->setEntity(cutProcess->cuttingParams());

    emit q->cuttingParamsChanged(cuttingParams);
}

void ResourcePoolQmlWrapperPrivate::updateMedia()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP cutProcess = entity<ResourcePool>();
    if (media == nullptr)
        media = cutProcess->media()->toQmlWrapper(q);
    else
        media->setEntity(cutProcess->media());
    emit q->mediaChanged(media);
}

void ResourcePoolQmlWrapperPrivate::updateFoldingParams()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP resourcePool = entity<ResourcePool>();
    if (foldingParams == nullptr)
        foldingParams = resourcePool->foldingParams()->toQmlWrapper(q);
    else
        foldingParams->setEntity(resourcePool->foldingParams());
    emit q->foldingParamsChanged(foldingParams);
}

void ResourcePoolQmlWrapperPrivate::updateLaminatingIntent()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP resourcePool = entity<ResourcePool>();
    if (laminatingIntent == nullptr)
        laminatingIntent = resourcePool->laminatingIntent()->toQmlWrapper(q);
    else
        laminatingIntent->setEntity(resourcePool->laminatingIntent());
    emit q->laminatingIntentChanged(laminatingIntent);

}

ComponentQmlWrapper *ResourcePoolQmlWrapperPrivate::componentAt(QQmlListProperty<ComponentQmlWrapper> *property, int index)
{
    return static_cast<QList<ComponentQmlWrapper *> *>(property->data)->at(index);
}

int ResourcePoolQmlWrapperPrivate::componentsCount(QQmlListProperty<ComponentQmlWrapper> *property)
{
    return static_cast<QList<ComponentQmlWrapper *> *>(property->data)->count();
}
