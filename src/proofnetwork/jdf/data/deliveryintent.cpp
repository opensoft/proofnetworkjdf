#include "deliveryintent.h"

#include "dropintent.h"

#include "proofnetwork/jdf/data/qmlwrappers/deliveryintentqmlwrapper.h"
#include "proofnetwork/jdf/data/deliveryintentlink.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(DeliveryIntent)

public:
    DeliveryIntentPrivate() : AbstractResourcePrivate(ApiHelper::ResourceClass::IntentClass)
    {
        registerChildren(dropIntents);
    }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    TimeSpan required;
    QList<DropIntentSP> dropIntents;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

TimeSpan DeliveryIntent::required() const
{
    Q_D(const DeliveryIntent);
    return d->required;
}

QList<DropIntentSP> DeliveryIntent::dropIntents() const
{
    Q_D(const DeliveryIntent);
    return d->dropIntents;
}

void DeliveryIntent::setRequired(const TimeSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->required != arg) {
        d->required = arg;
        emit requiredChanged(arg);
    }
}

void DeliveryIntent::setDropIntents(const QList<DropIntentSP> &arg)
{
    Q_D(DeliveryIntent);
    d->dropIntents = arg;
    emit dropIntentsChanged();
}

void DeliveryIntent::addDropIntent(const DropIntentSP &arg)
{
    Q_D(DeliveryIntent);
    if (!arg)
        return;
    d->dropIntents << arg;
    emit dropIntentsChanged();
}

DeliveryIntentQmlWrapper *DeliveryIntent::toQmlWrapper(QObject *parent) const
{
    Q_D(const DeliveryIntent);
    DeliveryIntentSP castedSelf = qSharedPointerCast<DeliveryIntent>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new DeliveryIntentQmlWrapper(castedSelf, parent);
}

DeliveryIntentSP DeliveryIntent::create()
{
    DeliveryIntentSP result(new DeliveryIntent());
    initSelfWeakPtr(result);
    return result;
}

DeliveryIntentSP DeliveryIntent::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    DeliveryIntentSP deliveryIntent = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "DeliveryIntent" && xmlReader.isStartElement() && !deliveryIntent->isFetched()) {
            deliveryIntent->setFetched(true);
            AbstractResourceSP castedDeliveryIntent = qSharedPointerCast<AbstractResource>(deliveryIntent);
            AbstractResource::fromJdf(xmlReader, castedDeliveryIntent);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Required") {
                deliveryIntent->setRequired(TimeSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "DropIntent") {
                DropIntentSP dropIntent = DropIntent::fromJdf(xmlReader, jobId, sanitize);
                deliveryIntent->addDropIntent(dropIntent);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return deliveryIntent;
}

void DeliveryIntent::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(DeliveryIntent);

    jdfWriter.writeStartElement("DeliveryIntent");
    AbstractResource::toJdf(jdfWriter);

    if (!required().actual().isNull())
        required().toJdf("Required", jdfWriter);

    for (const DropIntentSP &dropIntent : d->dropIntents) {
        if (isValidAndDirty(dropIntent))
            dropIntent->toJdf(jdfWriter);
    }
    jdfWriter.writeEndElement();
}

DeliveryIntentLinkSP DeliveryIntent::toLink(ApiHelper::Usage usage) const
{
    DeliveryIntentLinkSP link = DeliveryIntentLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

DeliveryIntent::DeliveryIntent()
    : AbstractResource(*new DeliveryIntentPrivate)
{
}

void DeliveryIntentPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(DeliveryIntent);
    DeliveryIntentSP castedOther = qSharedPointerCast<DeliveryIntent>(other);
    q->setRequired(castedOther->required());
    q->setDropIntents(castedOther->dropIntents());

    AbstractResourcePrivate::updateFrom(other);
}

