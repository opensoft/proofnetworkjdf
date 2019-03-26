#ifndef XJDF_CUTTINGPARAMS_H
#define XJDF_CUTTINGPARAMS_H

#include "resource.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class CuttingParamsPrivate;
class PROOF_NETWORK_XJDF_EXPORT CuttingParams : public Resource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CuttingParams)
public:
    CuttingParams(const CuttingParams &) = delete;
    CuttingParams &operator=(const Resource &) = delete;
    CuttingParams(Resource &&) = delete;
    CuttingParams &operator=(CuttingParams &&) = delete;
    ~CuttingParams() = default;

    QVector<CutBlockSP> cutBlocks() const;
    void setCutBlocks(const QVector<CutBlockSP> &arg);

    static CuttingParamsSP create();

    static CuttingParamsSP fromXJdf(QXmlStreamReader &reader);
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void cutBlocksChanged(const QVector<Proof::XJdf::CutBlockSP> &arg);

protected:
    explicit CuttingParams();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_CUTTINGPARAMS_H
