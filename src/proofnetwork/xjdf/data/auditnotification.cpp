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
#include "proofnetwork/xjdf/data/auditnotification.h"

#include "proofnetwork/xjdf/data/audititembase_p.h"

namespace Proof {
namespace XJdf {

class AuditNotificationPrivate : public AuditItemBasePrivate
{
    Q_DECLARE_PUBLIC(AuditNotification)
public:
    AuditNotificationPrivate() = default;

    Severity severityClass = Severity::Event;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

Severity AuditNotification::severityClass() const
{
    Q_D_CONST(AuditNotification);
    return d->severityClass;
}

void AuditNotification::setSeverityClass(Severity arg)
{
    Q_D(AuditNotification);
    if (arg != d->severityClass) {
        d->severityClass = arg;
        emit severityClassChanged(arg);
    }
}

AuditNotificationSP AuditNotification::create()
{
    AuditNotificationSP result(new AuditNotification());
    initSelfWeakPtr(result);
    return result;
}

AuditNotificationSP AuditNotification::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    AuditNotificationSP notification = create();
    notification->d_func()->document = document;
    reader.readNextStartElement();
    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.isStartElement()) {
            if (reader.name() == QStringLiteral("Notification")) {
                notification->setSeverityClass(
                    severityFromString(reader.attributes().value(QStringLiteral("Class")).toString()));
            } else {
                notification->readFieldsFromXJdf(reader);
            }
        } else if (reader.isEndElement()) {
            if (reader.name() == QStringLiteral("AuditNotification"))
                break;
        }
        reader.readNext();
    }
    notification->setFetched(true);
    return notification;
}

void AuditNotification::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(AuditNotification);
    writer.writeStartElement(QStringLiteral("AuditNotification"));
    writer.writeStartElement(QStringLiteral("Header"));
    AuditItemBase::toXJdf(writer);
    writer.writeEndElement();
    writer.writeStartElement(QStringLiteral("Notification"));
    writer.writeAttribute(QStringLiteral("Class"), severityToString(d->severityClass));
    writer.writeEndElement();
    writer.writeEndElement();
}

AuditNotification::AuditNotification() : AuditItemBase(*new AuditNotificationPrivate)
{}

void AuditNotification::updateSelf(const NetworkDataEntitySP &other)
{
    AuditNotificationSP castedOther = qSharedPointerCast<AuditNotification>(other);
    setSeverityClass(castedOther->severityClass());

    AuditItemBase::updateSelf(other);
}
