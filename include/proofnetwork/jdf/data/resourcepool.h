#ifndef PROOF_JDF_RESOURCEPOOL_H
#define PROOF_JDF_RESOURCEPOOL_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/data/qmlwrappers/resourcepoolqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofcore/objectscache.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class ResourcePoolPrivate;
class PROOF_NETWORK_JDF_EXPORT ResourcePool : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ResourcePool)
public:
    QList<ComponentSP> components() const;
    CuttingParamsSP cuttingParams() const;
    MediaSP media() const;
    LaminatingIntentSP laminatingIntent() const;
    FoldingParamsSP foldingParams() const;

    void setComponents(const QList<ComponentSP> &arg);
    void setCuttingParams(const CuttingParamsSP &arg);
    void setMedia(const MediaSP &media);
    void setLaminatingIntent(const LaminatingIntentSP &laminatingIntent);
    void setFoldingParams(const FoldingParamsSP &foldingParams);

    ResourcePoolQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static ResourcePoolSP create();

    static ResourcePoolSP fromJdf(QXmlStreamReader &xmlReader, const QString &jdfId);
    void toJdf(QXmlStreamWriter &jdfWriter);
    void toJdfLink(QXmlStreamWriter &jdfWriter);
    static ResourcePoolSP defaultObject();

signals:
    void componentsChanged();
    void cuttingParamsChanged(const Proof::Jdf::CuttingParamsSP &arg);
    void mediaChanged(const Proof::Jdf::MediaSP &arg);
    void laminatingIntentChanged(const Proof::Jdf::LaminatingIntentSP &arg);
    void foldingParamsChanged(const Proof::Jdf::FoldingParamsSP &arg);

protected:
    explicit ResourcePool();

};

}
}

#endif // PROOF_JDF_RESOURCEPOOL_H
