#include "deliveryintentlink.h"

#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(DeliveryIntentLink)
};

DeliveryIntentLinkQmlWrapper *DeliveryIntentLink::toQmlWrapper(QObject *parent) const
{
    Q_D(const DeliveryIntentLink);
    DeliveryIntentLinkSP castedSelf = qSharedPointerCast<DeliveryIntentLink>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new DeliveryIntentLinkQmlWrapper(castedSelf, parent);
}

DeliveryIntentLinkSP DeliveryIntentLink::create()
{
    DeliveryIntentLinkSP result(new DeliveryIntentLink());
    initSelfWeakPtr(result);
    return result;
}

DeliveryIntentLinkSP DeliveryIntentLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    DeliveryIntentLinkSP deliveryParams = create();
    AbstractResourceLink::fromJdf(xmlReader, deliveryParams);
    return deliveryParams;
}

DeliveryIntentLink::DeliveryIntentLink(QObject *parent)
    : AbstractResourceLink(*new DeliveryIntentLinkPrivate, parent)
{
}

}
}
