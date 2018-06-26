#include "auditpoolqmlwrapper.h"

#include "createdauditqmlwrapper.h"
#include "modifiedauditqmlwrapper.h"

#include "proofnetwork/jdf/data/auditpool.h"
#include "proofnetwork/jdf/data/createdaudit.h"
#include "proofnetwork/jdf/data/modifiedaudit.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class AuditPoolQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(AuditPoolQmlWrapper)
    void updateCreated();
    void updateModified();

    CreatedAuditQmlWrapper *created = nullptr;
    ModifiedAuditQmlWrapper *modified = nullptr;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

AuditPoolQmlWrapper::AuditPoolQmlWrapper(const AuditPoolSP &auditPool, QObject *parent)
    : NetworkDataEntityQmlWrapper(auditPool, *new AuditPoolQmlWrapperPrivate, parent)
{
    setupEntity();
}

AuditPoolQmlWrapper::~AuditPoolQmlWrapper()
{}

CreatedAuditQmlWrapper *AuditPoolQmlWrapper::created() const
{
    Q_D(const AuditPoolQmlWrapper);
    return d->created;
}

ModifiedAuditQmlWrapper *AuditPoolQmlWrapper::modified() const
{
    Q_D(const AuditPoolQmlWrapper);
    return d->modified;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(AuditPool)

void AuditPoolQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(AuditPoolQmlWrapper);
    Q_UNUSED(old)
    AuditPoolSP auditPool = entity<AuditPool>();
    Q_ASSERT(auditPool);

    connect(auditPool.data(), &AuditPool::createdChanged, entityConnectContext(), [d]() { d->updateCreated(); });
    connect(auditPool.data(), &AuditPool::modifiedChanged, entityConnectContext(), [d]() { d->updateModified(); });

    d->updateCreated();
    d->updateModified();
}

void AuditPoolQmlWrapperPrivate::updateCreated()
{
    Q_Q(AuditPoolQmlWrapper);
    AuditPoolSP auditPool = q->entity<AuditPool>();
    if (created == nullptr)
        created = auditPool->created()->toQmlWrapper(q);
    else
        created->setEntity(auditPool->created());
    emit q->createdChanged(created);
}

void AuditPoolQmlWrapperPrivate::updateModified()
{
    Q_Q(AuditPoolQmlWrapper);
    AuditPoolSP auditPool = q->entity<AuditPool>();
    if (modified == nullptr)
        modified = auditPool->modified()->toQmlWrapper(q);
    else
        modified->setEntity(auditPool->modified());
    emit q->modifiedChanged(modified);
}
