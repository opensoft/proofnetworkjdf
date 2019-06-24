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
#include "proofnetwork/xjdf/data/auditpool.h"

#include "proofnetwork/xjdf/data/abstractnode_p.h"
#include "proofnetwork/xjdf/data/auditcreated.h"
#include "proofnetwork/xjdf/data/auditnotification.h"

namespace Proof {
namespace XJdf {

class AuditPoolPrivate : public AbstractNodePrivate
{
    Q_DECLARE_PUBLIC(AuditPool)

    AuditPoolPrivate() { registerChildren(created, notifications); }

    AuditCreatedSP created;
    QVector<AuditNotificationSP> notifications;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

AuditPool::AuditPool() : AbstractNode(*new AuditPoolPrivate)
{}

AuditCreatedSP AuditPool::created() const
{
    Q_D_CONST(AuditPool);
    return d->created;
}

QVector<AuditNotificationSP> AuditPool::notifications() const
{
    Q_D_CONST(AuditPool);
    return d->notifications;
}

AuditPoolSP AuditPool::create(const DocumentSP &document)
{
    AuditPoolSP result(new AuditPool());
    result->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

AuditPoolSP AuditPool::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    AuditPoolSP auditPool = create(document);

    QVector<AuditNotificationSP> notifications;
    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.isStartElement()) {
            if (reader.name() == QStringLiteral("AuditNotification")) {
                auto notification = AuditNotification::fromXJdf(reader, document);
                if (!notification) {
                    qCWarning(proofNetworkXJdfDataLog) << "AuditPool not created. Modified is invalid.";
                    return AuditPoolSP();
                }
                notifications << notification;
            } else if (reader.name() == QStringLiteral("AuditCreated")) {
                AuditCreatedSP created = AuditCreated::fromXJdf(reader, document);
                if (!created) {
                    qCWarning(proofNetworkXJdfDataLog) << "AuditPool not created. Created is invalid.";
                    return AuditPoolSP();
                }
                auditPool->setCreated(created);
            }
        } else if (reader.isEndElement() && reader.name() == QStringLiteral("AuditPool")) {
            break;
        }
        reader.readNext();
    }
    auditPool->setNotifications(notifications);
    auditPool->setFetched(true);

    return auditPool;
}

void AuditPool::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(AuditPool);

    writer.writeStartElement(QStringLiteral("AuditPool"));

    if (isValidAndDirty(d->created))
        d->created->toXJdf(writer);
    for (const auto &notification : d->notifications)
        notification->toXJdf(writer);

    writer.writeEndElement();
}

void AuditPool::setCreated(const AuditCreatedSP &created)
{
    Q_ASSERT(created);
    Q_D(AuditPool);
    if (created == nullptr) {
        d->created.reset();
    } else if (d->created != created) {
        d->created = created;
        emit createdChanged(d->created);
    }
}

void AuditPool::setNotifications(const QVector<AuditNotificationSP> &arg)
{
    Q_D(AuditPool);
    bool emitNeeded = arg.count() != d->notifications.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->notifications[i]->id();
    if (emitNeeded) {
        d->notifications = arg;
        emit notificationsChanged(d->notifications);
    }
}

void AuditPool::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AuditPoolSP castedOther = qSharedPointerCast<AuditPool>(other);
    setCreated(castedOther->created());
    setNotifications(castedOther->notifications());
    AbstractNode::updateSelf(other);
}
