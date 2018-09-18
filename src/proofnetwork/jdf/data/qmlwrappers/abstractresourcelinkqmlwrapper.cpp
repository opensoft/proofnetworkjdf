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
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"

using namespace Proof::Jdf;

AbstractResourceLinkQmlWrapper::AbstractResourceLinkQmlWrapper(const QSharedPointer<AbstractResourceLink> &link,
                                                               AbstractResourceLinkQmlWrapperPrivate &dd, QObject *parent)
    : NetworkDataEntityQmlWrapper(link, dd, parent)
{
    setupEntity();
}

AbstractResourceLinkQmlWrapper::~AbstractResourceLinkQmlWrapper()
{}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResourceLink, QString, rRef)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResourceLink, Proof::Jdf::LinkUsage, usage)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResourceLink, Proof::Jdf::ProcessUsage, processUsage)

void AbstractResourceLinkQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    AbstractResourceLinkSP abstractResourceLink = entity<AbstractResourceLink>();
    Q_ASSERT(abstractResourceLink);

    connect(abstractResourceLink.data(), &AbstractResourceLink::rRefChanged, this,
            &AbstractResourceLinkQmlWrapper::rRefChanged);
    connect(abstractResourceLink.data(), &AbstractResourceLink::usageChanged, this,
            &AbstractResourceLinkQmlWrapper::usageChanged);
    connect(abstractResourceLink.data(), &AbstractResourceLink::processUsageChanged, this,
            &AbstractResourceLinkQmlWrapper::processUsageChanged);

    AbstractResourceLinkSP castedOld = qSharedPointerCast<AbstractResourceLink>(old);
    if (castedOld) {
        if (abstractResourceLink->rRef() != castedOld->rRef())
            emit rRefChanged(abstractResourceLink->rRef());

        if (abstractResourceLink->usage() != castedOld->usage())
            emit usageChanged(abstractResourceLink->usage());

        if (abstractResourceLink->processUsage() != castedOld->processUsage())
            emit processUsageChanged(abstractResourceLink->processUsage());
    }
}
