#ifndef PROOF_JDF_RESOURCEPOOLQMLWRAPPER_H
#define PROOF_JDF_RESOURCEPOOLQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class ComponentQmlWrapper;
class CuttingParamsQmlWrapper;
class MediaQmlWrapper;
class FoldingParamsQmlWrapper;

class ResourcePoolQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT ResourcePoolQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> components READ components NOTIFY componentsChanged)
    Q_PROPERTY(Proof::Jdf::CuttingParamsQmlWrapper *cuttingParams READ cuttingParams NOTIFY cuttingParamsChanged)
    Q_PROPERTY(Proof::Jdf::MediaQmlWrapper *media READ media NOTIFY mediaChanged)

    Q_DECLARE_PRIVATE(ResourcePoolQmlWrapper)
public:
    explicit ResourcePoolQmlWrapper(const ResourcePoolSP &resourcePool, QObject *parent = 0);
    ~ResourcePoolQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(ResourcePool)

    QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> components() const;

    CuttingParamsQmlWrapper *cuttingParams() const;
    MediaQmlWrapper *media() const;
    FoldingParamsQmlWrapper *foldingParams() const;

signals:
    void componentsChanged(const QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> &arg);
    void cuttingParamsChanged(Proof::Jdf::CuttingParamsQmlWrapper *arg);
    void mediaChanged(Proof::Jdf::MediaQmlWrapper *arg);
    void foldingParamsChanged(Proof::Jdf::FoldingParamsQmlWrapper *arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // PROOF_JDF_RESOURCEPOOLQMLWRAPPER_H
