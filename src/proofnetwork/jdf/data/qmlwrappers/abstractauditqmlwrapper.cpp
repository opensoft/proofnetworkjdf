#include "abstractauditqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractaudit.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper_p.h"

using namespace Proof;
using namespace Proof::Jdf;

AbstractAuditQmlWrapper::AbstractAuditQmlWrapper(const AbstractAuditSP &abstractAudit,
                                                 AbstractAuditQmlWrapperPrivate &dd, QObject *parent)
    : NetworkDataEntityQmlWrapper(abstractAudit, dd, parent)
{
    setupEntity();
}

AbstractAuditQmlWrapper::~AbstractAuditQmlWrapper()
{}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractAudit, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractAudit, QString, agentName)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractAudit, QString, agentVersion)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractAudit, QDateTime, timeStamp)

void AbstractAuditQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(AbstractAuditQmlWrapper);
    AbstractAuditSP abstractAudit = d->entity<AbstractAudit>();
    Q_ASSERT(abstractAudit);

    connect(abstractAudit.data(), &AbstractAudit::idChanged, this, &AbstractAuditQmlWrapper::idChanged);
    connect(abstractAudit.data(), &AbstractAudit::agentNameChanged, this, &AbstractAuditQmlWrapper::agentNameChanged);
    connect(abstractAudit.data(), &AbstractAudit::agentVersionChanged, this,
            &AbstractAuditQmlWrapper::agentVersionChanged);
    connect(abstractAudit.data(), &AbstractAudit::timeStampChanged, this, &AbstractAuditQmlWrapper::timeStampChanged);

    AbstractAuditSP oldAbstractAudit = qSharedPointerCast<AbstractAudit>(old);
    if (oldAbstractAudit) {
        if (abstractAudit->id() != oldAbstractAudit->id())
            emit idChanged(abstractAudit->id());
        if (abstractAudit->agentName() != oldAbstractAudit->agentName())
            emit agentNameChanged(abstractAudit->agentName());
        if (abstractAudit->agentVersion() != oldAbstractAudit->agentVersion())
            emit agentVersionChanged(abstractAudit->agentVersion());
        if (abstractAudit->timeStamp() != oldAbstractAudit->timeStamp())
            emit timeStampChanged(abstractAudit->timeStamp());
    }
}
