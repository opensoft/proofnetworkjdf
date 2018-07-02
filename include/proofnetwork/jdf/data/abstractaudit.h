#ifndef PROOF_JDF_ABSTRACTAUDIT_H
#define PROOF_JDF_ABSTRACTAUDIT_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QDateTime>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractAuditPrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractAudit : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractAudit)
public:
    QString id() const;
    QString agentName() const;
    QString agentVersion() const;
    QDateTime timeStamp() const;

    void setId(const QString &arg);
    void setAgentName(const QString &arg);
    void setAgentVersion(const QString &arg);
    void setTimeStamp(const QDateTime &arg);

    static bool fromJdf(const QXmlStreamReader &xmlReader, AbstractAuditSP &abstractAudit);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void idChanged(const QString &arg);
    void agentNameChanged(const QString &arg);
    void agentVersionChanged(const QString &arg);
    void timeStampChanged(const QDateTime &arg);

protected:
    explicit AbstractAudit() = delete;
    AbstractAudit(AbstractAuditPrivate &dd);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_ABSTRACTAUDIT_H
