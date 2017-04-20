#include "boxpackingparams.h"
#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/boxpackingparamslink.h"

namespace Proof {
namespace Jdf {

class BoxPackingParamsPrivate : AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(BoxPackingParams)

    BoxPackingParamsPrivate() : AbstractResourcePrivate(ResourceClass::ParameterClass) {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

BoxPackingParamsQmlWrapper *BoxPackingParams::toQmlWrapper(QObject *parent) const
{
    Q_D(const BoxPackingParams);
    BoxPackingParamsSP castedSelf = qSharedPointerCast<BoxPackingParams>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new BoxPackingParamsQmlWrapper(castedSelf, parent);
}

BoxPackingParamsSP BoxPackingParams::create()
{
    BoxPackingParamsSP result(new BoxPackingParams());
    initSelfWeakPtr(result);
    return result;
}

BoxPackingParamsSP BoxPackingParams::fromJdf(QXmlStreamReader &xmlReader)
{
    BoxPackingParamsSP boxPackingParams = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "BoxPackingParams" && xmlReader.isStartElement() && !boxPackingParams->isFetched()) {
            boxPackingParams->setFetched(true);
            AbstractResourceSP castedBoxPackingParams = qSharedPointerCast<AbstractResource>(boxPackingParams);
            AbstractResource::fromJdf(xmlReader, castedBoxPackingParams);

        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return boxPackingParams;
}

void BoxPackingParams::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement(jdfNodeName());
    AbstractResource::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

BoxPackingParamsLinkSP BoxPackingParams::toLink(LinkUsage usage) const
{
    BoxPackingParamsLinkSP link = BoxPackingParamsLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

BoxPackingParams::BoxPackingParams()
    : AbstractResource(*new BoxPackingParamsPrivate)
{
}

void BoxPackingParamsPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    AbstractResourcePrivate::updateFrom(other);
}
