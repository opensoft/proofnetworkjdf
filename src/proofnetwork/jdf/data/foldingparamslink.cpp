#include "foldingparamslink.h"

#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

namespace Proof {
namespace Jdf {

class FoldingParamsLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(FoldingParamsLink)
};

FoldingParamsLinkQmlWrapper *FoldingParamsLink::toQmlWrapper(QObject *parent) const
{
    Q_D(const FoldingParamsLink);
    FoldingParamsLinkSP castedSelf = qSharedPointerCast<FoldingParamsLink>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new FoldingParamsLinkQmlWrapper(castedSelf, parent);

}

FoldingParamsLinkSP FoldingParamsLink::create()
{
    FoldingParamsLinkSP result(new FoldingParamsLink());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

FoldingParamsLinkSP FoldingParamsLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    FoldingParamsLinkSP foldingParams = create();
    AbstractResourceLink::fromJdf(xmlReader, foldingParams);
    return foldingParams;
}

void FoldingParamsLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement("FoldingParamsLink");
    AbstractResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

FoldingParamsLinkSP FoldingParamsLink::defaultObject()
{
    static FoldingParamsLinkSP entity = create();
    return entity;
}

FoldingParamsLink::FoldingParamsLink(QObject *parent)
    : AbstractResourceLink(*new FoldingParamsLinkPrivate, parent)
{
}

}
}
