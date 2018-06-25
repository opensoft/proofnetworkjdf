#include "dropintent.h"

#include "deliveryintent.h"

#include "proofnetwork/jdf/data/dropitemintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DropIntentPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DropIntent)

    DropIntentPrivate() : NetworkDataEntityPrivate() { registerChildren(dropItemIntents); }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    TimeSpan earliest;
    DurationSpan earliestDuration;
    TimeSpan required;
    DurationSpan requiredDuration;
    NameSpan returnMethod;
    StringSpan serviceLevel;
    EnumerationSpan surplusHandling;
    EnumerationSpan transfer;

    QVector<DropItemIntentSP> dropItemIntents;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

TimeSpan DropIntent::earliest() const
{
    Q_D(const DropIntent);
    return d->earliest;
}

DurationSpan DropIntent::earliestDuration() const
{
    Q_D(const DropIntent);
    return d->earliestDuration;
}

TimeSpan DropIntent::required() const
{
    Q_D(const DropIntent);
    return d->required;
}

DurationSpan DropIntent::requiredDuration() const
{
    Q_D(const DropIntent);
    return d->requiredDuration;
}

NameSpan DropIntent::returnMethod() const
{
    Q_D(const DropIntent);
    return d->returnMethod;
}

StringSpan DropIntent::serviceLevel() const
{
    Q_D(const DropIntent);
    return d->serviceLevel;
}

EnumerationSpan DropIntent::surplusHandling() const
{
    Q_D(const DropIntent);
    return d->surplusHandling;
}

EnumerationSpan DropIntent::transfer() const
{
    Q_D(const DropIntent);
    return d->transfer;
}

QVector<DropItemIntentSP> DropIntent::dropItemIntents() const
{
    Q_D(const DropIntent);
    return d->dropItemIntents;
}

void DropIntent::setEarliest(const TimeSpan &arg)
{
    Q_D(DropIntent);
    if (d->earliest != arg) {
        d->earliest = arg;
        emit earliestChanged(arg);
    }
}

void DropIntent::setEarliestDuration(const DurationSpan &arg)
{
    Q_D(DropIntent);
    if (d->earliestDuration != arg) {
        d->earliestDuration = arg;
        emit earliestDurationChanged(arg);
    }
}

void DropIntent::setRequired(const TimeSpan &arg)
{
    Q_D(DropIntent);
    if (d->required != arg) {
        d->required = arg;
        emit requiredChanged(arg);
    }
}

void DropIntent::setRequiredDuration(const DurationSpan &arg)
{
    Q_D(DropIntent);
    if (d->requiredDuration != arg) {
        d->requiredDuration = arg;
        emit requiredDurationChanged(arg);
    }
}

void DropIntent::setReturnMethod(const NameSpan &arg)
{
    Q_D(DropIntent);
    if (d->returnMethod != arg) {
        d->returnMethod = arg;
        emit returnMethodChanged(arg);
    }
}

void DropIntent::setServiceLevel(const StringSpan &arg)
{
    Q_D(DropIntent);
    if (d->serviceLevel != arg) {
        d->serviceLevel = arg;
        emit serviceLevelChanged(arg);
    }
}

void DropIntent::setSurplusHandling(const EnumerationSpan &arg)
{
    Q_D(DropIntent);
    if (d->surplusHandling != arg) {
        d->surplusHandling = arg;
        emit surplusHandlingChanged(arg);
    }
}

void DropIntent::setTransfer(const EnumerationSpan &arg)
{
    Q_D(DropIntent);
    if (d->transfer != arg) {
        d->transfer = arg;
        emit transferChanged(arg);
    }
}

void DropIntent::setDropItemIntents(const QVector<DropItemIntentSP> &arg)
{
    Q_D(DropIntent);
    d->dropItemIntents = arg;
    emit dropItemIntentsChanged();
}

void DropIntent::addDropItemIntent(const DropItemIntentSP &arg)
{
    Q_D(DropIntent);
    if (!arg)
        return;
    d->dropItemIntents.append(arg);
    emit dropItemIntentsChanged();
}

