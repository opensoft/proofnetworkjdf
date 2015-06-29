 #ifndef CUTTINGPARAMSLINK_H
#define CUTTINGPARAMSLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingparamslinkqmlwrapper.h"

namespace Proof {
namespace Jdf {

class CuttingParamsLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT CuttingParamsLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CuttingParamsLink)
public:
    CuttingParamsLinkQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static CuttingParamsLinkSP create();

    static CuttingParamsLinkSP fromJdf(const QXmlStreamReader &xmlReader);

protected:
    explicit CuttingParamsLink(QObject *parent = 0);
};

}
}
#endif // CUTTINGPARAMSLINK_H
