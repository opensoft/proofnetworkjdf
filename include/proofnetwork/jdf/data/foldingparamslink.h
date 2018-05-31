#ifndef FOLDINGPARAMSLINK_H
#define FOLDINGPARAMSLINK_H

#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/qmlwrappers/foldingparamslinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class FoldingParamsLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT FoldingParamsLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FoldingParamsLink)
public:
    FoldingParamsLinkQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static FoldingParamsLinkSP create();

    static FoldingParamsLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;

protected:
    explicit FoldingParamsLink(QObject *parent = nullptr);
};

} // namespace Jdf
} // namespace Proof

#endif // FOLDINGPARAMSLINK_H
