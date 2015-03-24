#ifndef PROOF_JDF_BUNDLEQMLWRAPPER_H
#define PROOF_JDF_BUNDLEQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class Bundle;

class BundleQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT BundleQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::ApiHelper::BundleType bundleType READ bundleType NOTIFY bundleTypeChanged)
    Q_PROPERTY(int totalAmount READ totalAmount NOTIFY totalAmountChanged)
    Q_DECLARE_PRIVATE(BundleQmlWrapper)
public:
    explicit BundleQmlWrapper(const BundleSP &bundle, QObject *parent = 0);
    ~BundleQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(Bundle)

    ApiHelper::BundleType bundleType() const;
    int totalAmount() const;

signals:
    void bundleTypeChanged(Proof::Jdf::ApiHelper::BundleType arg);
    void totalAmountChanged(int arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}

#endif // PROOF_JDF_BUNDLEQMLWRAPPER_H
