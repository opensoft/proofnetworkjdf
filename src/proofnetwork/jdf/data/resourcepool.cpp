#include "proofnetwork/jdf/data/resourcepool.h"

#include "proofnetwork/jdf/data/boxpackingparams.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/laminatingintent.h"
#include "proofnetwork/jdf/data/layout.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class ResourcePoolPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(ResourcePool)
    ResourcePoolPrivate()
    {
        registerChildren(components, cuttingParams, media, layouts, laminatingIntent, deliveryIntent, foldingParams,
                         boxPackingParams);
    }

    QVector<ComponentSP> components;
    CuttingParamsSP cuttingParams = CuttingParams::create();
    QVector<MediaSP> media;
    QVector<LayoutSP> layouts;
    LaminatingIntentSP laminatingIntent = LaminatingIntent::create();
    DeliveryIntentSP deliveryIntent = DeliveryIntent::create();
    FoldingParamsSP foldingParams = FoldingParams::create();
    BoxPackingParamsSP boxPackingParams = BoxPackingParams::create();
};

ObjectsCache<QString, ResourcePool> &cuttingProcessCache()
{
    return WeakObjectsCache<QString, ResourcePool>::instance();
}

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ResourcePool::ResourcePool() : NetworkDataEntity(*new ResourcePoolPrivate)
{}

QVector<ComponentSP> ResourcePool::components() const
{
    Q_D_CONST(ResourcePool);
    return d->components;
}

CuttingParamsSP ResourcePool::cuttingParams() const
{
    Q_D_CONST(ResourcePool);
    return d->cuttingParams;
}

QVector<MediaSP> ResourcePool::media() const
{
    Q_D_CONST(ResourcePool);
    return d->media;
}

LaminatingIntentSP ResourcePool::laminatingIntent() const
{
    Q_D_CONST(ResourcePool);
    return d->laminatingIntent;
}

DeliveryIntentSP ResourcePool::deliveryIntent() const
{
    Q_D_CONST(ResourcePool);
    return d->deliveryIntent;
}

FoldingParamsSP ResourcePool::foldingParams() const
{
    Q_D_CONST(ResourcePool);
    return d->foldingParams;
}

BoxPackingParamsSP ResourcePool::boxPackingParams() const
{
    Q_D_CONST(ResourcePool);
    return d->boxPackingParams;
}

QVector<LayoutSP> ResourcePool::layouts() const
{
    Q_D_CONST(ResourcePool);
    return d->layouts;
}

ResourcePoolQmlWrapper *ResourcePool::toQmlWrapper(QObject *parent) const
{
    ResourcePoolSP castedSelf = castedSelfPtr<ResourcePool>();
    Q_ASSERT(castedSelf);
    return new ResourcePoolQmlWrapper(castedSelf, parent);
}

ResourcePoolSP ResourcePool::create()
{
    ResourcePoolSP result(new ResourcePool());
    initSelfWeakPtr(result);
    return result;
}

ResourcePoolSP ResourcePool::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    ResourcePoolSP resourcePool = create();

    QVector<ComponentSP> componentsList;
    QVector<MediaSP> mediaList;
    QVector<LayoutSP> layoutsList;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "ResourcePool" && xmlReader.isStartElement() && !resourcePool->isFetched()) {
            resourcePool->setFetched(true);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Media") {
                MediaSP media = Media::fromJdf(xmlReader, jobId, sanitize);
                if (!media) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourcePool not created. Media is invalid.";
                    return ResourcePoolSP();
                }
                mediaList << media;
            } else if (xmlReader.name() == "Layout") {
                LayoutSP layout = Layout::fromJdf(xmlReader, jobId, sanitize);
                if (!layout) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourcePool not created. Layout is invalid.";
                    return ResourcePoolSP();
                }
                layoutsList << layout;
            } else if (xmlReader.name() == "LaminatingIntent") {
                LaminatingIntentSP laminatingIntent = LaminatingIntent::fromJdf(xmlReader);
                if (!laminatingIntent) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourcePool not created. LaminatingIntent is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setLaminatingIntent(laminatingIntent);
            } else if (xmlReader.name() == "DeliveryIntent") {
                DeliveryIntentSP deliveryIntent = DeliveryIntent::fromJdf(xmlReader, jobId, sanitize);
                if (!deliveryIntent) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourcePool not created. DeliveryIntent is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setDeliveryIntent(deliveryIntent);
            } else if (xmlReader.name() == "Component") {
                ComponentSP component = Component::fromJdf(xmlReader, jobId, sanitize);
                if (!component) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourcePool not created. Component is invalid.";
                    return ResourcePoolSP();
                }
                componentsList.append(component);
            } else if (xmlReader.name() == "CuttingParams") {
                CuttingParamsSP cuttingParams = CuttingParams::fromJdf(xmlReader, jobId, sanitize);
                if (!cuttingParams) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourcePool not created. CuttingParams is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setCuttingParams(cuttingParams);
            } else if (xmlReader.name() == "FoldingParams") {
                FoldingParamsSP foldingParams = FoldingParams::fromJdf(xmlReader);
                if (!foldingParams) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourcePool not created. FoldingParams is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setFoldingParams(foldingParams);
            } else if (xmlReader.name() == "BoxPackingParams") {
                BoxPackingParamsSP boxPackingParams = BoxPackingParams::fromJdf(xmlReader);
                if (!boxPackingParams) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourcePool not created. BoxPackingParams is invalid.";
                    return ResourcePoolSP();
                }
                resourcePool->setBoxPackingParams(boxPackingParams);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    resourcePool->setComponents(componentsList);
    resourcePool->setMedia(mediaList);
    resourcePool->setLayouts(layoutsList);

    return resourcePool;
}

