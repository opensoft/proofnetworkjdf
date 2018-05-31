#include "foldingparamslinkqmlwrapper.h"

#include "proofnetwork/jdf/data/foldingparamslink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class FoldingParamsLinkQmlWrapperPrivate : public AbstractResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(FoldingParamsLinkQmlWrapper)
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

FoldingParamsLinkQmlWrapper::FoldingParamsLinkQmlWrapper(const FoldingParamsLinkSP &folding, QObject *parent)
    : AbstractResourceLinkQmlWrapper(folding, *new FoldingParamsLinkQmlWrapperPrivate, parent)
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(FoldingParamsLink)
