#ifndef PROOF_JDF_MODIFIEDAUDIT_H
#define PROOF_JDF_MODIFIEDAUDIT_H

#include "proofnetwork/jdf/data/abstractaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/modifiedauditqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class ModifiedAuditPrivate;
class PROOF_NETWORK_JDF_EXPORT ModifiedAudit : public AbstractAudit
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ModifiedAudit)
public:
    ModifiedAuditQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static ModifiedAuditSP create();

    static ModifiedAuditSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;

protected:
    explicit ModifiedAudit();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_MODIFIEDAUDIT_H
