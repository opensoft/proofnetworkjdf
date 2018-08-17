#include "proofnetwork/jdf/data/bundleitem.h"

#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class BundleItemPrivate : NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(BundleItem)

    BundleItemPrivate() : NetworkDataEntityPrivate() { registerChildren(component); }

    int amount = 1;
    ComponentSP component = Component::create();
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

int BundleItem::amount() const
{
    Q_D_CONST(BundleItem);
    return d->amount;
}

ComponentSP BundleItem::component() const
{
    Q_D_CONST(BundleItem);
    return d->component;
}

void BundleItem::setAmount(int arg)
{
    Q_D(BundleItem);
    if (d->amount != arg) {
        d->amount = arg;
        emit amountChanged(arg);
    }
}

void BundleItem::setComponent(const ComponentSP &arg)
{
    Q_D(BundleItem);
    if (d->component != arg) {
        d->component = arg;
        emit componentChanged(arg);
    }
}

BundleItemQmlWrapper *BundleItem::toQmlWrapper(QObject *parent) const
{
    BundleItemSP castedSelf = castedSelfPtr<BundleItem>();
    Q_ASSERT(castedSelf);
    return new BundleItemQmlWrapper(castedSelf, parent);
}

BundleItemSP BundleItem::create()
{
    BundleItemSP result(new BundleItem());
    initSelfWeakPtr(result);
    return result;
}

BundleItemSP BundleItem::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    BundleItemSP bundleItem = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "BundleItem" && xmlReader.isStartElement() && !bundleItem->isFetched()) {
            bundleItem->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            bundleItem->setAmount(attributes.value(QStringLiteral("Amount")).toInt());
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "ComponentRef") {
                ComponentSP component = Component::fromJdf(xmlReader, jobId, sanitize);
                bundleItem->setComponent(component);
            }
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
    jdfWriter.writeStartElement(QStringLiteral("BundleItem"));
    jdfWriter.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount));
    if (isValidAndDirty(d->component))
        d->component->refToJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

BundleItem::BundleItem() : NetworkDataEntity(*new BundleItemPrivate)
{}

void BundleItem::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    BundleItemSP castedOther = qSharedPointerCast<BundleItem>(other);
    setAmount(castedOther->amount());
    setComponent(castedOther->component());

    NetworkDataEntity::updateSelf(other);
}
