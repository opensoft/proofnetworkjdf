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
