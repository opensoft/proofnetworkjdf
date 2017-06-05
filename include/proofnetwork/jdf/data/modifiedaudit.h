#ifndef PROOF_JDF_MODIFIEDAUDIT_H
#define PROOF_JDF_MODIFIEDAUDIT_H

#include "proofnetwork/jdf/data/abstractaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/modifiedauditqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class ModifiedAuditPrivate;
class PROOF_NETWORK_JDF_EXPORT ModifiedAudit : public AbstractAudit // clazy:exclude=ctor-missing-parent-argument
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

};

}
}

#endif // PROOF_JDF_MODIFIEDAUDIT_H
