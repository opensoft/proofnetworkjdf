#include "componentlink.h"

#include "proofnetwork/jdf/data/abstractphysicalresourcelink_p.h"

namespace Proof {
namespace Jdf {

class ComponentLinkPrivate : public AbstractPhysicalResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(ComponentLink)
};

ComponentLink::ComponentLink() : AbstractPhysicalResourceLink(*new ComponentLinkPrivate)
{}

ComponentLinkSP ComponentLink::create()
{
    ComponentLinkSP result(new ComponentLink());
    initSelfWeakPtr(result);
    return result;
}

ComponentLinkQmlWrapper *ComponentLink::toQmlWrapper(QObject *parent) const
{
    ComponentLinkSP castedSelf = castedSelfPtr<ComponentLink>();
    Q_ASSERT(castedSelf);
    return new ComponentLinkQmlWrapper(castedSelf, parent);
}

ComponentLinkSP ComponentLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    ComponentLinkSP componentLink = create();
    AbstractPhysicalResourceLink::fromJdf(xmlReader, componentLink);
    return componentLink;
}

void ComponentLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement(jdfNodeName());
    AbstractPhysicalResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

} // namespace Jdf
} // namespace Proof
