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
#include "proofnetwork/jdf/data/qmlwrappers/createdauditqmlwrapper.h"

#include "proofnetwork/jdf/data/createdaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class CreatedAuditQmlWrapperPrivate : public AbstractAuditQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CreatedAuditQmlWrapper)
};

CreatedAuditQmlWrapper::CreatedAuditQmlWrapper(const CreatedAuditSP &createdAudit, QObject *parent)
    : AbstractAuditQmlWrapper(createdAudit, *new CreatedAuditQmlWrapperPrivate, parent)
{
    setupEntity(); // NOLINT
}

CreatedAuditQmlWrapper::~CreatedAuditQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(CreatedAudit)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CreatedAudit, QString, templateId)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CreatedAudit, QString, templateVersion)

void CreatedAuditQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    CreatedAuditSP createdAudit = entity<CreatedAudit>();
    Q_ASSERT(createdAudit);

    connect(createdAudit.data(), &CreatedAudit::templateIdChanged, this, &CreatedAuditQmlWrapper::templateIdChanged);
    connect(createdAudit.data(), &CreatedAudit::templateVersionChanged, this,
            &CreatedAuditQmlWrapper::templateVersionChanged);

    CreatedAuditSP oldCreatedAudit = qSharedPointerCast<CreatedAudit>(old);
    if (oldCreatedAudit) {
        if (createdAudit->templateId() != oldCreatedAudit->templateId())
            emit templateIdChanged(createdAudit->templateId());
        if (createdAudit->templateVersion() != oldCreatedAudit->templateVersion())
            emit templateVersionChanged(createdAudit->templateVersion());
    }
}

} // namespace Jdf
} // namespace Proof
