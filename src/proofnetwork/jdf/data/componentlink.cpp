#include "componentlink.h"

#include "proofnetwork/jdf/data/abstractphysicalresourcelink_p.h"

namespace Proof {
namespace Jdf {

class ComponentLinkPrivate : public AbstractPhysicalResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(ComponentLink)
};

ComponentLink::ComponentLink(QObject *parent)
    : AbstractPhysicalResourceLink(*new ComponentLinkPrivate, parent)
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
    AbstractPhysicalResourceLink::fromJdf(xmlReader, componentLink);
    return componentLink;
}

ComponentLinkSP ComponentLink::defaultObject()
{
    static ComponentLinkSP entity = create();
    return entity;
}

}
}
