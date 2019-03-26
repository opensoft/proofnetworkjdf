#ifndef XJDF_DROPITEM_H
#define XJDF_DROPITEM_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class DropItemPrivate;
class PROOF_NETWORK_XJDF_EXPORT DropItem : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DropItem)
public:
    DropItem(const DropItem &) = delete;
    DropItem &operator=(const XJdfAbstractNode &) = delete;
    DropItem(XJdfAbstractNode &&) = delete;
    DropItem &operator=(DropItem &&) = delete;
    ~DropItem() = default;

    qulonglong amount() const;
    ProductSP product() const;

    void setAmount(qulonglong arg);
    void setProduct(const ProductSP &arg);

    static DropItemSP create();

    static DropItemSP fromXJdf(QXmlStreamReader &reader);
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void amountChanged(qulonglong arg);
    void productChanged(const Proof::XJdf::ProductSP &arg);

protected:
    explicit DropItem();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_DROPITEM_H
