#include "componentlinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourcelinkqmlwrapper_p.h"
#include "proofnetwork/jdf/data/componentlink.h"

namespace Proof {
namespace Jdf {

class ComponentLinkQmlWrapperPrivate : public AbstractPhysicalResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ComponentLinkQmlWrapper)
};

}
}

using namespace Proof::Jdf;

ComponentLinkQmlWrapper::ComponentLinkQmlWrapper(const ComponentLinkSP &component, QObject *parent) :
    AbstractPhysicalResourceLinkQmlWrapper(component, *new ComponentLinkQmlWrapperPrivate, parent)
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(ComponentLink)
