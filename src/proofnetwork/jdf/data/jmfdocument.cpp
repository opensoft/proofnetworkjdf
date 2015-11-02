#include "jmfdocument.h"

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/data/message.h"

#include <QXmlStreamWriter>

#include <algorithm>

namespace Proof {
namespace Jdf {

class JmfDocumentPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(JmfDocument)

    JmfDocumentPrivate()
        : NetworkDataEntityPrivate()
    {
        registerChildren(messages);
    }

    void updateFrom(const NetworkDataEntitySP &other) override;

    QString senderId = "Proof generator";
    QString version = "1.4";
    QDateTime timeStamp;
    QList<MessageSP> messages;
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

QList<MessageSP> JmfDocument::messages() const
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

void JmfDocument::setMessages(const QList<MessageSP> &arg)
{
    Q_D(JmfDocument);
    if (d->messages.size() == arg.size()) {
        bool equal = std::all_of(d->messages.cbegin(), d->messages.cend(), [&arg](const MessageSP &lhs)
        {
            return std::any_of(arg.cbegin(), arg.cend(), [&lhs](const MessageSP &rhs) { return lhs == rhs; });
        });
        if (equal)
            return;
    }
    d->messages = arg;
    emit messagesChanged(d->messages);
}

void JmfDocument::addMessage(const MessageSP &arg)
{
    Q_D(JmfDocument);
    d->messages << arg;
    emit messagesChanged(d->messages);
}

NetworkDataEntityQmlWrapper *JmfDocument::toQmlWrapper(QObject *) const
{
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
                document->setSenderId(attributes.value("SenderID").toString());
                document->d_func()->version = attributes.value("Version").toString();
                document->setTimeStamp(QDateTime::fromString(attributes.value("TimeStamp").toString(), Qt::ISODate));

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
    jmfWriter.writeDefaultNamespace("http://www.CIP4.org/JDFSchema_1_1");
    jmfWriter.writeStartElement("JMF");
    {
        jmfWriter.writeAttribute("SenderID", d->senderId);
        jmfWriter.writeAttribute("Version", d->version);
        jmfWriter.writeAttribute("TimeStamp", d->timeStamp.toString(Qt::ISODate));
        for (const MessageSP &message : d->messages)
            message->toJmf(jmfWriter);
    }
    jmfWriter.writeEndElement();
    jmfWriter.writeEndDocument();
    return jmf;
}

JmfDocument::JmfDocument()
    : NetworkDataEntity(*new JmfDocumentPrivate)
{
}

void JmfDocumentPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(JmfDocument);
    JmfDocumentSP castedOther = qSharedPointerCast<JmfDocument>(other);
    q->setSenderId(castedOther->senderId());
    q->setTimeStamp(castedOther->timeStamp());
    q->setMessages(castedOther->messages());
    NetworkDataEntityPrivate::updateFrom(other);
}

} // namespace Jdf
} // namespace Proof

