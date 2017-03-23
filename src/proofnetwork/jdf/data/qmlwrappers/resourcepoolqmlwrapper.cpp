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
    void updateComponents();
    void updateCutingParams();
    void updateMedia();
    void updateFoldingParams();
    void updateLaminatingIntent();

    QList<ComponentQmlWrapper *> components;
    QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> qmlComponentsList;
    static ComponentQmlWrapper *componentAt(QQmlListProperty<ComponentQmlWrapper> *property, int index);
    static int componentsCount(QQmlListProperty<ComponentQmlWrapper> *property);

    QList<MediaQmlWrapper *> media;
    QQmlListProperty<Proof::Jdf::MediaQmlWrapper> qmlMediaList;
    static MediaQmlWrapper *mediaAt(QQmlListProperty<MediaQmlWrapper> *property, int index);
    static int mediaCount(QQmlListProperty<MediaQmlWrapper> *property);

    CuttingParamsQmlWrapper *cuttingParams = nullptr;
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

QQmlListProperty<MediaQmlWrapper> ResourcePoolQmlWrapper::media() const
{
    Q_D(const ResourcePoolQmlWrapper);
    return d->qmlMediaList;
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
    Q_UNUSED(old)
    ResourcePoolSP resourcePool = d->entity<ResourcePool>();
    Q_ASSERT(resourcePool);

    connect(resourcePool.data(), &ResourcePool::componentsChanged,
            d->lambdaConnectContext, [d](){d->updateComponents();});
    connect(resourcePool.data(), &ResourcePool::cuttingParamsChanged,
            d->lambdaConnectContext, [d](){d->updateCutingParams();});
    connect(resourcePool.data(), &ResourcePool::laminatingIntentChanged,
            d->lambdaConnectContext, [d](){d->updateLaminatingIntent();});
    connect(resourcePool.data(), &ResourcePool::mediaChanged,
            d->lambdaConnectContext, [d](){d->updateMedia();});
    connect(resourcePool.data(), &ResourcePool::foldingParamsChanged,
            d->lambdaConnectContext, [d](){d->updateFoldingParams();});

    d->updateComponents();
    d->updateCutingParams();
    d->updateMedia();
    d->updateFoldingParams();
}

void ResourcePoolQmlWrapperPrivate::updateComponents()
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
    ResourcePoolSP resourcePool = entity<ResourcePool>();
    for (MediaQmlWrapper *wrapper : media)
        wrapper->deleteLater();

    media.clear();
    for (const MediaSP &md : resourcePool->media())
        media << md->toQmlWrapper(q);

    qmlMediaList = QQmlListProperty<Proof::Jdf::MediaQmlWrapper>(q, &media,
                                                                 &ResourcePoolQmlWrapperPrivate::mediaCount,
                                                                 &ResourcePoolQmlWrapperPrivate::mediaAt);
    emit q->mediaChanged(qmlMediaList);
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

MediaQmlWrapper *ResourcePoolQmlWrapperPrivate::mediaAt(QQmlListProperty<MediaQmlWrapper> *property, int index)
{
    return static_cast<QList<MediaQmlWrapper *> *>(property->data)->at(index);
}

int ResourcePoolQmlWrapperPrivate::mediaCount(QQmlListProperty<MediaQmlWrapper> *property)
{
    return static_cast<QList<MediaQmlWrapper *> *>(property->data)->count();
}
