#include "abstractphysicalresourcelink.h"

#include "proofnetwork/jdf/data/abstractphysicalresourcelink_p.h"

namespace Proof {
namespace Jdf {

AbstractPhysicalResourceLink::AbstractPhysicalResourceLink(AbstractPhysicalResourceLinkPrivate &dd)
    : AbstractResourceLink(dd)
{}

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

bool AbstractPhysicalResourceLink::fromJdf(const QXmlStreamReader &xmlReader,
                                           const AbstractPhysicalResourceLinkSP &resource)
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
        jdfWriter.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount, 'f', 4));
    AbstractResourceLink::toJdf(jdfWriter);
}

void AbstractPhysicalResourceLink::updateSelf(const NetworkDataEntitySP &other)
{
    AbstractPhysicalResourceLinkSP castedOther = qSharedPointerCast<AbstractPhysicalResourceLink>(other);
    setOrientation(castedOther->orientation());
    setAmount(castedOther->amount());

    AbstractResourceLink::updateSelf(other);
}

} // namespace Jdf
} // namespace Proof
