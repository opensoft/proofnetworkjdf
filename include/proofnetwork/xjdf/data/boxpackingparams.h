#ifndef XJDF_BOXPACKINGPARAMS_H
#define XJDF_BOXPACKINGPARAMS_H

#include "resource.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class BoxPackingParamsPrivate;
class PROOF_NETWORK_XJDF_EXPORT BoxPackingParams : public Resource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BoxPackingParams)
public:
    BoxPackingParams(const BoxPackingParams &) = delete;
    BoxPackingParams &operator=(const Resource &) = delete;
    BoxPackingParams(Resource &&) = delete;
    BoxPackingParams &operator=(BoxPackingParams &&) = delete;
    ~BoxPackingParams() = default;

    BoxType boxType() const;
    QString boxTypeDetails() const;

    void setBoxType(BoxType arg);
    void setBoxTypeDetails(const QString &arg);

    static BoxPackingParamsSP create();

    static BoxPackingParamsSP fromXJdf(QXmlStreamReader &reader);
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void boxTypeChanged(Proof::XJdf::BoxType arg);
    void boxTypeDetailsChanged(const QString &arg);

protected:
    BoxPackingParams();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_BOXPACKINGPARAMS_H
