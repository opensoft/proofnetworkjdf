#include "laminatingintentlink.h"

#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(LaminatingIntentLink)
};

LaminatingIntentLinkQmlWrapper *LaminatingIntentLink::toQmlWrapper(QObject *parent) const
{
    Q_D(const LaminatingIntentLink);
    LaminatingIntentLinkSP castedSelf = qSharedPointerCast<LaminatingIntentLink>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new LaminatingIntentLinkQmlWrapper(castedSelf, parent);

}

LaminatingIntentLinkSP LaminatingIntentLink::create()
{
    LaminatingIntentLinkSP result(new LaminatingIntentLink());
    initSelfWeakPtr(result);
    return result;
}

LaminatingIntentLinkSP LaminatingIntentLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    LaminatingIntentLinkSP laminatingParams = create();
    AbstractResourceLink::fromJdf(xmlReader, laminatingParams);
    return laminatingParams;
}

LaminatingIntentLink::LaminatingIntentLink(QObject *parent)
    : AbstractResourceLink(*new LaminatingIntentLinkPrivate, parent)
{
}

}
}
