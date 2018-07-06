#include "createdaudit.h"

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
