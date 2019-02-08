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
#ifndef PROOF_JDF_ABSTRACTAUDIT_H
#define PROOF_JDF_ABSTRACTAUDIT_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QDateTime>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractAuditPrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractAudit : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractAudit)
public:
    explicit AbstractAudit() = delete;
    AbstractAudit(const AbstractAudit &) = delete;
    AbstractAudit &operator=(const AbstractAudit &) = delete;
    AbstractAudit(AbstractAudit &&) = delete;
    AbstractAudit &operator=(AbstractAudit &&) = delete;
    ~AbstractAudit() = default;

    QString id() const;
    QString agentName() const;
    QString agentVersion() const;
    QDateTime timeStamp() const;

    void setId(const QString &arg);
    void setAgentName(const QString &arg);
    void setAgentVersion(const QString &arg);
    void setTimeStamp(const QDateTime &arg);

    static bool fromJdf(const QXmlStreamReader &xmlReader, AbstractAuditSP &abstractAudit);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void idChanged(const QString &arg);
    void agentNameChanged(const QString &arg);
    void agentVersionChanged(const QString &arg);
    void timeStampChanged(const QDateTime &arg);

protected:
    explicit AbstractAudit(AbstractAuditPrivate &dd);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_ABSTRACTAUDIT_H
