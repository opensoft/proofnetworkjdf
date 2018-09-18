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
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractphysicalresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper_p.h"

using namespace Proof;
using namespace Proof::Jdf;

AbstractPhysicalResourceQmlWrapper::AbstractPhysicalResourceQmlWrapper(
    const QSharedPointer<AbstractPhysicalResource> &abstractPhysicalResource,
    AbstractPhysicalResourceQmlWrapperPrivate &dd, QObject *parent)
    : AbstractResourceQmlWrapper(abstractPhysicalResource, dd, parent)
{
    setupEntity();
}

AbstractPhysicalResourceQmlWrapper::~AbstractPhysicalResourceQmlWrapper()
{}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractPhysicalResource, double, amount)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractPhysicalResource, double, resourceWeight)

void AbstractPhysicalResourceQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    AbstractPhysicalResourceSP abstractPhysicalResource = entity<AbstractPhysicalResource>();
    Q_ASSERT(abstractPhysicalResource);

    connect(abstractPhysicalResource.data(), &AbstractPhysicalResource::amountChanged, this,
            &AbstractPhysicalResourceQmlWrapper::amountChanged);
    connect(abstractPhysicalResource.data(), &AbstractPhysicalResource::resourceWeightChanged, this,
            &AbstractPhysicalResourceQmlWrapper::resourceWeightChanged);

    AbstractPhysicalResourceSP oldAbstractPhysicalResource = qSharedPointerCast<AbstractPhysicalResource>(old);
    if (oldAbstractPhysicalResource) {
        if (abstractPhysicalResource->amount() != oldAbstractPhysicalResource->amount())
            emit amountChanged(abstractPhysicalResource->amount());
        if (abstractPhysicalResource->resourceWeight() != oldAbstractPhysicalResource->resourceWeight())
            emit resourceWeightChanged(abstractPhysicalResource->resourceWeight());
    }

    AbstractResourceQmlWrapper::setupEntity(old);
}
