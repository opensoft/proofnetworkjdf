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

    void updateBundleItem();

    BundleItemQmlWrapper *bundleItem = nullptr;
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

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Bundle, Proof::Jdf::ApiHelper::BundleType, bundleType)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Bundle, int, totalAmount)

BundleItemQmlWrapper *BundleQmlWrapper::bundleItem() const
{
    Q_D(const BundleQmlWrapper);
    return d->bundleItem;
}

void BundleQmlWrapperPrivate::updateBundleItem()
{
    Q_Q(BundleQmlWrapper);
    BundleSP bundle = entity<Bundle>();
    if (!bundleItem)
        bundleItem = bundle->bundleItem()->toQmlWrapper(q);
    else
        bundleItem->setEntity(bundle->bundleItem());
    q->bundleItemChanged(bundleItem);
}

void BundleQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(BundleQmlWrapper);
    BundleSP bundle = d->entity<Bundle>();
    Q_ASSERT(bundle);

    connect(bundle.data(), &Bundle::bundleTypeChanged, this, &BundleQmlWrapper::bundleTypeChanged);
    connect(bundle.data(), &Bundle::totalAmountChanged, this, &BundleQmlWrapper::totalAmountChanged);
    connect(bundle.data(), &Bundle::bundleItemChanged,
            d->lambdaConnectContext, [d](){d->updateBundleItem();});

    BundleSP oldBundle = qSharedPointerCast<Bundle>(old);
    if (oldBundle) {
        if (bundle->bundleType() != oldBundle->bundleType())
            emit bundleTypeChanged(bundle->bundleType());
        if (bundle->totalAmount() != oldBundle->totalAmount())
            emit totalAmountChanged(bundle->totalAmount());
    }

    d->updateBundleItem();
}

}
}

