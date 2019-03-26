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
    AuditNotification &operator=(const AuditNotification &) = delete;
    AuditNotification(AuditNotification &&) = delete;
    AuditNotification &operator=(AuditNotification &&) = delete;
    ~AuditNotification() = default;

    Severity severityClass() const;
    void setSeverityClass(Severity arg);

    static AuditNotificationSP create();

    static AuditNotificationSP fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document = XJdfDocumentSP());
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void severityClassChanged(Proof::XJdf::Severity severity);

protected:
    explicit AuditNotification();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_AUDITNOTIFICATION_H
