#include "boxpackingparamslink.h"

#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

namespace Proof {
namespace Jdf {

class BoxPackingParamsLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(BoxPackingParamsLink)
};

BoxPackingParamsLinkQmlWrapper *BoxPackingParamsLink::toQmlWrapper(QObject *parent) const
{
    Q_D(const BoxPackingParamsLink);
    BoxPackingParamsLinkSP castedSelf = qSharedPointerCast<BoxPackingParamsLink>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new BoxPackingParamsLinkQmlWrapper(castedSelf, parent);

}

BoxPackingParamsLinkSP BoxPackingParamsLink::create()
{
    BoxPackingParamsLinkSP result(new BoxPackingParamsLink());
    initSelfWeakPtr(result);
    return result;
}

BoxPackingParamsLinkSP BoxPackingParamsLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    BoxPackingParamsLinkSP boxPackingParamsLink = create();
    AbstractResourceLink::fromJdf(xmlReader, boxPackingParamsLink);
    return boxPackingParamsLink;
}

void BoxPackingParamsLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement(jdfNodeName());
    AbstractResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

BoxPackingParamsLink::BoxPackingParamsLink(QObject *parent)
    : AbstractResourceLink(*new BoxPackingParamsLinkPrivate, parent)
{
}

}
}
