#ifndef COMPONENTLINK_H
#define COMPONENTLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/qmlwrappers/componentlinkqmlwrapper.h"

namespace Proof {
namespace Jdf {

class ComponentLinkPrivate;
class ComponentLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ComponentLink)
public:
    ComponentLinkQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static ComponentLinkSP create();

    static ComponentLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    static ComponentLinkSP defaultObject();

protected:
    explicit ComponentLink(QObject *parent = 0);
};

}
}
#endif // COMPONENTLINK_H
