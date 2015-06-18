#ifndef ABSTRACTRESOURCELINK_P_H
#define ABSTRACTRESOURCELINK_P_H

#include "abstractresourcelink.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class AbstractResourceLinkPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractResourceLink)
public:
    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    ApiHelper::Usage usage = ApiHelper::Usage::InputUsage;
    QString rRef;
};

}
}

#endif // ABSTRACTRESOURCELINK_P_H
