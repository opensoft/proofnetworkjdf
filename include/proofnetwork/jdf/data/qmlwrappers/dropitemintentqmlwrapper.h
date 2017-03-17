#ifndef DROPITEMINTENTQMLWRAPPER_H
#define DROPITEMINTENTQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

#include "proofnetwork/jdf/data/qmlwrappers/componentqmlwrapper.h"

namespace Proof {
namespace Jdf {

class DropItemIntent;

class DropItemIntentQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT DropItemIntentQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(ComponentQmlWrapper component READ component NOTIFY componentChanged)
    Q_DECLARE_PRIVATE(DropItemIntentQmlWrapper)
public:
    explicit DropItemIntentQmlWrapper(const DropItemIntentSP &dropItemIntent, QObject *parent = nullptr);
    ~DropItemIntentQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(DropIntent)

    ComponentQmlWrapper *component() const;

signals:
    void componentChanged(Proof::Jdf::ComponentQmlWrapper *component);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}

#endif // DROPITEMINTENTQMLWRAPPER_H
