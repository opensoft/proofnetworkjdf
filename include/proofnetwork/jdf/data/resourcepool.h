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

    void setComponents(const QList<ComponentSP> &arg);
    void setCuttingParams(const CuttingParamsSP &arg);
    void setMedia(const MediaSP &media);

    void updateFrom(const NetworkDataEntitySP &other) override;
    ResourcePoolQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static ResourcePoolSP create();

    static ResourcePoolSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);
    static ResourcePoolSP defaultObject();

signals:
    void componentsChanged();
    void cuttingParamsChanged(const Proof::Jdf::CuttingParamsSP &arg);
    void mediaChanged(const Proof::Jdf::MediaSP &arg);

protected:
    explicit ResourcePool();

};

}
}

#endif // PROOF_JDF_RESOURCEPOOL_H
