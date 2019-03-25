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
 * FITNESS FOR A ProductICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "proofnetwork/xjdf/data/product.h"

#include "proofnetwork/xjdf/data/intent.h"
#include "proofnetwork/xjdf/data/xjdfabstractnode_p.h"

namespace Proof {
namespace XJdf {
class ProductPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(Product)

public:
    ProductPrivate() = default;

    QString id;
    QString externalId;
    qulonglong amount = 0;
    bool isRoot = false;
    ProductType type = ProductType::NoProductType;
    QVector<IntentSP> intents;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QString Product::id() const
{
    Q_D_CONST(Product);
    return d->id;
}

QString Product::externalId() const
{
    Q_D_CONST(Product);
    return d->externalId;
}

qulonglong Product::amount() const
{
    Q_D_CONST(Product);
    return d->amount;
}

bool Product::isRoot() const
{
    Q_D_CONST(Product);
    return d->isRoot;
}

ProductType Product::type() const
{
    Q_D_CONST(Product);
    return d->type;
}

QVector<IntentSP> Product::intents() const
{
    Q_D_CONST(Product);
    return d->intents;
}

void Product::setId(const QString &arg)
{
    Q_D(Product);
    if (arg != d->id) {
        d->id = arg;
        emit idChanged(arg);
    }
}

void Product::setExternalId(const QString &arg)
{
    Q_D(Product);
    if (arg != d->externalId) {
        d->externalId = arg;
        emit externalIdChanged(arg);
    }
}

void Product::setAmount(qulonglong arg)
{
    Q_D(Product);
    if (arg != d->amount) {
        d->amount = arg;
        emit amountChanged(arg);
    }
}

void Product::setRoot(bool arg)
{
    Q_D(Product);
    if (arg != d->isRoot) {
        d->isRoot = arg;
        emit isRootChanged(arg);
    }
}

void Product::setType(ProductType arg)
{
    Q_D(Product);
    if (arg != d->type) {
        d->type = arg;
        emit typeChanged(arg);
    }
}

void Product::setIntents(const QVector<IntentSP> &arg)
{
    Q_D(Product);
    //TODO: Make it right
    d->intents = arg;
    emit intentsChanged(arg);
}

ProductSP Product::create(const QString &id)
{
    ProductSP result(new Product(id));
    initSelfWeakPtr(result);
    return result;
}

ProductSP Product::fromXJdf(QXmlStreamReader &xjdfReader)
{
    ProductSP product;
    if (xjdfReader.isStartElement() && xjdfReader.name() == "Product") {
        auto attributes = xjdfReader.attributes();
        auto id = attributes.value("ID").toString();
        product = create(id);

        if (attributes.hasAttribute("ExternalID"))
            product->setExternalId(attributes.value("ExternalID").toString());
        if (attributes.hasAttribute("Amount"))
            product->setAmount(attributes.value("Amount").toULongLong());
        if (attributes.hasAttribute("IsRoot"))
            product->setRoot(!attributes.value("IsRoot").toString().compare("true", Qt::CaseInsensitive));
        if (attributes.hasAttribute("ProductType"))
            product->setType(productTypeFromString(attributes.value("ProductType").toString()));

        QVector<IntentSP> intents;
        while (!xjdfReader.atEnd() && !xjdfReader.hasError()) {
            if (xjdfReader.isStartElement() && xjdfReader.name() == "Intent") {
                auto intent = Intent::fromXJdf(xjdfReader);
                if (!intent)
                    return ProductSP();
                intents << intent;
            } else if (xjdfReader.isEndElement() && xjdfReader.name() == "Product") {
                break;
            }
            xjdfReader.readNext();
        }

        product->setFetched(true);
        product->setIntents(intents);
    }
    return product;
}

void Product::toXJdf(QXmlStreamWriter &xjdfWriter, bool) const
{
    Q_D_CONST(Product);
    xjdfWriter.writeStartElement(QStringLiteral("Product"));
    xjdfWriter.writeAttribute("ID", d->id);
    if (!d->externalId.isEmpty())
        xjdfWriter.writeAttribute("ExternalID", d->externalId);
    if (d->amount)
        xjdfWriter.writeAttribute("Amount", QString::number(d->amount));
    if (d->isRoot)
        xjdfWriter.writeAttribute("IsRoot", "true");
    if (d->type != ProductType::NoProductType)
        xjdfWriter.writeAttribute("ProductType", productTypeToString(d->type));

    for (const auto &intent : d->intents)
        intent->toXJdf(xjdfWriter);
    xjdfWriter.writeEndElement();
}

Product::Product(const QString &id) : XJdfAbstractNode(*new ProductPrivate)
{
    setId(id);
}

void Product::updateSelf(const NetworkDataEntitySP &other)
{
    ProductSP castedOther = qSharedPointerCast<Product>(other);
    setId(castedOther->id());
    setExternalId(castedOther->externalId());
    setAmount(castedOther->amount());
    setRoot(castedOther->isRoot());
    setType(castedOther->type());

    XJdfAbstractNode::updateSelf(other);
}
