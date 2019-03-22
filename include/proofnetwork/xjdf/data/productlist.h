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
#ifndef PROOF_XJDF_PRODUCTLIST_H
#define PROOF_XJDF_PRODUCTLIST_H

#include "proofnetwork/xjdf/data/xjdfabstractnode.h"

#include <QXmlStreamReader>

namespace Proof {
namespace XJdf {

class ProductListPrivate;
class PROOF_NETWORK_XJDF_EXPORT ProductList : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ProductList)
public:
    ProductList(const ProductList &) = delete;
    ProductList &operator=(const ProductList &) = delete;
    ProductList(ProductList &&) = delete;
    ProductList &operator=(ProductList &&) = delete;
    ~ProductList() = default;

    QVector<ProductSP> products() const;

    void setProducts(const QVector<ProductSP> &products);
    void addProduct(const ProductSP &arg);

    static ProductListSP create();

    static ProductListSP fromXJdf(QXmlStreamReader &xjdfReader);
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;

signals:
    void productsChanged(const QVector<Proof::XJdf::ProductSP> &arg);

protected:
    explicit ProductList();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // PROOF_XJDF_PRODUCTLIST_H
