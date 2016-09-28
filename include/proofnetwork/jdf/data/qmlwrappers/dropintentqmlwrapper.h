#ifndef DROPINTENTQMLWRAPPER_H
#define DROPINTENTQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

#include "proofnetwork/jdf/data/qmlwrappers/dropitemintentqmlwrapper.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class DropIntent;

class DropIntentQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT DropIntentQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::DropItemIntentQmlWrapper> dropItemIntents READ dropItemIntents NOTIFY dropItemIntentsChanged)
    Q_DECLARE_PRIVATE(DropIntentQmlWrapper)
public:
    explicit DropIntentQmlWrapper(const DropIntentSP &dropIntent, QObject *parent = 0);
    ~DropIntentQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(DropIntent)

    QQmlListProperty<Proof::Jdf::DropItemIntentQmlWrapper> dropItemIntents() const;

signals:
    void dropItemIntentsChanged(const QQmlListProperty<Proof::Jdf::DropItemIntentQmlWrapper> &dropItemIntents);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}

#endif // DROPINTENTQMLWRAPPER_H
