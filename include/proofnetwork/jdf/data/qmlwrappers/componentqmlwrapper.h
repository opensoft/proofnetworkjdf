#ifndef PROOF_JDF_COMPONENTQMLWRAPPER_H
#define PROOF_JDF_COMPONENTQMLWRAPPER_H


#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class Component;
class BundleQmlWrapper;

class ComponentQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT ComponentQmlWrapper : public AbstractPhysicalResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::ApiHelper::ComponentType componentType READ componentType NOTIFY componentTypeChanged)
    Q_PROPERTY(Proof::Jdf::BundleQmlWrapper *bundle READ bundle NOTIFY bundleChanged)
    Q_DECLARE_PRIVATE(ComponentQmlWrapper)
public:
    explicit ComponentQmlWrapper(const ComponentSP &component, QObject *parent = 0);
    ~ComponentQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(Component)

    Proof::Jdf::ApiHelper::ComponentType componentType() const;
    Proof::Jdf::BundleQmlWrapper *bundle() const;

signals:
    void componentTypeChanged(Proof::Jdf::ApiHelper::ComponentType arg);
    void bundleChanged(Proof::Jdf::BundleQmlWrapper *arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}

#endif // PROOF_JDF_COMPONENTQMLWRAPPER_H
