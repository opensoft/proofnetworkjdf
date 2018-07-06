#include "bundle.h"

#include "proofnetwork/jdf/data/bundleitem.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class BundlePrivate : NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(Bundle)

    BundlePrivate() : NetworkDataEntityPrivate() { registerChildren(bundleItems); }

    BundleType bundleType = BundleType::BoxBundle;
    int totalAmount = 0;
    QVector<BundleItemSP> bundleItems;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

BundleType Bundle::bundleType() const
{
    Q_D_CONST(Bundle);
    return d->bundleType;
}

int Bundle::totalAmount() const
{
    Q_D_CONST(Bundle);
    return d->totalAmount;
}

QVector<BundleItemSP> Bundle::bundleItems() const
{
    Q_D_CONST(Bundle);
    return d->bundleItems;
}

void Bundle::setBundleType(BundleType arg)
{
    Q_D(Bundle);
    if (d->bundleType != arg) {
        d->bundleType = arg;
        emit bundleTypeChanged(arg);
    }
}

void Bundle::setTotalAmount(int arg)
{
    Q_D(Bundle);
    if (d->totalAmount != arg) {
        d->totalAmount = arg;
        emit totalAmountChanged(arg);
    }
}

void Bundle::setBundleItems(const QVector<BundleItemSP> &arg)
{
    Q_D(Bundle);
    d->bundleItems = arg;
    emit bundleItemsChanged();
}

void Bundle::addBundleItem(const BundleItemSP &arg)
{
    Q_D(Bundle);
    if (!arg)
        return;
    d->bundleItems.append(arg);
    emit bundleItemsChanged();
}

BundleQmlWrapper *Bundle::toQmlWrapper(QObject *parent) const
{
    BundleSP castedSelf = castedSelfPtr<Bundle>();
    Q_ASSERT(castedSelf);
    return new BundleQmlWrapper(castedSelf, parent);
}

BundleSP Bundle::create()
{
    BundleSP result(new Bundle());
    initSelfWeakPtr(result);
    return result;
}

BundleSP Bundle::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    BundleSP bundle = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Bundle" && xmlReader.isStartElement() && !bundle->isFetched()) {
            bundle->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            bundle->setBundleType(bundleTypeFromString(attributes.value(QStringLiteral("BundleType")).toString()));
            bundle->setTotalAmount(attributes.value(QStringLiteral("TotalAmount")).toInt());
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "BundleItem") {
                BundleItemSP bundleItem = BundleItem::fromJdf(xmlReader, jobId, sanitize);
                bundle->addBundleItem(bundleItem);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return bundle;
}

void Bundle::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Bundle);
    jdfWriter.writeStartElement(QStringLiteral("Bundle"));
    jdfWriter.writeAttribute(QStringLiteral("BundleType"), bundleTypeToString(d->bundleType));
    jdfWriter.writeAttribute(QStringLiteral("TotalAmount"), QString::number(d->totalAmount));

    for (const auto &bundleItem : qAsConst(d->bundleItems)) {
        if (isValidAndDirty(bundleItem))
            bundleItem->toJdf(jdfWriter);
    }

    jdfWriter.writeEndElement();
}

Bundle::Bundle() : NetworkDataEntity(*new BundlePrivate)
{}

void Bundle::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    BundleSP castedOther = qSharedPointerCast<Bundle>(other);
    setBundleType(castedOther->bundleType());
    setTotalAmount(castedOther->totalAmount());
    setBundleItems(castedOther->bundleItems());

    NetworkDataEntity::updateSelf(other);
}
