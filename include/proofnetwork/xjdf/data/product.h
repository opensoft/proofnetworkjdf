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
#ifndef XJDF_PRODUCT_H
#define XJDF_PRODUCT_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class ProductPrivate;
class PROOF_NETWORK_XJDF_EXPORT Product : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Product)
public:
    Product(const Product &) = delete;
    Product &operator=(const Product &) = delete;
    Product(Product &&) = delete;
    Product &operator=(Product &&) = delete;
    ~Product() = default;

    QString id() const;
    QString externalId() const;
    qulonglong amount() const;
    bool isRoot() const;
    ProductType type() const;

    QVector<IntentSP> intents() const;

    template <class T>
    QVector<QSharedPointer<T>> intentsByType()
    {
        const auto &all = intents();
        QVector<QSharedPointer<T>> result;
        for (const auto &intent : all) {
            auto converted = qSharedPointerDynamicCast<T>(intent);
            if (converted)
                result << converted;
        }

        return result;
    }

    void setId(const QString &arg);
    void setExternalId(const QString &arg);
    void setAmount(qulonglong arg);
    void setRoot(bool arg);
    void setType(ProductType arg);
    void setIntents(const QVector<IntentSP> &arg);

    static ProductSP create(const QString &id);

    static ProductSP fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document = XJdfDocumentSP());
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void idChanged(const QString &arg);
    void externalIdChanged(const QString &arg);
    void amountChanged(qulonglong arg);
    void isRootChanged(bool arg);
    void typeChanged(Proof::XJdf::ProductType arg);
    void intentsChanged(const QVector<Proof::XJdf::IntentSP> &arg);

protected:
    explicit Product(const QString &id);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_PRODUCT_H
