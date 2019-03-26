#ifndef XJDF_PART_H
#define XJDF_PART_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class PartPrivate;
class PROOF_NETWORK_XJDF_EXPORT Part : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Part)
public:
    Part(const Part &) = delete;
    Part &operator=(const Part &) = delete;
    Part(Part &&) = delete;
    Part &operator=(Part &&) = delete;
    ~Part() = default;

    ProductSP product() const;
    CutBlockSP block() const;

    void setProduct(const ProductSP &arg);
    void setBlock(const CutBlockSP &arg);

    static PartSP create();

    static PartSP fromXJdf(QXmlStreamReader &reader);
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void productChanged(const Proof::XJdf::ProductSP &arg);
    void blockChanged(const Proof::XJdf::CutBlockSP &arg);

protected:
    explicit Part();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_PART_H
