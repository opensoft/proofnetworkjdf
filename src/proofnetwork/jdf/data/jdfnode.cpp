#include "jdfdocument.h"

#include "proofnetwork/jdf/data/jdfnode_p.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfnodeqmlwrapper.h"
#include "proofnetwork/jdf/data/component.h"

#include "proofcore/proofglobal.h"

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

QStringList JdfNode::types() const
{
    Q_D(const JdfNode);
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

JdfNodeSP Proof::Jdf::JdfNode::findNode(const std::function<bool (const JdfNodeSP &)> &predicate) const
{
    Q_D(const JdfNode);
    JdfNodeSP castedSelf = qSharedPointerCast<JdfNode>(d->weakSelf);
    Q_ASSERT(castedSelf);
    if (predicate(castedSelf))
        return castedSelf;

    for (const auto &node : d->jdfNodes) {
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


QList<JdfNodeSP> JdfNode::findAllNodes(const std::function<bool (const JdfNodeSP &)> &predicate) const
{
    Q_D(const JdfNode);
    QList<JdfNodeSP> result;
    JdfNodeSP castedSelf = qSharedPointerCast<JdfNode>(d->weakSelf);
    Q_ASSERT(castedSelf);
    if (predicate(castedSelf))
        result << castedSelf;

    std::for_each(d->jdfNodes.cbegin(), d->jdfNodes.cend(), [&result, predicate](const JdfNodeSP &node){result.append(node->findAllNodes(predicate));});
    return result;
}

QList<ComponentSP> JdfNode::findAllComponents(const std::function<bool (const ComponentSP &)> &predicate) const
{
    Q_D(const JdfNode);
    QList<ComponentSP> result;
    const auto allComponents = resourcePool()->components();
    for (const auto &component : allComponents) {
        if (predicate(component))
            result << component;
        const auto componentParts = component->parts();
        for (const auto &componentOther : componentParts) {
            if (predicate(componentOther))
                result << componentOther;
        }
    }

    std::for_each(d->jdfNodes.cbegin(), d->jdfNodes.cend(), [&result, predicate](const JdfNodeSP &node){result.append(node->findAllComponents(predicate));});
    return result;
}

QList<ComponentLinkSP> JdfNode::findAllComponentLinks(const std::function<bool (const ComponentLinkSP &)> &predicate) const
{
    Q_D(const JdfNode);
    auto result = algorithms::filter(resourceLinkPool()->componentLinks(), predicate);
    std::for_each(d->jdfNodes.cbegin(), d->jdfNodes.cend(), [&result, predicate](const JdfNodeSP &node){result.append(node->findAllComponentLinks(predicate));});
    return result;
}

QList<MediaSP> JdfNode::findAllMedia(const std::function<bool (const MediaSP &)> &predicate) const
{
    Q_D(const JdfNode);
    auto result = algorithms::filter(resourcePool()->media(), predicate);
    std::for_each(d->jdfNodes.cbegin(), d->jdfNodes.cend(), [&result, predicate](const JdfNodeSP &node){result.append(node->findAllMedia(predicate));});
    return result;
}

QList<LayoutSP> JdfNode::findAllLayouts(const std::function<bool (const LayoutSP &)> &predicate) const
{
    Q_D(const JdfNode);
    auto result = algorithms::filter(resourcePool()->layouts(), predicate);
    std::for_each(d->jdfNodes.cbegin(), d->jdfNodes.cend(), [&result, predicate](const JdfNodeSP &node){result.append(node->findAllLayouts(predicate));});
    return result;
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
                    QString loweredType = document->type().toLower();
                    if (loweredType == QLatin1String("processgroup") || loweredType == QLatin1String("combined")) {
                        QStringList rawTypes = attributes.value(QStringLiteral("Types")).toString().split(" ");
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
            jdfWriter.writeAttribute(QStringLiteral("Types"), d->types.join(" "));
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
    q->setTypes(castedOther->types());
    q->setAuditPool(castedOther->auditPool());
    q->setResourcePool(castedOther->resourcePool());
    q->setResourceLinkPool(castedOther->resourceLinkPool());
    q->setJdfNodes(castedOther->jdfNodes());
    NetworkDataEntityPrivate::updateFrom(other);
}
