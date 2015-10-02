#include "resourcepool.h"

#include "component.h"
#include "cuttingparams.h"
#include "media.h"
#include "laminatingintent.h"
#include "cutblock.h"
#include "foldingparams.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class ResourcePoolPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(ResourcePool)

    ResourcePoolPrivate()
    {
        registerChildren(components, cuttingParams, media, laminatingIntent, foldingParams);
    }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QList<ComponentSP> components;
    CuttingParamsSP cuttingParams = CuttingParams::create();
    MediaSP media = Media::create();
    LaminatingIntentSP laminatingIntent = LaminatingIntent::create();
    FoldingParamsSP foldingParams = FoldingParams::create();
};

ObjectsCache<QString, ResourcePool> &cuttingProcessCache()
{
    return WeakObjectsCache<QString, ResourcePool>::instance();
}

}
}

using namespace Proof::Jdf;

ResourcePool::ResourcePool()
    : NetworkDataEntity(*new ResourcePoolPrivate)
{
}

QList<ComponentSP> ResourcePool::components() const
{
    Q_D(const ResourcePool);
    return d->components;
}

CuttingParamsSP ResourcePool::cuttingParams() const
{
    Q_D(const ResourcePool);
    return d->cuttingParams;
}

MediaSP ResourcePool::media() const
{
    Q_D(const ResourcePool);
    return d->media;
}

LaminatingIntentSP ResourcePool::laminatingIntent() const
{
    Q_D(const ResourcePool);
    return d->laminatingIntent;
}

FoldingParamsSP ResourcePool::foldingParams() const
{
    Q_D(const ResourcePool);
    return d->foldingParams;
}

ResourcePoolQmlWrapper *ResourcePool::toQmlWrapper(QObject *parent) const
{
    Q_D(const ResourcePool);
    ResourcePoolSP castedSelf = qSharedPointerCast<ResourcePool>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new ResourcePoolQmlWrapper(castedSelf, parent);
}

ResourcePoolSP ResourcePool::create()
{
    ResourcePoolSP result(new ResourcePool());
    initSelfWeakPtr(result);
    return result;
}

ResourcePoolSP ResourcePool::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId)
{
    ResourcePoolSP resourcePool = create();

    QList<ComponentSP> components;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "ResourcePool" && xmlReader.isStartElement() && !resourcePool->isFetched()) {
            resourcePool->setFetched(true);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Media") {
                MediaSP media = Media::fromJdf(xmlReader);
                if (!media) {
                    qCCritical(proofNetworkJdfDataLog) << "ResourcePool not created. Media is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setMedia(media);
            } else if (xmlReader.name() == "LaminatingIntent") {
                LaminatingIntentSP laminatingIntent = LaminatingIntent::fromJdf(xmlReader);
                if (!laminatingIntent) {
                    qCCritical(proofNetworkJdfDataLog) << "ResourcePool not created. LaminatingIntent is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setLaminatingIntent(laminatingIntent);
            } else if (xmlReader.name() == "Component") {
                ComponentSP component = Component::fromJdf(xmlReader, jobId);
                if (!component) {
                    qCCritical(proofNetworkJdfDataLog) << "ResourcePool not created. Component is invalid.";
                    return ResourcePoolSP();
                }
                components.append(component);
            } else if (xmlReader.name() == "CuttingParams") {
                CuttingParamsSP cuttingParams = CuttingParams::fromJdf(xmlReader, jobId);
                if (!cuttingParams) {
                    qCCritical(proofNetworkJdfDataLog) << "ResourcePool not created. CuttingParams is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setCuttingParams(cuttingParams);
            } else if (xmlReader.name() == "FoldingParams") {
                FoldingParamsSP foldingParams = FoldingParams::fromJdf(xmlReader);
                if (!foldingParams) {
                    qCCritical(proofNetworkJdfDataLog) << "ResourcePool not created. FoldingParams is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setFoldingParams(foldingParams);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    resourcePool->setComponents(components);

    return resourcePool;
}

void ResourcePool::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(ResourcePool);

    jdfWriter.writeStartElement("ResourcePool");

    for (const ComponentSP &component : d->components) {
        if (isValidAndDirty(component))
            component->toJdf(jdfWriter);
    }
    if (isValidAndDirty(d->media))
        d->media->toJdf(jdfWriter);

    if (isValidAndDirty(d->laminatingIntent))
        d->laminatingIntent->toJdf(jdfWriter);

    if (isValidAndDirty(d->cuttingParams))
        d->cuttingParams->toJdf(jdfWriter);

    if (isValidAndDirty(d->foldingParams))
        d->foldingParams->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

void ResourcePool::setComponents(const QList<ComponentSP> &arg)
{
    Q_D(ResourcePool);
    bool emitNeeded = arg.count() != d->components.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->components[i]->id();
    if (emitNeeded) {
        d->components = arg;
        emit componentsChanged();
    }
}

void ResourcePool::addComponent(const ComponentSP &arg)
{
    Q_D(ResourcePool);
    if (!arg)
        return;
    d->components << arg;
    emit componentsChanged();
}

void ResourcePool::setCuttingParams(const CuttingParamsSP &arg)
{
    Q_ASSERT(arg);
    Q_D(ResourcePool);
    if (d->cuttingParams != arg) {
        d->cuttingParams = arg;
        emit cuttingParamsChanged(d->cuttingParams);
    }
}

void ResourcePool::setMedia(const MediaSP &media)
{
    Q_ASSERT(media);
    Q_D(ResourcePool);
    if (media == nullptr)
        setMedia(Media::create());
    else if (d->media != media) {
        d->media = media;
        emit mediaChanged(d->media);
    }
}

void ResourcePool::setLaminatingIntent(const LaminatingIntentSP &laminatingIntent)
{
    Q_ASSERT(laminatingIntent);
    Q_D(ResourcePool);
    if (laminatingIntent == nullptr)
        setLaminatingIntent(LaminatingIntent::create());
    else if (d->laminatingIntent != laminatingIntent) {
        d->laminatingIntent = laminatingIntent;
        emit laminatingIntentChanged(d->laminatingIntent);
    }
}

void ResourcePool::setFoldingParams(const FoldingParamsSP &foldingParams)
{
    Q_ASSERT(foldingParams);
    Q_D(ResourcePool);
    if (foldingParams == nullptr) {
        setFoldingParams(FoldingParams::create());
    } else if (d->foldingParams != foldingParams) {
        d->foldingParams = foldingParams;
        emit foldingParamsChanged(d->foldingParams);
    }
}

void ResourcePoolPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(ResourcePool);
    ResourcePoolSP castedOther = qSharedPointerCast<ResourcePool>(other);
    q->setComponents(castedOther->components());
    q->setCuttingParams(castedOther->cuttingParams());
    q->setMedia(castedOther->media());
    q->setFoldingParams(castedOther->foldingParams());

    NetworkDataEntityPrivate::updateFrom(other);
}
