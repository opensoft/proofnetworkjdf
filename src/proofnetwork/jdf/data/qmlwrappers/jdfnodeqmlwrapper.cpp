#include "jdfnodeqmlwrapper.h"

#include "proofnetwork/jdf/data/auditpool.h"
#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/qmlwrappers/auditpoolqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/resourcepoolqmlwrapper.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class JdfNodeQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(JdfNodeQmlWrapper)

    void updateAuditPool();
    void updateResourcePool();

    void updateJdfNodes();

    static JdfNodeQmlWrapper *jdfNodeAt(QQmlListProperty<JdfNodeQmlWrapper> *property, int index);
    static int jdfNodesCount(QQmlListProperty<JdfNodeQmlWrapper> *property);

    AuditPoolQmlWrapper *auditPool = nullptr;
    ResourcePoolQmlWrapper *resourcePool = nullptr;
    QVector<JdfNodeQmlWrapper *> jdfNodes;
    QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper> qmlJdfNodes;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

JdfNodeQmlWrapper::JdfNodeQmlWrapper(const JdfNodeSP &jdfNode, QObject *parent)
    : NetworkDataEntityQmlWrapper(jdfNode, *new JdfNodeQmlWrapperPrivate, parent)
{
    setupEntity();
}

JdfNodeQmlWrapper::~JdfNodeQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(JdfNode)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(JdfNode, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(JdfNode, QString, jobId)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(JdfNode, QString, jobPartId)

AuditPoolQmlWrapper *JdfNodeQmlWrapper::auditPool() const
{
    Q_D(const JdfNodeQmlWrapper);
    return d->auditPool;
}

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
    connect(jdfDoc.data(), &JdfNode::auditPoolChanged, entityConnectContext(), [d] { d->updateAuditPool(); });
    connect(jdfDoc.data(), &JdfNode::resourcePoolChanged, entityConnectContext(), [d] { d->updateResourcePool(); });
    connect(jdfDoc.data(), &JdfNode::jdfNodesChanged, entityConnectContext(), [d] { d->updateJdfNodes(); });

    d->updateResourcePool();

    JdfNodeSP oldJdfDoc = qSharedPointerCast<JdfNode>(old);
    if (oldJdfDoc) {
        if (jdfDoc->id() != oldJdfDoc->id())
            emit idChanged(jdfDoc->id());
        if (jdfDoc->jobId() != oldJdfDoc->jobId())
            emit jobIdChanged(jdfDoc->jobId());
        if (jdfDoc->jobPartId() != oldJdfDoc->jobPartId())
            emit jobPartIdChanged(jdfDoc->jobPartId());
    }
}

void JdfNodeQmlWrapperPrivate::updateAuditPool()
{
    Q_Q(JdfNodeQmlWrapper);
    JdfNodeSP jdfDoc = q->entity<JdfNode>();
    if (auditPool == nullptr)
        auditPool = jdfDoc->auditPool()->toQmlWrapper(q);
    else
        auditPool->setEntity(jdfDoc->auditPool());
    emit q->auditPoolChanged(auditPool);
}

void JdfNodeQmlWrapperPrivate::updateResourcePool()
{
    Q_Q(JdfNodeQmlWrapper);
    JdfNodeSP jdfDoc = q->entity<JdfNode>();
    if (resourcePool == nullptr)
        resourcePool = jdfDoc->resourcePool()->toQmlWrapper(q);
    else
        resourcePool->setEntity(jdfDoc->resourcePool());
    emit q->resourcePoolChanged(resourcePool);
}

void JdfNodeQmlWrapperPrivate::updateJdfNodes()
{
    Q_Q(JdfNodeQmlWrapper);
    JdfNodeSP jdfNode = q->entity<JdfNode>();
    for (JdfNodeQmlWrapper *wrapper : qAsConst(jdfNodes))
        wrapper->deleteLater();

    jdfNodes.clear();
    const auto allNdeNodes = jdfNode->jdfNodes();
    for (const JdfNodeSP &node : allNdeNodes)
        jdfNodes << node->toQmlWrapper(q);

    qmlJdfNodes = QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>(q, &jdfNodes, &JdfNodeQmlWrapperPrivate::jdfNodesCount,
                                                                  &JdfNodeQmlWrapperPrivate::jdfNodeAt);
    emit q->jdfNodesChanged(qmlJdfNodes);
}

JdfNodeQmlWrapper *JdfNodeQmlWrapperPrivate::jdfNodeAt(QQmlListProperty<JdfNodeQmlWrapper> *property, int index)
{
    return static_cast<QVector<JdfNodeQmlWrapper *> *>(property->data)->at(index);
}

int JdfNodeQmlWrapperPrivate::jdfNodesCount(QQmlListProperty<JdfNodeQmlWrapper> *property)
{
    return static_cast<QVector<JdfNodeQmlWrapper *> *>(property->data)->count();
}
