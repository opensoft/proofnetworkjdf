#include "createdauditqmlwrapper.h"

#include "proofnetwork/jdf/data/createdaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class CreatedAuditQmlWrapperPrivate : public AbstractAuditQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CreatedAuditQmlWrapper)
};

CreatedAuditQmlWrapper::CreatedAuditQmlWrapper(const CreatedAuditSP &createdAudit, QObject *parent)
    : AbstractAuditQmlWrapper(createdAudit, *new CreatedAuditQmlWrapperPrivate, parent)
{
    setupEntity();
}

CreatedAuditQmlWrapper::~CreatedAuditQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(CreatedAudit)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CreatedAudit, QString, templateId)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CreatedAudit, QString, templateVersion)

void CreatedAuditQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    CreatedAuditSP createdAudit = entity<CreatedAudit>();
    Q_ASSERT(createdAudit);

    connect(createdAudit.data(), &CreatedAudit::templateIdChanged, this, &CreatedAuditQmlWrapper::templateIdChanged);
    connect(createdAudit.data(), &CreatedAudit::templateVersionChanged, this,
            &CreatedAuditQmlWrapper::templateVersionChanged);

    CreatedAuditSP oldCreatedAudit = qSharedPointerCast<CreatedAudit>(old);
    if (oldCreatedAudit) {
        if (createdAudit->templateId() != oldCreatedAudit->templateId())
            emit templateIdChanged(createdAudit->templateId());
        if (createdAudit->templateVersion() != oldCreatedAudit->templateVersion())
            emit templateVersionChanged(createdAudit->templateVersion());
    }
}

} // namespace Jdf
} // namespace Proof
