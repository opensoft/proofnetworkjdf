#ifndef PROOF_JDF_ABSTRACTRESOURCE_P_H
#define PROOF_JDF_ABSTRACTRESOURCE_P_H

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class AbstractResourcePrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractResource)
public:
    AbstractResourcePrivate() : NetworkDataEntityPrivate() {}
    AbstractResourcePrivate(ResourceClass resourceClass)
        : NetworkDataEntityPrivate(), resourceClass(resourceClass)
    {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString id;

    ResourceStatus resourceStatus = ResourceStatus::NoStatus;
    ResourceClass resourceClass = ResourceClass::NoClass;

    QList<ResourcePartType> partIdKeys;
    QHash<ResourcePartType, QString> partAttributes;
};

}
}

#endif // PROOF_JDF_ABSTRACTRESOURCE_P_H

