#include "abstractphysicalresourcelink.h"
#include "proofnetwork/jdf/data/abstractphysicalresourcelink_p.h"

namespace Proof {
namespace Jdf {

AbstractPhysicalResourceLink::AbstractPhysicalResourceLink(AbstractPhysicalResourceLinkPrivate &dd, QObject *parent)
    : AbstractResourceLink(dd, parent)
{
}

ApiHelper::ResourceOrientation AbstractPhysicalResourceLink::orientation() const
{
    Q_D(const AbstractPhysicalResourceLink);
    return d->orientation;
}

double AbstractPhysicalResourceLink::amount() const
{
    Q_D(const AbstractPhysicalResourceLink);
    return d->amount;
}

void AbstractPhysicalResourceLink::setOrientation(ApiHelper::ResourceOrientation arg)
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
    QString value = attributes.value("Orientation").toString();
    resource->setOrientation(ApiHelper::resourceOrientationFromString(value));
    resource->setAmount(attributes.value("Amount").toDouble());

    return AbstractResourceLink::fromJdf(xmlReader, resource);
}

void AbstractPhysicalResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractPhysicalResourceLink);
    QString className = QString(metaObject()->className()).remove(0, QString(metaObject()->className()).lastIndexOf(":") + 1);
    jdfWriter.writeStartElement(className);
    jdfWriter.writeAttribute("Usage", ApiHelper::usageToString(usage()));
    jdfWriter.writeAttribute("rRef", rRef());
    if (d->orientation != ApiHelper::ResourceOrientation::Rotate0Orientation)
        jdfWriter.writeAttribute("Orientation", ApiHelper::resourceOrientationToString(d->orientation));
    if (d->amount != 0)
        jdfWriter.writeAttribute("Amount", QString::number(d->amount,'f', 4));

    jdfWriter.writeEndElement();
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
