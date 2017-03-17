#ifndef COMPONENTLINK_H
#define COMPONENTLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractphysicalresourcelink.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/qmlwrappers/componentlinkqmlwrapper.h"

namespace Proof {
namespace Jdf {

class ComponentLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT ComponentLink : public AbstractPhysicalResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ComponentLink)
public:
    ComponentLinkQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static ComponentLinkSP create();

    static ComponentLinkSP fromJdf(const QXmlStreamReader &xmlReader);

protected:
    explicit ComponentLink(QObject *parent = nullptr);
};

}
}
#endif // COMPONENTLINK_H
