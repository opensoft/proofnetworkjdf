#include "deliveryintentqmlwrapper.h"

#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/dropintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(DeliveryIntentQmlWrapper)

    void updateDropIntents();

    QVector<DropIntentQmlWrapper *> dropIntents;
    QQmlListProperty<Proof::Jdf::DropIntentQmlWrapper> qmlDropIntentsList;
    static DropIntentQmlWrapper *dropIntentAt(QQmlListProperty<DropIntentQmlWrapper> *property, int index);
    static int dropIntentsCount(QQmlListProperty<DropIntentQmlWrapper> *property);
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

DeliveryIntentQmlWrapper::DeliveryIntentQmlWrapper(const DeliveryIntentSP &deliveryIntent, QObject *parent)
    : AbstractResourceQmlWrapper(deliveryIntent, *new DeliveryIntentQmlWrapperPrivate, parent)
{
    setupEntity();
}

DeliveryIntentQmlWrapper::~DeliveryIntentQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(DeliveryIntent)

QQmlListProperty<DropIntentQmlWrapper> DeliveryIntentQmlWrapper::dropIntents() const
{
    Q_D(const DeliveryIntentQmlWrapper);
    return d->qmlDropIntentsList;
}

void DeliveryIntentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> & /*old*/)
{
    Q_D(DeliveryIntentQmlWrapper);
    DeliveryIntentSP deliveryIntent = entity<DeliveryIntent>();
    Q_ASSERT(deliveryIntent);

    connect(deliveryIntent.data(), &DeliveryIntent::dropIntentsChanged, entityConnectContext(),
            [d]() { d->updateDropIntents(); });

    d->updateDropIntents();
}

void DeliveryIntentQmlWrapperPrivate::updateDropIntents()
{
    Q_Q(DeliveryIntentQmlWrapper);
    DeliveryIntentSP resourcePool = q->entity<DeliveryIntent>();
    for (DropIntentQmlWrapper *wrapper : qAsConst(dropIntents))
        wrapper->deleteLater();

    dropIntents.clear();
    const auto ndeIntents = resourcePool->dropIntents();
    for (const DropIntentSP &dropIntent : ndeIntents)
        dropIntents << dropIntent->toQmlWrapper(q);

    qmlDropIntentsList =
        QQmlListProperty<Proof::Jdf::DropIntentQmlWrapper>(q, &dropIntents,
                                                           &DeliveryIntentQmlWrapperPrivate::dropIntentsCount,
                                                           &DeliveryIntentQmlWrapperPrivate::dropIntentAt);
    emit q->dropIntentsChanged(qmlDropIntentsList);
}

DropIntentQmlWrapper *DeliveryIntentQmlWrapperPrivate::dropIntentAt(QQmlListProperty<DropIntentQmlWrapper> *property,
                                                                    int index)
{
    return static_cast<QVector<DropIntentQmlWrapper *> *>(property->data)->at(index);
}

int DeliveryIntentQmlWrapperPrivate::dropIntentsCount(QQmlListProperty<DropIntentQmlWrapper> *property)
{
    return static_cast<QVector<DropIntentQmlWrapper *> *>(property->data)->count();
}
