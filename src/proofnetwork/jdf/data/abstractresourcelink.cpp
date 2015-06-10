#include "proofnetwork/networkdataentity_p.h"
#include "abstractresourcelink.h"

namespace Proof {
namespace Jdf {

class AbstractResourceLinkPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractResource)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override
    {
        Q_Q(AbstractResourceLink);
        AbstractResourceLinkSP castedOther = qSharedPointerCast<AbstractResourceLink>(other);
        q->setUsage(castedOther->usage());
        q->setRRef(castedOther->rRef());
    }

    ApiHelper::Usage usage = ApiHelper::InputUsage;
    QString rRef;
};

}
}

using namespace Proof::Jdf;

ApiHelper::Usage AbstractResourceLink::usage() const
{
    Q_D(AbstractResourceLink);
    return d->usage;
}

QString AbstractResourceLink::rRef() const
{
    Q_D(AbstractResourceLink);
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
        emit usageChanged(d->rRef);
    }
}

void AbstractResourceLink::fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceLinkSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractResource->setUsage(ApiHelper::usageFromString(attributes.value("usage").toString()));
    abstractResourceLink->setRRef(attributes.value("rRef").toString());
}

void AbstractResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResourceLink);
    jdfWriter.writeAttribute("usage", ApiHelper::usageToString(d->usage()));
    jdfWriter.writeAttribute("rRef", d->rRef());
}

AbstractResourceLink::AbstractResourceLink()
{
}
