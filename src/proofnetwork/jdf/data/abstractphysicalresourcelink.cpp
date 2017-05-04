#include "abstractphysicalresourcelink.h"
#include "proofnetwork/jdf/data/abstractphysicalresourcelink_p.h"

namespace Proof {
namespace Jdf {

AbstractPhysicalResourceLink::AbstractPhysicalResourceLink(AbstractPhysicalResourceLinkPrivate &dd, QObject *parent)
    : AbstractResourceLink(dd, parent)
{
}

ResourceOrientation AbstractPhysicalResourceLink::orientation() const
{
    Q_D(const AbstractPhysicalResourceLink);
    return d->orientation;
}

double AbstractPhysicalResourceLink::amount() const
{
    Q_D(const AbstractPhysicalResourceLink);
    return d->amount;
}

void AbstractPhysicalResourceLink::setOrientation(ResourceOrientation arg)
{
    Q_D(AbstractPhysicalResourceLink);
    if (d->orientation != arg) {
        d->orientation = arg;
        emit orientationChanged(arg);
    }
}

void AbstractPhysicalResourceLink::setAmount(double arg)
{
    Q_D(AbstractPhysicalResourceLink);
    if (d->amount != arg) {
        d->amount = arg;
        emit amountChanged(d->amount);
    }
}

bool AbstractPhysicalResourceLink::fromJdf(const QXmlStreamReader &xmlReader, const AbstractPhysicalResourceLinkSP &resource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString value = attributes.value(QStringLiteral("Orientation")).toString();
    resource->setOrientation(resourceOrientationFromString(value));
    resource->setAmount(attributes.value(QStringLiteral("Amount")).toDouble());

    return AbstractResourceLink::fromJdf(xmlReader, resource);
}

void AbstractPhysicalResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractPhysicalResourceLink);
    if (d->orientation != ResourceOrientation::Rotate0Orientation)
        jdfWriter.writeAttribute(QStringLiteral("Orientation"), resourceOrientationToString(d->orientation));
    if (d->amount != 0)
        jdfWriter.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount,'f', 4));
    AbstractResourceLink::toJdf(jdfWriter);
}

void AbstractPhysicalResourceLinkPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(AbstractPhysicalResourceLink);
    AbstractPhysicalResourceLinkSP castedOther = qSharedPointerCast<AbstractPhysicalResourceLink>(other);
    q->setOrientation(castedOther->orientation());
    q->setAmount(castedOther->amount());

    AbstractResourceLinkPrivate::updateFrom(other);
}

}
}
