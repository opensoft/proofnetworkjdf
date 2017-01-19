#include "bundleitem.h"

#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class BundleItemPrivate : NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(BundleItem)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;
    int amount = 1;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

int BundleItem::amount() const
{
    Q_D(const BundleItem);
    return d->amount;
}

void BundleItem::setAmount(int arg)
{
    Q_D(BundleItem);
    if (d->amount != arg) {
        d->amount = arg;
        emit amountChanged(arg);
    }
}

BundleItemQmlWrapper *BundleItem::toQmlWrapper(QObject *parent) const
{
    Q_D(const BundleItem);
    BundleItemSP castedSelf = qSharedPointerCast<BundleItem>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new BundleItemQmlWrapper(castedSelf, parent);
}

BundleItemSP BundleItem::create()
{
    BundleItemSP result(new BundleItem());
    initSelfWeakPtr(result);
    return result;
}

BundleItemSP BundleItem::fromJdf(QXmlStreamReader &xmlReader)
{
    BundleItemSP bundleItem = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "BundleItem" && xmlReader.isStartElement() && ! bundleItem->isFetched()) {
            bundleItem->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            bundleItem->setAmount(attributes.value("Amount").toInt());
        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return bundleItem;
}

void BundleItem::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(BundleItem);
    jdfWriter.writeStartElement("BundleItem");
    jdfWriter.writeAttribute("Amount", QString::number(d->amount));
    jdfWriter.writeEndElement();
}

BundleItem::BundleItem()
    : NetworkDataEntity(*new BundleItemPrivate)
{
}

void BundleItemPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(BundleItem);
    BundleItemSP castedOther = qSharedPointerCast<BundleItem>(other);
    q->setAmount(castedOther->amount());

    NetworkDataEntityPrivate::updateFrom(other);
}

