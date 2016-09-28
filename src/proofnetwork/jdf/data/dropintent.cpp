#include "dropintent.h"

#include "deliveryintent.h"

#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"
#include "proofnetwork/jdf/data/dropitemintent.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DropIntentPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DropIntent)

    DropIntentPrivate() : NetworkDataEntityPrivate()
    {
        registerChildren(dropItemIntents);
    }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    TimeSpan required;
    QList<DropItemIntentSP> dropItemIntents;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

TimeSpan DropIntent::required() const
{
    Q_D(const DropIntent);
    return d->required;
}

QList<DropItemIntentSP> DropIntent::dropItemIntents() const
{
    Q_D(const DropIntent);
    return d->dropItemIntents;
}

void DropIntent::setRequired(const TimeSpan &arg)
{
    Q_D(DropIntent);
    if (d->required != arg) {
        d->required = arg;
        emit requiredChanged(arg);
    }
}

void DropIntent::setDropItemIntents(const QList<DropItemIntentSP> &arg)
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
            if (xmlReader.name() == "Required") {
                dropIntent->setRequired(TimeSpan::fromJdf("Required", xmlReader));
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
    jdfWriter.writeStartElement("DropIntent");

    if (!d->required.actual().isNull())
        d->required.toJdf("Required", jdfWriter);

    for (const auto &dropItemIntent : dropItemIntents()) {
        if (isValidAndDirty(dropItemIntent))
            dropItemIntent->toJdf(jdfWriter);
    }

    jdfWriter.writeEndElement();
}

DropIntent::DropIntent()
    : NetworkDataEntity(*new DropIntentPrivate)
{
}

void DropIntentPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(DropIntent);
    DropIntentSP castedOther = qSharedPointerCast<DropIntent>(other);
    q->setRequired(castedOther->required());
    q->setDropItemIntents(castedOther->dropItemIntents());

    NetworkDataEntityPrivate::updateFrom(other);
}

