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
#include "proofnetwork/jdf/data/abstractaudit.h"

#include "proofnetwork/jdf/data/abstractaudit_p.h"

using namespace Proof::Jdf;

QString AbstractAudit::id() const
{
    Q_D_CONST(AbstractAudit);
    return d->id;
}

QString AbstractAudit::agentName() const
{
    Q_D_CONST(AbstractAudit);
    return d->agentName;
}

QString AbstractAudit::agentVersion() const
{
    Q_D_CONST(AbstractAudit);
    return d->agentVersion;
}

QDateTime AbstractAudit::timeStamp() const
{
    Q_D_CONST(AbstractAudit);
    return d->timeStamp;
}

void AbstractAudit::setId(const QString &arg)
{
    Q_D(AbstractAudit);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void AbstractAudit::setAgentName(const QString &arg)
{
    Q_D(AbstractAudit);
    if (d->agentName != arg) {
        d->agentName = arg;
        emit agentNameChanged(d->agentName);
    }
}

void AbstractAudit::setAgentVersion(const QString &arg)
{
    Q_D(AbstractAudit);
    if (d->agentVersion != arg) {
        d->agentVersion = arg;
        emit agentVersionChanged(d->agentVersion);
    }
}

void AbstractAudit::setTimeStamp(const QDateTime &arg)
{
    Q_D(AbstractAudit);
    if (d->timeStamp != arg) {
        d->timeStamp = arg;
        emit timeStampChanged(d->timeStamp);
    }
}

bool AbstractAudit::fromJdf(const QXmlStreamReader &xmlReader, AbstractAuditSP &abstractAudit)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractAudit->setId(attributes.value(QStringLiteral("ID")).toString());
    abstractAudit->setAgentName(attributes.value(QStringLiteral("AgentName")).toString());
    abstractAudit->setAgentVersion(attributes.value(QStringLiteral("AgentVersion")).toString());
    abstractAudit->setTimeStamp(
        QDateTime::fromString(attributes.value(QStringLiteral("TimeStamp")).toString(), Qt::ISODate));

    return true;
}

void AbstractAudit::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractAudit);
    if (!d->id.isEmpty())
        jdfWriter.writeAttribute(QStringLiteral("ID"), d->id);
    if (!d->agentName.isEmpty())
        jdfWriter.writeAttribute(QStringLiteral("AgentName"), d->agentName);
    if (!d->agentVersion.isEmpty())
        jdfWriter.writeAttribute(QStringLiteral("AgentVersion"), d->agentVersion);
    if (!d->timeStamp.isNull())
        jdfWriter.writeAttribute(QStringLiteral("TimeStamp"), d->timeStamp.toUTC().toString(Qt::ISODate));
}

AbstractAudit::AbstractAudit(AbstractAuditPrivate &dd) : NetworkDataEntity(dd)
{}

void AbstractAudit::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AbstractAuditSP castedOther = qSharedPointerCast<AbstractAudit>(other);
    setId(castedOther->id());
    setAgentName(castedOther->agentName());
    setAgentVersion(castedOther->agentVersion());
    setTimeStamp(castedOther->timeStamp());

    NetworkDataEntity::updateSelf(other);
}
