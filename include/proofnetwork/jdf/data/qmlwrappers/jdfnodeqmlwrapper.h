#ifndef JDFJDFNODEQMLWRAPPER_H
#define JDFJDFNODEQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

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

}
}

#endif // JDFJDFNODEQMLWRAPPER_H
