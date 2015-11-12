#ifndef ABSTRACTPHYSICALRESOURCELINK_P_H
#define ABSTRACTPHYSICALRESOURCELINK_P_H

#include "proofnetwork/jdf/data/abstractresourcelink_p.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourceLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(AbstractPhysicalResourceLink)
public:
    AbstractPhysicalResourceLinkPrivate() :  AbstractResourceLinkPrivate() {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    ApiHelper::ResourceOrientation orientation = ApiHelper::ResourceOrientation::Rotate0Orientation;
    double amount;
};

}
}

#endif // ABSTRACTPHYSICALRESOURCELINK_P_H

