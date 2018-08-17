#include "proofnetwork/jdf/data/laminatingintentlink.h"

#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(LaminatingIntentLink)
};

LaminatingIntentLinkQmlWrapper *LaminatingIntentLink::toQmlWrapper(QObject *parent) const
{
    LaminatingIntentLinkSP castedSelf = castedSelfPtr<LaminatingIntentLink>();
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

void LaminatingIntentLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement(jdfNodeName());
    AbstractResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

LaminatingIntentLink::LaminatingIntentLink() : AbstractResourceLink(*new LaminatingIntentLinkPrivate)
{}

} // namespace Jdf
} // namespace Proof
