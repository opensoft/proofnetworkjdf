#include "notification.h"

#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class NotificationPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(Notification)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    NotificationClass notificationClass;
    QString comment;
};

NotificationClass Notification::notificationClass() const
{
    Q_D(const Notification);
    return d->notificationClass;
}

QString Notification::comment() const
{
    Q_D(const Notification);
    return d->comment;
}

void Notification::setNotificationClass(NotificationClass arg)
{
    Q_D(Notification);
    if (d->notificationClass != arg) {
        d->notificationClass = arg;
        emit notificationClassChanged(d->notificationClass);
    }
}

void Notification::setComment(const QString &arg)
{
    Q_D(Notification);
    if (d->comment != arg) {
        d->comment = arg;
        emit commentChanged(d->comment);
    }
}

NotificationSP Notification::create()
{
    NotificationSP result(new Notification());
    initSelfWeakPtr(result);
    return result;
}

NetworkDataEntityQmlWrapper *Notification::toQmlWrapper(QObject *parent) const
{
    Q_UNUSED(parent)
    Q_ASSERT(false);
    return nullptr;
}

void Notification::toJdf(QXmlStreamWriter &xmlWriter)
{
    Q_D(Notification);
    xmlWriter.writeStartElement("Notification");
    xmlWriter.writeAttribute("Class", notificationClassToString(d->notificationClass));
    xmlWriter.writeStartElement("Comment");
    xmlWriter.writeCharacters(d->comment);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
}

NotificationSP Notification::fromJdf(QXmlStreamReader &xmlReader)
{
    NotificationSP result;
    if (xmlReader.isStartElement() && xmlReader.name() == "Notification") {
        result = create();
        auto attributes = xmlReader.attributes();
        result->setNotificationClass(notificationClassFromString(attributes.value("Class").toString()));
        while (xmlReader.readNextStartElement()) {
            if (xmlReader.name() == "Comment")
                result->setComment(xmlReader.readElementText());
            else
                xmlReader.skipCurrentElement();
        }
    }
    return result;
}

Notification::Notification()
    : NetworkDataEntity(*new NotificationPrivate)
{
}

void NotificationPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(Notification);
    NotificationSP castedOther = qSharedPointerCast<Notification>(other);
    q->setNotificationClass(castedOther->notificationClass());
    NetworkDataEntityPrivate::updateFrom(other);
}

} // namespace Jdf
} // namespace Proof

