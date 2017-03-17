#ifndef DELIVERYINTENTLINKQMLWRAPPER_H
#define DELIVERYINTENTLINKQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentLinkQmlWrapperPrivate;
class DeliveryIntentLinkQmlWrapper : public AbstractResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeliveryIntentLinkQmlWrapper)
public:
    explicit DeliveryIntentLinkQmlWrapper(const DeliveryIntentLinkSP &delivery, QObject *parent = nullptr);
    PROOF_NDE_WRAPPER_TOOLS(DeliveryIntentLink)
};

}
}

#endif // DELIVERYINTENTLINKQMLWRAPPER_H
