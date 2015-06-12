#include "componentlink.h"

#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

namespace Proof {
namespace Jdf {

class ComponentLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(ComponentLink)
};

ComponentLink::ComponentLink(QObject *parent)
    : AbstractResourceLink(*new ComponentLinkPrivate, parent)
{
}

ComponentLinkSP ComponentLink::create()
{
    ComponentLinkSP result(new ComponentLink());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

ComponentLinkQmlWrapper *ComponentLink::toQmlWrapper(QObject *parent) const
{
    Q_D(const ComponentLink);
    ComponentLinkSP castedSelf = qSharedPointerCast<ComponentLink>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new ComponentLinkQmlWrapper(castedSelf, parent);

}

ComponentLinkSP ComponentLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    ComponentLinkSP componentLink = create();
    AbstractResourceLink::fromJdf(xmlReader, componentLink);
    return componentLink;
}

void ComponentLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement("ComponentLink");
    AbstractResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

}
}
