#include "modifiedaudit.h"

#include "proofnetwork/jdf/data/abstractaudit_p.h"

namespace Proof {
namespace Jdf {

class ModifiedAuditPrivate : AbstractAuditPrivate
{
    Q_DECLARE_PUBLIC(ModifiedAudit)

    ModifiedAuditPrivate() : AbstractAuditPrivate() {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

ModifiedAuditQmlWrapper *ModifiedAudit::toQmlWrapper(QObject *parent) const
{
    Q_D(const ModifiedAudit);
    ModifiedAuditSP castedSelf = qSharedPointerCast<ModifiedAudit>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new ModifiedAuditQmlWrapper(castedSelf, parent);
}

ModifiedAuditSP ModifiedAudit::create()
{
    ModifiedAuditSP result(new ModifiedAudit());
    initSelfWeakPtr(result);
    return result;
}

ModifiedAuditSP ModifiedAudit::fromJdf(QXmlStreamReader &xmlReader)
{
    ModifiedAuditSP modifiedAudit = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Modified" && xmlReader.isStartElement() && !modifiedAudit->isFetched()) {
            modifiedAudit->setFetched(true);
            AbstractAuditSP castedCreatedAudit = qSharedPointerCast<AbstractAudit>(modifiedAudit);
            AbstractAudit::fromJdf(xmlReader, castedCreatedAudit);
        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return modifiedAudit;
}

void ModifiedAudit::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement(QStringLiteral("Modified"));
    AbstractAudit::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

ModifiedAudit::ModifiedAudit()
    : AbstractAudit(*new ModifiedAuditPrivate)
{
}

void ModifiedAuditPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    AbstractAuditPrivate::updateFrom(other);
}
