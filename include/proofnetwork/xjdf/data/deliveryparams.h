#ifndef XJDF_DELIVERYPARAMS_H
#define XJDF_DELIVERYPARAMS_H

#include "resource.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class DeliveryParamsPrivate;
class PROOF_NETWORK_XJDF_EXPORT DeliveryParams : public Resource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeliveryParams)
public:
    DeliveryParams(const DeliveryParams &) = delete;
    DeliveryParams &operator=(const Resource &) = delete;
    DeliveryParams(Resource &&) = delete;
    DeliveryParams &operator=(DeliveryParams &&) = delete;
    ~DeliveryParams() = default;

    QDateTime required() const;
    QVector<DropItemSP> items() const;

    void setRequired(const QDateTime &arg);
    void setItems(const QVector<DropItemSP> &arg);

    static DeliveryParamsSP create();

    static DeliveryParamsSP fromXJdf(QXmlStreamReader &xjdfReader);
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;

signals:
    void requiredChanged(const QDateTime &arg) const;
    void itemsChanged(const QVector<DropItemSP> &arg) const;

protected:
    DeliveryParams();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_DELIVERYPARAMS_H
