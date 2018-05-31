#include "resourcelinkpool.h"

#include "proofnetwork/jdf/data/boxpackingparamslink.h"
#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"
#include "proofnetwork/jdf/data/deliveryintentlink.h"
#include "proofnetwork/jdf/data/foldingparamslink.h"
#include "proofnetwork/jdf/data/laminatingintentlink.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/networkdataentity_p.h"

#include <set>

namespace Proof {
namespace Jdf {

class ResourceLinkPoolPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(ResourceLinkPool)

    ResourceLinkPoolPrivate()
    {
        registerChildren(componentLinks, cuttingParamsLink, mediaLinks, laminatingIntentLink, deliveryIntentLink,
                         foldingParamsLink, boxPackingParamsLink);
    }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QList<ComponentLinkSP> componentLinks;
    CuttingParamsLinkSP cuttingParamsLink = CuttingParamsLink::create();
    QList<MediaLinkSP> mediaLinks;
    LaminatingIntentLinkSP laminatingIntentLink = LaminatingIntentLink::create();
    DeliveryIntentLinkSP deliveryIntentLink = DeliveryIntentLink::create();
    FoldingParamsLinkSP foldingParamsLink = FoldingParamsLink::create();
    BoxPackingParamsLinkSP boxPackingParamsLink = BoxPackingParamsLink::create();
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

QList<ComponentLinkSP> ResourceLinkPool::componentLinks() const
{
    Q_D(const ResourceLinkPool);
    return d->componentLinks;
}

CuttingParamsLinkSP ResourceLinkPool::cuttingParamsLink() const
{
    Q_D(const ResourceLinkPool);
    return d->cuttingParamsLink;
}

QList<MediaLinkSP> ResourceLinkPool::mediaLinks() const
{
    Q_D(const ResourceLinkPool);
    return d->mediaLinks;
}

LaminatingIntentLinkSP ResourceLinkPool::laminatingIntentLink() const
{
    Q_D(const ResourceLinkPool);
    return d->laminatingIntentLink;
}

DeliveryIntentLinkSP ResourceLinkPool::deliveryIntentLink() const
{
    Q_D(const ResourceLinkPool);
    return d->deliveryIntentLink;
}

FoldingParamsLinkSP ResourceLinkPool::foldingParamsLink() const
{
    Q_D(const ResourceLinkPool);
    return d->foldingParamsLink;
}

BoxPackingParamsLinkSP ResourceLinkPool::boxPackingParamsLink() const
{
    Q_D(const ResourceLinkPool);
    return d->boxPackingParamsLink;
}

void ResourceLinkPool::setComponentLinks(const QList<ComponentLinkSP> &arg)
{
    Q_D(ResourceLinkPool);
    std::multiset<QString> newIds;
    for (const auto &componentLink : arg)
        newIds.insert(componentLink->rRef());

    std::multiset<QString> oldIds;
    for (const auto &componentLink : d->componentLinks)
        oldIds.insert(componentLink->rRef());

    if (newIds != oldIds) {
        d->componentLinks = arg;
        emit componentLinksChanged();
    }
}

void ResourceLinkPool::addComponentLink(const ComponentLinkSP &componentLink)
{
    Q_D(ResourceLinkPool);
    if (!componentLink)
        return;

    d->componentLinks << componentLink;
    emit componentLinksChanged();
}

void ResourceLinkPool::setCuttingParamsLink(const CuttingParamsLinkSP &cuttingParams)
{
    Q_ASSERT(cuttingParams);
    Q_D(ResourceLinkPool);
    if (d->cuttingParamsLink != cuttingParams) {
        d->cuttingParamsLink = cuttingParams;
        emit cuttingParamsLinkChanged(d->cuttingParamsLink);
    }
}

void ResourceLinkPool::setMediaLinks(const QList<MediaLinkSP> &mediaLinks)
{
    Q_D(ResourceLinkPool);
    d->mediaLinks = mediaLinks;
    emit mediaLinksChanged();
}

void ResourceLinkPool::addMediaLink(const MediaLinkSP &mediaLink)
{
    Q_ASSERT(mediaLink);
    Q_D(ResourceLinkPool);
    d->mediaLinks << mediaLink;
    emit mediaLinksChanged();
}

void ResourceLinkPool::setLaminatingIntentLink(const LaminatingIntentLinkSP &laminatingIntent)
{
    Q_ASSERT(laminatingIntent);
    Q_D(ResourceLinkPool);
    if (d->laminatingIntentLink != laminatingIntent) {
        d->laminatingIntentLink = laminatingIntent;
        emit laminatingIntentLinkChanged(d->laminatingIntentLink);
    }
}

void ResourceLinkPool::setDeliveryIntentLink(const DeliveryIntentLinkSP &deliveryIntent)
{
    Q_ASSERT(deliveryIntent);
    Q_D(ResourceLinkPool);
    if (d->deliveryIntentLink != deliveryIntent) {
        d->deliveryIntentLink = deliveryIntent;
        emit deliveryIntentLinkChanged(d->deliveryIntentLink);
    }
}

void ResourceLinkPool::setFoldingParamsLink(const FoldingParamsLinkSP &foldingParamsLink)
{
    Q_ASSERT(foldingParamsLink);
    Q_D(ResourceLinkPool);
    if (d->foldingParamsLink != foldingParamsLink) {
        d->foldingParamsLink = foldingParamsLink;
        emit foldingParamsLinkChanged(d->foldingParamsLink);
    }
}

void ResourceLinkPool::setBoxPackingParamsLink(const BoxPackingParamsLinkSP &boxPackingParamsLink)
{
    Q_ASSERT(boxPackingParamsLink);
    Q_D(ResourceLinkPool);
    if (d->boxPackingParamsLink != boxPackingParamsLink) {
        d->boxPackingParamsLink = boxPackingParamsLink;
        emit boxPackingParamsLinkChanged(d->boxPackingParamsLink);
    }
}

ResourceLinkPoolQmlWrapper *ResourceLinkPool::toQmlWrapper(QObject *parent) const
{
    Q_D(const ResourceLinkPool);
    ResourceLinkPoolSP castedSelf = qSharedPointerCast<ResourceLinkPool>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new ResourceLinkPoolQmlWrapper(castedSelf, parent);
}

ResourceLinkPoolSP ResourceLinkPool::create()
{
    ResourceLinkPoolSP result(new ResourceLinkPool());
    initSelfWeakPtr(result);
    return result;
}

ResourceLinkPoolSP ResourceLinkPool::fromJdf(QXmlStreamReader &xmlReader)
{
    ResourceLinkPoolSP linkPool = create();

    QList<ComponentLinkSP> components;
    QList<MediaLinkSP> mediaLinksList;
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "ResourceLinkPool" && xmlReader.isStartElement() && !linkPool->isFetched()) {
            linkPool->setFetched(true);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "MediaLink") {
                MediaLinkSP media = MediaLink::fromJdf(xmlReader);
                if (!media) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourceLinkPool not created. MediaLink is invalid.";
                    return ResourceLinkPoolSP();
                }
                mediaLinksList << media;
            } else if (xmlReader.name() == "LaminatingIntentLink") {
                LaminatingIntentLinkSP laminatingIntent = LaminatingIntentLink::fromJdf(xmlReader);
                if (!laminatingIntent) {
                    qCWarning(proofNetworkJdfDataLog)
                        << "ResourceLinkPool not created. LaminatingIntentLink is invalid.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setLaminatingIntentLink(laminatingIntent);
            } else if (xmlReader.name() == "DeliveryIntentLink") {
                DeliveryIntentLinkSP deliveryIntent = DeliveryIntentLink::fromJdf(xmlReader);
                if (!deliveryIntent) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourceLinkPool not created. DeliveryIntentLink is invalid.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setDeliveryIntentLink(deliveryIntent);
            } else if (xmlReader.name() == "ComponentLink") {
                ComponentLinkSP component = ComponentLink::fromJdf(xmlReader);
                if (!component) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourceLinkPool not created. ComponentLink is invalid.";
                    return ResourceLinkPoolSP();
                }
                components.append(component);
            } else if (xmlReader.name() == "CuttingParamsLink") {
                CuttingParamsLinkSP cuttingParams = CuttingParamsLink::fromJdf(xmlReader);
                if (!cuttingParams) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourceLinkPool not created. CuttingParamsLink is invalid.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setCuttingParamsLink(cuttingParams);
            } else if (xmlReader.name() == "FoldingParamsLink") {
                FoldingParamsLinkSP foldingParams = FoldingParamsLink::fromJdf(xmlReader);
                if (!foldingParams) {
                    qCWarning(proofNetworkJdfDataLog) << "ResourceLinkPool not created. FoldingParamsLink is invalid.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setFoldingParamsLink(foldingParams);
            } else if (xmlReader.name() == "BoxPackingParamsLink") {
                BoxPackingParamsLinkSP boxPackingParamsLink = BoxPackingParamsLink::fromJdf(xmlReader);
                if (!boxPackingParamsLink) {
                    qCWarning(proofNetworkJdfDataLog)
                        << "ResourceLinkPool not created. BoxPackingParamsLink is invalid.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setBoxPackingParamsLink(boxPackingParamsLink);
            };
        } else if (xmlReader.name() == "ResourceLinkPool" && xmlReader.isEndElement() && linkPool->isFetched()) {
            break;
        }
        xmlReader.readNext();
    }
    linkPool->setComponentLinks(components);
    linkPool->setMediaLinks(mediaLinksList);

