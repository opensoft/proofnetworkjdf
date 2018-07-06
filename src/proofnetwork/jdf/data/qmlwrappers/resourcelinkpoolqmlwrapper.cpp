#include "resourcelinkpoolqmlwrapper.h"

#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"
#include "proofnetwork/jdf/data/foldingparamslink.h"
#include "proofnetwork/jdf/data/laminatingintentlink.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/qmlwrappers/componentlinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingparamslinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/foldingparamslinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentlinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/medialinkqmlwrapper.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class ResourceLinkPoolQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ResourceLinkPoolQmlWrapper)

    void updateComponentLinks();
    void updateCuttingParamsLink();
    void updateMediaLinks();
    void updateFoldingParamsLink();
    void updateLaminatingParamsLink();

    QVector<ComponentLinkQmlWrapper *> componentLinks;
    QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper> qmlComponentLinks;
    static ComponentLinkQmlWrapper *componentAt(QQmlListProperty<ComponentLinkQmlWrapper> *property, int index);
    static int componentsCount(QQmlListProperty<ComponentLinkQmlWrapper> *property);

    QVector<MediaLinkQmlWrapper *> mediaLinks;
    QQmlListProperty<Proof::Jdf::MediaLinkQmlWrapper> qmlMediaLinks;
    static MediaLinkQmlWrapper *mediaLinkAt(QQmlListProperty<MediaLinkQmlWrapper> *property, int index);
    static int mediaLinksCount(QQmlListProperty<MediaLinkQmlWrapper> *property);

    CuttingParamsLinkQmlWrapper *cuttingParamsLink = nullptr;
    FoldingParamsLinkQmlWrapper *foldingParamsLink = nullptr;
    LaminatingIntentLinkQmlWrapper *laminatingIntentLink = nullptr;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ResourceLinkPoolQmlWrapper::ResourceLinkPoolQmlWrapper(const ResourceLinkPoolSP &pool, QObject *parent)
    : NetworkDataEntityQmlWrapper(pool, *new ResourceLinkPoolQmlWrapperPrivate, parent)
{
    setupEntity();
}

ResourceLinkPoolQmlWrapper::~ResourceLinkPoolQmlWrapper()
{}

QQmlListProperty<ComponentLinkQmlWrapper> ResourceLinkPoolQmlWrapper::componentLinks() const
{
    Q_D_CONST(ResourceLinkPoolQmlWrapper);
    return d->qmlComponentLinks;
}

CuttingParamsLinkQmlWrapper *ResourceLinkPoolQmlWrapper::cuttingParamsLink() const
{
    Q_D_CONST(ResourceLinkPoolQmlWrapper);
    return d->cuttingParamsLink;
}

QQmlListProperty<MediaLinkQmlWrapper> ResourceLinkPoolQmlWrapper::mediaLinks() const
{
    Q_D_CONST(ResourceLinkPoolQmlWrapper);
    return d->qmlMediaLinks;
}

FoldingParamsLinkQmlWrapper *ResourceLinkPoolQmlWrapper::foldingParamsLink() const
{
    Q_D_CONST(ResourceLinkPoolQmlWrapper);
    return d->foldingParamsLink;
}

LaminatingIntentLinkQmlWrapper *ResourceLinkPoolQmlWrapper::laminatingIntentLink() const
{
    Q_D_CONST(ResourceLinkPoolQmlWrapper);
    return d->laminatingIntentLink;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(ResourceLinkPool)

void ResourceLinkPoolQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    Q_D(ResourceLinkPoolQmlWrapper);
    Q_UNUSED(old)
    ResourceLinkPoolSP linkPool = entity<ResourceLinkPool>();
    Q_ASSERT(linkPool);

    connect(linkPool.data(), &ResourceLinkPool::componentLinksChanged, entityConnectContext(),
            [d]() { d->updateComponentLinks(); });
    connect(linkPool.data(), &ResourceLinkPool::cuttingParamsLinkChanged, entityConnectContext(),
            [d]() { d->updateCuttingParamsLink(); });
    connect(linkPool.data(), &ResourceLinkPool::mediaLinksChanged, entityConnectContext(),
            [d]() { d->updateMediaLinks(); });
    connect(linkPool.data(), &ResourceLinkPool::foldingParamsLinkChanged, entityConnectContext(),
            [d]() { d->updateFoldingParamsLink(); });
    connect(linkPool.data(), &ResourceLinkPool::laminatingIntentLinkChanged, entityConnectContext(),
            [d]() { d->updateLaminatingParamsLink(); });

    d->updateComponentLinks();
    d->updateCuttingParamsLink();
    d->updateLaminatingParamsLink();
    d->updateMediaLinks();
    d->updateFoldingParamsLink();
}

