#include "bundleqmlwrapper.h"

#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/bundleitem.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"
#include "proofnetwork/jdf/data/qmlwrappers/bundleitemqmlwrapper.h"

namespace Proof {
namespace Jdf {

class BundleQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(BundleQmlWrapper)

    void updateBundleItems();

    QList<BundleItemQmlWrapper *> bundleItems;
    QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper> qmlBundleItemsList;
    static BundleItemQmlWrapper *bundleItemAt(QQmlListProperty<BundleItemQmlWrapper> *property, int index);
    static int bundleItemsCount(QQmlListProperty<BundleItemQmlWrapper> *property);
};

BundleQmlWrapper::BundleQmlWrapper(const BundleSP &bundle, QObject *parent)
    : NetworkDataEntityQmlWrapper(bundle, *new BundleQmlWrapperPrivate, parent)
{
    setupEntity();
}

BundleQmlWrapper::~BundleQmlWrapper()
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Bundle)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Bundle, Proof::Jdf::BundleType, bundleType)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Bundle, int, totalAmount)

QQmlListProperty<BundleItemQmlWrapper> BundleQmlWrapper::bundleItems() const
{
    Q_D(const BundleQmlWrapper);
    return d->qmlBundleItemsList;
}

void BundleQmlWrapperPrivate::updateBundleItems()
{
    Q_Q(BundleQmlWrapper);
    for (BundleItemQmlWrapper *wrapper : bundleItems)
        wrapper->deleteLater();

    bundleItems.clear();

    BundleSP bundle = entity<Bundle>();
    for (const auto &bundleItem : bundle->bundleItems())
        bundleItems << bundleItem->toQmlWrapper(q);

    qmlBundleItemsList = QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper>(q, &bundleItems,
                                                                            &BundleQmlWrapperPrivate::bundleItemsCount,
                                                                            &BundleQmlWrapperPrivate::bundleItemAt);
    emit q->bundleItemsChanged(qmlBundleItemsList);
}

void BundleQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(BundleQmlWrapper);
    BundleSP bundle = d->entity<Bundle>();
    Q_ASSERT(bundle);

    connect(bundle.data(), &Bundle::bundleTypeChanged, this, &BundleQmlWrapper::bundleTypeChanged);
    connect(bundle.data(), &Bundle::totalAmountChanged, this, &BundleQmlWrapper::totalAmountChanged);
    connect(bundle.data(), &Bundle::bundleItemsChanged,
            d->lambdaConnectContext, [d](){d->updateBundleItems();});

    BundleSP oldBundle = qSharedPointerCast<Bundle>(old);
    if (oldBundle) {
        if (bundle->bundleType() != oldBundle->bundleType())
            emit bundleTypeChanged(bundle->bundleType());
        if (bundle->totalAmount() != oldBundle->totalAmount())
            emit totalAmountChanged(bundle->totalAmount());
    }

    d->updateBundleItems();
}

BundleItemQmlWrapper *BundleQmlWrapperPrivate::bundleItemAt(QQmlListProperty<BundleItemQmlWrapper> *property, int index)
{
    return static_cast<QList<BundleItemQmlWrapper *> *>(property->data)->at(index);
}

int BundleQmlWrapperPrivate::bundleItemsCount(QQmlListProperty<BundleItemQmlWrapper> *property)
{
    return static_cast<QList<BundleItemQmlWrapper *> *>(property->data)->count();
}

}
}

