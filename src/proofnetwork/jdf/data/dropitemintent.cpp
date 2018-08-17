#include "proofnetwork/jdf/data/dropitemintent.h"

#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DropItemIntentPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DropItemIntent)

    DropItemIntentPrivate() : NetworkDataEntityPrivate() { registerChildren(component); }

    ComponentSP component = Component::create();
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ComponentSP DropItemIntent::component() const
{
    Q_D_CONST(DropItemIntent);
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
    DropItemIntentSP castedSelf = castedSelfPtr<DropItemIntent>();
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
    jdfWriter.writeStartElement(QStringLiteral("DropItemIntent"));
    if (isValidAndDirty(d->component))
        d->component->refToJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

DropItemIntent::DropItemIntent() : NetworkDataEntity(*new DropItemIntentPrivate)
{}

void DropItemIntent::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    DropItemIntentSP castedOther = qSharedPointerCast<DropItemIntent>(other);
    setComponent(castedOther->component());

    NetworkDataEntity::updateSelf(other);
}
