#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"

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
{}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, Proof::Jdf::ResourceStatus, resourceStatus)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, Proof::Jdf::ResourceClass, resourceClass)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractResource, QVector<ResourcePartType>, partIdKeys)

void AbstractResourceQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    AbstractResourceSP abstractResource = entity<AbstractResource>();
    Q_ASSERT(abstractResource);

    connect(abstractResource.data(), &AbstractResource::idChanged, this, &AbstractResourceQmlWrapper::idChanged);
    connect(abstractResource.data(), &AbstractResource::statusChanged, this,
            &AbstractResourceQmlWrapper::resourceStatusChanged);
    connect(abstractResource.data(), &AbstractResource::resourceClassChanged, this,
            &AbstractResourceQmlWrapper::resourceClassChanged);
    connect(abstractResource.data(), &AbstractResource::partIdKeysChanged, this,
            &AbstractResourceQmlWrapper::partIdKeysChanged);

    AbstractResourceSP oldAbstractResource = qSharedPointerCast<AbstractResource>(old);
    if (oldAbstractResource) {
        if (abstractResource->id() != oldAbstractResource->id())
            emit idChanged(abstractResource->id());
        if (abstractResource->resourceStatus() != oldAbstractResource->resourceStatus())
            emit resourceStatusChanged(abstractResource->resourceStatus());
        if (abstractResource->resourceClass() != oldAbstractResource->resourceClass())
            emit resourceClassChanged(abstractResource->resourceClass());
        if (abstractResource->partIdKeys() != oldAbstractResource->partIdKeys())
            emit partIdKeysChanged(abstractResource->partIdKeys());
    }
}
