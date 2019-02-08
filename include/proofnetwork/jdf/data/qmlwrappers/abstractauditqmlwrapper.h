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
#ifndef ABSTRACTAUDITQMLWRAPPER_H
#define ABSTRACTAUDITQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"

#include <QDateTime>

namespace Proof {
namespace Jdf {

class AbstractAuditQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractAuditQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(QString agentName READ agentName NOTIFY agentNameChanged)
    Q_PROPERTY(QString agentVersion READ agentVersion NOTIFY agentVersionChanged)
    Q_PROPERTY(QDateTime timeStamp READ timeStamp NOTIFY timeStampChanged)

    Q_DECLARE_PRIVATE(AbstractAuditQmlWrapper)
public:
    explicit AbstractAuditQmlWrapper(const QSharedPointer<AbstractAudit> &abstractAudit,
                                     AbstractAuditQmlWrapperPrivate &dd, QObject *parent = nullptr);
    AbstractAuditQmlWrapper(const AbstractAuditQmlWrapper &) = delete;
    AbstractAuditQmlWrapper &operator=(const AbstractAuditQmlWrapper &) = delete;
    AbstractAuditQmlWrapper(AbstractAuditQmlWrapper &&) = delete;
    AbstractAuditQmlWrapper &operator=(AbstractAuditQmlWrapper &&) = delete;
    ~AbstractAuditQmlWrapper();

    QString id() const;
    QString agentName() const;
    QString agentVersion() const;
    QDateTime timeStamp() const;

signals:
    void idChanged(const QString &id);
    void agentNameChanged(const QString &id);
    void agentVersionChanged(const QString &id);
    void timeStampChanged(const QDateTime &id);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // ABSTRACTAUDITQMLWRAPPER_H
