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
#include "proofnetwork/xjdf/data/auditcreated.h"

#include "proofnetwork/xjdf/data/auditabstractitem_p.h"

namespace Proof {
namespace XJdf {

class AuditCreatedPrivate : public AuditAbstractItemPrivate
{
    Q_DECLARE_PUBLIC(AuditCreated)
public:
    AuditCreatedPrivate() = default;
    QString templateId;
    QString templateVersion;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QString AuditCreated::templateId() const
{
    Q_D_CONST(AuditCreated);
    return d->templateId;
}

QString AuditCreated::templateVersion() const
{
    Q_D_CONST(AuditCreated);
    return d->templateVersion;
}

void AuditCreated::setTemplateId(const QString &arg)
{
    Q_D(AuditCreated);
    if (arg != d->templateId) {
        d->templateId = arg;
        emit templateIdChanged(arg);
    }
}

void AuditCreated::setTemplateVersion(const QString &arg)
{
    Q_D(AuditCreated);
    if (arg != d->templateVersion) {
        d->templateVersion = arg;
        emit templateVersionChanged(arg);
    }
}

AuditCreatedSP AuditCreated::create()
{
    AuditCreatedSP result(new AuditCreated());
    initSelfWeakPtr(result);
    return result;
}

AuditCreatedSP AuditCreated::fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document)
{
    AuditCreatedSP created = create();
    created->d_func()->document = document;

    reader.readNextStartElement();
    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.isStartElement()) {
            if (reader.name() == QStringLiteral("Header")) {
                created->readAttributesFromXJdf(reader);
                auto attributes = reader.attributes();
                created->setTemplateId(attributes.value(QStringLiteral("profit:TemplateID")).toString());
                created->setTemplateVersion(attributes.value(QStringLiteral("profit:TemplateVersion")).toString());
            }
        } else if (reader.isEndElement()) {
            if (reader.name() == QStringLiteral("AuditCreated"))
                break;
        }
        reader.readNext();
    }
    created->setFetched(true);
    return created;
}

void AuditCreated::toXJdf(QXmlStreamWriter &writer, bool writeEnd) const
{
    Q_D_CONST(AuditCreated);
    writer.writeStartElement(QStringLiteral("AuditCreated"));
    writer.writeStartElement(QStringLiteral("Header"));
    writer.writeAttribute(QStringLiteral("profit:TemplateID"), d->templateId);
    writer.writeAttribute(QStringLiteral("profit:TemplateVersion"), d->templateVersion);
    AuditAbstractItem::toXJdf(writer);
    writer.writeEndElement();
    writer.writeEndElement();
}

AuditCreated::AuditCreated() : AuditAbstractItem(*new AuditCreatedPrivate)
{}

void AuditCreated::updateSelf(const NetworkDataEntitySP &other)
{
    AuditCreatedSP castedOther = qSharedPointerCast<AuditCreated>(other);
    setTemplateId(castedOther->templateId());
    setTemplateVersion(castedOther->templateVersion());

    AuditAbstractItem::updateSelf(other);
}
