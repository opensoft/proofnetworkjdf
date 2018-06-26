#include "knowndevicesresponse.h"

#include "proofnetwork/jdf/data/deviceinfo.h"
#include "proofnetwork/jdf/data/notification.h"
#include "proofnetwork/jdf/data/response_p.h"

#include <algorithm>

namespace Proof {
namespace Jdf {

class KnownDevicesResponsePrivate : public ResponsePrivate
{
    Q_DECLARE_PUBLIC(KnownDevicesResponse)

protected:
    KnownDevicesResponsePrivate() { registerChildren(deviceInfos); }

    void specificMessageFromJmf(QXmlStreamReader &xmlReader) override;
    QString typeName() const override;
    void specificMessageToJmf(QXmlStreamWriter &xmlWriter) const override;

private:
    QVector<DeviceInfoSP> deviceInfos;
};

QVector<DeviceInfoSP> KnownDevicesResponse::deviceInfos() const
{
    Q_D(const KnownDevicesResponse);
    return d->deviceInfos;
}

void KnownDevicesResponse::setDeviceInfos(const QVector<DeviceInfoSP> &arg)
{
    Q_D(KnownDevicesResponse);
    bool notEqual = d->deviceInfos.size() != arg.size()
                    || !std::is_permutation(d->deviceInfos.cbegin(), d->deviceInfos.cend(), arg.cbegin());
    if (notEqual) {
        d->deviceInfos = arg;
        emit deviceInfosChanged(d->deviceInfos);
    }
}

void KnownDevicesResponse::addDeviceInfo(const DeviceInfoSP &arg)
{
    Q_D(KnownDevicesResponse);
    d->deviceInfos << arg;
    emit deviceInfosChanged(d->deviceInfos);
}

KnownDevicesResponseSP KnownDevicesResponse::create()
{
    KnownDevicesResponseSP result(new KnownDevicesResponse());
    initSelfWeakPtr(result);
    return result;
}

KnownDevicesResponse::KnownDevicesResponse() : Response(*new KnownDevicesResponsePrivate)
{}

void KnownDevicesResponse::updateSelf(const NetworkDataEntitySP &other)
{
    KnownDevicesResponseSP castedOther = qSharedPointerCast<KnownDevicesResponse>(other);
    setDeviceInfos(castedOther->deviceInfos());
    setNotification(castedOther->notification());
    Response::updateSelf(other);
}

void KnownDevicesResponsePrivate::specificMessageFromJmf(QXmlStreamReader &xmlReader)
{
    Q_Q(KnownDevicesResponse);
    while (xmlReader.readNextStartElement()) {
        if (xmlReader.name() == "DeviceList") {
            while (xmlReader.readNextStartElement()) {
                if (xmlReader.name() == "DeviceInfo") {
                    auto deviceInfo = DeviceInfo::fromJmf(xmlReader);
                    if (deviceInfo != nullptr)
                        q->addDeviceInfo(deviceInfo);
                }
            }
        } else {
            ResponsePrivate::specificMessageFromJmf(xmlReader);
        }
    }
}

QString KnownDevicesResponsePrivate::typeName() const
{
    return QStringLiteral("KnownDevices");
}

void KnownDevicesResponsePrivate::specificMessageToJmf(QXmlStreamWriter &xmlWriter) const
{
    if (!deviceInfos.isEmpty()) {
        xmlWriter.writeStartElement(QStringLiteral("DeviceList"));
        for (const DeviceInfoSP &deviceInfo : deviceInfos)
            deviceInfo->toJmf(xmlWriter);
        xmlWriter.writeEndElement();
    }
    ResponsePrivate::specificMessageToJmf(xmlWriter);
}

} // namespace Jdf
} // namespace Proof
