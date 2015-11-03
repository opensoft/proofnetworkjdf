#ifndef PROOF_JDF_MESSAGE_P_H
#define PROOF_JDF_MESSAGE_P_H

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QHash>
#include <QXmlStreamReader>

#include <functional>

namespace Proof {
namespace Jdf {

class MessagePrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(Message)

    template<class T> friend void registerJmfMessage(const QString &tagName, const QString &type);
    friend MessageSP instantiateJmfMessage(const QString &tagName, const QString &typeName);

protected:
    void updateFrom(const NetworkDataEntitySP &other) override;
    virtual void specificMessageFromJmf(QXmlStreamReader &xmlReader) = 0;
    virtual QString tagName() const = 0;
    virtual QString typeName() const = 0;
    virtual void specificMessageToJmf(QXmlStreamWriter &xmlWriter) const = 0;

private:
    QString id;

    using CreatorKey = QPair<QString, QString>;
    using CreatorType = std::function<MessageSP ()>;
    static QHash<CreatorKey, CreatorType> messageCreators;
};

template<class T>
void registerJmfMessage(const QString &tagName, const QString &type)
{
    MessagePrivate::messageCreators.insert(qMakePair(tagName, type), &T::create);
}

}
}

#endif // PROOF_JDF_MESSAGE_P_H

