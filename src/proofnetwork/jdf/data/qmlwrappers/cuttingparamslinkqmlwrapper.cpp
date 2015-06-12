#include "cuttingparamslinkqmlwrapper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"

namespace Proof {
namespace Jdf {

class CuttingParamsLinkQmlWrapperPrivate : public AbstractResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CuttingParamsLinkQmlWrapper)
};

}
}

using namespace Proof::Jdf;

CuttingParamsLinkQmlWrapper::CuttingParamsLinkQmlWrapper(const CuttingParamsLinkSP &cuttingParamsLink, QObject *parent)
    : AbstractResourceLinkQmlWrapper(cuttingParamsLink, *new CuttingParamsLinkQmlWrapperPrivate, parent)
{
}
PROOF_NDE_WRAPPER_TOOLS_IMPL(CuttingParamsLink)
