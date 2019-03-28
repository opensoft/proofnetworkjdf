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
#include "proofnetwork/xjdf/data/productlist.h"

#include "proofnetwork/xjdf/data/abstractnode_p.h"
#include "proofnetwork/xjdf/data/product.h"

namespace Proof {
namespace XJdf {

class ProductListPrivate : public AbstractNodePrivate
{
    Q_DECLARE_PUBLIC(ProductList)
    ProductListPrivate() { registerChildren(products); }

    QVector<ProductSP> products;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof::XJdf;

ProductList::ProductList() : AbstractNode(*new ProductListPrivate)
{}

QVector<ProductSP> ProductList::products() const
{
    Q_D_CONST(ProductList);
    return d->products;
}

ProductListSP ProductList::create()
{
    ProductListSP result(new ProductList());
    initSelfWeakPtr(result);
    return result;
}

ProductListSP ProductList::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    ProductListSP productList = create();
    productList->d_func()->document = document;

    QVector<ProductSP> list;

    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.name() == QStringLiteral("ProductList") && reader.isStartElement() && !productList->isFetched()) {
            productList->setFetched(true);
        } else if (reader.isStartElement()) {
            if (reader.name() == QStringLiteral("Product")) {
                ProductSP product = Product::fromXJdf(reader, document);
                if (!product) {
                    qCWarning(proofNetworkXJdfDataLog) << "ProductPool not created. Component is invalid.";
                    return ProductListSP();
                }
                list.append(product);
            }
        } else if (reader.isEndElement()) {
            break;
        }
        reader.readNext();
    }

    productList->setProducts(list);

    return productList;
}

void ProductList::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(ProductList);

    writer.writeStartElement(QStringLiteral("ProductList"));

    for (const ProductSP &product : qAsConst(d->products)) {
        if (isValidAndDirty(product))
            product->toXJdf(writer);
    }

    writer.writeEndElement();
}

void ProductList::setProducts(const QVector<ProductSP> &arg)
{
    Q_D(ProductList);
    bool emitNeeded = arg.count() != d->products.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->products[i]->id();
    if (emitNeeded) {
        d->products = arg;
        emit productsChanged(arg);
    }
}

void ProductList::addProduct(const ProductSP &arg)
{
    Q_D(ProductList);
    if (!arg)
        return;
    d->products << arg;
    emit productsChanged(d->products);
}

void ProductList::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    ProductListSP castedOther = qSharedPointerCast<ProductList>(other);
    setProducts(castedOther->products());

    AbstractNode::updateSelf(other);
}
