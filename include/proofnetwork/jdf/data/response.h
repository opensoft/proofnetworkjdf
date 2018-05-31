#ifndef PROOF_JDF_RESPONSE_H
#define PROOF_JDF_RESPONSE_H

#include "proofnetwork/jdf/data/message.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class ResponsePrivate;
class PROOF_NETWORK_JDF_EXPORT Response : public Message
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Response)

public:
    NotificationSP notification() const;

    void setNotification(const NotificationSP &arg);

signals:
    void notificationChanged(Proof::Jdf::NotificationSP arg);

protected:
    explicit Response(ResponsePrivate &dd, QObject *parent = nullptr);
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_RESPONSE_H
