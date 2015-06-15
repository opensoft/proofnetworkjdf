#ifndef LAMINATINGINTENTLINK_H
#define LAMINATINGINTENTLINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/laminatingintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentlinkqmlwrapper.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentLinkPrivate;
class LaminatingIntentLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LaminatingIntentLink)
public:
    LaminatingIntentLinkQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static LaminatingIntentLinkSP create();

    static LaminatingIntentLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    static LaminatingIntentLinkSP defaultObject();

protected:
    explicit LaminatingIntentLink(QObject *parent = 0);
};

}
}
#endif // LAMINATINGINTENTLINK_H
