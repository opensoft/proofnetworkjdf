#include "proofnetwork/jdf/data/modifiedaudit.h"

#include "proofnetwork/jdf/data/abstractaudit_p.h"

namespace Proof {
namespace Jdf {

class ModifiedAuditPrivate : AbstractAuditPrivate
{
    Q_DECLARE_PUBLIC(ModifiedAudit)

    ModifiedAuditPrivate() : AbstractAuditPrivate() {}
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

ModifiedAuditQmlWrapper *ModifiedAudit::toQmlWrapper(QObject *parent) const
{
    ModifiedAuditSP castedSelf = castedSelfPtr<ModifiedAudit>();
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

ModifiedAudit::ModifiedAudit() : AbstractAudit(*new ModifiedAuditPrivate)
{}

void ModifiedAudit::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AbstractAudit::updateSelf(other);
}
