#ifndef FOLDINGPARAMSLINK_H
#define FOLDINGPARAMSLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/qmlwrappers/foldingparamslinkqmlwrapper.h"

namespace Proof {
namespace Jdf {

class FoldingParamsLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT FoldingParamsLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FoldingParamsLink)
public:
    FoldingParamsLinkQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static FoldingParamsLinkSP create();

    static FoldingParamsLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    static FoldingParamsLinkSP defaultObject();

protected:
    explicit FoldingParamsLink(QObject *parent = 0);
};

}
}

#endif // FOLDINGPARAMSLINK_H
