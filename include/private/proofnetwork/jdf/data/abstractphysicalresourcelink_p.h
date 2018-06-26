#ifndef ABSTRACTPHYSICALRESOURCELINK_P_H
#define ABSTRACTPHYSICALRESOURCELINK_P_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractresourcelink_p.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourceLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(AbstractPhysicalResourceLink)
public:
    AbstractPhysicalResourceLinkPrivate() : AbstractResourceLinkPrivate() {}

    ResourceOrientation orientation = ResourceOrientation::Rotate0Orientation;
    double amount = 0;
};

} // namespace Jdf
} // namespace Proof

#endif // ABSTRACTPHYSICALRESOURCELINK_P_H
