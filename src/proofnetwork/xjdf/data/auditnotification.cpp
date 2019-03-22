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
#include "proofnetwork/xjdf/data/auditnotification.h"

#include "proofnetwork/xjdf/data/auditabstractitem_p.h"

namespace Proof {
namespace XJdf {

class AuditNotificationPrivate : public AuditAbstractItemPrivate
{
    Q_DECLARE_PUBLIC(AuditNotification)
public:
    AuditNotificationPrivate() {}

    Severity severityClass;
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

AuditNotificationSP AuditNotification::fromXJdf(QXmlStreamReader &xjdfReader)
{
    AuditNotificationSP notification = create();
    xjdfReader.readNextStartElement();
    while (!xjdfReader.atEnd() && !xjdfReader.hasError()) {
        if (xjdfReader.isStartElement()) {
            if (xjdfReader.name() == "Header") {
                notification->readAttributesFromXJdf(xjdfReader);
            } else if (xjdfReader.name() == "Notification") {
                notification->setSeverityClass(severityFromString(xjdfReader.attributes().value("Class").toString()));
            }
        } else if (xjdfReader.isEndElement()) {
            if (xjdfReader.name() == "AuditNotification")
                break;
        }
        xjdfReader.readNext();
    }
    notification->setFetched(true);
    return notification;
}

void AuditNotification::toXJdf(QXmlStreamWriter &xjdfWriter, bool) const
{
    Q_D_CONST(AuditNotification);
    xjdfWriter.writeStartElement("AuditCreated");
    xjdfWriter.writeStartElement("Header");
    AuditAbstractItem::toXJdf(xjdfWriter);
    xjdfWriter.writeEndElement();
    xjdfWriter.writeStartElement("Notification");
    xjdfWriter.writeAttribute("Class", severityToString(d->severityClass));
    xjdfWriter.writeEndElement();
    xjdfWriter.writeEndElement();
}

AuditNotification::AuditNotification() : AuditAbstractItem(*new AuditNotificationPrivate)
{}

void AuditNotification::updateSelf(const NetworkDataEntitySP &other)
{
    AuditNotificationSP castedOther = qSharedPointerCast<AuditNotification>(other);
    setSeverityClass(castedOther->severityClass());

    AuditAbstractItem::updateSelf(other);
}
