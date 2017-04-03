#ifndef PROOF_JDF_BUNDLE_H
#define PROOF_JDF_BUNDLE_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/bundleqmlwrapper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class BundlePrivate;
class PROOF_NETWORK_JDF_EXPORT Bundle : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Bundle)
public:
    BundleType bundleType() const;
    int totalAmount() const;
    BundleItemSP bundleItem() const;

    void setBundleType(BundleType arg);
    void setTotalAmount(int arg);
    void setBundleItem(const BundleItemSP &arg);

    BundleQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static BundleSP create();

    static BundleSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void bundleTypeChanged(Proof::Jdf::BundleType arg);
    void totalAmountChanged(int arg);
    void bundleItemChanged(const Proof::Jdf::BundleItemSP &arg);

protected:
    explicit Bundle();

};

}
}

#endif // PROOF_JDF_BUNDLE_H
