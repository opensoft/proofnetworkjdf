#ifndef PROOF_JDF_BUNDLEITEMQMLWRAPPER_H
#define PROOF_JDF_BUNDLEITEMQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class BundleItem;

class BundleItemQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT BundleItemQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(int amount READ amount NOTIFY amountChanged)
    Q_DECLARE_PRIVATE(BundleItemQmlWrapper)
public:
    explicit BundleItemQmlWrapper(const BundleItemSP &bundleItem, QObject *parent = 0);
    ~BundleItemQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(BundleItem)

    int amount() const;

signals:
    void amountChanged(int amount);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}

#endif // PROOF_JDF_BUNDLEITEMQMLWRAPPER_H
