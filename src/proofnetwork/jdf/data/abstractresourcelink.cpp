#include "abstractresourcelink.h"

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

using namespace Proof::Jdf;

AbstractResourceLink::AbstractResourceLink(AbstractResourceLinkPrivate &dd, QObject *parent)
    : NetworkDataEntity(dd, parent)
{
}

ApiHelper::Usage AbstractResourceLink::usage() const
{
    Q_D(const AbstractResourceLink);
    return d->usage;
}

QString AbstractResourceLink::rRef() const
{
    Q_D(const AbstractResourceLink);
    return d->rRef;
}

void AbstractResourceLink::setUsage(ApiHelper::Usage arg)
{
    Q_D(AbstractResourceLink);
    if (d->usage != arg) {
        d->usage = arg;
        emit usageChanged(d->usage);
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

void AbstractResourceLink::fromJdf(const QXmlStreamReader &xmlReader, const AbstractResourceLinkSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractResource->setUsage(ApiHelper::usageFromString(attributes.value("Usage").toString()));
    abstractResource->setRRef(attributes.value("rRef").toString());
}

// TODO: should we make toJdf method for every subclass of AbstractResourceLink?
void AbstractResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResourceLink);
    QString className = QString(metaObject()->className()).remove(0, QString(metaObject()->className()).lastIndexOf(":") + 1);
    jdfWriter.writeStartElement(className);
    jdfWriter.writeAttribute("Usage", ApiHelper::usageToString(d->usage));
    jdfWriter.writeAttribute("rRef", d->rRef);
    jdfWriter.writeEndElement();
}

void AbstractResourceLinkPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(AbstractResourceLink);
    AbstractResourceLinkSP castedOther = qSharedPointerCast<AbstractResourceLink>(other);
    q->setUsage(castedOther->usage());
    q->setRRef(castedOther->rRef());

    NetworkDataEntityPrivate::updateFrom(other);
}
