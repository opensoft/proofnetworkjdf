/* Copyright 2019, OpenSoft Inc.
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
#ifndef PROOF_XJDF_AUDITPOOL_H
#define PROOF_XJDF_AUDITPOOL_H

#include "proofnetwork/xjdf/data/abstractnode.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_global.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace XJdf {

class AuditPoolPrivate;
class PROOF_NETWORK_XJDF_EXPORT AuditPool : public AbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AuditPool)
    friend Document;

public:
    AuditPool(const AuditPool &) = delete;
    AuditPool &operator=(const AuditPool &) = delete;
    AuditPool(AuditPool &&) = delete;
    AuditPool &operator=(AuditPool &&) = delete;
    ~AuditPool() = default;

    AuditPoolSP cloneTo(const DocumentSP &document) const;

    AuditCreatedSP created() const;
    QVector<AuditNotificationSP> notifications() const;

    void setCreated(const AuditCreatedSP &created);
    void setNotifications(const QVector<AuditNotificationSP> &arg);

    static AuditPoolSP fromXJdf(QXmlStreamReader &reader, const DocumentSP &document);
    void toXJdf(QXmlStreamWriter &writer) const override;

signals:
    void createdChanged(const Proof::XJdf::AuditCreatedSP &arg);
    void notificationsChanged(const QVector<Proof::XJdf::AuditNotificationSP> &arg);

protected:
    explicit AuditPool();
    static AuditPoolSP create(const DocumentSP &document);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // PROOF_JDF_AUDITPOOL_H