void ResourceLinkPoolQmlWrapperPrivate::updateComponentLinks()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = q->entity<ResourceLinkPool>();
    for (ComponentLinkQmlWrapper *wrapper : qAsConst(componentLinks))
        wrapper->deleteLater();

    componentLinks.clear();
    const auto ndeComponentLinks = linkPool->componentLinks();
    for (const ComponentLinkSP &component : ndeComponentLinks)
        componentLinks << component->toQmlWrapper(q);

    qmlComponentLinks =
        QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper>(q, &componentLinks,
                                                              &ResourceLinkPoolQmlWrapperPrivate::componentsCount,
                                                              &ResourceLinkPoolQmlWrapperPrivate::componentAt);
    emit q->componentLinksChanged(qmlComponentLinks);
}

void ResourceLinkPoolQmlWrapperPrivate::updateCuttingParamsLink()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = q->entity<ResourceLinkPool>();
    if (cuttingParamsLink == nullptr)
        cuttingParamsLink = linkPool->cuttingParamsLink()->toQmlWrapper(q);
    else
        cuttingParamsLink->setEntity(linkPool->cuttingParamsLink());

    emit q->cuttingParamsLinkChanged(cuttingParamsLink);
}

void ResourceLinkPoolQmlWrapperPrivate::updateMediaLinks()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = q->entity<ResourceLinkPool>();
    for (MediaLinkQmlWrapper *wrapper : qAsConst(mediaLinks))
        wrapper->deleteLater();

    mediaLinks.clear();
    const auto ndeMediaLinks = linkPool->mediaLinks();
    for (const auto &media : ndeMediaLinks)
        mediaLinks << media->toQmlWrapper(q);

    qmlMediaLinks = QQmlListProperty<Proof::Jdf::MediaLinkQmlWrapper>(q, &mediaLinks,
                                                                      &ResourceLinkPoolQmlWrapperPrivate::mediaLinksCount,
                                                                      &ResourceLinkPoolQmlWrapperPrivate::mediaLinkAt);
    emit q->mediaLinksChanged(qmlMediaLinks);
}

void ResourceLinkPoolQmlWrapperPrivate::updateFoldingParamsLink()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = q->entity<ResourceLinkPool>();
    if (foldingParamsLink == nullptr)
        foldingParamsLink = linkPool->foldingParamsLink()->toQmlWrapper(q);
    else
        foldingParamsLink->setEntity(linkPool->foldingParamsLink());

    emit q->foldingParamsLinkChanged(foldingParamsLink);
}

void ResourceLinkPoolQmlWrapperPrivate::updateLaminatingParamsLink()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = q->entity<ResourceLinkPool>();
    if (laminatingIntentLink == nullptr)
        laminatingIntentLink = linkPool->laminatingIntentLink()->toQmlWrapper(q);
    else
        laminatingIntentLink->setEntity(linkPool->laminatingIntentLink());

    emit q->laminatingIntentLinkChanged(laminatingIntentLink);
}

ComponentLinkQmlWrapper *
ResourceLinkPoolQmlWrapperPrivate::componentAt(QQmlListProperty<ComponentLinkQmlWrapper> *property, int index)
{
    return static_cast<QVector<ComponentLinkQmlWrapper *> *>(property->data)->at(index);
}

int ResourceLinkPoolQmlWrapperPrivate::componentsCount(QQmlListProperty<ComponentLinkQmlWrapper> *property)
{
    return static_cast<QVector<ComponentLinkQmlWrapper *> *>(property->data)->count();
}

MediaLinkQmlWrapper *ResourceLinkPoolQmlWrapperPrivate::mediaLinkAt(QQmlListProperty<MediaLinkQmlWrapper> *property,
                                                                    int index)
{
    return static_cast<QVector<MediaLinkQmlWrapper *> *>(property->data)->at(index);
}

int ResourceLinkPoolQmlWrapperPrivate::mediaLinksCount(QQmlListProperty<MediaLinkQmlWrapper> *property)
{
    return static_cast<QVector<MediaLinkQmlWrapper *> *>(property->data)->count();
}
