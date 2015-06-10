#ifndef FOLDINGPARAMSLINK_H
#define FOLDINGPARAMSLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"

namespace Proof {
namespace Jdf {

class FoldingParamsLink : public AbstractResourceLink
{
    Q_OBJECT
public:
    explicit FoldingParamsLink(const FoldingParamsSP &foldingParams, QObject *parent = 0)
        : AbstractResourceLink(qSharedPointerCast<AbstractResource>(foldingParams), parent)
    {
    }
};

}
}

#endif // FOLDINGPARAMSLINK_H
