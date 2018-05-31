#include "boxpackingparamsqmlwrapper.h"

#include "proofnetwork/jdf/data/boxpackingparams.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class BoxPackingParamsQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(BoxPackingParamsQmlWrapper)
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

BoxPackingParamsQmlWrapper::BoxPackingParamsQmlWrapper(const BoxPackingParamsSP &boxPackingParams, QObject *parent)
    : AbstractResourceQmlWrapper(boxPackingParams, *new BoxPackingParamsQmlWrapperPrivate, parent)
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(BoxPackingParams)
