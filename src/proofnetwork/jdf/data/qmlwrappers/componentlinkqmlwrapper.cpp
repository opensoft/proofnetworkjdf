#include "proofnetwork/jdf/data/qmlwrappers/componentlinkqmlwrapper.h"

#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourcelinkqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class ComponentLinkQmlWrapperPrivate : public AbstractPhysicalResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ComponentLinkQmlWrapper)
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ComponentLinkQmlWrapper::ComponentLinkQmlWrapper(const ComponentLinkSP &component, QObject *parent)
    : AbstractPhysicalResourceLinkQmlWrapper(component, *new ComponentLinkQmlWrapperPrivate, parent)
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(ComponentLink)
