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
#ifndef JDFJDFNODE_H
#define JDFJDFNODE_H

#include "proofnetwork/jdf/data/qmlwrappers/jdfnodeqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QVector>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class JdfNodePrivate;
class PROOF_NETWORK_JDF_EXPORT JdfNode : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(JdfNode)
public:
    QString id() const;
    QString jobId() const;
    QString jobPartId() const;
    AuditPoolSP auditPool() const;
    ResourcePoolSP resourcePool() const;
    ResourceLinkPoolSP resourceLinkPool() const;
    QVector<JdfNodeSP> jdfNodes() const;
    QString type() const;
    QStringList types() const;

    void setId(const QString &arg);
    void setJobId(const QString &arg);
    void setJobPartId(const QString &arg);
    void setAuditPool(const AuditPoolSP &arg);
    void setResourcePool(const ResourcePoolSP &arg);
    void setResourceLinkPool(const ResourceLinkPoolSP &arg);
    void setJdfNodes(const QVector<JdfNodeSP> &arg);
    void addJdfNode(const JdfNodeSP &arg);
    void setType(const QString &arg);
    void setTypes(const QStringList &arg);

    JdfNodeSP findNode(const std::function<bool(const JdfNodeSP &)> &predicate) const;
    ComponentSP findComponent(const std::function<bool(const Proof::Jdf::ComponentSP &)> &predicate) const;
    ComponentLinkSP findComponentLink(const std::function<bool(const Proof::Jdf::ComponentLinkSP &)> &predicate) const;
    MediaLinkSP findMediaLink(const std::function<bool(const Proof::Jdf::MediaLinkSP &)> &predicate) const;
    MediaSP findMedia(const std::function<bool(const MediaSP &)> &predicate) const;
    LayoutSP findLayout(const std::function<bool(const LayoutSP &)> &predicate) const;

    QVector<JdfNodeSP> findAllNodes(const std::function<bool(const JdfNodeSP &)> &predicate) const;
    QVector<ComponentSP> findAllComponents(const std::function<bool(const Proof::Jdf::ComponentSP &)> &predicate) const;
    QVector<ComponentLinkSP>
    findAllComponentLinks(const std::function<bool(const Proof::Jdf::ComponentLinkSP &)> &predicate) const;
    QVector<MediaLinkSP> findAllMediaLinks(const std::function<bool(const Proof::Jdf::MediaLinkSP &)> &predicate) const;
    QVector<MediaSP> findAllMedia(const std::function<bool(const MediaSP &)> &predicate) const;
    QVector<LayoutSP> findAllLayouts(const std::function<bool(const LayoutSP &)> &predicate) const;

    JdfNodeQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static JdfNodeSP create();

    static JdfNodeSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId = QString(),
                             const QStringList &alternativeIdAttributes = QStringList(), bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter, bool rootNode = false);

signals:
    void idChanged(const QString &arg);
    void jobIdChanged(const QString &arg);
    void jobPartIdChanged(const QString &arg);
    void auditPoolChanged(const Proof::Jdf::AuditPoolSP &arg);
    void resourcePoolChanged(const Proof::Jdf::ResourcePoolSP &arg);
    void resourceLinkPoolChanged(const Proof::Jdf::ResourceLinkPoolSP &resourceLinkPool);
    void jdfNodesChanged();
    void typeChanged(const QString &type);
    void typesChanged(const QStringList &types);

protected:
    JdfNode();
    JdfNode(JdfNodePrivate &dd);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFJDFNODE_H
