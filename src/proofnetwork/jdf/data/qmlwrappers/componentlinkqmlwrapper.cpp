#include "componentlinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"
#include "proofnetwork/jdf/data/componentlink.h"

namespace Proof {
namespace Jdf {

class ComponentLinkQmlWrapperPrivate : public AbstractResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ComponentLinkQmlWrapper)
};

}
}

using namespace Proof::Jdf;

ComponentLinkQmlWrapper::ComponentLinkQmlWrapper(const ComponentLinkSP &component, QObject *parent) :
    AbstractResourceLinkQmlWrapper(component, *new ComponentLinkQmlWrapperPrivate, parent)
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(ComponentLink)
