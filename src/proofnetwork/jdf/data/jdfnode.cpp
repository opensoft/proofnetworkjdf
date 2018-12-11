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
#include "proofnetwork/jdf/data/jdfnode.h"

#include "proofcore/proofglobal.h"

#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/jdfnode_p.h"
#include "proofnetwork/jdf/data/layout.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfnodeqmlwrapper.h"

#include <set>

using namespace Proof::Jdf;

QString JdfNode::id() const
{
    Q_D_CONST(JdfNode);
    return d->id;
}

QString JdfNode::jobId() const
{
    Q_D_CONST(JdfNode);
    return d->jobId;
}

QString JdfNode::jobPartId() const
{
    Q_D_CONST(JdfNode);
    return d->jobPartId;
}

AuditPoolSP JdfNode::auditPool() const
{
    Q_D_CONST(JdfNode);
    return d->auditPool;
}

ResourcePoolSP JdfNode::resourcePool() const
{
    Q_D_CONST(JdfNode);
    return d->resourcePool;
}

ResourceLinkPoolSP JdfNode::resourceLinkPool() const
{
    Q_D_CONST(JdfNode);
    return d->resourceLinkPool;
}

QVector<JdfNodeSP> JdfNode::jdfNodes() const
{
    Q_D_CONST(JdfNode);
    return d->jdfNodes;
}

QString JdfNode::type() const
{
    Q_D_CONST(JdfNode);
    return d->type;
}

QStringList JdfNode::types() const
{
    Q_D_CONST(JdfNode);
    return d->types;
}

