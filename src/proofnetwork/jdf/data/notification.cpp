/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "proofnetwork/jdf/data/notification.h"

#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class NotificationPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(Notification)

    NotificationClass notificationClass;
    QString comment;
};

NotificationClass Notification::notificationClass() const
{
    Q_D_CONST(Notification);
    return d->notificationClass;
}

QString Notification::comment() const
{
    Q_D_CONST(Notification);
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
    xmlWriter.writeStartElement(QStringLiteral("Notification"));
    xmlWriter.writeAttribute(QStringLiteral("Class"), notificationClassToString(d->notificationClass));
    xmlWriter.writeStartElement(QStringLiteral("Comment"));
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
        result->setNotificationClass(notificationClassFromString(attributes.value(QStringLiteral("Class")).toString()));
        while (xmlReader.readNextStartElement()) {
            if (xmlReader.name() == "Comment")
                result->setComment(xmlReader.readElementText());
            else
                xmlReader.skipCurrentElement();
        }
    }
    return result;
}

Notification::Notification() : NetworkDataEntity(*new NotificationPrivate)
{}

void Notification::updateSelf(const NetworkDataEntitySP &other)
{
    NotificationSP castedOther = qSharedPointerCast<Notification>(other);
    setNotificationClass(castedOther->notificationClass());
    NetworkDataEntity::updateSelf(other);
}

} // namespace Jdf
} // namespace Proof
