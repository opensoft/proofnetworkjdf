#ifndef PROOF_JDF_ABSTRACTRESOURCE_P_H
#define PROOF_JDF_ABSTRACTRESOURCE_P_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class AbstractResourcePrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractResource)
public:
    AbstractResourcePrivate() : NetworkDataEntityPrivate() {}
    AbstractResourcePrivate(ResourceClass resourceClass) : NetworkDataEntityPrivate(), resourceClass(resourceClass) {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString id;
    mutable QString jdfNodeName;
    mutable QString jdfNodeRefName;

    ResourceStatus resourceStatus = ResourceStatus::NoStatus;
    ResourceClass resourceClass = ResourceClass::NoClass;

    QList<ResourcePartType> partIdKeys;
    QHash<ResourcePartType, QString> partAttributes;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_ABSTRACTRESOURCE_P_H
