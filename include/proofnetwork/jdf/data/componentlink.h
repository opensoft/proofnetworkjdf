#ifndef COMPONENTLINK_H
#define COMPONENTLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/component.h"

namespace Proof {
namespace Jdf {

class ComponentLink : public AbstractResourceLink
{
    Q_OBJECT
public:
    explicit ComponentLink(const ComponentSP &component, QObject *parent = 0)
        : AbstractResourceLink( qSharedPointerCast<AbstractResource>(component), parent)
    {
    }
};

}
}
#endif // COMPONENTLINK_H
