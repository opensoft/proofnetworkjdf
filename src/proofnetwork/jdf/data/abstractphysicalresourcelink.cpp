#include "abstractphysicalresourcelink.h"
#include "proofnetwork/jdf/data/abstractphysicalresourcelink_p.h"

namespace Proof {
namespace Jdf {

AbstractPhysicalResourceLink::AbstractPhysicalResourceLink(AbstractPhysicalResourceLinkPrivate &dd, QObject *parent)
    : AbstractResourceLink(dd, parent)
{
}

ApiHelper::ComponentOrientation AbstractPhysicalResourceLink::orientation() const
{
    Q_D(const AbstractPhysicalResourceLink);
    return d->orientation;
}

void AbstractPhysicalResourceLink::setOrientation(ApiHelper::ComponentOrientation arg)
{
    Q_D(AbstractPhysicalResourceLink);
    if (d->orientation != arg) {
        d->orientation = arg;
        emit orientationChanged(arg);
    }
}

void AbstractPhysicalResourceLink::fromJdf(const QXmlStreamReader &xmlReader, const AbstractPhysicalResourceLinkSP &resource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString value = attributes.value("Orientation").toString();
    if (!value.isEmpty())
        resource->setOrientation( ApiHelper::componentOrientationFromString(value) );

    AbstractResourceLink::fromJdf(xmlReader, resource);
}

void AbstractPhysicalResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractPhysicalResourceLink);
    QString className = QString(metaObject()->className()).remove(0, QString(metaObject()->className()).lastIndexOf(":") + 1);
    jdfWriter.writeStartElement(className);
    jdfWriter.writeAttribute("Usage", ApiHelper::usageToString(usage()));
    jdfWriter.writeAttribute("rRef", rRef());
    if (d->orientation != ApiHelper::ComponentOrientation::Rotate0Orientation)
        jdfWriter.writeAttribute("Orientation", ApiHelper::componentOrientationToString(d->orientation));

    jdfWriter.writeEndElement();
}

void AbstractPhysicalResourceLinkPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(AbstractPhysicalResourceLink);
    AbstractPhysicalResourceLinkSP castedOther = qSharedPointerCast<AbstractPhysicalResourceLink>(other);
    q->setOrientation(castedOther->orientation());
}

}
}
