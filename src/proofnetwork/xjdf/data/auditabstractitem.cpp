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
#include "proofnetwork/xjdf/data/auditabstractitem.h"

#include "proofnetwork/xjdf/data/auditabstractitem_p.h"

using namespace Proof;
using namespace Proof::XJdf;

QString AuditAbstractItem::agentName() const
{
    Q_D_CONST(AuditAbstractItem);
    return d->agentName;
}

QString AuditAbstractItem::agentVersion() const
{
    Q_D_CONST(AuditAbstractItem);
    return d->agentVersion;
}

QDateTime AuditAbstractItem::timestamp() const
{
    Q_D_CONST(AuditAbstractItem);
    return d->timestamp;
}

QString AuditAbstractItem::id() const
{
    Q_D_CONST(AuditAbstractItem);
    return d->id;
}

QString AuditAbstractItem::deviceId() const
{
    Q_D_CONST(AuditAbstractItem);
    return d->deviceId;
}

void AuditAbstractItem::setAgentName(const QString &arg)
{
    Q_D(AuditAbstractItem);
    if (arg != d->agentName) {
        d->agentName = arg;
        emit agentNameChanged(arg);
    }
}

void AuditAbstractItem::setAgentVersion(const QString &arg)
{
    Q_D(AuditAbstractItem);
    if (arg != d->agentVersion) {
        d->agentVersion = arg;
        emit agentVersionChanged(arg);
    }
}

void AuditAbstractItem::setTimestamp(const QDateTime &arg)
{
    Q_D(AuditAbstractItem);
    if (arg != d->timestamp) {
        d->timestamp = arg;
        emit timestampChanged(arg);
    }
}

void AuditAbstractItem::setId(const QString &arg)
{
    Q_D(AuditAbstractItem);
    if (arg != d->id) {
        d->id = arg;
        emit idChanged(arg);
    }
}

void AuditAbstractItem::setDeviceId(const QString &arg)
{
    Q_D(AuditAbstractItem);
    if (arg != d->deviceId) {
        d->deviceId = arg;
        emit deviceIdChanged(arg);
    }
}

bool AuditAbstractItem::fillFromXJdf(QXmlStreamReader &)
{
    //NOTE: Nothing there for now
    return false;
}

void AuditAbstractItem::readAttributesFromXJdf(QXmlStreamReader &xjdfReader)
{
    auto attributes = xjdfReader.attributes();
    if (attributes.hasAttribute("AgentVersion"))
        setAgentVersion(attributes.value("AgentVersion").toString());
    if (attributes.hasAttribute("AgentName"))
        setAgentName(attributes.value("AgentName").toString());
    if (attributes.hasAttribute("ID"))
        setId(attributes.value("ID").toString());
    if (attributes.hasAttribute("DeviceId"))
        setDeviceId(attributes.value("DeviceID").toString());
    if (attributes.hasAttribute("Time"))
        setTimestamp(QDateTime::fromString(attributes.value("Time").toString(), Qt::ISODate));
}

void AuditAbstractItem::toXJdf(QXmlStreamWriter &xjdfWriter, bool) const
{
    Q_D_CONST(AuditAbstractItem);
    xjdfWriter.writeAttribute("AgentVersion", d->agentVersion);
    xjdfWriter.writeAttribute("AgentName", d->agentName);
    xjdfWriter.writeAttribute("ID", d->id);
    xjdfWriter.writeAttribute("DeviceId", d->deviceId);
    xjdfWriter.writeAttribute("Time", d->timestamp.toString(Qt::ISODate));
}

AuditAbstractItem::AuditAbstractItem() : AuditAbstractItem(*new AuditAbstractItemPrivate)
{}

AuditAbstractItem::AuditAbstractItem(AuditAbstractItemPrivate &dd) : XJdfAbstractNode(dd)
{}

void AuditAbstractItem::updateSelf(const NetworkDataEntitySP &other)
{
    AuditAbstractItemSP castedOther = qSharedPointerCast<AuditAbstractItem>(other);
    setId(castedOther->id());
    setDeviceId(castedOther->deviceId());
    setAgentName(castedOther->agentName());
    setAgentVersion(castedOther->agentVersion());
    setTimestamp(castedOther->timestamp());

    XJdfAbstractNode::updateSelf(other);
}
