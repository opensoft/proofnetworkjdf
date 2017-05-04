#include "knowndevicesquery.h"

#include "query_p.h"
#include "devicefilter.h"

namespace Proof {
namespace Jdf {

class KnownDevicesQueryPrivate : public QueryPrivate
{
    Q_DECLARE_PUBLIC(KnownDevicesQuery)

protected:
    KnownDevicesQueryPrivate()
    {
        registerChildren(deviceFilter);
    }

    void updateFrom(const NetworkDataEntitySP &other) override;
    void specificMessageFromJmf(QXmlStreamReader &xmlReader) override;
    QString typeName() const override;
    void specificMessageToJmf(QXmlStreamWriter &xmlWriter) const override;

private:
    DeviceFilterSP deviceFilter = DeviceFilter::create();
};

DeviceFilterSP KnownDevicesQuery::deviceFilter() const
{
    Q_D(const KnownDevicesQuery);
    return d->deviceFilter;
}

void KnownDevicesQuery::setDeviceFilter(const DeviceFilterSP &arg)
{
    Q_D(KnownDevicesQuery);
    if (d->deviceFilter != arg) {
        d->deviceFilter = arg;
        emit deviceFilterChanged(d->deviceFilter);
    }
}

KnownDevicesQuerySP KnownDevicesQuery::create()
{
    KnownDevicesQuerySP result(new KnownDevicesQuery());
    initSelfWeakPtr(result);
    return result;
}

KnownDevicesQuery::KnownDevicesQuery()
    : Query(*new KnownDevicesQueryPrivate)
{
}

void KnownDevicesQueryPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(KnownDevicesQuery);
    KnownDevicesQuerySP castedOther = qSharedPointerCast<KnownDevicesQuery>(other);
    q->setDeviceFilter(castedOther->deviceFilter());
    QueryPrivate::updateFrom(other);
}

void KnownDevicesQueryPrivate::specificMessageFromJmf(QXmlStreamReader &xmlReader)
{
    Q_Q(KnownDevicesQuery);
    while (xmlReader.readNextStartElement()) {
        if (xmlReader.name() == "DeviceFilter") {
            auto filter = DeviceFilter::fromJmf(xmlReader);
            if (filter != nullptr)
                q->setDeviceFilter(filter);
            else
                xmlReader.skipCurrentElement();
        } else {
            QueryPrivate::specificMessageFromJmf(xmlReader);
        }
    }
}

QString KnownDevicesQueryPrivate::typeName() const
{
    return QStringLiteral("KnownDevices");
}

void KnownDevicesQueryPrivate::specificMessageToJmf(QXmlStreamWriter &xmlWriter) const
{
    if (deviceFilter != nullptr)
        deviceFilter->toJmf(xmlWriter);
    QueryPrivate::specificMessageToJmf(xmlWriter);
}

} // namespace Jdf
} // namespace Proof

