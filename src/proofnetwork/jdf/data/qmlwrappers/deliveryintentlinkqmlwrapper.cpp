#include "deliveryintentlinkqmlwrapper.h"

#include "proofnetwork/jdf/data/deliveryintentlink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentLinkQmlWrapperPrivate : public AbstractResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(DeliveryIntentLinkQmlWrapper)
};

DeliveryIntentLinkQmlWrapper::DeliveryIntentLinkQmlWrapper(const DeliveryIntentLinkSP &delivery, QObject *parent)
    : AbstractResourceLinkQmlWrapper(delivery, *new DeliveryIntentLinkQmlWrapperPrivate, parent)
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(DeliveryIntentLink)

}
}
