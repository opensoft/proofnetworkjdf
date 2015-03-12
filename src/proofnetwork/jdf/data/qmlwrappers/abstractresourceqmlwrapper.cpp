#include "abstractresourceqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

using namespace Proof;
using namespace Proof::Jdf;

AbstractResourceQmlWrapper::AbstractResourceQmlWrapper(const QSharedPointer<AbstractResource> &abstractResource,
                                                       AbstractResourceQmlWrapperPrivate &dd, QObject *parent)
    : NetworkDataEntityQmlWrapper(abstractResource, dd, parent)
{
    setupEntity();
}

AbstractResourceQmlWrapper::~AbstractResourceQmlWrapper()
{
}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, Proof::Jdf::ApiHelper::ResourceStatus, status)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, Proof::Jdf::ApiHelper::ResourceClass, resourceClass)

void AbstractResourceQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(AbstractResourceQmlWrapper);
    AbstractResourceSP abstractResource = d->entity<AbstractResource>();
    Q_ASSERT(abstractResource);

    connect(abstractResource.data(), &AbstractResource::idChanged,
            this, &AbstractResourceQmlWrapper::idChanged);
    connect(abstractResource.data(), &AbstractResource::statusChanged,
            this, &AbstractResourceQmlWrapper::statusChanged);
    connect(abstractResource.data(), &AbstractResource::resourceClassChanged,
            this, &AbstractResourceQmlWrapper::resourceClassChanged);

    AbstractResourceSP oldAbstractResource = qSharedPointerCast<AbstractResource>(old);
    if (oldAbstractResource) {
        if (abstractResource->id() != oldAbstractResource->id())
            emit idChanged(abstractResource->id());
        if (abstractResource->status() != oldAbstractResource->status())
            emit statusChanged(abstractResource->status());
        if (abstractResource->resourceClass() != oldAbstractResource->resourceClass())
            emit resourceClassChanged(abstractResource->resourceClass());
    }
}


