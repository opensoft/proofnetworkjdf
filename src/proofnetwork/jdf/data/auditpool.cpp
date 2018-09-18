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
#include "proofnetwork/jdf/data/auditpool.h"

#include "proofcore/objectscache.h"

#include "proofnetwork/jdf/data/createdaudit.h"
#include "proofnetwork/jdf/data/modifiedaudit.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class AuditPoolPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AuditPool)

    AuditPoolPrivate() { registerChildren(created, modified); }

    CreatedAuditSP created = CreatedAudit::create();
    ModifiedAuditSP modified = ModifiedAudit::create();
};

ObjectsCache<QString, AuditPool> &auditPoolCache()
{
    return WeakObjectsCache<QString, AuditPool>::instance();
}

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

AuditPool::AuditPool() : NetworkDataEntity(*new AuditPoolPrivate)
{}

CreatedAuditSP AuditPool::created() const
{
    Q_D_CONST(AuditPool);
    return d->created;
}

ModifiedAuditSP AuditPool::modified() const
{
    Q_D_CONST(AuditPool);
    return d->modified;
}

AuditPoolQmlWrapper *AuditPool::toQmlWrapper(QObject *parent) const
{
    AuditPoolSP castedSelf = castedSelfPtr<AuditPool>();
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

void AuditPool::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AuditPoolSP castedOther = qSharedPointerCast<AuditPool>(other);
    setCreated(castedOther->created());
    setModified(castedOther->modified());
    NetworkDataEntity::updateSelf(other);
}
