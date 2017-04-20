#ifndef PROOF_JDF_BUNDLEITEM_H
#define PROOF_JDF_BUNDLEITEM_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/bundleitemqmlwrapper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class BundleItemPrivate;
class PROOF_NETWORK_JDF_EXPORT BundleItem : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BundleItem)
public:
    int amount() const;
    ComponentSP component() const;

    void setAmount(int arg);
    void setComponent(const ComponentSP &arg);

    BundleItemQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static BundleItemSP create();

    static BundleItemSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void amountChanged(int arg);
    void componentChanged(const ComponentSP &component);

protected:
    explicit BundleItem();

};

}
}

#endif // PROOF_JDF_BUNDLEITEM_H
