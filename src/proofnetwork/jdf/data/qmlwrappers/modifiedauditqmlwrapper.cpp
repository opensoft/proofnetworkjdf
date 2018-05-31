#include "modifiedauditqmlwrapper.h"

#include "proofnetwork/jdf/data/modifiedaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class ModifiedAuditQmlWrapperPrivate : public AbstractAuditQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ModifiedAuditQmlWrapper)
};

ModifiedAuditQmlWrapper::ModifiedAuditQmlWrapper(const ModifiedAuditSP &modifiedAudit, QObject *parent)
    : AbstractAuditQmlWrapper(modifiedAudit, *new ModifiedAuditQmlWrapperPrivate, parent)
{
    setupEntity();
}

ModifiedAuditQmlWrapper::~ModifiedAuditQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(ModifiedAudit)

void ModifiedAuditQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> & /*old*/)
{}

} // namespace Jdf
} // namespace Proof
