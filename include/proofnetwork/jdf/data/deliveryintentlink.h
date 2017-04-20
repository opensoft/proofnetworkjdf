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
    DeliveryIntentLinkQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DeliveryIntentLinkSP create();

    static DeliveryIntentLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;

protected:
    explicit DeliveryIntentLink(QObject *parent = nullptr);
};

}
}

#endif // DELIVERYINTENTLINK_H
