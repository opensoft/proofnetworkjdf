#ifndef ABSTRACTRESOURCELINK_P_H
#define ABSTRACTRESOURCELINK_P_H

#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class AbstractResourceLinkPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractResourceLink)
public:
    LinkUsage usage = LinkUsage::InputLink;
    ProcessUsage processUsage = ProcessUsage::UseAsDefault;
    QString rRef;
};

} // namespace Jdf
} // namespace Proof

#endif // ABSTRACTRESOURCELINK_P_H
