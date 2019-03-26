#ifndef XJDF_AUDITABSTRACTITEM_H
#define XJDF_AUDITABSTRACTITEM_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class AuditAbstractItemPrivate;
class PROOF_NETWORK_XJDF_EXPORT AuditAbstractItem : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AuditAbstractItem)
public:
    AuditAbstractItem(const AuditAbstractItem &) = delete;
    AuditAbstractItem &operator=(const XJdfAbstractNode &) = delete;
    AuditAbstractItem(XJdfAbstractNode &&) = delete;
    AuditAbstractItem &operator=(Resource &&) = delete;
    ~AuditAbstractItem() = default;

    QString agentName() const;
    QString agentVersion() const;
    QDateTime timestamp() const;
    QString id() const;
    QString deviceId() const;

    void setAgentName(const QString &arg);
    void setAgentVersion(const QString &arg);
    void setTimestamp(const QDateTime &arg);
    void setId(const QString &arg);
    void setDeviceId(const QString &arg);

    bool fillFromXJdf(QXmlStreamReader &reader) override;
    void readAttributesFromXJdf(QXmlStreamReader &reader) override;
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void agentNameChanged(const QString &arg);
    void agentVersionChanged(const QString &arg);
    void timestampChanged(const QDateTime &arg);
    void idChanged(const QString &arg);
    void deviceIdChanged(const QString &arg);

protected:
    explicit AuditAbstractItem();
    explicit AuditAbstractItem(AuditAbstractItemPrivate &dd);
    void updateSelf(const NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_AUDITABSTRACTITEM_H
