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
#include "proofnetwork/jdf/data/bundle.h"

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
