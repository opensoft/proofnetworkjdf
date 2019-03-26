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
