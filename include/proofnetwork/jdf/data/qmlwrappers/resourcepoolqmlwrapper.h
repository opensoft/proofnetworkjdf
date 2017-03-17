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
class LaminatingIntentQmlWrapper;

class ResourcePoolQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT ResourcePoolQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> components READ components NOTIFY componentsChanged)
    Q_PROPERTY(Proof::Jdf::CuttingParamsQmlWrapper *cuttingParams READ cuttingParams NOTIFY cuttingParamsChanged)
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::MediaQmlWrapper> media READ media NOTIFY mediaChanged)
    Q_PROPERTY(Proof::Jdf::FoldingParamsQmlWrapper *foldingParams READ foldingParams NOTIFY foldingParamsChanged)
    Q_PROPERTY(Proof::Jdf::LaminatingIntentQmlWrapper *laminatingIntent READ laminatingIntent NOTIFY laminatingIntentChanged)

    Q_DECLARE_PRIVATE(ResourcePoolQmlWrapper)

public:
    explicit ResourcePoolQmlWrapper(const ResourcePoolSP &resourcePool, QObject *parent = nullptr);
    ~ResourcePoolQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(ResourcePool)

    QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> components() const;

    CuttingParamsQmlWrapper *cuttingParams() const;
    QQmlListProperty<Proof::Jdf::MediaQmlWrapper> media() const;
    FoldingParamsQmlWrapper *foldingParams() const;
    LaminatingIntentQmlWrapper *laminatingIntent() const;

signals:
    void componentsChanged(const QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> &components);
    void cuttingParamsChanged(Proof::Jdf::CuttingParamsQmlWrapper *cuttingParams);
    void mediaChanged(const QQmlListProperty<Proof::Jdf::MediaQmlWrapper> &media);
    void foldingParamsChanged(Proof::Jdf::FoldingParamsQmlWrapper *foldingParams);
    void laminatingIntentChanged(Proof::Jdf::LaminatingIntentQmlWrapper *laminatingIntent);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // PROOF_JDF_RESOURCEPOOLQMLWRAPPER_H
