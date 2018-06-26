#include "deliveryintent.h"

#include "dropintent.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/deliveryintentlink.h"
#include "proofnetwork/jdf/data/qmlwrappers/deliveryintentqmlwrapper.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(DeliveryIntent)

public:
    DeliveryIntentPrivate() : AbstractResourcePrivate(ResourceClass::IntentClass) { registerChildren(dropIntents); }

    EnumerationSpan deliveryCharge;
    TimeSpan earliest;
    DurationSpan earliestDuration;
    NameSpan method;
    NumberSpan overage;
    TimeSpan required;
    DurationSpan requiredDuration;
    NameSpan returnMethod;
    StringSpan serviceLevel;
    EnumerationSpan surplusHandling;
    EnumerationSpan transfer;
    NumberSpan underage;

    QVector<DropIntentSP> dropIntents;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

EnumerationSpan DeliveryIntent::deliveryCharge() const
{
    Q_D(const DeliveryIntent);
    return d->deliveryCharge;
}

TimeSpan DeliveryIntent::earliest() const
{
    Q_D(const DeliveryIntent);
    return d->earliest;
}

DurationSpan DeliveryIntent::earliestDuration() const
{
    Q_D(const DeliveryIntent);
    return d->earliestDuration;
}

NameSpan DeliveryIntent::method() const
{
    Q_D(const DeliveryIntent);
    return d->method;
}

NumberSpan DeliveryIntent::overage() const
{
    Q_D(const DeliveryIntent);
    return d->overage;
}

TimeSpan DeliveryIntent::required() const
{
    Q_D(const DeliveryIntent);
    return d->required;
}

DurationSpan DeliveryIntent::requiredDuration() const
{
    Q_D(const DeliveryIntent);
    return d->requiredDuration;
}

NameSpan DeliveryIntent::returnMethod() const
{
    Q_D(const DeliveryIntent);
    return d->returnMethod;
}

StringSpan DeliveryIntent::serviceLevel() const
{
    Q_D(const DeliveryIntent);
    return d->serviceLevel;
}

EnumerationSpan DeliveryIntent::surplusHandling() const
{
    Q_D(const DeliveryIntent);
    return d->surplusHandling;
}

EnumerationSpan DeliveryIntent::transfer() const
{
    Q_D(const DeliveryIntent);
    return d->transfer;
}

NumberSpan DeliveryIntent::underage() const
{
    Q_D(const DeliveryIntent);
    return d->underage;
}

QVector<DropIntentSP> DeliveryIntent::dropIntents() const
{
    Q_D(const DeliveryIntent);
    return d->dropIntents;
}

void DeliveryIntent::setDeliveryCharge(const EnumerationSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->deliveryCharge != arg) {
        d->deliveryCharge = arg;
        emit deliveryChargeChanged(arg);
    }
}

void DeliveryIntent::setEarliest(const TimeSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->earliest != arg) {
        d->earliest = arg;
        emit earliestChanged(arg);
    }
}

void DeliveryIntent::setEarliestDuration(const DurationSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->earliestDuration != arg) {
        d->earliestDuration = arg;
        emit earliestDurationChanged(arg);
    }
}

void DeliveryIntent::setMethod(const NameSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->method != arg) {
        d->method = arg;
        emit methodChanged(arg);
    }
}

void DeliveryIntent::setOverage(const NumberSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->overage != arg) {
        d->overage = arg;
        emit overageChanged(arg);
    }
}

void DeliveryIntent::setRequired(const TimeSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->required != arg) {
        d->required = arg;
        emit requiredChanged(arg);
    }
}

void DeliveryIntent::setRequiredDuration(const DurationSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->requiredDuration != arg) {
        d->requiredDuration = arg;
        emit requiredDurationChanged(arg);
    }
}

void DeliveryIntent::setReturnMethod(const NameSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->returnMethod != arg) {
        d->returnMethod = arg;
        emit returnMethodChanged(arg);
    }
}

void DeliveryIntent::setServiceLevel(const StringSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->serviceLevel != arg) {
        d->serviceLevel = arg;
        emit serviceLevelChanged(arg);
    }
}

