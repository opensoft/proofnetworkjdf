#include "dropitemintent.h"

#include "deliveryintent.h"

#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DropItemIntentPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DropItemIntent)

    DropItemIntentPrivate() : NetworkDataEntityPrivate()
    {
        registerChildren(component);
    }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    ComponentSP component = Component::create();
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ComponentSP DropItemIntent::component() const
{
    Q_D(const DropItemIntent);
    return d->component;
}

void DropItemIntent::setComponent(const ComponentSP &arg)
{
    Q_D(DropItemIntent);
    if (d->component != arg) {
        d->component = arg;
        emit componentChanged(arg);
    }
}

DropItemIntentQmlWrapper *DropItemIntent::toQmlWrapper(QObject *parent) const
{
    Q_D(const DropItemIntent);
    DropItemIntentSP castedSelf = qSharedPointerCast<DropItemIntent>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new DropItemIntentQmlWrapper(castedSelf, parent);
}

DropItemIntentSP DropItemIntent::create()
{
    DropItemIntentSP result(new DropItemIntent());
    initSelfWeakPtr(result);
    return result;
}

DropItemIntentSP DropItemIntent::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    DropItemIntentSP dropItemIntent = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "DropItemIntent" && xmlReader.isStartElement() && !dropItemIntent->isFetched()) {
            dropItemIntent->setFetched(true);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "ComponentRef") {
                ComponentSP component = Component::fromJdf(xmlReader, jobId, sanitize);
                dropItemIntent->setComponent(component);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return dropItemIntent;
}

void DropItemIntent::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(DropItemIntent);
    jdfWriter.writeStartElement("DropItemIntent");
    if (isValidAndDirty(d->component))
        d->component->refToJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

DropItemIntent::DropItemIntent()
    : NetworkDataEntity(*new DropItemIntentPrivate)
{
}

void DropItemIntentPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(DropItemIntent);
    DropItemIntentSP castedOther = qSharedPointerCast<DropItemIntent>(other);
    q->setComponent(castedOther->component());

    NetworkDataEntityPrivate::updateFrom(other);
}
