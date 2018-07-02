#ifndef PROOF_JDF_RESOURCEPOOL_H
#define PROOF_JDF_RESOURCEPOOL_H

#include "proofcore/objectscache.h"

#include "proofnetwork/jdf/data/qmlwrappers/resourcepoolqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class ResourcePoolPrivate;
class PROOF_NETWORK_JDF_EXPORT ResourcePool : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ResourcePool)
public:
    QVector<ComponentSP> components() const;
    CuttingParamsSP cuttingParams() const;
    QVector<MediaSP> media() const;
    LaminatingIntentSP laminatingIntent() const;
    DeliveryIntentSP deliveryIntent() const;
    FoldingParamsSP foldingParams() const;
    BoxPackingParamsSP boxPackingParams() const;
    QVector<LayoutSP> layouts() const;

    void setComponents(const QVector<ComponentSP> &arg);
    void addComponent(const ComponentSP &arg);
    void setCuttingParams(const CuttingParamsSP &arg);
    void setMedia(const QVector<MediaSP> &arg);
    void addMedia(const MediaSP &arg);
    void setLaminatingIntent(const LaminatingIntentSP &laminatingIntent);
    void setDeliveryIntent(const DeliveryIntentSP &arg);
    void setFoldingParams(const FoldingParamsSP &foldingParams);
    void setBoxPackingParams(const BoxPackingParamsSP &boxPackingParams);
    void setLayouts(const QVector<LayoutSP> &arg);
    void addLayout(const LayoutSP &arg);

    ResourcePoolQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static ResourcePoolSP create();

    static ResourcePoolSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void componentsChanged();
    void cuttingParamsChanged(const Proof::Jdf::CuttingParamsSP &arg);
    void mediaChanged();
    void laminatingIntentChanged(const Proof::Jdf::LaminatingIntentSP &arg);
    void deliveryIntentChanged(const Proof::Jdf::DeliveryIntentSP &arg);
    void foldingParamsChanged(const Proof::Jdf::FoldingParamsSP &arg);
    void boxPackingParamsChanged(const Proof::Jdf::BoxPackingParamsSP &arg);
    void layoutsChanged();

protected:
    explicit ResourcePool();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_RESOURCEPOOL_H
