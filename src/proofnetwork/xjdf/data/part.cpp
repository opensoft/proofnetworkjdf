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
#include "proofnetwork/xjdf/data/part.h"

#include "proofnetwork/xjdf/data/abstractnode_p.h"
#include "proofnetwork/xjdf/data/cutblock.h"
#include "proofnetwork/xjdf/data/cuttingparams.h"
#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/data/product.h"
#include "proofnetwork/xjdf/data/productlist.h"
#include "proofnetwork/xjdf/data/resourceset.h"

namespace Proof {
namespace XJdf {
class PartPrivate : public AbstractNodePrivate
{
    Q_DECLARE_PUBLIC(Part)

public:
    PartPrivate() = default;

    QString productPart;
    QString blockName;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QString Part::productPart() const
{
    Q_D_CONST(Part);
    return d->productPart;
}

QString Part::blockName() const
{
    Q_D_CONST(Part);
    return d->blockName;
}

void Part::setProductPart(const QString &arg)
{
    Q_D(Part);
    if (arg != d->productPart) {
        d->productPart = arg;
        emit productPartChanged(d->productPart);
    }
}

void Part::setBlockName(const QString &arg)
{
    Q_D(Part);
    if (arg != d->blockName) {
        d->blockName = arg;
        emit blockNameChanged(d->blockName);
    }
}

PartSP Part::create(const DocumentSP &document)
{
    PartSP result(new Part());
    result->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

PartSP Part::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    PartSP part;

    if (reader.isStartElement() && reader.name() == QStringLiteral("Part")) {
        part = create(document);
        part->setFetched(true);
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("ProductPart")))
            part->setProductPart(attributes.value(QStringLiteral("ProductPart")).toString());
        if (attributes.hasAttribute(QStringLiteral("BlockName")))
            part->setBlockName(attributes.value(QStringLiteral("BlockName")).toString());
    }
    reader.skipCurrentElement();
    return part;
}

void Part::toXJdf(QXmlStreamWriter &writer) const
{
    writer.writeStartElement(QStringLiteral("Part"));
    if (!productPart().isEmpty())
        writer.writeAttribute(QStringLiteral("ProductPart"), productPart());
    if (!blockName().isEmpty())
        writer.writeAttribute(QStringLiteral("BlockName"), blockName());
    writer.writeEndElement();
}

Part::Part() : AbstractNode(*new PartPrivate)
{}

void Part::updateSelf(const NetworkDataEntitySP &other)
{
    PartSP castedOther = qSharedPointerCast<Part>(other);
    setBlockName(castedOther->blockName());
    setProductPart(castedOther->productPart());
    AbstractNode::updateSelf(other);
}
