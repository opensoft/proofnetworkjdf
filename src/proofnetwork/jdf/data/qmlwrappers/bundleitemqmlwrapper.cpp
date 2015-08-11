#include "bundleitemqmlwrapper.h"

#include "proofnetwork/jdf/data/bundleitem.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class BundleItemQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(BundleItemQmlWrapper)
};

BundleItemQmlWrapper::BundleItemQmlWrapper(const BundleItemSP &bundleItem, QObject *parent)
    : NetworkDataEntityQmlWrapper(bundleItem, *new BundleItemQmlWrapperPrivate, parent)
{
    setupEntity();
}

BundleItemQmlWrapper::~BundleItemQmlWrapper()
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(BundleItem)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(BundleItem, int, amount)

void BundleItemQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(BundleItemQmlWrapper);
    BundleItemSP bundleItem = d->entity<BundleItem>();
    Q_ASSERT(bundleItem);

    connect(bundleItem.data(), &BundleItem::amountChanged, this, &BundleItemQmlWrapper::amountChanged);

    BundleItemSP oldBundleItem = qSharedPointerCast<BundleItem>(old);
    if (oldBundleItem) {
        if (bundleItem->amount() != oldBundleItem->amount())
            emit amountChanged(bundleItem->amount());
    }
}

}
}
