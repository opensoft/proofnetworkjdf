#include "abstractphysicalresourceqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractphysicalresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper_p.h"

using namespace Proof;
using namespace Proof::Jdf;

AbstractPhysicalResourceQmlWrapper::AbstractPhysicalResourceQmlWrapper(const QSharedPointer<AbstractPhysicalResource> &abstractPhysicalResource,
                                                       AbstractPhysicalResourceQmlWrapperPrivate &dd, QObject *parent)
    : AbstractResourceQmlWrapper(abstractPhysicalResource, dd, parent)
{
    setupEntity();
}

AbstractPhysicalResourceQmlWrapper::~AbstractPhysicalResourceQmlWrapper()
{
}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractPhysicalResource, double, amount)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractPhysicalResource, double, resourceWeight)

void AbstractPhysicalResourceQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(AbstractPhysicalResourceQmlWrapper);
    AbstractPhysicalResourceSP abstractPhysicalResource = d->entity<AbstractPhysicalResource>();
    Q_ASSERT(abstractPhysicalResource);

    connect(abstractPhysicalResource.data(), &AbstractPhysicalResource::amountChanged,
            this, &AbstractPhysicalResourceQmlWrapper::amountChanged);
    connect(abstractPhysicalResource.data(), &AbstractPhysicalResource::resourceWeightChanged,
            this, &AbstractPhysicalResourceQmlWrapper::resourceWeightChanged);

    AbstractPhysicalResourceSP oldAbstractPhysicalResource = qSharedPointerCast<AbstractPhysicalResource>(old);
    if (oldAbstractPhysicalResource) {
        if (abstractPhysicalResource->amount() != oldAbstractPhysicalResource->amount())
            emit amountChanged(abstractPhysicalResource->amount());
        if (abstractPhysicalResource->resourceWeight() != oldAbstractPhysicalResource->resourceWeight())
            emit resourceWeightChanged(abstractPhysicalResource->resourceWeight());
    }
}


