#include "deviceinfo.h"

#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DeviceInfoPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DeviceInfo)

    QString deviceId;
    DeviceStatus status = DeviceStatus::UnknownDeviceStatus;
    DeviceCondition condition = DeviceCondition::OkDeviceCondition;
};

QString DeviceInfo::deviceId() const
{
    Q_D(const DeviceInfo);
    return d->deviceId;
}

DeviceStatus Proof::Jdf::DeviceInfo::status() const
{
    Q_D(const DeviceInfo);
    return d->status;
}

DeviceCondition DeviceInfo::condition() const
{
    Q_D(const DeviceInfo);
    return d->condition;
}

void DeviceInfo::setDeviceId(const QString &arg)
{
    Q_D(DeviceInfo);
    if (d->deviceId != arg) {
        d->deviceId = arg;
        emit deviceIdChanged(d->deviceId);
    }
}

void Proof::Jdf::DeviceInfo::setStatus(DeviceStatus arg)
{
    Q_D(DeviceInfo);
    if (d->status != arg) {
        d->status = arg;
        emit statusChanged(d->status);
    }
}

void Proof::Jdf::DeviceInfo::setCondition(DeviceCondition arg)
{
    Q_D(DeviceInfo);
    if (d->condition != arg) {
        d->condition = arg;
        emit conditionChanged(d->condition);
    }
}

NetworkDataEntityQmlWrapper *DeviceInfo::toQmlWrapper(QObject *) const
{
    Q_ASSERT(false);
    return nullptr;
}

DeviceInfoSP DeviceInfo::create()
{
    DeviceInfoSP result(new DeviceInfo());
    initSelfWeakPtr(result);
    return result;
}

DeviceInfoSP DeviceInfo::fromJmf(QXmlStreamReader &xmlReader)
{
    DeviceInfoSP deviceInfo;
    if (xmlReader.isStartElement() && xmlReader.name() == "DeviceInfo") {
        deviceInfo = create();
        deviceInfo->setFetched(true);
        auto attributes = xmlReader.attributes();
        deviceInfo->setDeviceId(attributes.value(QStringLiteral("DeviceID")).toString());
        deviceInfo->setStatus(deviceStatusFromString(attributes.value(QStringLiteral("DeviceStatus")).toString()));
        deviceInfo->setCondition(
            deviceConditionFromString(attributes.value(QStringLiteral("DeviceCondition")).toString()));
    }
    xmlReader.skipCurrentElement();
    return deviceInfo;
}

void DeviceInfo::toJmf(QXmlStreamWriter &xmlWriter)
{
    Q_D(DeviceInfo);
    xmlWriter.writeStartElement(QStringLiteral("DeviceInfo"));
    xmlWriter.writeAttribute(QStringLiteral("DeviceID"), d->deviceId);
    xmlWriter.writeAttribute(QStringLiteral("DeviceStatus"), deviceStatusToString(d->status));
    xmlWriter.writeAttribute(QStringLiteral("DeviceCondition"), deviceConditionToString(d->condition));
    xmlWriter.writeEndElement();
}

DeviceInfo::DeviceInfo() : NetworkDataEntity(*new DeviceInfoPrivate)
{}

} // namespace Jdf
} // namespace Proof
