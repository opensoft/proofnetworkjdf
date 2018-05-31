#ifndef ABSTRACTAUDITQMLWRAPPER_H
#define ABSTRACTAUDITQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"

#include <QDateTime>

namespace Proof {
namespace Jdf {

class AbstractAuditQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractAuditQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(QString agentName READ agentName NOTIFY agentNameChanged)
    Q_PROPERTY(QString agentVersion READ agentVersion NOTIFY agentVersionChanged)
    Q_PROPERTY(QDateTime timeStamp READ timeStamp NOTIFY timeStampChanged)

    Q_DECLARE_PRIVATE(AbstractAuditQmlWrapper)
public:
    explicit AbstractAuditQmlWrapper(const QSharedPointer<AbstractAudit> &abstractAudit,
                                     AbstractAuditQmlWrapperPrivate &dd, QObject *parent = nullptr);
    ~AbstractAuditQmlWrapper();

    QString id() const;
    QString agentName() const;
    QString agentVersion() const;
    QDateTime timeStamp() const;

signals:
    void idChanged(const QString &id);
    void agentNameChanged(const QString &id);
    void agentVersionChanged(const QString &id);
    void timeStampChanged(const QDateTime &id);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // ABSTRACTAUDITQMLWRAPPER_H
