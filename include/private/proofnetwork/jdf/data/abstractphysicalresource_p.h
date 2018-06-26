#ifndef ABSTRACTPHYSICALRESOURCE_P_H
#define ABSTRACTPHYSICALRESOURCE_P_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourcePrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(AbstractPhysicalResource)
public:
    AbstractPhysicalResourcePrivate() : AbstractResourcePrivate() {}
    explicit AbstractPhysicalResourcePrivate(ResourceClass resourceClass) : AbstractResourcePrivate(resourceClass) {}

    double amount = 0.0;
    double resourceWeight = 0.0;
};

} // namespace Jdf
} // namespace Proof

#endif // ABSTRACTPHYSICALRESOURCE_P_H
