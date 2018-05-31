#ifndef CUTTINGPARAMSLINKQMLWRAPPER_H
#define CUTTINGPARAMSLINKQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class CuttingParamsLinkQmlWrapperPrivate;
class CuttingParamsLinkQmlWrapper : public AbstractResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CuttingParamsLinkQmlWrapper)
public:
    explicit CuttingParamsLinkQmlWrapper(const CuttingParamsLinkSP &cuttingParamsLink, QObject *parent = nullptr);
    PROOF_NDE_WRAPPER_TOOLS(CuttingParamsLink)
};

} // namespace Jdf
} // namespace Proof
#endif // CUTTINGPARAMSLINKQMLWRAPPER_H
