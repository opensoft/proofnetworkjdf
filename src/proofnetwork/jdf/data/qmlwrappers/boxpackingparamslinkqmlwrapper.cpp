#include "boxpackingparamslinkqmlwrapper.h"

#include "proofnetwork/jdf/data/boxpackingparamslink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class BoxPackingParamsLinkQmlWrapperPrivate : public AbstractResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(BoxPackingParamsLinkQmlWrapper)
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

BoxPackingParamsLinkQmlWrapper::BoxPackingParamsLinkQmlWrapper(const BoxPackingParamsLinkSP &boxPackingParamsLink,
                                                               QObject *parent)
    : AbstractResourceLinkQmlWrapper(boxPackingParamsLink, *new BoxPackingParamsLinkQmlWrapperPrivate, parent)
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(BoxPackingParamsLink)
