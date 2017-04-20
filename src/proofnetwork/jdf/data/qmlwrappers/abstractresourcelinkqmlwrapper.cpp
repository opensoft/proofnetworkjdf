#include "abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"

using namespace Proof::Jdf;

AbstractResourceLinkQmlWrapper::AbstractResourceLinkQmlWrapper(
        const QSharedPointer<AbstractResourceLink> &link,
        AbstractResourceLinkQmlWrapperPrivate &dd,
        QObject *parent)
    : NetworkDataEntityQmlWrapper(link, dd, parent)
{
    setupEntity();
}

AbstractResourceLinkQmlWrapper::~AbstractResourceLinkQmlWrapper()
{
}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResourceLink, QString, rRef)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResourceLink, Proof::Jdf::LinkUsage, usage)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResourceLink, Proof::Jdf::ProcessUsage, processUsage)

void AbstractResourceLinkQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    Q_D(AbstractResourceLinkQmlWrapper);
    AbstractResourceLinkSP abstractResourceLink = d->entity<AbstractResourceLink>();
    Q_ASSERT(abstractResourceLink);

    connect(abstractResourceLink.data(), &AbstractResourceLink::rRefChanged,
            this, &AbstractResourceLinkQmlWrapper::rRefChanged);
    connect(abstractResourceLink.data(), &AbstractResourceLink::usageChanged,
            this, &AbstractResourceLinkQmlWrapper::usageChanged);
    connect(abstractResourceLink.data(), &AbstractResourceLink::processUsageChanged,
            this, &AbstractResourceLinkQmlWrapper::processUsageChanged);

    AbstractResourceLinkSP castedOld = qSharedPointerCast<AbstractResourceLink>(old);
    if (castedOld) {
        if (abstractResourceLink->rRef() != castedOld->rRef())
            emit rRefChanged(abstractResourceLink->rRef());

        if (abstractResourceLink->usage() != castedOld->usage())
            emit usageChanged(abstractResourceLink->usage());

        if (abstractResourceLink->processUsage() != castedOld->processUsage())
            emit processUsageChanged(abstractResourceLink->processUsage());
    }
}

