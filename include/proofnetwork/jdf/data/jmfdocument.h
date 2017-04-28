#ifndef PROOF_JDF_JMFDOCUMENT_H
#define PROOF_JDF_JMFDOCUMENT_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class JmfDocumentPrivate;
class PROOF_NETWORK_JDF_EXPORT JmfDocument : public NetworkDataEntity // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(JmfDocument)
public:
    QString senderId() const;
    QDateTime timeStamp() const;
    QList<MessageSP> messages() const;
    QString version() const;

    void setSenderId(const QString &arg);
    void setTimeStamp(const QDateTime &arg);
    void setMessages(const QList<MessageSP> &arg);
    void addMessage(const MessageSP &arg);

    NetworkDataEntityQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static JmfDocumentSP create();

    static JmfDocumentSP fromJmf(QXmlStreamReader &xmlReader);
    QString toJmf();

signals:
    void senderIdChanged(const QString &arg);
    void timeStampChanged(const QDateTime &arg);
    void messagesChanged(const QList<Proof::Jdf::MessageSP> &arg);

protected:
    explicit JmfDocument();
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_JMFDOCUMENT_H
