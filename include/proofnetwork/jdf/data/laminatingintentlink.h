#ifndef LAMINATINGINTENTLINK_H
#define LAMINATINGINTENTLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentLink : public AbstractResourceLink
{
    Q_OBJECT
public:
    explicit LaminatingIntentLink(const LaminatingIntentSP &laminatingIntent, QObject *parent = 0)
        : AbstractResourceLink( qSharedPointerCast<AbstractResource>(laminatingIntent), parent)
    {
    }
};

}
}
#endif // LAMINATINGINTENTLINK_H
