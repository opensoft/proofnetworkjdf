#ifndef XJDF_AUDITCREATED_H
#define XJDF_AUDITCREATED_H

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/auditabstractitem.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class AuditCreatedPrivate;
class PROOF_NETWORK_XJDF_EXPORT AuditCreated : public AuditAbstractItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AuditCreated)
public:
    AuditCreated(const AuditCreated &) = delete;
    AuditCreated &operator=(const AuditAbstractItem &) = delete;
    AuditCreated(XJdfAbstractNode &&) = delete;
    AuditCreated &operator=(Resource &&) = delete;
    ~AuditCreated() = default;

    QString templateId() const;
    QString templateVersion() const;

    void setTemplateId(const QString &arg);
    void setTemplateVersion(const QString &arg);

    static AuditCreatedSP create();

    static AuditCreatedSP fromXJdf(QXmlStreamReader &xjdfReader);
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;

signals:
    void templateIdChanged(const QString &arg);
    void templateVersionChanged(const QString &arg);

protected:
    AuditCreated();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_AUDITCREATED_H
