#include "jdfdocument.h"

#include "proofnetwork/jdf/data/jdfnode_p.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfnodeqmlwrapper.h"


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

void JdfNode::setResourcePool(const ResourcePoolSP &arg)
{
    Q_D(JdfNode);
    if (arg == nullptr)
        setResourcePool(ResourcePool::create());
    else if (d->resourcePool != arg) {
        d->resourcePool = arg;
        emit resourcePoolChanged(d->resourcePool);
    }
}

void JdfNode::setResourceLinkPool(const ResourceLinkPoolSP &arg)
{
    Q_D(JdfNode);
    if (arg == nullptr)
        setResourceLinkPool(ResourceLinkPool::create());
    else if (d->resourceLinkPool != arg) {
        d->resourceLinkPool = arg;
        emit resourceLinkPoolChanged(d->resourceLinkPool);
    }
}

void JdfNode::setJdfNodes(const QList<JdfNodeSP> &jdfNodes)
{
    Q_D(JdfNode);

    // TODO: check if nodes really changed
    d->jdfNodes = jdfNodes;
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

JdfNodeSP Proof::Jdf::JdfNode::findSubNode(std::function<bool (const JdfNodeSP &)> predicate) const
{
    for (const Proof::Jdf::JdfNodeSP &node : jdfNodes()) {
        if (predicate(node))
            return node;

        Proof::Jdf::JdfNodeSP result = node->findSubNode(predicate);
        if (result)
            return result;
    }
    return Proof::Jdf::JdfNodeSP();
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

JdfNodeSP JdfNode::fromJdf(QXmlStreamReader &xmlReader)
{
    JdfNodeSP document = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "JDF") {
                if (!document->isFetched()) {
                    document->setFetched(true);
                    QXmlStreamAttributes attributes = xmlReader.attributes();
                    document->setId(attributes.value("ID").toString());
                    document->setJobId(attributes.value("JobID").toString());
                    document->setJobPartId(attributes.value("JobPartID").toString());
                    document->setType(attributes.value("Type").toString());
                } else {
                    JdfNodeSP jdfNode = JdfNode::fromJdf(xmlReader);
                    document->d_func()->jdfNodes.push_back(jdfNode);
                }
            }

            if (xmlReader.name() == "ResourcePool")
                document->setResourcePool(ResourcePool::fromJdf(xmlReader, document->id()));
            if (xmlReader.name() == "ResourceLinkPool")
                document->setResourceLinkPool(ResourceLinkPool::fromJdf(xmlReader));
        }

        if (xmlReader.isEndElement()) {
            if (xmlReader.name() == "JDF") {
                xmlReader.readNext();
                return document;
            }
        }

        xmlReader.readNext();
    }

    return document;
}

void JdfNode::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(JdfNode);

    jdfWriter.writeStartElement("JDF");
    {
        jdfWriter.writeAttribute("ID", d->id);
        if (!d->jobId.isEmpty())
            jdfWriter.writeAttribute("JobID", d->jobId);
        if (!d->jobPartId.isEmpty())
            jdfWriter.writeAttribute("JobPartID", d->jobPartId);
        if (!d->type.isEmpty())
            jdfWriter.writeAttribute("Type", d->type);

        jdfWriter.writeAttribute("Status", "Waiting");
        jdfWriter.writeAttribute("Version", "1.4");
        if (isValidAndDirty(d->resourcePool)) {
            d->resourcePool->toJdf(jdfWriter);
            d->resourceLinkPool->toJdf(jdfWriter);
        }
        for (const JdfNodeSP &jdf: jdfNodes())
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

void JdfNode::update(const JdfNodeSP &other)
{
    Q_D(JdfNode);
    d->updateFrom(other.dynamicCast<NetworkDataEntity>());
}

Proof::Jdf::JdfNodePrivate::JdfNodePrivate()
{
    registerChildren(resourcePool, resourceLinkPool, jdfNodes);
}

void JdfNodePrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(JdfNode);
    JdfNodeSP castedOther = qSharedPointerCast<JdfNode>(other);
    q->setId(castedOther->id());
    q->setJobId(castedOther->jobId());
    q->setJobPartId(castedOther->jobPartId());
    q->setType(castedOther->type());
    q->setResourcePool(castedOther->resourcePool());
    q->setResourceLinkPool(castedOther->resourceLinkPool());
    q->setJdfNodes(castedOther->jdfNodes());
    NetworkDataEntityPrivate::updateFrom(other);
}