DropIntentQmlWrapper *DropIntent::toQmlWrapper(QObject *parent) const
{
    Q_D(const DropIntent);
    DropIntentSP castedSelf = qSharedPointerCast<DropIntent>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new DropIntentQmlWrapper(castedSelf, parent);
}

DropIntentSP DropIntent::create()
{
    DropIntentSP result(new DropIntent());
    initSelfWeakPtr(result);
    return result;
}

DropIntentSP DropIntent::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    DropIntentSP dropIntent = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "DropIntent" && xmlReader.isStartElement() && !dropIntent->isFetched()) {
            dropIntent->setFetched(true);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Earliest") {
                dropIntent->setEarliest(TimeSpan::fromJdf(QStringLiteral("Earliest"), xmlReader));
            } else if (xmlReader.name() == "EarliestDuration") {
                dropIntent->setEarliestDuration(DurationSpan::fromJdf(QStringLiteral("EarliestDuration"), xmlReader));
            } else if (xmlReader.name() == "Required") {
                dropIntent->setRequired(TimeSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "RequiredDuration") {
                dropIntent->setRequiredDuration(DurationSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "ReturnMethod") {
                dropIntent->setReturnMethod(NameSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "ServiceLevel") {
                dropIntent->setServiceLevel(StringSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "SurplusHandling") {
                dropIntent->setSurplusHandling(EnumerationSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "Transfer") {
                dropIntent->setTransfer(EnumerationSpan::fromJdf(xmlReader.name().toString(), xmlReader));
            } else if (xmlReader.name() == "DropItemIntent") {
                DropItemIntentSP dropItemIntent = DropItemIntent::fromJdf(xmlReader, jobId, sanitize);
                dropIntent->addDropItemIntent(dropItemIntent);
            } else if (xmlReader.isEndElement()) {
                break;
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }
    return dropIntent;
}

void DropIntent::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(DropIntent);
    jdfWriter.writeStartElement(QStringLiteral("DropIntent"));

    if (!d->earliest.actual().isNull())
        d->earliest.toJdf(QStringLiteral("Earliest"), jdfWriter);
    if (!d->earliestDuration.actual().isNull())
        d->earliestDuration.toJdf(QStringLiteral("EarliestDuration"), jdfWriter);
    if (!d->required.actual().isNull())
        d->required.toJdf(QStringLiteral("Required"), jdfWriter);
    if (!d->requiredDuration.actual().isNull())
        d->requiredDuration.toJdf(QStringLiteral("RequiredDuration"), jdfWriter);
    if (!d->returnMethod.actual().isNull())
        d->returnMethod.toJdf(QStringLiteral("ReturnMethod"), jdfWriter);
    if (!d->serviceLevel.actual().isNull())
        d->serviceLevel.toJdf(QStringLiteral("ServiceLevel"), jdfWriter);
    if (!d->surplusHandling.actual().isNull())
        d->surplusHandling.toJdf(QStringLiteral("SurplusHandling"), jdfWriter);
    if (!d->transfer.actual().isNull())
        d->transfer.toJdf(QStringLiteral("Transfer"), jdfWriter);

    for (const auto &dropItemIntent : qAsConst(d->dropItemIntents)) {
        if (isValidAndDirty(dropItemIntent))
            dropItemIntent->toJdf(jdfWriter);
    }

    jdfWriter.writeEndElement();
}

DropIntent::DropIntent() : NetworkDataEntity(*new DropIntentPrivate)
{}

void DropIntentPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(DropIntent);
    DropIntentSP castedOther = qSharedPointerCast<DropIntent>(other);
    q->setEarliest(castedOther->earliest());
    q->setEarliestDuration(castedOther->earliestDuration());
    q->setRequired(castedOther->required());
    q->setRequiredDuration(castedOther->requiredDuration());
    q->setReturnMethod(castedOther->returnMethod());
    q->setServiceLevel(castedOther->serviceLevel());
    q->setSurplusHandling(castedOther->surplusHandling());
    q->setTransfer(castedOther->transfer());
    q->setDropItemIntents(castedOther->dropItemIntents());

    NetworkDataEntityPrivate::updateFrom(other);
}
