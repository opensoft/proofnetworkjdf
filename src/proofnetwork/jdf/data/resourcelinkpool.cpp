/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "proofnetwork/jdf/data/resourcelinkpool.h"

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

    QVector<ComponentLinkSP> componentLinks;
    CuttingParamsLinkSP cuttingParamsLink = CuttingParamsLink::create();
    QVector<MediaLinkSP> mediaLinks;
    LaminatingIntentLinkSP laminatingIntentLink = LaminatingIntentLink::create();
    DeliveryIntentLinkSP deliveryIntentLink = DeliveryIntentLink::create();
    FoldingParamsLinkSP foldingParamsLink = FoldingParamsLink::create();
    BoxPackingParamsLinkSP boxPackingParamsLink = BoxPackingParamsLink::create();
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

QVector<ComponentLinkSP> ResourceLinkPool::componentLinks() const
{
    Q_D_CONST(ResourceLinkPool);
    return d->componentLinks;
}

CuttingParamsLinkSP ResourceLinkPool::cuttingParamsLink() const
{
    Q_D_CONST(ResourceLinkPool);
    return d->cuttingParamsLink;
}

QVector<MediaLinkSP> ResourceLinkPool::mediaLinks() const
{
    Q_D_CONST(ResourceLinkPool);
    return d->mediaLinks;
}

LaminatingIntentLinkSP ResourceLinkPool::laminatingIntentLink() const
{
    Q_D_CONST(ResourceLinkPool);
    return d->laminatingIntentLink;
}

DeliveryIntentLinkSP ResourceLinkPool::deliveryIntentLink() const
{
    Q_D_CONST(ResourceLinkPool);
    return d->deliveryIntentLink;
}

FoldingParamsLinkSP ResourceLinkPool::foldingParamsLink() const
{
    Q_D_CONST(ResourceLinkPool);
    return d->foldingParamsLink;
}

BoxPackingParamsLinkSP ResourceLinkPool::boxPackingParamsLink() const
{
    Q_D_CONST(ResourceLinkPool);
    return d->boxPackingParamsLink;
}

void ResourceLinkPool::setComponentLinks(const QVector<ComponentLinkSP> &componentLinks)
{
    Q_D(ResourceLinkPool);
    std::multiset<QString> newIds;
    for (const auto &componentLink : componentLinks)
        newIds.insert(componentLink->rRef());

    std::multiset<QString> oldIds;
    for (const auto &componentLink : qAsConst(d->componentLinks))
        oldIds.insert(componentLink->rRef());

    if (newIds != oldIds) {
        d->componentLinks = componentLinks;
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

void ResourceLinkPool::setMediaLinks(const QVector<MediaLinkSP> &mediaLinks)
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
    ResourceLinkPoolSP castedSelf = castedSelfPtr<ResourceLinkPool>();
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

    QVector<ComponentLinkSP> components;
    QVector<MediaLinkSP> mediaLinksList;
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

void ResourceLinkPool::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    ResourceLinkPoolSP castedOther = qSharedPointerCast<ResourceLinkPool>(other);
    setComponentLinks(castedOther->componentLinks());
    setCuttingParamsLink(castedOther->cuttingParamsLink());
    setLaminatingIntentLink(castedOther->laminatingIntentLink());
    setDeliveryIntentLink(castedOther->deliveryIntentLink());
    setMediaLinks(castedOther->mediaLinks());
    setFoldingParamsLink(castedOther->foldingParamsLink());
    setBoxPackingParamsLink(castedOther->boxPackingParamsLink());

    NetworkDataEntity::updateSelf(other);
}
