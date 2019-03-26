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
#include "proofnetwork/xjdf/data/part.h"

#include "proofnetwork/xjdf/data/cutblock.h"
#include "proofnetwork/xjdf/data/product.h"
#include "proofnetwork/xjdf/data/xjdfabstractnode_p.h"

namespace Proof {
namespace XJdf {
class PartPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(Part)

public:
    PartPrivate() = default;

    ProductWP product;
    CutBlockWP block;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

ProductSP Part::product() const
{
    Q_D_CONST(Part);
    return d->product.toStrongRef();
}

CutBlockSP Part::block() const
{
    Q_D_CONST(Part);
    return d->block.toStrongRef();
}

void Part::setProduct(const ProductSP &arg)
{
    Q_D(Part);
    if (arg && arg != d->product.toStrongRef()) {
        d->product = arg.toWeakRef();
        emit productChanged(arg);
    }
}

void Part::setBlock(const CutBlockSP &arg)
{
    Q_D(Part);
    if (arg && arg != d->block.toStrongRef()) {
        d->block = arg.toWeakRef();
        emit blockChanged(arg);
    }
}

PartSP Part::create()
{
    PartSP result(new Part());
    initSelfWeakPtr(result);
    return result;
}

PartSP Part::fromXJdf(QXmlStreamReader &reader)
{
    PartSP part;
    if (reader.isStartElement() && reader.name() == QStringLiteral("Part")) {
        part = create();
        part->setFetched(true);
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("ProductPart")))
            part->setProduct(Product::create(attributes.value(QStringLiteral("ProductPart")).toString()));
        if (attributes.hasAttribute(QStringLiteral("BlockName")))
            part->setBlock(CutBlock::create(attributes.value(QStringLiteral("BlockName")).toString()));
    }
    reader.skipCurrentElement();
    return part;
}

void Part::toXJdf(QXmlStreamWriter &writer, bool writeEnd) const
{
    Q_D_CONST(Part);
    writer.writeStartElement(QStringLiteral("Part"));
    if (d->product.toStrongRef())
        writer.writeAttribute(QStringLiteral("ProductPart"), d->product.toStrongRef()->id());
    if (d->block.toStrongRef())
        writer.writeAttribute(QStringLiteral("BlockName"), d->block.toStrongRef()->blockName());
    writer.writeEndElement();
}

Part::Part() : XJdfAbstractNode(*new PartPrivate)
{}

void Part::updateSelf(const NetworkDataEntitySP &other)
{
    PartSP castedOther = qSharedPointerCast<Part>(other);
    setBlock(castedOther->block());
    setProduct(castedOther->product());
    XJdfAbstractNode::updateSelf(other);
}
