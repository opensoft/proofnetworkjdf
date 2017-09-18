#include "auditpool.h"

#include "createdaudit.h"
#include "modifiedaudit.h"
#include "proofnetwork/networkdataentity_p.h"
#include "proofcore/objectscache.h"

namespace Proof {
namespace Jdf {

class AuditPoolPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AuditPool)

    AuditPoolPrivate()
    {
        registerChildren(created, modified);
    }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    CreatedAuditSP created = CreatedAudit::create();
    ModifiedAuditSP modified = ModifiedAudit::create();
};

ObjectsCache<QString, AuditPool> &auditPoolCache()
{
    return WeakObjectsCache<QString, AuditPool>::instance();
}

}
}

using namespace Proof;
using namespace Proof::Jdf;

AuditPool::AuditPool()
    : NetworkDataEntity(*new AuditPoolPrivate)
{
}

CreatedAuditSP AuditPool::created() const
{
    Q_D(const AuditPool);
    return d->created;
}

ModifiedAuditSP AuditPool::modified() const
{
    Q_D(const AuditPool);
    return d->modified;
}

AuditPoolQmlWrapper *AuditPool::toQmlWrapper(QObject *parent) const
{
    Q_D(const AuditPool);
    AuditPoolSP castedSelf = qSharedPointerCast<AuditPool>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new AuditPoolQmlWrapper(castedSelf, parent);
}

AuditPoolSP AuditPool::create()
{
    AuditPoolSP result(new AuditPool());
    initSelfWeakPtr(result);
    return result;
}

AuditPoolSP AuditPool::fromJdf(QXmlStreamReader &xmlReader)
{
    AuditPoolSP auditPool = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "AuditPool" && xmlReader.isStartElement() && !auditPool->isFetched()) {
            auditPool->setFetched(true);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Modified") {
                ModifiedAuditSP modified = ModifiedAudit::fromJdf(xmlReader);
                if (!modified) {
                    qCWarning(proofNetworkJdfDataLog) << "AuditPool not created. Modified is invalid.";
                    return AuditPoolSP();
                }
                auditPool->setModified(modified);
            } else if (xmlReader.name() == "Created") {
                CreatedAuditSP created = CreatedAudit::fromJdf(xmlReader);
                if (!created) {
                    qCWarning(proofNetworkJdfDataLog) << "AuditPool not created. Created is invalid.";
                    return AuditPoolSP();
                }
                auditPool->setCreated(created);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return auditPool;
}

void AuditPool::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AuditPool);

    jdfWriter.writeStartElement(QStringLiteral("AuditPool"));

    if (isValidAndDirty(d->created))
        d->created->toJdf(jdfWriter);
    if (isValidAndDirty(d->modified))
        d->modified->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

void AuditPool::setCreated(const CreatedAuditSP &created)
{
    Q_ASSERT(created);
    Q_D(AuditPool);
    if (created == nullptr) {
        setCreated(CreatedAudit::create());
    } else if (d->created != created) {
        d->created = created;
        emit createdChanged(d->created);
    }
}

void AuditPool::setModified(const ModifiedAuditSP &modified)
{
    Q_ASSERT(modified);
    Q_D(AuditPool);
    if (modified == nullptr) {
        setModified(ModifiedAudit::create());
    } else if (d->modified != modified) {
        d->modified = modified;
        emit modifiedChanged(d->modified);
    }
}

void AuditPoolPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(AuditPool);
    AuditPoolSP castedOther = qSharedPointerCast<AuditPool>(other);
    q->setCreated(castedOther->created());
    q->setModified(castedOther->modified());
    NetworkDataEntityPrivate::updateFrom(other);
}
