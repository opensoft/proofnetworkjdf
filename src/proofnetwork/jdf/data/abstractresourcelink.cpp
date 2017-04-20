#include "abstractresourcelink.h"

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

using namespace Proof::Jdf;

AbstractResourceLink::AbstractResourceLink(AbstractResourceLinkPrivate &dd, QObject *parent)
    : NetworkDataEntity(dd, parent)
{
}

LinkUsage AbstractResourceLink::usage() const
{
    Q_D(const AbstractResourceLink);
    return d->usage;
}

ProcessUsage AbstractResourceLink::processUsage() const
{
    Q_D(const AbstractResourceLink);
    return d->processUsage;
}

QString AbstractResourceLink::rRef() const
{
    Q_D(const AbstractResourceLink);
    return d->rRef;
}

void AbstractResourceLink::setUsage(LinkUsage arg)
{
    Q_D(AbstractResourceLink);
    if (d->usage != arg) {
        d->usage = arg;
        emit usageChanged(d->usage);
    }
}

void AbstractResourceLink::setProcessUsage(ProcessUsage arg)
{
    Q_D(AbstractResourceLink);
    if (d->processUsage != arg) {
        d->processUsage = arg;
        emit processUsageChanged(d->processUsage);
    }
}

void AbstractResourceLink::setRRef(const QString &arg)
{
    Q_D(AbstractResourceLink);
    if (d->rRef != arg) {
        d->rRef = arg;
        emit rRefChanged(d->rRef);
    }
}

bool AbstractResourceLink::fromJdf(const QXmlStreamReader &xmlReader, const AbstractResourceLinkSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractResource->setUsage(linkUsageFromString(attributes.value("Usage").toString()));
    abstractResource->setProcessUsage(processUsageFromString(attributes.value("ProcessUsage").toString()));
    abstractResource->setRRef(attributes.value("rRef").toString());

    return true;
}

void AbstractResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResourceLink);
    jdfWriter.writeAttribute("Usage", linkUsageToString(d->usage));
    if (d->processUsage != ProcessUsage::UseAsDefault)
        jdfWriter.writeAttribute("ProcessUsage", processUsageToString(d->processUsage));
    jdfWriter.writeAttribute("rRef", d->rRef);
}

QString AbstractResourceLink::jdfNodeName() const
{
    return QString(metaObject()->className()).remove(0, QString(metaObject()->className()).lastIndexOf(":") + 1);
}

QString AbstractResourceLink::jdfNodeRefName() const
{
    return QString("%1Ref").arg(jdfNodeName());
}

void AbstractResourceLinkPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(AbstractResourceLink);
    AbstractResourceLinkSP castedOther = qSharedPointerCast<AbstractResourceLink>(other);
    q->setUsage(castedOther->usage());
    q->setProcessUsage(castedOther->processUsage());
    q->setRRef(castedOther->rRef());

    NetworkDataEntityPrivate::updateFrom(other);
}
