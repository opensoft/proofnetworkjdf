#ifndef JDFLAMINATINGINTENTQMLWRAPPER_H
#define JDFLAMINATINGINTENTQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class LaminatingIntent;

class LaminatingIntentQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT LaminatingIntentQmlWrapper : public AbstractResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::LaminatingSurface surface READ surface NOTIFY surfaceChanged)
    Q_DECLARE_PRIVATE(LaminatingIntentQmlWrapper)
public:
    explicit LaminatingIntentQmlWrapper(const LaminatingIntentSP &laminatingIntent, QObject *parent = nullptr);
    ~LaminatingIntentQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(LaminatingIntent)

    LaminatingSurface surface() const;

signals:
    void surfaceChanged(Proof::Jdf::LaminatingSurface surface);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFLAMINATINGINTENTQMLWRAPPER_H
