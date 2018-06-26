#include "devicefilter.h"

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DeviceFilterPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DeviceFilter)

    DeviceFilterDetails details = DeviceFilterDetails::NoneDeviceFilterDetails;
};

DeviceFilterDetails DeviceFilter::details() const
{
    Q_D(const DeviceFilter);
    return d->details;
}

void DeviceFilter::setDetails(DeviceFilterDetails arg)
{
    Q_D(DeviceFilter);
    if (d->details != arg) {
        d->details = arg;
        emit detailsChanged(d->details);
    }
}

NetworkDataEntityQmlWrapper *DeviceFilter::toQmlWrapper(QObject *) const
{
    Q_ASSERT(false);
    return nullptr;
}

DeviceFilterSP DeviceFilter::create()
{
    DeviceFilterSP result(new DeviceFilter());
    initSelfWeakPtr(result);
    return result;
}

void DeviceFilter::toJmf(QXmlStreamWriter &xmlWriter)
{
    xmlWriter.writeStartElement(QStringLiteral("DeviceFilter"));
    xmlWriter.writeAttribute(QStringLiteral("DeviceDetails"), deviceFilterDetailsToString(details()));
    xmlWriter.writeEndElement();
}

DeviceFilterSP DeviceFilter::fromJmf(QXmlStreamReader &xmlReader)
{
    DeviceFilterSP result;
    if (xmlReader.isStartElement() && xmlReader.name() == "DeviceFilter") {
        result = create();
        result->setFetched(true);
        auto attributes = xmlReader.attributes();
        result->setDetails(deviceFilterDetailsFromString(attributes.value(QStringLiteral("DeviceDetails")).toString()));
        xmlReader.skipCurrentElement();
    }
    return result;
}

DeviceFilter::DeviceFilter() : NetworkDataEntity(*new DeviceFilterPrivate)
{}

void DeviceFilter::updateSelf(const NetworkDataEntitySP &other)
{
    DeviceFilterSP castedOther = qSharedPointerCast<DeviceFilter>(other);
    setDetails(castedOther->details());
    NetworkDataEntity::updateSelf(other);
}

} // namespace Jdf
} // namespace Proof
