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
#include "proofnetwork/jdf/data/qmlwrappers/resourcepoolqmlwrapper.h"

#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/laminatingintent.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/qmlwrappers/componentqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingparamsqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/foldingparamsqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"
#include "proofnetwork/jdf/data/resourcepool.h"
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

    QVector<ComponentQmlWrapper *> components;
    QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> qmlComponentsList;
    static ComponentQmlWrapper *componentAt(QQmlListProperty<ComponentQmlWrapper> *property, int index);
    static int componentsCount(QQmlListProperty<ComponentQmlWrapper> *property);

    QVector<MediaQmlWrapper *> media;
    QQmlListProperty<Proof::Jdf::MediaQmlWrapper> qmlMediaList;
    static MediaQmlWrapper *mediaAt(QQmlListProperty<MediaQmlWrapper> *property, int index);
    static int mediaCount(QQmlListProperty<MediaQmlWrapper> *property);

    CuttingParamsQmlWrapper *cuttingParams = nullptr;
    FoldingParamsQmlWrapper *foldingParams = nullptr;
    LaminatingIntentQmlWrapper *laminatingIntent = nullptr;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

ResourcePoolQmlWrapper::ResourcePoolQmlWrapper(const ResourcePoolSP &resourcePool, QObject *parent)
    : NetworkDataEntityQmlWrapper(resourcePool, *new ResourcePoolQmlWrapperPrivate, parent)
{
    setupEntity();
}

ResourcePoolQmlWrapper::~ResourcePoolQmlWrapper()
{}

QQmlListProperty<ComponentQmlWrapper> ResourcePoolQmlWrapper::components() const
{
    Q_D_CONST(ResourcePoolQmlWrapper);
    return d->qmlComponentsList;
}

CuttingParamsQmlWrapper *ResourcePoolQmlWrapper::cuttingParams() const
{
    Q_D_CONST(ResourcePoolQmlWrapper);
    return d->cuttingParams;
}

QQmlListProperty<MediaQmlWrapper> ResourcePoolQmlWrapper::media() const
{
    Q_D_CONST(ResourcePoolQmlWrapper);
    return d->qmlMediaList;
}

FoldingParamsQmlWrapper *ResourcePoolQmlWrapper::foldingParams() const
{
    Q_D_CONST(ResourcePoolQmlWrapper);
    return d->foldingParams;
}

LaminatingIntentQmlWrapper *ResourcePoolQmlWrapper::laminatingIntent() const
{
    Q_D_CONST(ResourcePoolQmlWrapper);
    return d->laminatingIntent;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(ResourcePool)

void ResourcePoolQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(ResourcePoolQmlWrapper);
    Q_UNUSED(old)
    ResourcePoolSP resourcePool = entity<ResourcePool>();
    Q_ASSERT(resourcePool);

    connect(resourcePool.data(), &ResourcePool::componentsChanged, entityConnectContext(),
            [d]() { d->updateComponents(); });
    connect(resourcePool.data(), &ResourcePool::cuttingParamsChanged, entityConnectContext(),
            [d]() { d->updateCutingParams(); });
    connect(resourcePool.data(), &ResourcePool::laminatingIntentChanged, entityConnectContext(),
            [d]() { d->updateLaminatingIntent(); });
    connect(resourcePool.data(), &ResourcePool::mediaChanged, entityConnectContext(), [d]() { d->updateMedia(); });
    connect(resourcePool.data(), &ResourcePool::foldingParamsChanged, entityConnectContext(),
            [d]() { d->updateFoldingParams(); });

    d->updateComponents();
    d->updateCutingParams();
    d->updateMedia();
    d->updateFoldingParams();
}

void ResourcePoolQmlWrapperPrivate::updateComponents()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP resourcePool = q->entity<ResourcePool>();
    for (ComponentQmlWrapper *wrapper : qAsConst(components))
        wrapper->deleteLater();

    components.clear();
    const auto ndeComponents = resourcePool->components();
    for (const ComponentSP &component : ndeComponents)
        components << component->toQmlWrapper(q);

    qmlComponentsList = QQmlListProperty<Proof::Jdf::ComponentQmlWrapper>(q, &components,
                                                                          &ResourcePoolQmlWrapperPrivate::componentsCount,
                                                                          &ResourcePoolQmlWrapperPrivate::componentAt);
    emit q->componentsChanged(qmlComponentsList);
}

void ResourcePoolQmlWrapperPrivate::updateCutingParams()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP cutProcess = q->entity<ResourcePool>();
    if (cuttingParams == nullptr)
        cuttingParams = cutProcess->cuttingParams()->toQmlWrapper(q);
    else
        cuttingParams->setEntity(cutProcess->cuttingParams());

    emit q->cuttingParamsChanged(cuttingParams);
}

void ResourcePoolQmlWrapperPrivate::updateMedia()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP resourcePool = q->entity<ResourcePool>();
    for (MediaQmlWrapper *wrapper : qAsConst(media))
        wrapper->deleteLater();

    media.clear();
    const auto ndeMedia = resourcePool->media();
    for (const MediaSP &md : ndeMedia)
        media << md->toQmlWrapper(q);

    qmlMediaList = QQmlListProperty<Proof::Jdf::MediaQmlWrapper>(q, &media, &ResourcePoolQmlWrapperPrivate::mediaCount,
                                                                 &ResourcePoolQmlWrapperPrivate::mediaAt);
    emit q->mediaChanged(qmlMediaList);
}

void ResourcePoolQmlWrapperPrivate::updateFoldingParams()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP resourcePool = q->entity<ResourcePool>();
    if (foldingParams == nullptr)
        foldingParams = resourcePool->foldingParams()->toQmlWrapper(q);
    else
        foldingParams->setEntity(resourcePool->foldingParams());
    emit q->foldingParamsChanged(foldingParams);
}

void ResourcePoolQmlWrapperPrivate::updateLaminatingIntent()
{
    Q_Q(ResourcePoolQmlWrapper);
    ResourcePoolSP resourcePool = q->entity<ResourcePool>();
    if (laminatingIntent == nullptr)
        laminatingIntent = resourcePool->laminatingIntent()->toQmlWrapper(q);
    else
        laminatingIntent->setEntity(resourcePool->laminatingIntent());
    emit q->laminatingIntentChanged(laminatingIntent);
}

ComponentQmlWrapper *ResourcePoolQmlWrapperPrivate::componentAt(QQmlListProperty<ComponentQmlWrapper> *property, int index)
{
    return static_cast<QVector<ComponentQmlWrapper *> *>(property->data)->at(index);
}

int ResourcePoolQmlWrapperPrivate::componentsCount(QQmlListProperty<ComponentQmlWrapper> *property)
{
    return static_cast<QVector<ComponentQmlWrapper *> *>(property->data)->count();
}

MediaQmlWrapper *ResourcePoolQmlWrapperPrivate::mediaAt(QQmlListProperty<MediaQmlWrapper> *property, int index)
{
    return static_cast<QVector<MediaQmlWrapper *> *>(property->data)->at(index);
}

int ResourcePoolQmlWrapperPrivate::mediaCount(QQmlListProperty<MediaQmlWrapper> *property)
{
    return static_cast<QVector<MediaQmlWrapper *> *>(property->data)->count();
}
