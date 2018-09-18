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
#ifndef PROOF_JDF_CREATEDAUDITQMLWRAPPER_H
#define PROOF_JDF_CREATEDAUDITQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class CreatedAudit;

class CreatedAuditQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT CreatedAuditQmlWrapper : public AbstractAuditQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString templateId READ templateId NOTIFY templateIdChanged)
    Q_PROPERTY(QString templateVersion READ templateVersion NOTIFY templateVersionChanged)
    Q_DECLARE_PRIVATE(CreatedAuditQmlWrapper)
public:
    explicit CreatedAuditQmlWrapper(const CreatedAuditSP &createdAudit, QObject *parent = nullptr);
    ~CreatedAuditQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(CreatedAudit)

    QString templateId() const;
    QString templateVersion() const;

signals:
    void templateIdChanged(const QString &arg);
    void templateVersionChanged(const QString &arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_CREATEDAUDITQMLWRAPPER_H
