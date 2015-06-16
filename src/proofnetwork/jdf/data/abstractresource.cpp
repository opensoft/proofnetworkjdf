#include "abstractresource.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"

using namespace Proof::Jdf;

QString AbstractResource::id() const
{
    Q_D(const AbstractResource);
    return d->id;
}

ApiHelper::ResourceStatus AbstractResource::resourceStatus() const
{
    Q_D(const AbstractResource);
    return d->resourceStatus;
}

ApiHelper::ResourceClass AbstractResource::resourceClass() const
{
    Q_D(const AbstractResource);
    return d->resourceClass;
}

ApiHelper::Usage AbstractResource::usage() const
{
    Q_D(const AbstractResource);
    return d->usage;
}

void AbstractResource::setId(const QString &arg)
{
    Q_D(AbstractResource);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void AbstractResource::setResourceStatus(ApiHelper::ResourceStatus arg)
{
    Q_D(AbstractResource);
    if (d->resourceStatus != arg) {
        d->resourceStatus = arg;
        emit statusChanged(d->resourceStatus);
    }
}

void AbstractResource::setResourceClass(ApiHelper::ResourceClass arg)
{
    Q_D(AbstractResource);
    if (d->resourceClass != arg) {
        d->resourceClass = arg;
        emit resourceClassChanged(d->resourceClass);
    }
}

void AbstractResource::setUsage(ApiHelper::Usage arg)
{
    Q_D(AbstractResource);
    if (d->usage != arg) {
        d->usage = arg;
        emit usageChanged(d->usage);
    }
}

void AbstractResource::fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractResource->setId(attributes.value("ID").toString());
    abstractResource->setResourceStatus(ApiHelper::resourceStatusFromString(attributes.value("Status").toString()));
}

void AbstractResource::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResource);
    jdfWriter.writeAttribute("ID", d->id);
    jdfWriter.writeAttribute("Status", ApiHelper::resourceStatusToString(d->resourceStatus));
    jdfWriter.writeAttribute("Class", ApiHelper::resourceClassToString(d->resourceClass));
}

void AbstractResource::toJdfLink(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResource);
    QString className = QString(metaObject()->className()).remove(0, QString(metaObject()->className()).lastIndexOf(":") + 1);
    jdfWriter.writeStartElement(className + QString("Link"));
    jdfWriter.writeAttribute("Usage", ApiHelper::usageToString(d->usage));
    jdfWriter.writeAttribute("rRef", d->id);
    jdfWriter.writeEndElement();
}

AbstractResource::AbstractResource(AbstractResourcePrivate &dd, QObject *parent)
    : NetworkDataEntity(dd, parent)
{

}



void AbstractResourcePrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(AbstractResource);
    AbstractResourceSP castedOther = qSharedPointerCast<AbstractResource>(other);
    q->setId(castedOther->id());
    q->setResourceStatus(castedOther->resourceStatus());
    q->setResourceClass(castedOther->resourceClass());

    q->setUsage(castedOther->usage());

    NetworkDataEntityPrivate::updateFrom(other);
}
