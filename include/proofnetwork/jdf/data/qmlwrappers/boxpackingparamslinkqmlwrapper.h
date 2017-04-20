#ifndef PROOF_JDF_BOXPACKINGPARAMSLINKQMLWRAPPER_H
#define PROOF_JDF_BOXPACKINGPARAMSLINKQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

namespace Proof {
namespace Jdf {

class BoxPackingParamsLinkQmlWrapperPrivate;
class BoxPackingParamsLinkQmlWrapper : public AbstractResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BoxPackingParamsLinkQmlWrapper)
public:
    explicit BoxPackingParamsLinkQmlWrapper(const BoxPackingParamsLinkSP &boxPackingParamsLink,
                                            QObject *parent = nullptr);
    PROOF_NDE_WRAPPER_TOOLS(BoxPackingParamsLink)
};

}
}

#endif // PROOF_JDF_BOXPACKINGPARAMSLINKQMLWRAPPER_H
