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
#include "proofnetwork/jdf/data/createdaudit.h"

#include "proofnetwork/jdf/data/abstractaudit_p.h"

namespace Proof {
namespace Jdf {

class CreatedAuditPrivate : AbstractAuditPrivate
{
    Q_DECLARE_PUBLIC(CreatedAudit)

    CreatedAuditPrivate() : AbstractAuditPrivate() {}

    QString templateId;
    QString templateVersion;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

QString CreatedAudit::templateId() const
{
    Q_D_CONST(CreatedAudit);
    return d->templateId;
}

QString CreatedAudit::templateVersion() const
{
    Q_D_CONST(CreatedAudit);
    return d->templateVersion;
}

void CreatedAudit::setTemplateId(const QString &templateId)
{
    Q_D(CreatedAudit);
    if (d->templateId != templateId) {
        d->templateId = templateId;
        emit templateIdChanged(templateId);
    }
}

void CreatedAudit::setTemplateVersion(const QString &templateVersion)
{
    Q_D(CreatedAudit);
    if (d->templateVersion != templateVersion) {
        d->templateVersion = templateVersion;
        emit templateVersionChanged(templateVersion);
    }
}

CreatedAuditQmlWrapper *CreatedAudit::toQmlWrapper(QObject *parent) const
{
    CreatedAuditSP castedSelf = castedSelfPtr<CreatedAudit>();
    Q_ASSERT(castedSelf);
    return new CreatedAuditQmlWrapper(castedSelf, parent);
}

CreatedAuditSP CreatedAudit::create()
{
    CreatedAuditSP result(new CreatedAudit());
    initSelfWeakPtr(result);
    return result;
}

CreatedAuditSP CreatedAudit::fromJdf(QXmlStreamReader &xmlReader)
{
    CreatedAuditSP createdAudit = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Created" && xmlReader.isStartElement() && !createdAudit->isFetched()) {
            createdAudit->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            createdAudit->setTemplateId(attributes.value(QStringLiteral("TemplateID")).toString());
            createdAudit->setTemplateVersion(attributes.value(QStringLiteral("TemplateVersion")).toString());
            AbstractAuditSP castedCreatedAudit = qSharedPointerCast<AbstractAudit>(createdAudit);
            AbstractAudit::fromJdf(xmlReader, castedCreatedAudit);
        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return createdAudit;
}

void CreatedAudit::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(CreatedAudit);

    jdfWriter.writeStartElement(QStringLiteral("Created"));
    if (!d->templateId.isEmpty())
        jdfWriter.writeAttribute(QStringLiteral("TemplateID"), d->templateId);
    if (!d->templateVersion.isEmpty())
        jdfWriter.writeAttribute(QStringLiteral("TemplateVersion"), d->templateVersion);
    AbstractAudit::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

CreatedAudit::CreatedAudit() : AbstractAudit(*new CreatedAuditPrivate)
{}

void CreatedAudit::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    CreatedAuditSP castedOther = qSharedPointerCast<CreatedAudit>(other);
    setTemplateId(castedOther->templateId());
    setTemplateVersion(castedOther->templateVersion());

    AbstractAudit::updateSelf(other);
}
