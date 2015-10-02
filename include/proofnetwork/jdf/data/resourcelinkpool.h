#ifndef RESOURCELINKPOOL_H
#define RESOURCELINKPOOL_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/data/qmlwrappers/resourcelinkpoolqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QXmlStreamReader>
#include <QList>

namespace Proof {
namespace Jdf {

class ResourceLinkPoolPrivate;
class PROOF_NETWORK_JDF_EXPORT ResourceLinkPool : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ResourceLinkPool)
public:
    QList<ComponentLinkSP> componentLinks() const;
    CuttingParamsLinkSP cuttingParamsLink() const;
    MediaLinkSP mediaLink() const;
    LaminatingIntentLinkSP laminatingIntentLink() const;
    FoldingParamsLinkSP foldingParamsLink() const;

    void setComponentLinks(const QList<ComponentLinkSP> &componentLinks);
    void addComponentLink(const ComponentLinkSP &componentLink);
    void setCuttingParamsLink(const CuttingParamsLinkSP &cuttingParams);
    void setMediaLink(const MediaLinkSP &mediaLink);
    void setLaminatingIntentLink(const LaminatingIntentLinkSP &laminatingIntent);
    void setFoldingParamsLink(const FoldingParamsLinkSP &foldingParamsLink);

    ResourceLinkPoolQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static ResourceLinkPoolSP create();

    static ResourceLinkPoolSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void componentLinksChanged();
    void cuttingParamsLinkChanged(const Proof::Jdf::CuttingParamsLinkSP &arg);
    void mediaLinkChanged(const Proof::Jdf::MediaLinkSP &arg);
    void laminatingIntentLinkChanged(const Proof::Jdf::LaminatingIntentLinkSP &arg);
    void foldingParamsLinkChanged(const Proof::Jdf::FoldingParamsLinkSP &arg);

protected:
    explicit ResourceLinkPool();
};

}
}
#endif // RESOURCELINKPOOL_H
