#ifndef CUTTINGPARAMSLINK_H
#define CUTTINGPARAMSLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"

namespace Proof {
namespace Jdf {

class CuttingParamsLink : public AbstractResourceLink
{
    Q_OBJECT
public:
    explicit CuttingParamsLink(const CuttingParamsSP &cuttingParams, QObject *parent = 0)
        : AbstractResourceLink( qSharedPointerCast<AbstractResource>(cuttingParams), parent)
    {
    }
};

}
}
#endif // CUTTINGPARAMSLINK_H
