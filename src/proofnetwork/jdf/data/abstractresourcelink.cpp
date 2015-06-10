#include "abstractresourcelink.h"

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/data/abstractresource.h"

namespace Proof {
namespace Jdf {

class AbstractResourceLinkPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractResourceLink)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override
    {
        Q_Q(AbstractResourceLink);
        AbstractResourceLinkSP castedOther = qSharedPointerCast<AbstractResourceLink>(other);
        q->setUsage(castedOther->usage());
        q->setRRef(castedOther->rRef());
    }

    // TODO: should we use default usage?
    ApiHelper::Usage usage = ApiHelper::InputUsage;
    QString rRef;
};

}
}

using namespace Proof::Jdf;

// TODO: is it better to pass QString id, instead of object pointer?
AbstractResourceLink::AbstractResourceLink(const AbstractResourceSP &resource, QObject *parent)
    : NetworkDataEntity( *new AbstractResourceLinkPrivate, parent)
{
    Q_D(AbstractResourceLink);
    d->rRef = resource->id();
}

void AbstractResourceLink::toJdf(QXmlStreamWriter &jdfWriter, const AbstractResourceLinkPrivate *link)
{
    jdfWriter.writeAttribute("usage", ApiHelper::usageToString(link->usage));
    jdfWriter.writeAttribute("rRef", link->rRef);
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

void AbstractResourceLink::fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceLinkSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractResource->setUsage(ApiHelper::usageFromString(attributes.value("usage").toString()));
    abstractResource->setRRef(attributes.value("rRef").toString());
}

void AbstractResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResourceLink);
    jdfWriter.writeStartElement(metaObject()->className());
    toJdf(jdfWriter, d);
    jdfWriter.writeEndElement();
}

