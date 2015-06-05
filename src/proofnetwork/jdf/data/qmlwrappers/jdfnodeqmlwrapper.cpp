#include "jdfnodeqmlwrapper.h"

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"
#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/qmlwrappers/resourcepoolqmlwrapper.h"

namespace Proof {
namespace Jdf {

class JdfNodeQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(JdfNodeQmlWrapper)

    void updateResourcePool();

    void updateJdfNodes();

    static JdfNodeQmlWrapper *jdfNodeAt(QQmlListProperty<JdfNodeQmlWrapper> *property, int index);
    static int jdfNodesCount(QQmlListProperty<JdfNodeQmlWrapper> *property);

    ResourcePoolQmlWrapper *resourcePool = nullptr;
    QList<JdfNodeQmlWrapper *> jdfNodes;
    QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper> qmlJdfNodes;
};

}
}

using namespace Proof::Jdf;

JdfNodeQmlWrapper::JdfNodeQmlWrapper(const JdfNodeSP &jdfNode, QObject *parent)
    : NetworkDataEntityQmlWrapper(jdfNode, *new JdfNodeQmlWrapperPrivate, parent)
{
    setupEntity();
}

JdfNodeQmlWrapper::~JdfNodeQmlWrapper()
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(JdfNode)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(JdfNode, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(JdfNode, QString, jobId)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(JdfNode, QString, jobPartId)



ResourcePoolQmlWrapper *JdfNodeQmlWrapper::resourcePool() const
{
    Q_D(const JdfNodeQmlWrapper);
    return d->resourcePool;
}

QQmlListProperty<JdfNodeQmlWrapper> JdfNodeQmlWrapper::jdfNodes() const
{
    Q_D(const JdfNodeQmlWrapper);
    return d->qmlJdfNodes;
}

void JdfNodeQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    Q_D(JdfNodeQmlWrapper);
    JdfNodeSP jdfDoc = entity<JdfNode>();
    Q_ASSERT(jdfDoc);

    connect(jdfDoc.data(), &JdfNode::idChanged, this, &JdfNodeQmlWrapper::idChanged);
    connect(jdfDoc.data(), &JdfNode::jobIdChanged, this, &JdfNodeQmlWrapper::jobIdChanged);
    connect(jdfDoc.data(), &JdfNode::jobPartIdChanged, this, &JdfNodeQmlWrapper::jobPartIdChanged);
    connect(jdfDoc.data(), &JdfNode::resourcePoolChanged, d->lambdaConnectContext, [d]{d->updateResourcePool();});
    connect(jdfDoc.data(), &JdfNode::jdfNodesChanged, d->lambdaConnectContext, [d]{d->updateJdfNodes();});

    d->updateResourcePool();

    JdfNodeSP oldJdfDoc = qSharedPointerCast<JdfNode>(old);
    if (oldJdfDoc) {
        if (jdfDoc->id() != oldJdfDoc->id())
            emit idChanged(jdfDoc->id());
        if (oldJdfDoc->jobId() != oldJdfDoc->jobId())
            emit jobIdChanged(oldJdfDoc->jobId());
        if (oldJdfDoc->jobPartId() != oldJdfDoc->jobPartId())
            emit jobPartIdChanged(oldJdfDoc->jobPartId());
    }
}

void JdfNodeQmlWrapperPrivate::updateResourcePool()
{
    Q_Q(JdfNodeQmlWrapper);
    JdfNodeSP jdfDoc = entity<JdfNode>();
    if (resourcePool == nullptr)
        resourcePool = jdfDoc->resourcePool()->toQmlWrapper(q);
    else
        resourcePool->setEntity(jdfDoc->resourcePool());
    emit q->resourcePoolChanged(resourcePool);
}

void JdfNodeQmlWrapperPrivate::updateJdfNodes()
{
    Q_Q(JdfNodeQmlWrapper);
    JdfNodeSP jdfNode = entity<JdfNode>();
    for (JdfNodeQmlWrapper *wrapper : jdfNodes)
        wrapper->deleteLater();

    jdfNodes.clear();
    for (const JdfNodeSP &node : jdfNode->jdfNodes())
        jdfNodes << node->toQmlWrapper(q);

    qmlJdfNodes = QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>(q, &jdfNodes,
                                                &JdfNodeQmlWrapperPrivate::jdfNodesCount,
                                                &JdfNodeQmlWrapperPrivate::jdfNodeAt);
    emit q->jdfNodesChanged(qmlJdfNodes);
}

JdfNodeQmlWrapper *JdfNodeQmlWrapperPrivate::jdfNodeAt(QQmlListProperty<JdfNodeQmlWrapper> *property, int index)
{
    return static_cast<QList<JdfNodeQmlWrapper *> *>(property->data)->at(index);
}

int JdfNodeQmlWrapperPrivate::jdfNodesCount(QQmlListProperty<JdfNodeQmlWrapper> *property)
{
    return static_cast<QList<JdfNodeQmlWrapper *> *>(property->data)->count();
}
