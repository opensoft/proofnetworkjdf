#include "abstractaudit.h"

#include "proofnetwork/jdf/data/abstractaudit_p.h"

using namespace Proof::Jdf;

QString AbstractAudit::id() const
{
    Q_D(const AbstractAudit);
    return d->id;
}

QString AbstractAudit::agentName() const
{
    Q_D(const AbstractAudit);
    return d->agentName;
}

QString AbstractAudit::agentVersion() const
{
    Q_D(const AbstractAudit);
    return d->agentVersion;
}

QDateTime AbstractAudit::timeStamp() const
{
    Q_D(const AbstractAudit);
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

AbstractAudit::AbstractAudit(AbstractAuditPrivate &dd, QObject *parent) : NetworkDataEntity(dd, parent)
{}

void AbstractAuditPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(AbstractAudit);
    AbstractAuditSP castedOther = qSharedPointerCast<AbstractAudit>(other);
    q->setId(castedOther->id());
    q->setAgentName(castedOther->agentName());
    q->setAgentVersion(castedOther->agentVersion());
    q->setTimeStamp(castedOther->timeStamp());

    NetworkDataEntityPrivate::updateFrom(other);
}
