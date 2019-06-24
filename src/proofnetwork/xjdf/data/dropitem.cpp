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
#include "proofnetwork/xjdf/data/dropitem.h"

#include "proofnetwork/xjdf/data/abstractnode_p.h"
#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/data/product.h"
#include "proofnetwork/xjdf/data/productlist.h"

namespace Proof {
namespace XJdf {
class DropItemPrivate : public AbstractNodePrivate
{
    Q_DECLARE_PUBLIC(DropItem)

public:
    DropItemPrivate() = default;

    mutable ProductSP lazyProduct;
    QString productId;
    qulonglong amount = 0;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

qulonglong DropItem::amount() const
{
    Q_D_CONST(DropItem);
    return d->amount;
}

ProductSP DropItem::product() const
{
    Q_D_CONST(DropItem);
    if (d->lazyProduct)
        return d->lazyProduct;
    auto document = d->document.toStrongRef();
    if (document && document->productList()) {
        d->lazyProduct = algorithms::findIf(document->productList()->products(),
                                            [d](const auto &product) { return product->id() == d->productId; },
                                            ProductSP());
        if (d->lazyProduct)
            return d->lazyProduct;
    }
    auto dummy = Product::create(document, d->productId);
    return dummy;
}

void Proof::XJdf::DropItem::setAmount(qulonglong arg)
{
    Q_D(DropItem);
    if (arg && arg != d->amount) {
        d->amount = arg;
        emit amountChanged(arg);
    }
}

void DropItem::updateProduct(const QString &arg)
{
    Q_D(DropItem);
    if (arg != d->productId) {
        d->lazyProduct.reset();
        d->productId = arg;
        emit productChanged(product());
    }
}

DropItemSP DropItem::create(const DocumentSP &document)
{
    DropItemSP result(new DropItem());
    result->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

DropItemSP DropItem::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    DropItemSP item;

    if (reader.isStartElement() && reader.name() == QStringLiteral("DropItem")) {
        item = create(document);
        item->setFetched(true);
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("ItemRef")))
            item->updateProduct(attributes.value(QStringLiteral("ItemRef")).toString());
        if (attributes.hasAttribute(QStringLiteral("Amount")))
            item->setAmount(attributes.value(QStringLiteral("Amount")).toULongLong());
    }
    reader.skipCurrentElement();
    return item;
}

void DropItem::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(DropItem);
    writer.writeStartElement(QStringLiteral("DropItem"));
    auto product = this->product();
    if (product)
        writer.writeAttribute(QStringLiteral("ItemRef"), product->id());
    if (d->amount != 0)
        writer.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount));
    writer.writeEndElement();
}

DropItem::DropItem() : AbstractNode(*new DropItemPrivate)
{}

void DropItem::updateSelf(const NetworkDataEntitySP &other)
{
    DropItemSP castedOther = qSharedPointerCast<DropItem>(other);
    updateProduct(castedOther->d_func()->productId);
    setAmount(castedOther->amount());
    AbstractNode::updateSelf(other);
}
