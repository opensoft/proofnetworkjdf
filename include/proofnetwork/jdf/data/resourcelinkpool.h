#ifndef RESOURCELINKPOOL_H
#define RESOURCELINKPOOL_H

#include "proofnetwork/jdf/data/qmlwrappers/resourcelinkpoolqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QVector>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class ResourceLinkPoolPrivate;
class PROOF_NETWORK_JDF_EXPORT ResourceLinkPool : public NetworkDataEntity // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ResourceLinkPool)
public:
    QVector<ComponentLinkSP> componentLinks() const;
    CuttingParamsLinkSP cuttingParamsLink() const;
    QVector<MediaLinkSP> mediaLinks() const;
    LaminatingIntentLinkSP laminatingIntentLink() const;
    DeliveryIntentLinkSP deliveryIntentLink() const;
    FoldingParamsLinkSP foldingParamsLink() const;
    BoxPackingParamsLinkSP boxPackingParamsLink() const;

    void setComponentLinks(const QVector<ComponentLinkSP> &componentLinks);
    void addComponentLink(const ComponentLinkSP &componentLink);
    void setCuttingParamsLink(const CuttingParamsLinkSP &cuttingParams);
    void setMediaLinks(const QVector<MediaLinkSP> &mediaLinks);
    void addMediaLink(const MediaLinkSP &mediaLink);
    void setLaminatingIntentLink(const LaminatingIntentLinkSP &laminatingIntent);
    void setDeliveryIntentLink(const DeliveryIntentLinkSP &deliveryIntent);
    void setFoldingParamsLink(const FoldingParamsLinkSP &foldingParamsLink);
    void setBoxPackingParamsLink(const BoxPackingParamsLinkSP &boxPackingParamsLink);

    ResourceLinkPoolQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static ResourceLinkPoolSP create();

    static ResourceLinkPoolSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void componentLinksChanged();
    void cuttingParamsLinkChanged(const Proof::Jdf::CuttingParamsLinkSP &arg);
    void mediaLinksChanged();
    void laminatingIntentLinkChanged(const Proof::Jdf::LaminatingIntentLinkSP &arg);
    void deliveryIntentLinkChanged(const Proof::Jdf::DeliveryIntentLinkSP &arg);
    void foldingParamsLinkChanged(const Proof::Jdf::FoldingParamsLinkSP &arg);
    void boxPackingParamsLinkChanged(const Proof::Jdf::BoxPackingParamsLinkSP &arg);

protected:
    explicit ResourceLinkPool();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof
#endif // RESOURCELINKPOOL_H
