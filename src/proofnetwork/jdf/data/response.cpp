#include "response.h"

#include "response_p.h"

namespace Proof {
namespace Jdf {

NotificationSP Response::notification() const
{
    Q_D(const Response);
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

Response::Response(ResponsePrivate &dd, QObject *parent) : Message(dd, parent)
{}

void ResponsePrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(Response);
    ResponseSP castedOther = qSharedPointerCast<Response>(other);
    q->setNotification(castedOther->notification());
    MessagePrivate::updateFrom(other);
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