void ResourcePool::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(ResourcePool);

    jdfWriter.writeStartElement(QStringLiteral("ResourcePool"));

    for (const ComponentSP &component : qAsConst(d->components)) {
        if (isValidAndDirty(component))
            component->toJdf(jdfWriter);
    }

    for (const MediaSP &media : qAsConst(d->media)) {
        if (isValidAndDirty(media))
            media->toJdf(jdfWriter);
    }

    for (const LayoutSP &layout : qAsConst(d->layouts)) {
        if (isValidAndDirty(layout))
            layout->toJdf(jdfWriter);
    }

    if (isValidAndDirty(d->laminatingIntent))
        d->laminatingIntent->toJdf(jdfWriter);

    if (isValidAndDirty(d->deliveryIntent))
        d->deliveryIntent->toJdf(jdfWriter);

    if (isValidAndDirty(d->cuttingParams))
        d->cuttingParams->toJdf(jdfWriter);

    if (isValidAndDirty(d->foldingParams))
        d->foldingParams->toJdf(jdfWriter);

    if (isValidAndDirty(d->boxPackingParams))
        d->boxPackingParams->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

void ResourcePool::setComponents(const QVector<ComponentSP> &arg)
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

void ResourcePool::setMedia(const QVector<MediaSP> &arg)
{
    Q_D(ResourcePool);
    bool emitNeeded = arg.count() != d->media.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->media[i]->id();
    if (emitNeeded) {
        d->media = arg;
        emit mediaChanged();
    }
}

void ResourcePool::addMedia(const MediaSP &arg)
{
    Q_D(ResourcePool);
    if (!arg)
        return;
    d->media << arg;
    emit mediaChanged();
}

void ResourcePool::setLaminatingIntent(const LaminatingIntentSP &laminatingIntent)
{
    Q_ASSERT(laminatingIntent);
    Q_D(ResourcePool);
    if (laminatingIntent == nullptr) {
        setLaminatingIntent(LaminatingIntent::create());
    } else if (d->laminatingIntent != laminatingIntent) {
        d->laminatingIntent = laminatingIntent;
        emit laminatingIntentChanged(d->laminatingIntent);
    }
}

void ResourcePool::setDeliveryIntent(const DeliveryIntentSP &arg)
{
    Q_ASSERT(arg);
    Q_D(ResourcePool);
    if (arg == nullptr) {
        setDeliveryIntent(DeliveryIntent::create());
    } else if (d->deliveryIntent != arg) {
        d->deliveryIntent = arg;
        emit deliveryIntentChanged(d->deliveryIntent);
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

void ResourcePool::setBoxPackingParams(const BoxPackingParamsSP &boxPackingParams)
{
    Q_ASSERT(boxPackingParams);
    Q_D(ResourcePool);
    if (boxPackingParams == nullptr) {
        setBoxPackingParams(BoxPackingParams::create());
    } else if (d->boxPackingParams != boxPackingParams) {
        d->boxPackingParams = boxPackingParams;
        emit boxPackingParamsChanged(d->boxPackingParams);
    }
}

void ResourcePool::setLayouts(const QVector<LayoutSP> &arg)
{
    Q_D(ResourcePool);
    bool emitNeeded = arg.count() != d->layouts.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->layouts[i]->id();
    if (emitNeeded) {
        d->layouts = arg;
        emit layoutsChanged();
    }
}

void ResourcePool::addLayout(const LayoutSP &arg)
{
    Q_D(ResourcePool);
    if (!arg)
        return;
    d->layouts << arg;
    emit layoutsChanged();
}

void ResourcePool::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    ResourcePoolSP castedOther = qSharedPointerCast<ResourcePool>(other);
    setComponents(castedOther->components());
    setCuttingParams(castedOther->cuttingParams());
    setMedia(castedOther->media());
    setLaminatingIntent(castedOther->laminatingIntent());
    setDeliveryIntent(castedOther->deliveryIntent());
    setFoldingParams(castedOther->foldingParams());
    setBoxPackingParams(castedOther->boxPackingParams());
    setLayouts(castedOther->layouts());

    NetworkDataEntity::updateSelf(other);
}
