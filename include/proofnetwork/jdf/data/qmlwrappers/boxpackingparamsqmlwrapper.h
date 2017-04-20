#ifndef PROOF_JDF_BOXPACKINGPARAMSQMLWRAPPER_H
#define PROOF_JDF_BOXPACKINGPARAMSQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

namespace Proof {
namespace Jdf {

class BoxPackingParamsQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT BoxPackingParamsQmlWrapper : public AbstractResourceQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BoxPackingParamsQmlWrapper)
public:
    explicit BoxPackingParamsQmlWrapper(const BoxPackingParamsSP &boxPackingParams, QObject *parent = nullptr);
    PROOF_NDE_WRAPPER_TOOLS(BoxPackingParams)
};

}
}

#endif // PROOF_JDF_BOXPACKINGPARAMSQMLWRAPPER_H
