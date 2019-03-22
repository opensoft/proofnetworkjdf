#ifndef XJDF_AUDITNOTIFICATION_H
#define XJDF_AUDITNOTIFICATION_H

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/auditabstractitem.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class AuditNotificationPrivate;
class PROOF_NETWORK_XJDF_EXPORT AuditNotification : public AuditAbstractItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AuditNotification)
public:
    AuditNotification(const AuditNotification &) = delete;
    AuditNotification &operator=(const AuditAbstractItem &) = delete;
    AuditNotification(AuditAbstractItem &&) = delete;
    AuditNotification &operator=(Resource &&) = delete;
    ~AuditNotification() = default;

    Severity severityClass() const;
    void setSeverityClass(Severity arg);

    static AuditNotificationSP create();

    static AuditNotificationSP fromXJdf(QXmlStreamReader &xjdfReader);
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;

signals:
    void severityClassChanged(Severity severity);

protected:
    AuditNotification();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_AUDITNOTIFICATION_H
