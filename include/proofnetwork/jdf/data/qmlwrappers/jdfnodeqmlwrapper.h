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
#ifndef JDFJDFNODEQMLWRAPPER_H
#define JDFJDFNODEQMLWRAPPER_H

#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class AuditPoolQmlWrapper;
class ResourcePoolQmlWrapper;

class JdfNodeQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT JdfNodeQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(QString jobId READ jobId NOTIFY jobIdChanged)
    Q_PROPERTY(QString jobPartId READ jobPartId NOTIFY jobPartIdChanged)
    Q_PROPERTY(Proof::Jdf::AuditPoolQmlWrapper *auditPool READ auditPool NOTIFY auditPoolChanged)
    Q_PROPERTY(Proof::Jdf::ResourcePoolQmlWrapper *resourcePool READ resourcePool NOTIFY resourcePoolChanged)
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper> jdfNodes READ jdfNodes NOTIFY jdfNodesChanged)
    Q_DECLARE_PRIVATE(JdfNodeQmlWrapper)
public:
    explicit JdfNodeQmlWrapper(const JdfNodeSP &jdfNode, QObject *parent = nullptr);
    ~JdfNodeQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(JdfNode)

    QString id() const;
    QString jobId() const;
    QString jobPartId() const;
    AuditPoolQmlWrapper *auditPool() const;
    ResourcePoolQmlWrapper *resourcePool() const;
    QQmlListProperty<JdfNodeQmlWrapper> jdfNodes() const;

signals:
    void idChanged(const QString &id);
    void jobIdChanged(const QString &jobId);
    void jobPartIdChanged(const QString &jobPartId);
    void auditPoolChanged(Proof::Jdf::AuditPoolQmlWrapper *auditPool);
    void resourcePoolChanged(Proof::Jdf::ResourcePoolQmlWrapper *resourcePool);
    void jdfNodesChanged(QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper> &jdfNodes);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFJDFNODEQMLWRAPPER_H
