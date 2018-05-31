#include "laminatingintentlinkqmlwrapper.h"

#include "proofnetwork/jdf/data/laminatingintentlink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentLinkQmlWrapperPrivate : public AbstractResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(LaminatingIntentLinkQmlWrapper)
};

LaminatingIntentLinkQmlWrapper::LaminatingIntentLinkQmlWrapper(const LaminatingIntentLinkSP &laminating, QObject *parent)
    : AbstractResourceLinkQmlWrapper(laminating, *new LaminatingIntentLinkQmlWrapperPrivate, parent)
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(LaminatingIntentLink)

} // namespace Jdf
} // namespace Proof
