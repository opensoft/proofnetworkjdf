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
#include "proofnetwork/jdf/data/qmlwrappers/auditpoolqmlwrapper.h"

#include "proofnetwork/jdf/data/auditpool.h"
#include "proofnetwork/jdf/data/createdaudit.h"
#include "proofnetwork/jdf/data/modifiedaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/createdauditqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/modifiedauditqmlwrapper.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class AuditPoolQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(AuditPoolQmlWrapper)
    void updateCreated();
    void updateModified();

    CreatedAuditQmlWrapper *created = nullptr;
    ModifiedAuditQmlWrapper *modified = nullptr;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

AuditPoolQmlWrapper::AuditPoolQmlWrapper(const AuditPoolSP &auditPool, QObject *parent)
    : NetworkDataEntityQmlWrapper(auditPool, *new AuditPoolQmlWrapperPrivate, parent)
{
    setupEntity();
}

AuditPoolQmlWrapper::~AuditPoolQmlWrapper()
{}

CreatedAuditQmlWrapper *AuditPoolQmlWrapper::created() const
{
    Q_D_CONST(AuditPoolQmlWrapper);
    return d->created;
}

ModifiedAuditQmlWrapper *AuditPoolQmlWrapper::modified() const
{
    Q_D_CONST(AuditPoolQmlWrapper);
    return d->modified;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(AuditPool)

void AuditPoolQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(AuditPoolQmlWrapper);
    Q_UNUSED(old)
    AuditPoolSP auditPool = entity<AuditPool>();
    Q_ASSERT(auditPool);

    connect(auditPool.data(), &AuditPool::createdChanged, entityConnectContext(), [d]() { d->updateCreated(); });
    connect(auditPool.data(), &AuditPool::modifiedChanged, entityConnectContext(), [d]() { d->updateModified(); });

    d->updateCreated();
    d->updateModified();
}

void AuditPoolQmlWrapperPrivate::updateCreated()
{
    Q_Q(AuditPoolQmlWrapper);
    AuditPoolSP auditPool = q->entity<AuditPool>();
    if (created == nullptr)
        created = auditPool->created()->toQmlWrapper(q);
    else
        created->setEntity(auditPool->created());
    emit q->createdChanged(created);
}

void AuditPoolQmlWrapperPrivate::updateModified()
{
    Q_Q(AuditPoolQmlWrapper);
    AuditPoolSP auditPool = q->entity<AuditPool>();
    if (modified == nullptr)
        modified = auditPool->modified()->toQmlWrapper(q);
    else
        modified->setEntity(auditPool->modified());
    emit q->modifiedChanged(modified);
}
