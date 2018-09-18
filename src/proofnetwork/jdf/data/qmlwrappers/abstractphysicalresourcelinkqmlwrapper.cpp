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
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourcelinkqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractphysicalresourcelink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourcelinkqmlwrapper_p.h"

using namespace Proof::Jdf;

AbstractPhysicalResourceLinkQmlWrapper::AbstractPhysicalResourceLinkQmlWrapper(
    const QSharedPointer<AbstractPhysicalResourceLink> &link, AbstractPhysicalResourceLinkQmlWrapperPrivate &dd,
    QObject *parent)
    : AbstractResourceLinkQmlWrapper(link, dd, parent)
{
    setupEntity();
}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractPhysicalResourceLink, Proof::Jdf::ResourceOrientation, orientation)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractPhysicalResourceLink, double, amount)

void AbstractPhysicalResourceLinkQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    AbstractPhysicalResourceLinkSP link = entity<AbstractPhysicalResourceLink>();
    Q_ASSERT(link);

    connect(link.data(), &AbstractPhysicalResourceLink::orientationChanged, this,
            &AbstractPhysicalResourceLinkQmlWrapper::orientationChanged);
    connect(link.data(), &AbstractPhysicalResourceLink::amountChanged, this,
            &AbstractPhysicalResourceLinkQmlWrapper::amountChanged);

    AbstractPhysicalResourceLinkSP oldLink = qSharedPointerCast<AbstractPhysicalResourceLink>(old);
    if (oldLink) {
        if (link->orientation() != oldLink->orientation())
            emit orientationChanged(link->orientation());
        if (link->amount() != oldLink->amount())
            emit amountChanged(link->amount());
    }
}