void JdfNode::setId(const QString &arg)
{
    Q_D(JdfNode);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void JdfNode::setJobId(const QString &arg)
{
    Q_D(JdfNode);
    if (d->jobId != arg) {
        d->jobId = arg;
        emit jobIdChanged(d->jobId);
    }
}

void JdfNode::setJobPartId(const QString &arg)
{
    Q_D(JdfNode);
    if (d->jobPartId != arg) {
        d->jobPartId = arg;
        emit jobPartIdChanged(d->jobPartId);
    }
}

void JdfNode::setAuditPool(const AuditPoolSP &arg)
{
    Q_ASSERT(arg);
    Q_D(JdfNode);
    if (d->auditPool != arg) {
        d->auditPool = arg;
        emit auditPoolChanged(d->auditPool);
    }
}

void JdfNode::setResourcePool(const ResourcePoolSP &arg)
{
    Q_ASSERT(arg);
    Q_D(JdfNode);
    if (d->resourcePool != arg) {
        d->resourcePool = arg;
        emit resourcePoolChanged(d->resourcePool);
    }
}

void JdfNode::setResourceLinkPool(const ResourceLinkPoolSP &arg)
{
    Q_ASSERT(arg);
    Q_D(JdfNode);
    if (d->resourceLinkPool != arg) {
        d->resourceLinkPool = arg;
        emit resourceLinkPoolChanged(d->resourceLinkPool);
    }
}

void JdfNode::setJdfNodes(const QVector<JdfNodeSP> &arg)
{
    Q_D(JdfNode);
    std::multiset<QString> newIds;
    for (const auto &node : arg)
        newIds.insert(node->id());

    std::multiset<QString> oldIds;
    for (const auto &node : qAsConst(d->jdfNodes))
        oldIds.insert(node->id());

    if (newIds != oldIds) {
        d->jdfNodes = arg;
        emit jdfNodesChanged();
    }
}

void JdfNode::addJdfNode(const JdfNodeSP &arg)
{
    Q_D(JdfNode);
    if (!arg)
        return;
    d->jdfNodes << arg;
    emit jdfNodesChanged();
}

void JdfNode::setType(const QString &arg)
{
    Q_D(JdfNode);
    if (arg != d->type) {
        d->type = arg;
        emit typeChanged(d->type);
    }
}

void JdfNode::setTypes(const QStringList &arg)
{
    Q_D(JdfNode);
    if (arg != d->types) {
        d->types = arg;
        emit typesChanged(d->types);
    }
}

JdfNodeSP Proof::Jdf::JdfNode::findNode(const std::function<bool(const JdfNodeSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<JdfNodeSP> queue = {castedSelf};
    while (queue.count()) {
        auto head = queue.takeFirst();
        if (predicate(head))
            return head;
        queue << head->jdfNodes();
    }
    return JdfNodeSP();
}

ComponentSP Proof::Jdf::JdfNode::findComponent(const std::function<bool(const ComponentSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<JdfNodeSP> queue = {castedSelf};
    QVector<ComponentSP> componentsQueue;
    while (queue.count()) {
        componentsQueue.resize(0);
        auto head = queue.takeFirst();
        componentsQueue << head->resourcePool()->components();
        while (componentsQueue.count()) {
            auto component = componentsQueue.takeFirst();
            if (predicate(component))
                return component;
            componentsQueue << component->parts();
        }
        queue << head->jdfNodes();
    }
    return ComponentSP();
}

ComponentLinkSP JdfNode::findComponentLink(const std::function<bool(const ComponentLinkSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<JdfNodeSP> queue = {castedSelf};
    while (queue.count()) {
        auto head = queue.takeFirst();
        auto link = algorithms::findIf(head->resourceLinkPool()->componentLinks(), predicate);
        if (link)
            return link;
        queue << head->jdfNodes();
    }
    return ComponentLinkSP();
}

MediaLinkSP JdfNode::findMediaLink(const std::function<bool(const MediaLinkSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<JdfNodeSP> queue = {castedSelf};
    while (queue.count()) {
        auto head = queue.takeFirst();
        auto link = algorithms::findIf(head->resourceLinkPool()->mediaLinks(), predicate);
        if (link)
            return link;
        queue << head->jdfNodes();
    }
    return MediaLinkSP();
}

MediaSP JdfNode::findMedia(const std::function<bool(const MediaSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<JdfNodeSP> queue = {castedSelf};
    while (queue.count()) {
        auto head = queue.takeFirst();
        auto media = algorithms::findIf(head->resourcePool()->media(), predicate);
        if (media)
            return media;
        queue << head->jdfNodes();
    }
    return MediaSP();
}

LayoutSP JdfNode::findLayout(const std::function<bool(const LayoutSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<JdfNodeSP> queue = {castedSelf};
    QVector<LayoutSP> layoutsQueue;
    while (queue.count()) {
        layoutsQueue.resize(0);
        auto head = queue.takeFirst();
        layoutsQueue << head->resourcePool()->layouts();
        while (layoutsQueue.count()) {
            auto layout = layoutsQueue.takeFirst();
            if (predicate(layout))
                return layout;
            layoutsQueue << layout->parts();
        }
        queue << head->jdfNodes();
    }
    return LayoutSP();
}

QVector<JdfNodeSP> JdfNode::findAllNodes(const std::function<bool(const JdfNodeSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<JdfNodeSP> result;
    QVector<JdfNodeSP> queue = {castedSelf};
    while (queue.count()) {
        auto head = queue.takeFirst();
        if (predicate(head))
            result << head;
        queue << head->jdfNodes();
    }
    return result;
}

QVector<ComponentSP> JdfNode::findAllComponents(const std::function<bool(const ComponentSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<ComponentSP> result;
    QVector<JdfNodeSP> queue = {castedSelf};
    QVector<ComponentSP> componentsQueue;
    while (queue.count()) {
        componentsQueue.resize(0);
        auto head = queue.takeFirst();
        componentsQueue << head->resourcePool()->components();
        while (componentsQueue.count()) {
            auto component = componentsQueue.takeFirst();
            if (predicate(component))
                result << component;
            componentsQueue << component->parts();
        }
        queue << head->jdfNodes();
    }
    return result;
}

QVector<ComponentLinkSP> JdfNode::findAllComponentLinks(const std::function<bool(const ComponentLinkSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<ComponentLinkSP> result;
    QVector<JdfNodeSP> queue = {castedSelf};
    while (queue.count()) {
        auto head = queue.takeFirst();
        result << algorithms::filter(head->resourceLinkPool()->componentLinks(), predicate);
        queue << head->jdfNodes();
    }
    return result;
}

QVector<MediaLinkSP> JdfNode::findAllMediaLinks(const std::function<bool(const MediaLinkSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<MediaLinkSP> result;
    QVector<JdfNodeSP> queue = {castedSelf};
    while (queue.count()) {
        auto head = queue.takeFirst();
        result << algorithms::filter(head->resourceLinkPool()->mediaLinks(), predicate);
        queue << head->jdfNodes();
    }
    return result;
}

QVector<MediaSP> JdfNode::findAllMedia(const std::function<bool(const MediaSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<MediaSP> result;
    QVector<JdfNodeSP> queue = {castedSelf};
    while (queue.count()) {
        auto head = queue.takeFirst();
        result << algorithms::filter(head->resourcePool()->media(), predicate);
        queue << head->jdfNodes();
    }
    return result;
}

QVector<LayoutSP> JdfNode::findAllLayouts(const std::function<bool(const LayoutSP &)> &predicate) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);

    QVector<LayoutSP> result;
    QVector<JdfNodeSP> queue = {castedSelf};
    QVector<LayoutSP> layoutsQueue;
    while (queue.count()) {
        layoutsQueue.resize(0);
        auto head = queue.takeFirst();
        layoutsQueue << head->resourcePool()->layouts();
        while (layoutsQueue.count()) {
            auto layout = layoutsQueue.takeFirst();
            if (predicate(layout))
                result << layout;
            layoutsQueue << layout->parts();
        }
        queue << head->jdfNodes();
    }
    return result;
}

JdfNodeQmlWrapper *JdfNode::toQmlWrapper(QObject *parent) const
{
    JdfNodeSP castedSelf = castedSelfPtr<JdfNode>();
    Q_ASSERT(castedSelf);
    return new JdfNodeQmlWrapper(castedSelf, parent);
}

JdfNodeSP JdfNode::create()
{
    JdfNodeSP result(new JdfNode());
    initSelfWeakPtr(result);
    return result;
}

JdfNodeSP JdfNode::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId,
                           const QStringList &alternativeIdAttributes, bool sanitize)
{
    JdfNodeSP document = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "JDF") {
                if (!document->isFetched()) {
                    document->setFetched(true);
                    QXmlStreamAttributes attributes = xmlReader.attributes();
                    document->setId(attributes.value(QStringLiteral("ID")).toString());
                    document->setJobId(jobId.isEmpty() ? attributes.value(QStringLiteral("JobID")).toString() : jobId);
                    document->setJobPartId(attributes.value(QStringLiteral("JobPartID")).toString());
                    document->setType(attributes.value(QStringLiteral("Type")).toString());
                    QString loweredType = document->type().toLower();
                    if (loweredType == QLatin1String("processgroup") || loweredType == QLatin1String("combined")) {
                        QStringList rawTypes =
                            attributes.value(QStringLiteral("Types")).toString().split(QStringLiteral(" "));
                        QStringList types;
                        for (auto type : rawTypes) {
                            type = type.trimmed();
                            if (!type.isEmpty())
                                types << type;
                        }
                        document->setTypes(types);
                    }

                    if (document->id().isEmpty()) {
                        for (const QString &attribute : alternativeIdAttributes) {
                            if (!attributes.hasAttribute(attribute))
                                continue;
                            document->setId(attributes.value(attribute).toString());
                            if (!document->id().isEmpty())
                                break;
                        }
                    }
                } else {
                    JdfNodeSP jdfNode = JdfNode::fromJdf(xmlReader, document->jobId(), alternativeIdAttributes, sanitize);
                    if (!jdfNode) {
                        qCWarning(proofNetworkJdfDataLog) << "JDF not created. Sub JDF node is invalid.";
                        return JdfNodeSP();
                    }
                    document->d_func()->jdfNodes << jdfNode;
                }
            } else if (xmlReader.name() == "AuditPool") {
                auto auditPool = AuditPool::fromJdf(xmlReader);
                if (!auditPool) {
                    qCWarning(proofNetworkJdfDataLog) << "JDF not created. AuditPool is invalid.";
                    return JdfNodeSP();
                }
                document->setAuditPool(auditPool);
            } else if (xmlReader.name() == "ResourcePool") {
                auto resourcePool = ResourcePool::fromJdf(xmlReader, document->jobId(), sanitize);
                if (!resourcePool) {
                    qCWarning(proofNetworkJdfDataLog) << "JDF not created. ResourcePool is invalid.";
                    return JdfNodeSP();
                }
                document->setResourcePool(resourcePool);
            } else if (xmlReader.name() == "ResourceLinkPool") {
                auto resourceLinkPool = ResourceLinkPool::fromJdf(xmlReader);
                if (!resourceLinkPool) {
                    qCWarning(proofNetworkJdfDataLog) << "JDF not created. ResourceLinkPool is invalid.";
                    return JdfNodeSP();
                }
                document->setResourceLinkPool(resourceLinkPool);
            }
        } else if (xmlReader.isEndElement()) {
            if (xmlReader.name() == "JDF")
                return document;
        }

        xmlReader.readNext();
    }

    return document;
}

void JdfNode::toJdf(QXmlStreamWriter &jdfWriter, bool rootNode)
{
    Q_D(JdfNode);

    jdfWriter.writeStartElement(QStringLiteral("JDF"));
    {
        jdfWriter.writeAttribute(QStringLiteral("ID"), d->id);
        if (!d->jobId.isEmpty())
            jdfWriter.writeAttribute(QStringLiteral("JobID"), d->jobId);
        if (!d->jobPartId.isEmpty())
            jdfWriter.writeAttribute(QStringLiteral("JobPartID"), d->jobPartId);
        if (!d->type.isEmpty())
            jdfWriter.writeAttribute(QStringLiteral("Type"), d->type);
        if (!d->types.isEmpty()
            && (!d->type.compare(QLatin1String("processgroup"), Qt::CaseInsensitive)
                || !d->type.compare(QLatin1String("combined"), Qt::CaseInsensitive))) {
            jdfWriter.writeAttribute(QStringLiteral("Types"), d->types.join(QStringLiteral(" ")));
        }

        jdfWriter.writeAttribute(QStringLiteral("Status"), QStringLiteral("Waiting"));
        if (rootNode)
            jdfWriter.writeAttribute(QStringLiteral("Version"), QStringLiteral("1.5"));
        if (isValidAndDirty(d->auditPool))
            d->auditPool->toJdf(jdfWriter);
        if (isValidAndDirty(d->resourcePool))
            d->resourcePool->toJdf(jdfWriter);
        if (isValidAndDirty(d->resourceLinkPool))
            d->resourceLinkPool->toJdf(jdfWriter);
        for (const JdfNodeSP &jdf : qAsConst(d->jdfNodes))
            jdf->toJdf(jdfWriter);
    }
    jdfWriter.writeEndElement();
}

JdfNode::JdfNode() : NetworkDataEntity(*new JdfNodePrivate)
{}

JdfNode::JdfNode(JdfNodePrivate &dd) : NetworkDataEntity(dd)
{}

Proof::Jdf::JdfNodePrivate::JdfNodePrivate()
{
    registerChildren(auditPool, resourcePool, resourceLinkPool, jdfNodes);
}

void JdfNode::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    JdfNodeSP castedOther = qSharedPointerCast<JdfNode>(other);
    setId(castedOther->id());
    setJobId(castedOther->jobId());
    setJobPartId(castedOther->jobPartId());
    setType(castedOther->type());
    setTypes(castedOther->types());
    setAuditPool(castedOther->auditPool());
    setResourcePool(castedOther->resourcePool());
    setResourceLinkPool(castedOther->resourceLinkPool());
    setJdfNodes(castedOther->jdfNodes());
    NetworkDataEntity::updateSelf(other);
}
