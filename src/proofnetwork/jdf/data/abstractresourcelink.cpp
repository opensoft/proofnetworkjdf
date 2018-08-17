#include "proofnetwork/jdf/data/abstractresourcelink.h"

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

using namespace Proof::Jdf;

AbstractResourceLink::AbstractResourceLink(AbstractResourceLinkPrivate &dd) : NetworkDataEntity(dd)
{}

LinkUsage AbstractResourceLink::usage() const
{
    Q_D_CONST(AbstractResourceLink);
    return d->usage;
}

ProcessUsage AbstractResourceLink::processUsage() const
{
    Q_D_CONST(AbstractResourceLink);
    return d->processUsage;
}

QString AbstractResourceLink::rRef() const
{
    Q_D_CONST(AbstractResourceLink);
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
    abstractResource->setUsage(linkUsageFromString(attributes.value(QStringLiteral("Usage")).toString()));
    abstractResource->setProcessUsage(processUsageFromString(attributes.value(QStringLiteral("ProcessUsage")).toString()));
    abstractResource->setRRef(attributes.value(QStringLiteral("rRef")).toString());

    return true;
}

void AbstractResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResourceLink);
    jdfWriter.writeAttribute(QStringLiteral("Usage"), linkUsageToString(d->usage));
    if (d->processUsage != ProcessUsage::UseAsDefault)
        jdfWriter.writeAttribute(QStringLiteral("ProcessUsage"), processUsageToString(d->processUsage));
    jdfWriter.writeAttribute(QStringLiteral("rRef"), d->rRef);
}

QString AbstractResourceLink::jdfNodeName() const
{
    return QString(metaObject()->className())
        .remove(0, QString(metaObject()->className()).lastIndexOf(QLatin1String(":")) + 1);
}

QString AbstractResourceLink::jdfNodeRefName() const
{
    return QStringLiteral("%1Ref").arg(jdfNodeName());
}

void AbstractResourceLink::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AbstractResourceLinkSP castedOther = qSharedPointerCast<AbstractResourceLink>(other);
    setUsage(castedOther->usage());
    setProcessUsage(castedOther->processUsage());
    setRRef(castedOther->rRef());

    NetworkDataEntity::updateSelf(other);
}
