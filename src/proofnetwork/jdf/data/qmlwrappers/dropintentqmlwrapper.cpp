#include "dropintentqmlwrapper.h"

#include "proofnetwork/jdf/data/dropintent.h"
#include "proofnetwork/jdf/data/dropitemintent.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class DropIntentQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(DropIntentQmlWrapper)

    void updateDropItemIntents();

    QVector<DropItemIntentQmlWrapper *> dropItemIntents;
    QQmlListProperty<Proof::Jdf::DropItemIntentQmlWrapper> qmlDropItemIntentsList;
    static DropItemIntentQmlWrapper *dropItemIntentAt(QQmlListProperty<DropItemIntentQmlWrapper> *property, int index);
    static int dropItemIntentsCount(QQmlListProperty<DropItemIntentQmlWrapper> *property);
};

DropIntentQmlWrapper::DropIntentQmlWrapper(const DropIntentSP &dropIntent, QObject *parent)
    : NetworkDataEntityQmlWrapper(dropIntent, *new DropIntentQmlWrapperPrivate, parent)
{
    setupEntity();
}

DropIntentQmlWrapper::~DropIntentQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(DropIntent)

QQmlListProperty<DropItemIntentQmlWrapper> DropIntentQmlWrapper::dropItemIntents() const
{
    Q_D_CONST(DropIntentQmlWrapper);
    return d->qmlDropItemIntentsList;
}

void DropIntentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> & /*old*/)
{
    Q_D(DropIntentQmlWrapper);
    DropIntentSP dropIntent = entity<DropIntent>();
    Q_ASSERT(dropIntent);

    connect(dropIntent.data(), &DropIntent::dropItemIntentsChanged, entityConnectContext(),
            [d]() { d->updateDropItemIntents(); });

    d->updateDropItemIntents();
}

void DropIntentQmlWrapperPrivate::updateDropItemIntents()
{
    Q_Q(DropIntentQmlWrapper);
    DropIntentSP dropIntent = q->entity<DropIntent>();
    for (DropItemIntentQmlWrapper *wrapper : qAsConst(dropItemIntents))
        wrapper->deleteLater();

    dropItemIntents.clear();
    const auto ndeIntents = dropIntent->dropItemIntents();
    for (const DropItemIntentSP &dropItemIntent : ndeIntents)
        dropItemIntents << dropItemIntent->toQmlWrapper(q);

    qmlDropItemIntentsList =
        QQmlListProperty<Proof::Jdf::DropItemIntentQmlWrapper>(q, &dropItemIntents,
                                                               &DropIntentQmlWrapperPrivate::dropItemIntentsCount,
                                                               &DropIntentQmlWrapperPrivate::dropItemIntentAt);
    emit q->dropItemIntentsChanged(qmlDropItemIntentsList);
}

DropItemIntentQmlWrapper *
DropIntentQmlWrapperPrivate::dropItemIntentAt(QQmlListProperty<DropItemIntentQmlWrapper> *property, int index)
{
    return static_cast<QVector<DropItemIntentQmlWrapper *> *>(property->data)->at(index);
}

int DropIntentQmlWrapperPrivate::dropItemIntentsCount(QQmlListProperty<DropItemIntentQmlWrapper> *property)
{
    return static_cast<QVector<DropItemIntentQmlWrapper *> *>(property->data)->count();
}

} // namespace Jdf
} // namespace Proof
