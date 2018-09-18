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
#include "proofnetwork/jdf/data/deviceinfo.h"

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
    Q_D_CONST(DeviceInfo);
    return d->deviceId;
}

DeviceStatus Proof::Jdf::DeviceInfo::status() const
{
    Q_D_CONST(DeviceInfo);
    return d->status;
}

DeviceCondition DeviceInfo::condition() const
{
    Q_D_CONST(DeviceInfo);
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
