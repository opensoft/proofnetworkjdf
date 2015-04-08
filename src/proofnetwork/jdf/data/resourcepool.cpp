#include "resourcepool.h"

#include "component.h"
#include "cuttingparams.h"
#include "media.h"
#include "cutblock.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class ResourcePoolPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(ResourcePool)

    QList<ComponentSP> components;
    CuttingParamsSP cuttingParams = CuttingParams::defaultObject();
    MediaSP media = Media::defaultObject();

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

void ResourcePool::updateFrom(const NetworkDataEntitySP &other)
{
    ResourcePoolSP castedOther = qSharedPointerCast<ResourcePool>(other);
    setComponents(castedOther->components());
    setCuttingParams(castedOther->cuttingParams());
    setMedia(castedOther->media());

    NetworkDataEntity::updateFrom(other);
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
    result->d_func()->weakSelf = result.toWeakRef();
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

    for (const ComponentSP &component : d->components)
        component->toJdf(jdfWriter);
    if (d->media)
        d->media->toJdf(jdfWriter);
    if (d->cuttingParams)
        d->cuttingParams->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

void ResourcePool::toJdfLink(QXmlStreamWriter &jdfWriter)
{
    Q_D(ResourcePool);

    jdfWriter.writeStartElement("ResourceLinkPool");

    for (const ComponentSP &component : d->components)
        component->toJdfLink(jdfWriter);
    if (d->media)
        d->media->toJdfLink(jdfWriter);
    if (d->cuttingParams)
        d->cuttingParams->toJdfLink(jdfWriter);

    jdfWriter.writeEndElement();
}

ResourcePoolSP ResourcePool::defaultObject()
{
    static ResourcePoolSP entity = create();
    return entity;
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
    if (d->cuttingParams != arg) {
        d->cuttingParams = arg;
        emit cuttingParamsChanged(d->cuttingParams);
    }
}

void ResourcePool::setMedia(const MediaSP &media)
{
    Q_D(ResourcePool);
    if (media == nullptr)
        setMedia(Media::defaultObject());
    else if (d->media != media) {
        d->media = media;
        emit mediaChanged(d->media);
    }
}
