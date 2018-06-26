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
    FoldingParamsLinkSP castedSelf = castedSelfPtr<FoldingParamsLink>();
    Q_ASSERT(castedSelf);
    return new FoldingParamsLinkQmlWrapper(castedSelf, parent);
}

FoldingParamsLinkSP FoldingParamsLink::create()
{
    FoldingParamsLinkSP result(new FoldingParamsLink());
    initSelfWeakPtr(result);
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
    jdfWriter.writeStartElement(jdfNodeName());
    AbstractResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

FoldingParamsLink::FoldingParamsLink() : AbstractResourceLink(*new FoldingParamsLinkPrivate)
{}

} // namespace Jdf
} // namespace Proof
