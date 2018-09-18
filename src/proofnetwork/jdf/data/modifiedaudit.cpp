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
