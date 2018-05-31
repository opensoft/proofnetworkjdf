#ifndef PROOF_JDF_RESPONSE_P_H
#define PROOF_JDF_RESPONSE_P_H

#include "proofnetwork/jdf/data/message_p.h"
#include "proofnetwork/jdf/data/notification.h"

namespace Proof {
namespace Jdf {

class ResponsePrivate : public MessagePrivate
{
    Q_DECLARE_PUBLIC(Response)

    NotificationSP notification;

protected:
    ResponsePrivate() { registerChildren(notification); }

    void updateFrom(const NetworkDataEntitySP &other) override;
    void specificMessageFromJmf(QXmlStreamReader &xmlReader) override;
    QString tagName() const override;
    void specificMessageToJmf(QXmlStreamWriter &xmlWriter) const override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_RESPONSE_P_H
