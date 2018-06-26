#include "cuttingparamslink.h"

#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

namespace Proof {
namespace Jdf {

class CuttingParamsLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(CuttingParamsLink)
};

CuttingParamsLink::CuttingParamsLink() : AbstractResourceLink(*new CuttingParamsLinkPrivate)
{}

CuttingParamsLinkQmlWrapper *CuttingParamsLink::toQmlWrapper(QObject *parent) const
{
    CuttingParamsLinkSP castedSelf = castedSelfPtr<CuttingParamsLink>();
    Q_ASSERT(castedSelf);
    return new CuttingParamsLinkQmlWrapper(castedSelf, parent);
}

CuttingParamsLinkSP CuttingParamsLink::create()
{
    CuttingParamsLinkSP result(new CuttingParamsLink());
    initSelfWeakPtr(result);
    return result;
}

CuttingParamsLinkSP CuttingParamsLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    CuttingParamsLinkSP cuttingParams = create();
    AbstractResourceLink::fromJdf(xmlReader, cuttingParams);
    return cuttingParams;
}

void CuttingParamsLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement(jdfNodeName());
    AbstractResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

} // namespace Jdf
} // namespace Proof
