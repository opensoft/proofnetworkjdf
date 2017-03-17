#ifndef DELIVERYINTENTQMLWRAPPER_H
#define DELIVERYINTENTQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class DeliveryIntent;
class DropIntentQmlWrapper;

class DeliveryIntentQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT DeliveryIntentQmlWrapper : public AbstractResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::DropIntentQmlWrapper> dropIntents READ dropIntents NOTIFY dropIntentsChanged)
    Q_DECLARE_PRIVATE(DeliveryIntentQmlWrapper)
public:
    explicit DeliveryIntentQmlWrapper(const DeliveryIntentSP &deliveryIntent, QObject *parent = nullptr);
    ~DeliveryIntentQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(DeliveryIntent)

    QQmlListProperty<DropIntentQmlWrapper> dropIntents() const;

signals:
    void dropIntentsChanged(const QQmlListProperty<Proof::Jdf::DropIntentQmlWrapper> &dropIntents);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}

#endif // DELIVERYINTENTQMLWRAPPER_H
