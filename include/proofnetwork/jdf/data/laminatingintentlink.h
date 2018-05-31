#ifndef LAMINATINGINTENTLINK_H
#define LAMINATINGINTENTLINK_H

#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/laminatingintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentlinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT LaminatingIntentLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LaminatingIntentLink)
public:
    LaminatingIntentLinkQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static LaminatingIntentLinkSP create();

    static LaminatingIntentLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;

protected:
    explicit LaminatingIntentLink(QObject *parent = nullptr);
};

} // namespace Jdf
} // namespace Proof
#endif // LAMINATINGINTENTLINK_H
