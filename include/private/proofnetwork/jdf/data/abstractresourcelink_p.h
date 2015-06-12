#ifndef ABSTRACTRESOURCELINK_P_H
#define ABSTRACTRESOURCELINK_P_H

#include "abstractresourcelink.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class AbstractResourceLinkPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractResourceLink)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override
    {
        Q_Q(AbstractResourceLink);
        AbstractResourceLinkSP castedOther = qSharedPointerCast<AbstractResourceLink>(other);
        q->setUsage(castedOther->usage());
        q->setRRef(castedOther->rRef());
    }

    // TODO: should we use default usage?
    ApiHelper::Usage usage = ApiHelper::InputUsage;
    QString rRef;
};

}
}

#endif // ABSTRACTRESOURCELINK_P_H
