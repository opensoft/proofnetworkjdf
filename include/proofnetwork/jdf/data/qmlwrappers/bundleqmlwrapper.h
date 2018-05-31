#ifndef PROOF_JDF_BUNDLEQMLWRAPPER_H
#define PROOF_JDF_BUNDLEQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class Bundle;
class BundleItemQmlWrapper;

class BundleQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT BundleQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::BundleType bundleType READ bundleType NOTIFY bundleTypeChanged)
    Q_PROPERTY(int totalAmount READ totalAmount NOTIFY totalAmountChanged)
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper> bundleItems READ bundleItems NOTIFY bundleItemsChanged)
    Q_DECLARE_PRIVATE(BundleQmlWrapper)
public:
    explicit BundleQmlWrapper(const BundleSP &bundle, QObject *parent = nullptr);
    ~BundleQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(Bundle)

    BundleType bundleType() const;
    int totalAmount() const;
    QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper> bundleItems() const;

signals:
    void bundleTypeChanged(Proof::Jdf::BundleType bundleType);
    void totalAmountChanged(int totalAmount);
    void bundleItemsChanged(const QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper> &bundleItems);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_BUNDLEQMLWRAPPER_H
