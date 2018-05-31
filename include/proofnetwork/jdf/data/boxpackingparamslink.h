#ifndef BOXPACKINGPARAMSLINK_H
#define BOXPACKINGPARAMSLINK_H

#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/boxpackingparams.h"
#include "proofnetwork/jdf/data/qmlwrappers/boxpackingparamslinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class BoxPackingParamsLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT BoxPackingParamsLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BoxPackingParamsLink)
public:
    BoxPackingParamsLinkQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static BoxPackingParamsLinkSP create();

    static BoxPackingParamsLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;

protected:
    explicit BoxPackingParamsLink(QObject *parent = nullptr);
};

} // namespace Jdf
} // namespace Proof

#endif // BOXPACKINGPARAMSLINK_H
