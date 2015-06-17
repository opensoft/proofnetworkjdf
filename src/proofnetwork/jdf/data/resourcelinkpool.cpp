#include "resourcelinkpool.h"
#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"
#include "proofnetwork/jdf/data/foldingparamslink.h"
#include "proofnetwork/jdf/data/laminatingintentlink.h"
#include "proofnetwork/jdf/data/medialink.h"


namespace Proof {
namespace Jdf {

class ResourceLinkPoolPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(ResourceLinkPool)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QList<ComponentLinkSP> componentLinks;
    CuttingParamsLinkSP cuttingParamsLink = CuttingParamsLink::defaultObject();
    MediaLinkSP mediaLink = MediaLink::defaultObject();
    LaminatingIntentLinkSP laminatingIntentLink = LaminatingIntentLink::defaultObject();
    FoldingParamsLinkSP foldingParamsLink = FoldingParamsLink::defaultObject();
};

}
}

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

MediaLinkSP ResourceLinkPool::mediaLink() const
{
    Q_D(const ResourceLinkPool);
    return d->mediaLink;
}

LaminatingIntentLinkSP ResourceLinkPool::laminatingIntentLink() const
{
    Q_D(const ResourceLinkPool);
    return d->laminatingIntentLink;
}

FoldingParamsLinkSP ResourceLinkPool::foldingParamsLink() const
{
    Q_D(const ResourceLinkPool);
    return d->foldingParamsLink;
}

void ResourceLinkPool::setComponentLinks(const QList<ComponentLinkSP> &componentLinks)
{
    Q_D(ResourceLinkPool);

    // TODO: check, that links changed
    d->componentLinks = componentLinks;
    emit componentLinksChanged();
}

void ResourceLinkPool::setCuttingParamsLink(const CuttingParamsLinkSP &cuttingParams)
{
    Q_D(ResourceLinkPool);
    if (d->cuttingParamsLink != cuttingParams) {
        d->cuttingParamsLink = cuttingParams;
        emit cuttingParamsLinkChanged(d->cuttingParamsLink);
    }
}

void ResourceLinkPool::setMediaLink(const MediaLinkSP &mediaLink)
{
    Q_D(ResourceLinkPool);
    if (d->mediaLink != mediaLink) {
        d->mediaLink = mediaLink;
        emit mediaLinkChanged(d->mediaLink);
    }
}

void ResourceLinkPool::setLaminatingIntentLink(const LaminatingIntentLinkSP &laminatingIntent)
{
    Q_D(ResourceLinkPool);
    if (d->laminatingIntentLink != laminatingIntent) {
        d->laminatingIntentLink = laminatingIntent;
        emit laminatingIntentLinkChanged(d->laminatingIntentLink);
    }
}

void ResourceLinkPool::setFoldingParamsLink(const FoldingParamsLinkSP &foldingParamsLink)
{
    Q_D(ResourceLinkPool);
    if (d->foldingParamsLink != foldingParamsLink) {
        d->foldingParamsLink = foldingParamsLink;
        emit foldingParamsLinkChanged(d->foldingParamsLink);
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
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

ResourceLinkPoolSP ResourceLinkPool::fromJdf(QXmlStreamReader &xmlReader)
{
    ResourceLinkPoolSP linkPool = create();

    QList<ComponentLinkSP> components;
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "ResourceLinkPool" && xmlReader.isStartElement() && !linkPool->isFetched()) {
            linkPool->setFetched(true);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "MediaLink") {
                MediaLinkSP media = MediaLink::fromJdf(xmlReader);
                if (!media) {
                    qCCritical(proofNetworkJdfDataLog) << "MediaLink not created.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setMediaLink(media);
            } else if (xmlReader.name() == "LaminatingIntentLink") {
                LaminatingIntentLinkSP laminatingIntent = LaminatingIntentLink::fromJdf(xmlReader);
                if (!laminatingIntent) {
                    qCCritical(proofNetworkJdfDataLog) << "LaminatingIntentLink not created.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setLaminatingIntentLink(laminatingIntent);
            } else if (xmlReader.name() == "ComponentLink") {
                ComponentLinkSP component = ComponentLink::fromJdf(xmlReader);
                if (!component) {
                    qCCritical(proofNetworkJdfDataLog) << "ComponentLink not created.";
                    return ResourceLinkPoolSP();
                }
                components.append(component);
            } else if (xmlReader.name() == "CuttingParamsLink") {
                CuttingParamsLinkSP cuttingParams = CuttingParamsLink::fromJdf(xmlReader);
                if (!cuttingParams) {
                    qCCritical(proofNetworkJdfDataLog) << "CuttingParamsLink not created.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setCuttingParamsLink(cuttingParams);
            } else if (xmlReader.name() == "FoldingParamsLink") {
                FoldingParamsLinkSP foldingParams = FoldingParamsLink::fromJdf(xmlReader);
                if (!foldingParams) {
                    qCCritical(proofNetworkJdfDataLog) << "FoldingParamsLink not created.";
                    return ResourceLinkPoolSP();
                }
                linkPool->setFoldingParamsLink(foldingParams);
            };
        } else if (xmlReader.name() == "ResourceLinkPool" && xmlReader.isEndElement() && linkPool->isFetched()) {
            break;
        }
        xmlReader.readNext();
    }
    linkPool->setComponentLinks(components);

    return linkPool;
}

void ResourceLinkPool::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(ResourceLinkPool);

    jdfWriter.writeStartElement("ResourceLinkPool");

    for (const ComponentLinkSP &component : d->componentLinks) {
        if (component)
            component->toJdf(jdfWriter);
    }
    if (d->mediaLink != MediaLink::defaultObject())
        d->mediaLink->toJdf(jdfWriter);
    if (d->laminatingIntentLink != LaminatingIntentLink::defaultObject())
        d->laminatingIntentLink->toJdf(jdfWriter);
    if (d->cuttingParamsLink != CuttingParamsLink::defaultObject())
        d->cuttingParamsLink->toJdf(jdfWriter);
    if (d->foldingParamsLink != FoldingParamsLink::defaultObject())
        d->foldingParamsLink->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

ResourceLinkPoolSP ResourceLinkPool::defaultObject()
{
    static ResourceLinkPoolSP entity = create();
    return entity;
}

ResourceLinkPool::ResourceLinkPool() :
    NetworkDataEntity(*new ResourceLinkPoolPrivate)
{
}


void ResourceLinkPoolPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(ResourceLinkPool);
    ResourceLinkPoolSP castedOther = qSharedPointerCast<ResourceLinkPool>(other);
    q->setComponentLinks(castedOther->componentLinks());
    q->setCuttingParamsLink(castedOther->cuttingParamsLink());
    q->setLaminatingIntentLink(castedOther->laminatingIntentLink());
    q->setMediaLink(castedOther->mediaLink());
    q->setFoldingParamsLink(castedOther->foldingParamsLink());

    NetworkDataEntityPrivate::updateFrom(other);

}
