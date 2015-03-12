#include "abstractresource.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"

namespace Proof {
namespace Jdf {

QString AbstractResource::id() const
{
    Q_D(const AbstractResource);
    return d->id;
}

ApiHelper::ResourceStatus AbstractResource::status() const
{
    Q_D(const AbstractResource);
    return d->status;
}

ApiHelper::ResourceClass AbstractResource::resourceClass() const
{
    Q_D(const AbstractResource);
    return d->resourceClass;
}

void AbstractResource::setId(const QString &arg)
{
    Q_D(AbstractResource);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void AbstractResource::setStatus(ApiHelper::ResourceStatus arg)
{
    Q_D(AbstractResource);
    if (d->status != arg) {
        d->status = arg;
        emit statusChanged(d->status);
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

void AbstractResource::updateFrom(const NetworkDataEntitySP &other)
{
    AbstractResourceSP castedOther = qSharedPointerCast<AbstractResource>(other);
    setId(castedOther->id());
    setStatus(castedOther->status());
    setResourceClass(castedOther->resourceClass());

    NetworkDataEntity::updateFrom(other);
}

void AbstractResource::fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractResource->setId(attributes.value("ID").toString());
    abstractResource->setStatus(ApiHelper::resourceStatusFromString(attributes.value("Status").toString()));
}

void AbstractResource::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResource);
    jdfWriter.writeAttribute("ID", d->id);
    jdfWriter.writeAttribute("Status", ApiHelper::resourceStatusToString(d->status));
    jdfWriter.writeAttribute("Class", ApiHelper::resourceClassToString(d->resourceClass));
}

AbstractResource::AbstractResource(AbstractResourcePrivate &dd, QObject *parent)
    : NetworkDataEntity(dd, parent)
{

}

}
}

