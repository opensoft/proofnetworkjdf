/* Copyright 2019, OpenSoft Inc.
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
#include "proofnetwork/xjdf/data/audititembase.h"

#include "proofnetwork/xjdf/data/audititembase_p.h"

using namespace Proof;
using namespace Proof::XJdf;

QString AuditItemBase::agentName() const
{
    Q_D_CONST(AuditItemBase);
    return d->agentName;
}

QString AuditItemBase::agentVersion() const
{
    Q_D_CONST(AuditItemBase);
    return d->agentVersion;
}

QDateTime AuditItemBase::timestamp() const
{
    Q_D_CONST(AuditItemBase);
    return d->timestamp;
}

QString AuditItemBase::id() const
{
    Q_D_CONST(AuditItemBase);
    return d->id;
}

QString AuditItemBase::deviceId() const
{
    Q_D_CONST(AuditItemBase);
    return d->deviceId;
}

void AuditItemBase::setAgentName(const QString &arg)
{
    Q_D(AuditItemBase);
    if (arg != d->agentName) {
        d->agentName = arg;
        emit agentNameChanged(arg);
    }
}

void AuditItemBase::setAgentVersion(const QString &arg)
{
    Q_D(AuditItemBase);
    if (arg != d->agentVersion) {
        d->agentVersion = arg;
        emit agentVersionChanged(arg);
    }
}

void AuditItemBase::setTimestamp(const QDateTime &arg)
{
    Q_D(AuditItemBase);
    if (arg != d->timestamp) {
        d->timestamp = arg;
        emit timestampChanged(arg);
    }
}

void AuditItemBase::setId(const QString &arg)
{
    Q_D(AuditItemBase);
    if (arg != d->id) {
        d->id = arg;
        emit idChanged(arg);
    }
}

void AuditItemBase::setDeviceId(const QString &arg)
{
    Q_D(AuditItemBase);
    if (arg != d->deviceId) {
        d->deviceId = arg;
        emit deviceIdChanged(arg);
    }
}

bool AuditItemBase::readFieldsFromXJdf(QXmlStreamReader &reader)
{
    if (reader.name() == QStringLiteral("Header")) {
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("AgentVersion")))
            setAgentVersion(attributes.value(QStringLiteral("AgentVersion")).toString());
        if (attributes.hasAttribute(QStringLiteral("AgentName")))
            setAgentName(attributes.value(QStringLiteral("AgentName")).toString());
        if (attributes.hasAttribute(QStringLiteral("ID")))
            setId(attributes.value(QStringLiteral("ID")).toString());
        if (attributes.hasAttribute(QStringLiteral("DeviceId")))
            setDeviceId(attributes.value(QStringLiteral("DeviceID")).toString());
        if (attributes.hasAttribute(QStringLiteral("Time")))
            setTimestamp(QDateTime::fromString(attributes.value(QStringLiteral("Time")).toString(), Qt::ISODate));

        return true;
    }
    return false;
}

void AuditItemBase::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(AuditItemBase);
    if (!d->agentVersion.isEmpty())
        writer.writeAttribute(QStringLiteral("AgentVersion"), d->agentVersion);
    if (!d->agentName.isEmpty())
        writer.writeAttribute(QStringLiteral("AgentName"), d->agentName);
    if (!d->id.isEmpty())
        writer.writeAttribute(QStringLiteral("ID"), d->id);
    if (!d->deviceId.isEmpty())
        writer.writeAttribute(QStringLiteral("DeviceId"), d->deviceId);
    if (d->timestamp.isValid())
        writer.writeAttribute(QStringLiteral("Time"), d->timestamp.toString(Qt::ISODate));
}

AuditItemBase::AuditItemBase(AuditItemBasePrivate &dd) : AbstractNode(dd)
{}

void AuditItemBase::updateSelf(const NetworkDataEntitySP &other)
{
    AuditItemBaseSP castedOther = qSharedPointerCast<AuditItemBase>(other);
    setId(castedOther->id());
    setDeviceId(castedOther->deviceId());
    setAgentName(castedOther->agentName());
    setAgentVersion(castedOther->agentVersion());
    setTimestamp(castedOther->timestamp());

    AbstractNode::updateSelf(other);
}
