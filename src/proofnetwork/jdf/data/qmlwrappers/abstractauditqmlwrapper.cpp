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
#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper_p.h"

using namespace Proof;
using namespace Proof::Jdf;

AbstractAuditQmlWrapper::AbstractAuditQmlWrapper(const AbstractAuditSP &abstractAudit,
                                                 AbstractAuditQmlWrapperPrivate &dd, QObject *parent)
    : NetworkDataEntityQmlWrapper(abstractAudit, dd, parent)
{
    setupEntity(); // NOLINT
}

AbstractAuditQmlWrapper::~AbstractAuditQmlWrapper()
{}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractAudit, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractAudit, QString, agentName)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractAudit, QString, agentVersion)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractAudit, QDateTime, timeStamp)

void AbstractAuditQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    AbstractAuditSP abstractAudit = entity<AbstractAudit>();
    Q_ASSERT(abstractAudit);

    connect(abstractAudit.data(), &AbstractAudit::idChanged, this, &AbstractAuditQmlWrapper::idChanged);
    connect(abstractAudit.data(), &AbstractAudit::agentNameChanged, this, &AbstractAuditQmlWrapper::agentNameChanged);
    connect(abstractAudit.data(), &AbstractAudit::agentVersionChanged, this,
            &AbstractAuditQmlWrapper::agentVersionChanged);
    connect(abstractAudit.data(), &AbstractAudit::timeStampChanged, this, &AbstractAuditQmlWrapper::timeStampChanged);

    AbstractAuditSP oldAbstractAudit = qSharedPointerCast<AbstractAudit>(old);
    if (oldAbstractAudit) {
        if (abstractAudit->id() != oldAbstractAudit->id())
            emit idChanged(abstractAudit->id());
        if (abstractAudit->agentName() != oldAbstractAudit->agentName())
            emit agentNameChanged(abstractAudit->agentName());
        if (abstractAudit->agentVersion() != oldAbstractAudit->agentVersion())
            emit agentVersionChanged(abstractAudit->agentVersion());
        if (abstractAudit->timeStamp() != oldAbstractAudit->timeStamp())
            emit timeStampChanged(abstractAudit->timeStamp());
    }
}
