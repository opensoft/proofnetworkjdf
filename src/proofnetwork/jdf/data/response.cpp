#include "proofnetwork/jdf/data/response.h"

#include "proofnetwork/jdf/data/response_p.h"

namespace Proof {
namespace Jdf {

NotificationSP Response::notification() const
{
    Q_D_CONST(Response);
    return d->notification;
}

void Response::setNotification(const NotificationSP &arg)
{
    Q_D(Response);
    if (d->notification != arg) {
        d->notification = arg;
        emit notificationChanged(d->notification);
    }
}

Response::Response(ResponsePrivate &dd) : Message(dd)
{}

void Response::updateSelf(const NetworkDataEntitySP &other)
{
    ResponseSP castedOther = qSharedPointerCast<Response>(other);
    setNotification(castedOther->notification());
    Message::updateSelf(other);
}

void ResponsePrivate::specificMessageFromJmf(QXmlStreamReader &xmlReader)
{
    Q_Q(Response);
    if (xmlReader.name() == "Notification")
        q->setNotification(Notification::fromJdf(xmlReader));
    else
        xmlReader.skipCurrentElement();
}

QString ResponsePrivate::tagName() const
{
    return QStringLiteral("Response");
}

void ResponsePrivate::specificMessageToJmf(QXmlStreamWriter &xmlWriter) const
{
    if (notification != nullptr)
        notification->toJdf(xmlWriter);
}

} // namespace Jdf
} // namespace Proof
