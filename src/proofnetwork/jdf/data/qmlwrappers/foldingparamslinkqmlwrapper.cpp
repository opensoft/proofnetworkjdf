#include "foldingparamslinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"
#include "proofnetwork/jdf/data/foldingparamslink.h"

namespace Proof {
namespace Jdf {

class FoldingParamsLinkQmlWrapperPrivate : public AbstractResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(FoldingParamsLinkQmlWrapper)
};

}
}

using namespace Proof::Jdf;

FoldingParamsLinkQmlWrapper::FoldingParamsLinkQmlWrapper(const FoldingParamsLinkSP &folding, QObject *parent) :
    AbstractResourceLinkQmlWrapper(folding, *new FoldingParamsLinkQmlWrapperPrivate, parent)
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(FoldingParamsLink)
