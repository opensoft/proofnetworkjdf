#include "jdfdocument.h"

#include "proofnetwork/jdf/data/jdfnode_p.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfnodeqmlwrapper.h"
#include "proofnetwork/jdf/data/component.h"

#include <set>

using namespace Proof::Jdf;

QString JdfNode::id() const
{
    Q_D(const JdfNode);
    return d->id;
}

QString JdfNode::jobId() const
{
    Q_D(const JdfNode);
    return d->jobId;
}

QString JdfNode::jobPartId() const
{
    Q_D(const JdfNode);
    return d->jobPartId;
}

AuditPoolSP JdfNode::auditPool() const
{
    Q_D(const JdfNode);
    return d->auditPool;
}

ResourcePoolSP JdfNode::resourcePool() const
{
    Q_D(const JdfNode);
    return d->resourcePool;
}

ResourceLinkPoolSP JdfNode::resourceLinkPool() const
{
    Q_D(const JdfNode);
    return d->resourceLinkPool;
}

QList<JdfNodeSP> JdfNode::jdfNodes() const
{
    Q_D(const JdfNode);
    return d->jdfNodes;
}

QString JdfNode::type() const
{
    Q_D(const JdfNode);
    return d->type;
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

void JdfNode::setJdfNodes(const QList<JdfNodeSP> &arg)
{
    Q_D(JdfNode);
    std::multiset<QString> newIds;
    for (const auto &node : arg)
        newIds.insert(node->id());

    std::multiset<QString> oldIds;
    for (const auto &node : d->jdfNodes)
        oldIds.insert(node->id());

    if (newIds != oldIds) {
        d->jdfNodes = arg;
        emit jdfNodesChanged();
    }
}

void JdfNode::setType(const QString &arg)
{
    Q_D(JdfNode);
    if (arg != d->type) {
        d->type = arg;
        emit typeChanged(d->type);
    }
}

JdfNodeSP Proof::Jdf::JdfNode::findNode(const std::function<bool (const JdfNodeSP &)> &predicate) const
{
    Q_D(const JdfNode);
    JdfNodeSP castedSelf = qSharedPointerCast<JdfNode>(d->weakSelf);
    Q_ASSERT(castedSelf);
    if (predicate(castedSelf))
        return castedSelf;

    for (const auto &node : d->jdfNodes) {
        if (predicate(node))
            return node;

        auto result = node->findNode(predicate);
        if (result)
            return result;
    }
    return JdfNodeSP();
}

ComponentSP Proof::Jdf::JdfNode::findComponent(const std::function<bool (const ComponentSP &)> &predicate) const
{
    Q_D(const JdfNode);
    const auto allComponents = resourcePool()->components();
    for (const auto &component : allComponents) {
        if (predicate(component))
            return component;
        const auto componentParts = component->parts();
        for (const auto &componentOther : componentParts) {
            if (predicate(componentOther))
                return componentOther;
        }
    }

    for (const auto &node : d->jdfNodes) {
        auto result = node->findComponent(predicate);
        if (result)
            return result;
    }
    return ComponentSP();
}

ComponentLinkSP JdfNode::findComponentLink(const std::function<bool (const ComponentLinkSP &)> &predicate) const
{
    Q_D(const JdfNode);
    const auto allComponentLinks = resourceLinkPool()->componentLinks();
    for (const auto &componentLink : allComponentLinks) {
        if (predicate(componentLink))
            return componentLink;
    }

    for (const auto &node : d->jdfNodes) {
        auto result = node->findComponentLink(predicate);
        if (result)
            return result;
    }
    return ComponentLinkSP();
}

MediaSP JdfNode::findMedia(const std::function<bool (const MediaSP &)> &predicate) const
{
    Q_D(const JdfNode);
    const auto allMedia = resourcePool()->media();
    for (const auto &media : allMedia) {
        if (predicate(media))
            return media;
    }

    for (const Proof::Jdf::JdfNodeSP &node : d->jdfNodes) {
        auto result = node->findMedia(predicate);
        if (result)
            return result;
    }
    return MediaSP();
}

LayoutSP JdfNode::findLayout(const std::function<bool (const LayoutSP &)> &predicate) const
{
    Q_D(const JdfNode);
    const auto allLayouts = resourcePool()->layouts();
    for (const auto &layout : allLayouts) {
        if (predicate(layout))
            return layout;
    }

    for (const Proof::Jdf::JdfNodeSP &node : d->jdfNodes) {
        auto result = node->findLayout(predicate);
        if (result)
            return result;
    }
    return LayoutSP();
}

JdfNodeQmlWrapper *JdfNode::toQmlWrapper(QObject *parent) const
{
    Q_D(const JdfNode);
    JdfNodeSP castedSelf = qSharedPointerCast<JdfNode>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new JdfNodeQmlWrapper(castedSelf, parent);
}

JdfNodeSP JdfNode::create()
{
    JdfNodeSP result(new JdfNode());
    initSelfWeakPtr(result);
    return result;
}

JdfNodeSP JdfNode::fromJdf(QXmlStreamReader &xmlReader, const QStringList &alternativeIdAttributes, bool sanitize)
{
    JdfNodeSP document = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "JDF") {
                if (!document->isFetched()) {
                    document->setFetched(true);
                    QXmlStreamAttributes attributes = xmlReader.attributes();
                    document->setId(attributes.value(QStringLiteral("ID")).toString());
                    document->setJobId(attributes.value(QStringLiteral("JobID")).toString());
                    document->setJobPartId(attributes.value(QStringLiteral("JobPartID")).toString());
                    document->setType(attributes.value(QStringLiteral("Type")).toString());

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
                    JdfNodeSP jdfNode = JdfNode::fromJdf(xmlReader, alternativeIdAttributes, sanitize);
                    if (!jdfNode) {
                        qCCritical(proofNetworkJdfDataLog) << "JDF not created. Sub JDF node is invalid.";
                        return JdfNodeSP();
                    }
                    document->d_func()->jdfNodes << jdfNode;
                }
            } else if (xmlReader.name() == "AuditPool") {
                auto auditPool = AuditPool::fromJdf(xmlReader);
                if (!auditPool) {
                    qCCritical(proofNetworkJdfDataLog) << "JDF not created. AuditPool is invalid.";
                    return JdfNodeSP();
                }
                document->setAuditPool(auditPool);
            } else if (xmlReader.name() == "ResourcePool") {
                auto resourcePool = ResourcePool::fromJdf(xmlReader, document->jobId(), sanitize);
                if (!resourcePool) {
                    qCCritical(proofNetworkJdfDataLog) << "JDF not created. ResourcePool is invalid.";
                    return JdfNodeSP();
                }
                document->setResourcePool(resourcePool);
            } else if (xmlReader.name() == "ResourceLinkPool") {
                auto resourceLinkPool = ResourceLinkPool::fromJdf(xmlReader);
                if (!resourceLinkPool) {
                    qCCritical(proofNetworkJdfDataLog) << "JDF not created. ResourceLinkPool is invalid.";
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

void JdfNode::toJdf(QXmlStreamWriter &jdfWriter)
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

        jdfWriter.writeAttribute(QStringLiteral("Status"), QStringLiteral("Waiting"));
        jdfWriter.writeAttribute(QStringLiteral("Version"), QStringLiteral("1.4"));
        if (isValidAndDirty(d->auditPool))
            d->auditPool->toJdf(jdfWriter);
        if (isValidAndDirty(d->resourcePool))
            d->resourcePool->toJdf(jdfWriter);
        if (isValidAndDirty(d->resourceLinkPool))
            d->resourceLinkPool->toJdf(jdfWriter);
        for (const JdfNodeSP &jdf: qAsConst(d->jdfNodes))
            jdf->toJdf(jdfWriter);
    }
    jdfWriter.writeEndElement();
}

JdfNode::JdfNode()
    : NetworkDataEntity(*new JdfNodePrivate)
{
}

JdfNode::JdfNode(JdfNodePrivate &dd, QObject *parent)
    : NetworkDataEntity(dd, parent)
{
}

Proof::Jdf::JdfNodePrivate::JdfNodePrivate()
{
    registerChildren(auditPool, resourcePool, resourceLinkPool, jdfNodes);
}

void JdfNodePrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(JdfNode);
    JdfNodeSP castedOther = qSharedPointerCast<JdfNode>(other);
    q->setId(castedOther->id());
    q->setJobId(castedOther->jobId());
    q->setJobPartId(castedOther->jobPartId());
    q->setType(castedOther->type());
    q->setAuditPool(castedOther->auditPool());
    q->setResourcePool(castedOther->resourcePool());
    q->setResourceLinkPool(castedOther->resourceLinkPool());
    q->setJdfNodes(castedOther->jdfNodes());
    NetworkDataEntityPrivate::updateFrom(other);
}
