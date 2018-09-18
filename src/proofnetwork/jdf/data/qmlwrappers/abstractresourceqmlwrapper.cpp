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
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

using namespace Proof;
using namespace Proof::Jdf;

AbstractResourceQmlWrapper::AbstractResourceQmlWrapper(const QSharedPointer<AbstractResource> &abstractResource,
                                                       AbstractResourceQmlWrapperPrivate &dd, QObject *parent)
    : NetworkDataEntityQmlWrapper(abstractResource, dd, parent)
{
    setupEntity();
}

AbstractResourceQmlWrapper::~AbstractResourceQmlWrapper()
{}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, Proof::Jdf::ResourceStatus, resourceStatus)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, Proof::Jdf::ResourceClass, resourceClass)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, QVector<ResourcePartType>, partIdKeys)

void AbstractResourceQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    AbstractResourceSP abstractResource = entity<AbstractResource>();
    Q_ASSERT(abstractResource);

    connect(abstractResource.data(), &AbstractResource::idChanged, this, &AbstractResourceQmlWrapper::idChanged);
    connect(abstractResource.data(), &AbstractResource::statusChanged, this,
            &AbstractResourceQmlWrapper::resourceStatusChanged);
    connect(abstractResource.data(), &AbstractResource::resourceClassChanged, this,
            &AbstractResourceQmlWrapper::resourceClassChanged);
    connect(abstractResource.data(), &AbstractResource::partIdKeysChanged, this,
            &AbstractResourceQmlWrapper::partIdKeysChanged);

    AbstractResourceSP oldAbstractResource = qSharedPointerCast<AbstractResource>(old);
    if (oldAbstractResource) {
        if (abstractResource->id() != oldAbstractResource->id())
            emit idChanged(abstractResource->id());
        if (abstractResource->resourceStatus() != oldAbstractResource->resourceStatus())
            emit resourceStatusChanged(abstractResource->resourceStatus());
        if (abstractResource->resourceClass() != oldAbstractResource->resourceClass())
            emit resourceClassChanged(abstractResource->resourceClass());
        if (abstractResource->partIdKeys() != oldAbstractResource->partIdKeys())
            emit partIdKeysChanged(abstractResource->partIdKeys());
    }
}
