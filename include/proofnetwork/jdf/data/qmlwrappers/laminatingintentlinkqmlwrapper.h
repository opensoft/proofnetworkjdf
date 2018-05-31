#ifndef LAMINATINGINTENTLINKQMLWRAPPER_H
#define LAMINATINGINTENTLINKQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentLinkQmlWrapperPrivate;
class LaminatingIntentLinkQmlWrapper : public AbstractResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LaminatingIntentLinkQmlWrapper)
public:
    explicit LaminatingIntentLinkQmlWrapper(const LaminatingIntentLinkSP &laminating, QObject *parent = nullptr);
    PROOF_NDE_WRAPPER_TOOLS(LaminatingIntentLink)
};

} // namespace Jdf
} // namespace Proof
#endif // LAMINATINGINTENTLINKQMLWRAPPER_H
