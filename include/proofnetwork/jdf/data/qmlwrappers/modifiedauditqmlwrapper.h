#ifndef PROOF_JDF_MODIFIEDAUDITQMLWRAPPER_H
#define PROOF_JDF_MODIFIEDAUDITQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class ModifiedAudit;

class ModifiedAuditQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT ModifiedAuditQmlWrapper : public AbstractAuditQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ModifiedAuditQmlWrapper)
public:
    explicit ModifiedAuditQmlWrapper(const ModifiedAuditSP &modifiedAudit, QObject *parent = nullptr);
    ~ModifiedAuditQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(ModifiedAudit)

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_MODIFIEDAUDITQMLWRAPPER_H
