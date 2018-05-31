#ifndef PROOF_JDF_AUDITPOOL_H
#define PROOF_JDF_AUDITPOOL_H

#include "proofnetwork/jdf/data/qmlwrappers/auditpoolqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AuditPoolPrivate;
class PROOF_NETWORK_JDF_EXPORT AuditPool : public NetworkDataEntity // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AuditPool)
public:
    CreatedAuditSP created() const;
    ModifiedAuditSP modified() const;

    void setCreated(const CreatedAuditSP &created);
    void setModified(const ModifiedAuditSP &modified);

    AuditPoolQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static AuditPoolSP create();

    static AuditPoolSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void createdChanged(const Proof::Jdf::CreatedAuditSP &arg);
    void modifiedChanged(const Proof::Jdf::ModifiedAuditSP &arg);

protected:
    explicit AuditPool();
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_AUDITPOOL_H
