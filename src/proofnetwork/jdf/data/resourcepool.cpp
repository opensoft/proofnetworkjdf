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
        registerChilds(components, cuttingParams, media, laminatingIntent, foldingParams);
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
    makeWeakSelf(result);
    return result;
}

ResourcePoolSP ResourcePool::fromJdf(QXmlStreamReader &xmlReader, const QString &jdfId)
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
                    qCCritical(proofNetworkJdfDataLog) << "Media not created.";
                    return ResourcePoolSP();
                }
                resourcePool->setMedia(media);
            } else if (xmlReader.name() == "LaminatingIntent") {
                LaminatingIntentSP laminatingIntent = LaminatingIntent::fromJdf(xmlReader);
                if (!laminatingIntent) {
                    qCCritical(proofNetworkJdfDataLog) << "LaminatingIntent not created.";
                    return ResourcePoolSP();
                }
                resourcePool->setLaminatingIntent(laminatingIntent);
            } else if (xmlReader.name() == "Component") {
                ComponentSP component = Component::fromJdf(xmlReader, jdfId);
                if (!component) {
                    qCCritical(proofNetworkJdfDataLog) << "Component not created.";
                    return ResourcePoolSP();
                }
                components.append(component);
            } else if (xmlReader.name() == "CuttingParams") {
                CuttingParamsSP cuttingParams = CuttingParams::fromJdf(xmlReader, jdfId);
                if (!cuttingParams) {
                    qCCritical(proofNetworkJdfDataLog) << "CuttingParams not created.";
                    return ResourcePoolSP();
                }
                resourcePool->setCuttingParams(cuttingParams);
            } else if (xmlReader.name() == "FoldingParams") {
                FoldingParamsSP foldingParams = FoldingParams::fromJdf(xmlReader);
                if (!foldingParams) {
                    qCCritical(proofNetworkJdfDataLog) << "FoldingParams not created.";
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
        if (component->isDirty())
            component->toJdf(jdfWriter);
    }
    if (d->media->isDirty())
        d->media->toJdf(jdfWriter);
    if (d->laminatingIntent->isDirty())
        d->laminatingIntent->toJdf(jdfWriter);
    if (d->cuttingParams->isDirty())
        d->cuttingParams->toJdf(jdfWriter);
    if (d->foldingParams->isDirty())
        d->foldingParams->toJdf(jdfWriter);

    if (isValidAndNotDefault(d->laminatingIntent))
        d->laminatingIntent->toJdf(jdfWriter);

    if (isValidAndNotDefault(d->cuttingParams))
        d->cuttingParams->toJdf(jdfWriter);

    for (const ComponentSP &component : d->components) {
        if (component->isDirty())
            component->toJdfLink(jdfWriter);
    }
    if (d->media->isDirty())
        d->media->toJdfLink(jdfWriter);
    if (d->laminatingIntent->isDirty())
        d->laminatingIntent->toJdfLink(jdfWriter);
    if (d->cuttingParams->isDirty())
        d->cuttingParams->toJdfLink(jdfWriter);
    if (d->foldingParams->isDirty())
        d->foldingParams->toJdfLink(jdfWriter);

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

void ResourcePool::setCuttingParams(const CuttingParamsSP &arg)
{
    Q_D(ResourcePool);
    if (arg == nullptr) {
        setCuttingParams(CuttingParams::create());
    } else if (d->cuttingParams != arg) {
        d->cuttingParams = arg;
        emit cuttingParamsChanged(d->cuttingParams);
    }
}

void ResourcePool::setMedia(const MediaSP &media)
{
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
