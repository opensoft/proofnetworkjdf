#include "jmfdocument.h"

#include "proofnetwork/jdf/data/message.h"
#include "proofnetwork/networkdataentity_p.h"

#include <QXmlStreamWriter>

#include <algorithm>

namespace Proof {
namespace Jdf {

class JmfDocumentPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(JmfDocument)

    JmfDocumentPrivate() : NetworkDataEntityPrivate() { registerChildren(messages); }

    QString senderId = QStringLiteral("Proof generator");
    QString version = QStringLiteral("1.4");
    QDateTime timeStamp;
    QVector<MessageSP> messages;
};

QString JmfDocument::senderId() const
{
    Q_D(const JmfDocument);
    return d->senderId;
}

QDateTime JmfDocument::timeStamp() const
{
    Q_D(const JmfDocument);
    return d->timeStamp;
}

QVector<MessageSP> JmfDocument::messages() const
{
    Q_D(const JmfDocument);
    return d->messages;
}

QString JmfDocument::version() const
{
    Q_D(const JmfDocument);
    return d->version;
}

void JmfDocument::setSenderId(const QString &arg)
{
    Q_D(JmfDocument);
    if (d->senderId != arg) {
        d->senderId = arg;
        emit senderIdChanged(d->senderId);
    }
}

void JmfDocument::setTimeStamp(const QDateTime &arg)
{
    Q_D(JmfDocument);
    if (d->timeStamp != arg) {
        d->timeStamp = arg;
        emit timeStampChanged(d->timeStamp);
    }
}

void JmfDocument::setMessages(const QVector<MessageSP> &arg)
{
    Q_D(JmfDocument);
    bool notEqual = d->messages.size() != arg.size()
                    || !std::is_permutation(d->messages.cbegin(), d->messages.cend(), arg.cbegin());
    if (notEqual) {
        d->messages = arg;
        emit messagesChanged(d->messages);
    }
}

void JmfDocument::addMessage(const MessageSP &arg)
{
    Q_D(JmfDocument);
    d->messages << arg;
    emit messagesChanged(d->messages);
}

NetworkDataEntityQmlWrapper *JmfDocument::toQmlWrapper(QObject *) const
{
    Q_ASSERT(false);
    return nullptr;
}

JmfDocumentSP JmfDocument::create()
{
    JmfDocumentSP result(new JmfDocument());
    initSelfWeakPtr(result);
    return result;
}

JmfDocumentSP JmfDocument::fromJmf(QXmlStreamReader &xmlReader)
{
    JmfDocumentSP document;
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "JMF") {
                document = create();
                document->setFetched(true);
                QXmlStreamAttributes attributes = xmlReader.attributes();
                document->setSenderId(attributes.value(QStringLiteral("SenderID")).toString());
                document->d_func()->version = attributes.value(QStringLiteral("Version")).toString();
                document->setTimeStamp(
                    QDateTime::fromString(attributes.value(QStringLiteral("TimeStamp")).toString(), Qt::ISODate));

                while (xmlReader.readNextStartElement()) {
                    auto message = Message::fromJmf(xmlReader);
                    if (message != nullptr)
                        document->addMessage(message);
                    else
                        xmlReader.skipCurrentElement();
                }
            }
        }

        xmlReader.readNext();
    }
    return document;
}

QString JmfDocument::toJmf()
{
    Q_D(JmfDocument);
    QString jmf;
    QXmlStreamWriter jmfWriter(&jmf);

    jmfWriter.setAutoFormatting(true);
    jmfWriter.writeStartDocument();
    jmfWriter.writeDefaultNamespace(QStringLiteral("http://www.CIP4.org/JDFSchema_1_1"));
    jmfWriter.writeStartElement(QStringLiteral("JMF"));
    {
        jmfWriter.writeAttribute(QStringLiteral("SenderID"), d->senderId);
        jmfWriter.writeAttribute(QStringLiteral("Version"), d->version);
        jmfWriter.writeAttribute(QStringLiteral("TimeStamp"), d->timeStamp.toString(Qt::ISODate));
        for (const MessageSP &message : qAsConst(d->messages))
            message->toJmf(jmfWriter);
    }
    jmfWriter.writeEndElement();
    jmfWriter.writeEndDocument();
    return jmf;
}

JmfDocument::JmfDocument() : NetworkDataEntity(*new JmfDocumentPrivate)
{}

void JmfDocument::updateSelf(const NetworkDataEntitySP &other)
{
    JmfDocumentSP castedOther = qSharedPointerCast<JmfDocument>(other);
    setSenderId(castedOther->senderId());
    setTimeStamp(castedOther->timeStamp());
    setMessages(castedOther->messages());
    NetworkDataEntity::updateSelf(other);
}

} // namespace Jdf
} // namespace Proof
