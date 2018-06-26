#ifndef PROOF_JDF_CREATEDAUDIT_H
#define PROOF_JDF_CREATEDAUDIT_H

#include "proofnetwork/jdf/data/abstractaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/createdauditqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class CreatedAuditPrivate;
class PROOF_NETWORK_JDF_EXPORT CreatedAudit : public AbstractAudit // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CreatedAudit)
public:
    QString templateId() const;
    QString templateVersion() const;

    void setTemplateId(const QString &templateId);
    void setTemplateVersion(const QString &templateVersion);

    CreatedAuditQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static CreatedAuditSP create();

    static CreatedAuditSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;

signals:
    void templateIdChanged(const QString &arg);
    void templateVersionChanged(const QString &arg);

protected:
    explicit CreatedAudit();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_CREATEDAUDIT_H
