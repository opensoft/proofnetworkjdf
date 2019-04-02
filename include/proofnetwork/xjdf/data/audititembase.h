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
#ifndef XJDF_AUDITITEMBASE_H
#define XJDF_AUDITITEMBASE_H

#include "abstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class AuditItemBasePrivate;
class PROOF_NETWORK_XJDF_EXPORT AuditItemBase : public AbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AuditItemBase)
public:
    AuditItemBase(const AuditItemBase &) = delete;
    AuditItemBase &operator=(const AuditItemBase &) = delete;
    AuditItemBase(AuditItemBase &&) = delete;
    AuditItemBase &operator=(AuditItemBase &&) = delete;
    ~AuditItemBase() = default;

    QString agentName() const;
    QString agentVersion() const;
    QDateTime timestamp() const;
    QString id() const;
    QString deviceId() const;

    void setAgentName(const QString &arg);
    void setAgentVersion(const QString &arg);
    void setTimestamp(const QDateTime &arg);
    void setId(const QString &arg);
    void setDeviceId(const QString &arg);

    bool readFieldsFromXJdf(QXmlStreamReader &reader) override final;
    void toXJdf(QXmlStreamWriter &writer) const override;

signals:
    void agentNameChanged(const QString &arg);
    void agentVersionChanged(const QString &arg);
    void timestampChanged(const QDateTime &arg);
    void idChanged(const QString &arg);
    void deviceIdChanged(const QString &arg);

protected:
    explicit AuditItemBase(AuditItemBasePrivate &dd);
    void updateSelf(const NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_AUDITITEMBASE_H
