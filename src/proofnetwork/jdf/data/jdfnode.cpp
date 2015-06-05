#include "jdfdocument.h"

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfnodeqmlwrapper.h"

#include <QList>

namespace Proof {
namespace Jdf {

class JdfNodePrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(JdfNode)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString id;
    QString jobId;
    QString jobPartId;
    ResourcePoolSP resourcePool = ResourcePool::defaultObject();
    QList<JdfNodeSP> jdfNodes;
};

}
}

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

QList<JdfNodeSP> JdfNode::jdfNodes() const
{
    Q_D(const JdfNode);
    return d->jdfNodes;
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
        setResourcePool(ResourcePool::defaultObject());
    else if (d->resourcePool != arg) {
        d->resourcePool = arg;
        emit resourcePoolChanged(d->resourcePool);
    }
}

void JdfNode::setJdfNodes(const QList<JdfNodeSP> &jdfNodes)
{
    Q_D(JdfNode);
    bool changed = jdfNodes.count() != d->jdfNodes.count();
    for (int i = 0; i < jdfNodes.count() && !changed; ++i)
        changed = jdfNodes[i]->id() != d->jdfNodes[i]->id();

    if (changed) {
        d->jdfNodes = jdfNodes;
        emit jdfNodesChanged();
    }
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
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

JdfNodeSP JdfNode::fromJdf(QXmlStreamReader &xmlReader)
{
    // TODO: Change parsing
    JdfNodeSP document = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {        
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "JDF") {
                if (!document->isFetched()) {
                    document->setFetched(true);
                    QXmlStreamAttributes attributes = xmlReader.attributes();
                    if (attributes.value("Type").toString() == "Product") {
                        document->setId(attributes.value("ID").toString());
                        document->setJobId(attributes.value("JobID").toString());
                        document->setJobPartId(attributes.value("JobPartID").toString());
                    }
                } else {
                    JdfNodeSP jdfNode = JdfNode::fromJdf(xmlReader);
                    document->d_func()->jdfNodes.push_back(jdfNode);
                }
            }

            if (xmlReader.name() == "ResourcePool")
                document->setResourcePool(ResourcePool::fromJdf(xmlReader, document->id()));
            // TODO: Add parsing ResourceLinkPool
        }

        if (xmlReader.isEndElement()) {
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


    jdfWriter.writeStartElement("JDF");
    {
        jdfWriter.writeDefaultNamespace("http://www.CIP4.org/JDFSchema_1_1");
        jdfWriter.writeAttribute("ID", d->id);
        jdfWriter.writeAttribute("JobID", d->jobId);
        jdfWriter.writeAttribute("JobPartID", d->jobPartId);
        jdfWriter.writeAttribute("Status", "Waiting");
        jdfWriter.writeAttribute("Type", "Product");
        jdfWriter.writeAttribute("Version", "1.4");
        d->resourcePool->toJdf(jdfWriter);
        d->resourcePool->toJdfLink(jdfWriter);
    }
    jdfWriter.writeEndElement();
}

JdfNodeSP JdfNode::defaultObject()
{
    static JdfNodeSP entity = create();
    return entity;
}

JdfNode::JdfNode()
    : NetworkDataEntity(*new JdfNodePrivate)
{
}

void JdfNode::update(const JdfNodeSP &other)
{
    Q_D(JdfNode);
    d->updateFrom(other.dynamicCast<NetworkDataEntity>());
}

void JdfNodePrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(JdfNode);
    JdfNodeSP castedOther = qSharedPointerCast<JdfNode>(other);
    q->setId(castedOther->id());
    q->setJobId(castedOther->jobId());
    q->setJobPartId(castedOther->jobPartId());
    q->setResourcePool(castedOther->resourcePool());
    q->setJdfNodes(castedOther->jdfNodes());
    NetworkDataEntityPrivate::updateFrom(other);
}
