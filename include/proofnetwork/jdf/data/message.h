#ifndef PROOF_JDF_MESSAGE_H
#define PROOF_JDF_MESSAGE_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class MessagePrivate;
class PROOF_NETWORK_JDF_EXPORT Message : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Message)
public:
    QString id() const;

    void setId(const QString &arg);

    NetworkDataEntityQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static MessageSP fromJmf(QXmlStreamReader &xmlReader);
    void toJmf(QXmlStreamWriter &xmlWriter);

signals:
    void idChanged(const QString &arg);

protected:
    explicit Message(MessagePrivate &dd, QObject *parent = nullptr);
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_MESSAGE_H
