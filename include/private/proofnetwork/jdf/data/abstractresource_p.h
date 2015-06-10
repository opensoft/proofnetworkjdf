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

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString id;
    ApiHelper::ResourceStatus resourceStatus = ApiHelper::IncompleteStatus;
    ApiHelper::ResourceClass resourceClass = ApiHelper::ConsumableClass;
};

}
}

#endif // PROOF_JDF_ABSTRACTRESOURCE_P_H

