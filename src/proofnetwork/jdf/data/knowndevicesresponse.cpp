/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "proofnetwork/jdf/data/knowndevicesresponse.h"

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
    Q_D_CONST(KnownDevicesResponse);
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