    return linkPool;
}

void ResourceLinkPool::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(ResourceLinkPool);

    jdfWriter.writeStartElement(QStringLiteral("ResourceLinkPool"));

    for (const ComponentLinkSP &component : qAsConst(d->componentLinks)) {
        if (component)
            component->toJdf(jdfWriter);
    }
    for (const auto &media : qAsConst(d->mediaLinks)) {
        if (media)
            media->toJdf(jdfWriter);
    }
    if (d->laminatingIntentLink->isDirty())
        d->laminatingIntentLink->toJdf(jdfWriter);
    if (d->deliveryIntentLink->isDirty())
        d->deliveryIntentLink->toJdf(jdfWriter);
    if (d->cuttingParamsLink->isDirty())
        d->cuttingParamsLink->toJdf(jdfWriter);
    if (d->foldingParamsLink->isDirty())
        d->foldingParamsLink->toJdf(jdfWriter);
    if (d->boxPackingParamsLink->isDirty())
        d->boxPackingParamsLink->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

ResourceLinkPool::ResourceLinkPool() : NetworkDataEntity(*new ResourceLinkPoolPrivate)
{}

void ResourceLinkPoolPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(ResourceLinkPool);
    ResourceLinkPoolSP castedOther = qSharedPointerCast<ResourceLinkPool>(other);
    q->setComponentLinks(castedOther->componentLinks());
    q->setCuttingParamsLink(castedOther->cuttingParamsLink());
    q->setLaminatingIntentLink(castedOther->laminatingIntentLink());
    q->setDeliveryIntentLink(castedOther->deliveryIntentLink());
    q->setMediaLinks(castedOther->mediaLinks());
    q->setFoldingParamsLink(castedOther->foldingParamsLink());
    q->setBoxPackingParamsLink(castedOther->boxPackingParamsLink());

    NetworkDataEntityPrivate::updateFrom(other);
}
