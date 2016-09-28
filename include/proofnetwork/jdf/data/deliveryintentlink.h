#ifndef DELIVERYINTENTLINK_H
#define DELIVERYINTENTLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/deliveryintentlinkqmlwrapper.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT DeliveryIntentLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeliveryIntentLink)
public:
    DeliveryIntentLinkQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static DeliveryIntentLinkSP create();

    static DeliveryIntentLinkSP fromJdf(const QXmlStreamReader &xmlReader);

protected:
    explicit DeliveryIntentLink(QObject *parent = 0);
};

}
}

#endif // DELIVERYINTENTLINK_H
