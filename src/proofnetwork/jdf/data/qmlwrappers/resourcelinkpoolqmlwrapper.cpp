#include "resourcelinkpoolqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/componentlinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingparamslinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/foldingparamslinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentlinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/medialinkqmlwrapper.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"
#include "proofnetwork/jdf/data/foldingparamslink.h"
#include "proofnetwork/jdf/data/laminatingintentlink.h"
#include "proofnetwork/jdf/data/medialink.h"

namespace Proof {
namespace Jdf {

class ResourceLinkPoolQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ResourceLinkPoolQmlWrapper)

    void updateComponentLinks();
    void updateCuttingParamsLink();
    void updateMediaLink();
    void updateFoldingParamsLink();
    void updateLaminatingParamsLink();

    QList<ComponentLinkQmlWrapper *> componentLinks;
    QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper> qmlComponentLinks;
    static ComponentLinkQmlWrapper *componentAt(QQmlListProperty<ComponentLinkQmlWrapper> *property, int index);
    static int componentsCount(QQmlListProperty<ComponentLinkQmlWrapper> *property);

    CuttingParamsLinkQmlWrapper *cuttingParamsLink = nullptr;
    MediaLinkQmlWrapper *mediaLink = nullptr;
    FoldingParamsLinkQmlWrapper *foldingParamsLink = nullptr;
    LaminatingIntentLinkQmlWrapper *laminatingIntentLink = nullptr;
};

}
}

using namespace Proof::Jdf;

ResourceLinkPoolQmlWrapper::ResourceLinkPoolQmlWrapper(const ResourceLinkPoolSP &pool, QObject *parent)
        : NetworkDataEntityQmlWrapper(pool, *new ResourceLinkPoolQmlWrapperPrivate, parent)
{
    setupEntity();
}

ResourceLinkPoolQmlWrapper::~ResourceLinkPoolQmlWrapper()
{
}

QQmlListProperty<ComponentLinkQmlWrapper> ResourceLinkPoolQmlWrapper::componentLinks() const
{
    Q_D(const ResourceLinkPoolQmlWrapper);
    return d->qmlComponentLinks;
}

CuttingParamsLinkQmlWrapper *ResourceLinkPoolQmlWrapper::cuttingParamsLink() const
{
    Q_D(const ResourceLinkPoolQmlWrapper);
    return d->cuttingParamsLink;
}

MediaLinkQmlWrapper *ResourceLinkPoolQmlWrapper::mediaLink() const
{
    Q_D(const ResourceLinkPoolQmlWrapper);
    return d->mediaLink;
}

FoldingParamsLinkQmlWrapper *ResourceLinkPoolQmlWrapper::foldingParamsLink() const
{
    Q_D(const ResourceLinkPoolQmlWrapper);
    return d->foldingParamsLink;
}

LaminatingIntentLinkQmlWrapper *ResourceLinkPoolQmlWrapper::laminatingIntentLink() const
{
    Q_D(const ResourceLinkPoolQmlWrapper);
    return d->laminatingIntentLink;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(ResourceLinkPool)

void ResourceLinkPoolQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    Q_D(ResourceLinkPoolQmlWrapper);
    Q_UNUSED(old);
    ResourceLinkPoolSP linkPool = d->entity<ResourceLinkPool>();
    Q_ASSERT(linkPool);

    connect(linkPool.data(), &ResourceLinkPool::componentLinksChanged,
            d->lambdaConnectContext, [d](){d->updateComponentLinks();});
    connect(linkPool.data(), &ResourceLinkPool::cuttingParamsLinkChanged,
            d->lambdaConnectContext, [d](){d->updateCuttingParamsLink();});
    connect(linkPool.data(), &ResourceLinkPool::mediaLinkChanged,
            d->lambdaConnectContext, [d](){d->updateMediaLink();});
    connect(linkPool.data(), &ResourceLinkPool::foldingParamsLinkChanged,
            d->lambdaConnectContext, [d](){d->updateFoldingParamsLink();});
    connect(linkPool.data(), &ResourceLinkPool::laminatingIntentLinkChanged,
            d->lambdaConnectContext, [d](){d->updateLaminatingParamsLink();});

    d->updateComponentLinks();
    d->updateCuttingParamsLink();
    d->updateMediaLink();
    d->updateFoldingParamsLink();
}


void ResourceLinkPoolQmlWrapperPrivate::updateComponentLinks()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = entity<ResourceLinkPool>();
    for (ComponentLinkQmlWrapper *wrapper : componentLinks)
        wrapper->deleteLater();

    componentLinks.clear();
    for (const ComponentLinkSP &component : linkPool->componentLinks())
        componentLinks << component->toQmlWrapper(q);

    qmlComponentLinks = QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper>(q, &componentLinks,
                                            &ResourceLinkPoolQmlWrapperPrivate::componentsCount,
                                            &ResourceLinkPoolQmlWrapperPrivate::componentAt);
    emit q->componentLinksChanged(qmlComponentLinks);
}

void ResourceLinkPoolQmlWrapperPrivate::updateCuttingParamsLink()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = entity<ResourceLinkPool>();
    if (cuttingParamsLink == nullptr)
        cuttingParamsLink = linkPool->cuttingParamsLink()->toQmlWrapper(q);
    else
        cuttingParamsLink->setEntity(linkPool->cuttingParamsLink());

    emit q->cuttingParamsLinkChanged(cuttingParamsLink);
}

void ResourceLinkPoolQmlWrapperPrivate::updateMediaLink()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = entity<ResourceLinkPool>();
    if (mediaLink == nullptr)
        mediaLink = linkPool->mediaLink()->toQmlWrapper(q);
    else
        mediaLink->setEntity(linkPool->mediaLink());

    emit q->mediaLinkChanged(mediaLink);
}

void ResourceLinkPoolQmlWrapperPrivate::updateFoldingParamsLink()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = entity<ResourceLinkPool>();
    if (foldingParamsLink == nullptr)
        foldingParamsLink = linkPool->foldingParamsLink()->toQmlWrapper(q);
    else
        foldingParamsLink->setEntity(linkPool->foldingParamsLink());

    emit q->foldingParamsLinkChanged(foldingParamsLink);
}

void ResourceLinkPoolQmlWrapperPrivate::updateLaminatingParamsLink()
{
    Q_Q(ResourceLinkPoolQmlWrapper);
    ResourceLinkPoolSP linkPool = entity<ResourceLinkPool>();
    if (laminatingIntentLink == nullptr)
        laminatingIntentLink = linkPool->laminatingIntentLink()->toQmlWrapper(q);
    else
        laminatingIntentLink->setEntity(linkPool->laminatingIntentLink());

    emit q->laminatingIntentLinkChanged(laminatingIntentLink);
}

ComponentLinkQmlWrapper *ResourceLinkPoolQmlWrapperPrivate::componentAt(QQmlListProperty<ComponentLinkQmlWrapper> *property, int index)
{
    return static_cast<QList<ComponentLinkQmlWrapper *> *>(property->data)->at(index);
}

int ResourceLinkPoolQmlWrapperPrivate::componentsCount(QQmlListProperty<ComponentLinkQmlWrapper> *property)
{
    return static_cast<QList<ComponentLinkQmlWrapper *> *>(property->data)->count();
}
