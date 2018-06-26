#ifndef PROOF_JDF_BUNDLE_H
#define PROOF_JDF_BUNDLE_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/bundleqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class BundlePrivate;
class PROOF_NETWORK_JDF_EXPORT Bundle : public NetworkDataEntity // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Bundle)
public:
    BundleType bundleType() const;
    int totalAmount() const;
    QVector<BundleItemSP> bundleItems() const;

    void setBundleType(BundleType arg);
    void setTotalAmount(int arg);
    void setBundleItems(const QVector<BundleItemSP> &arg);
    void addBundleItem(const BundleItemSP &arg);

    BundleQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static BundleSP create();

    static BundleSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void bundleTypeChanged(Proof::Jdf::BundleType arg);
    void totalAmountChanged(int arg);
    void bundleItemsChanged();

protected:
    explicit Bundle();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_BUNDLE_H