void DeliveryIntent::setSurplusHandling(const EnumerationSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->surplusHandling != arg) {
        d->surplusHandling = arg;
        emit surplusHandlingChanged(arg);
    }
}

void DeliveryIntent::setTransfer(const EnumerationSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->transfer != arg) {
        d->transfer = arg;
        emit transferChanged(arg);
    }
}

void DeliveryIntent::setUnderage(const NumberSpan &arg)
{
    Q_D(DeliveryIntent);
    if (d->underage != arg) {
        d->underage = arg;
        emit underageChanged(arg);
    }
}

void DeliveryIntent::setDropIntents(const QVector<DropIntentSP> &arg)
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
    DeliveryIntentSP castedSelf = castedSelfPtr<DeliveryIntent>();
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
            if (xmlReader.name() == "DeliveryCharge") {
                deliveryIntent->setDeliveryCharge(EnumerationSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "Earliest") {
                deliveryIntent->setEarliest(TimeSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "EarliestDuration") {
                deliveryIntent->setEarliestDuration(DurationSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "Method") {
                deliveryIntent->setMethod(NameSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "Overage") {
                deliveryIntent->setOverage(NumberSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "Required") {
                deliveryIntent->setRequired(TimeSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "RequiredDuration") {
                deliveryIntent->setRequiredDuration(DurationSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "ReturnMethod") {
                deliveryIntent->setReturnMethod(NameSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "ServiceLevel") {
                deliveryIntent->setServiceLevel(StringSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "SurplusHandling") {
                deliveryIntent->setSurplusHandling(EnumerationSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "Transfer") {
                deliveryIntent->setTransfer(EnumerationSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "Underage") {
                deliveryIntent->setUnderage(NumberSpan::fromJdf(xmlReader.name().toString(), xmlReader));
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

    jdfWriter.writeStartElement(QStringLiteral("DeliveryIntent"));
    AbstractResource::toJdf(jdfWriter);

    if (d->deliveryCharge.isDirty())
        d->deliveryCharge.toJdf(QStringLiteral("DeliveryCharge"), jdfWriter);
    if (d->earliest.isDirty())
        d->earliest.toJdf(QStringLiteral("Earliest"), jdfWriter);
    if (d->earliestDuration.isDirty())
        d->earliestDuration.toJdf(QStringLiteral("EarliestDuration"), jdfWriter);
    if (d->method.isDirty())
        d->method.toJdf(QStringLiteral("Method"), jdfWriter);
    if (d->overage.isDirty())
        d->overage.toJdf(QStringLiteral("Overage"), jdfWriter);
    if (d->required.isDirty())
        d->required.toJdf(QStringLiteral("Required"), jdfWriter);
    if (d->requiredDuration.isDirty())
        d->requiredDuration.toJdf(QStringLiteral("RequiredDuration"), jdfWriter);
    if (d->returnMethod.isDirty())
        d->returnMethod.toJdf(QStringLiteral("ReturnMethod"), jdfWriter);
    if (d->serviceLevel.isDirty())
        d->serviceLevel.toJdf(QStringLiteral("ServiceLevel"), jdfWriter);
    if (d->surplusHandling.isDirty())
        d->surplusHandling.toJdf(QStringLiteral("SurplusHandling"), jdfWriter);
    if (d->transfer.isDirty())
        d->transfer.toJdf(QStringLiteral("Transfer"), jdfWriter);
    if (d->underage.isDirty())
        d->underage.toJdf(QStringLiteral("Underage"), jdfWriter);

    for (const DropIntentSP &dropIntent : qAsConst(d->dropIntents)) {
        if (isValidAndDirty(dropIntent))
            dropIntent->toJdf(jdfWriter);
    }
    jdfWriter.writeEndElement();
}

DeliveryIntentLinkSP DeliveryIntent::toLink(LinkUsage usage) const
{
    DeliveryIntentLinkSP link = DeliveryIntentLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

DeliveryIntent::DeliveryIntent() : AbstractResource(*new DeliveryIntentPrivate)
{}

void DeliveryIntent::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    DeliveryIntentSP castedOther = qSharedPointerCast<DeliveryIntent>(other);
    setRequired(castedOther->required());
    setDropIntents(castedOther->dropIntents());

    AbstractResource::updateSelf(other);
}
