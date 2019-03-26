#ifndef XJDF_PARTAMOUNT_H
#define XJDF_PARTAMOUNT_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class PartAmountPrivate;
class PROOF_NETWORK_XJDF_EXPORT PartAmount : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(PartAmount)
public:
    PartAmount(const PartAmount &) = delete;
    PartAmount &operator=(const PartAmount &) = delete;
    PartAmount(PartAmount &&) = delete;
    PartAmount &operator=(PartAmount &&) = delete;
    ~PartAmount() = default;

    qulonglong amount() const;
    void setAmount(qulonglong arg);

    static PartAmountSP create();

    static PartAmountSP fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document = XJdfDocumentSP());
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void amountChanged(qulonglong arg);

protected:
    explicit PartAmount();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_PARTAMOUNT_H
