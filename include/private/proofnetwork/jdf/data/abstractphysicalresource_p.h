#ifndef ABSTRACTPHYSICALRESOURCE_P_H
#define ABSTRACTPHYSICALRESOURCE_P_H

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourcePrivate : public  AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(AbstractPhysicalResource)
public:
    AbstractPhysicalResourcePrivate() :  AbstractResourcePrivate() {}

    double amount = 0.0;
    double resourceWeight = 0.0;
};

}
}

#endif // ABSTRACTPHYSICALRESOURCE_P_H

