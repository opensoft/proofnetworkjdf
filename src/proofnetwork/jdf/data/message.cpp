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
#include "proofnetwork/jdf/data/message.h"

#include "proofnetwork/jdf/data/message_p.h"

namespace Proof {
namespace Jdf {

MessageSP instantiateJmfMessage(const QString &tagName, const QString &type)
{
    MessageSP result;
    auto creator = MessagePrivate::messageCreators().value(qMakePair(tagName, type));
    if (creator)
        result = creator();
    return result;
}

QString Message::id() const
{
    Q_D_CONST(Message);
    return d->id;
}

void Message::setId(const QString &arg)
{
    Q_D(Message);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

NetworkDataEntityQmlWrapper *Message::toQmlWrapper(QObject *) const
{
    Q_ASSERT(false);
    return nullptr;
}

MessageSP Message::fromJmf(QXmlStreamReader &xmlReader)
{
    MessageSP message;
    if (xmlReader.isStartElement()) {
        QString tag = xmlReader.name().toString();
        auto attributes = xmlReader.attributes();
        QString id = attributes.value(QStringLiteral("ID")).toString();
        QString type = attributes.value(QStringLiteral("Type")).toString();
        message = instantiateJmfMessage(tag, type);
        if (message != nullptr) {
            message->setId(id);
            message->d_func()->specificMessageFromJmf(xmlReader);
        }
    }
    return message;
}

void Message::toJmf(QXmlStreamWriter &xmlWriter)
{
    Q_D(Message);
    xmlWriter.writeStartElement(d->tagName());
    xmlWriter.writeAttribute(QStringLiteral("ID"), d->id);
    xmlWriter.writeAttribute(QStringLiteral("Type"), d->typeName());
    d->specificMessageToJmf(xmlWriter);
    xmlWriter.writeEndElement();
}

Message::Message(MessagePrivate &dd) : NetworkDataEntity(dd)
{}

void Message::updateSelf(const NetworkDataEntitySP &other)
{
    MessageSP castedOther = qSharedPointerCast<Message>(other);
    setId(castedOther->id());
    NetworkDataEntity::updateSelf(other);
}

QHash<MessagePrivate::CreatorKey, MessagePrivate::CreatorType> &MessagePrivate::messageCreators()
{
    static QHash<MessagePrivate::CreatorKey, MessagePrivate::CreatorType> creators;
    return creators;
}

} // namespace Jdf
} // namespace Proof
