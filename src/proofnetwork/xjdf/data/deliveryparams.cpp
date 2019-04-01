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
#include "proofnetwork/xjdf/data/deliveryparams.h"

#include "proofnetwork/xjdf/data/dropitem.h"
#include "proofnetwork/xjdf/data/resource_p.h"

namespace Proof {
namespace XJdf {

class DeliveryParamsPrivate : public ResourcePrivate
{
    Q_DECLARE_PUBLIC(DeliveryParams)
    DeliveryParamsPrivate() {}
    QDateTime required;
    QVector<DropItemSP> items;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QDateTime DeliveryParams::required() const
{
    Q_D_CONST(DeliveryParams);
    return d->required;
}

QVector<DropItemSP> DeliveryParams::items() const
{
    Q_D_CONST(DeliveryParams);
    return d->items;
}

void DeliveryParams::setRequired(const QDateTime &arg)
{
    Q_D(DeliveryParams);
    if (d->required != arg) {
        d->required = arg;
        emit requiredChanged(arg);
    }
}

void DeliveryParams::setItems(const QVector<DropItemSP> &arg)
{
    Q_D(DeliveryParams);
    bool emitNeeded = arg.count() != d->items.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->product() != d->items[i]->product() || arg[i]->amount() != d->items[i]->amount();
    if (emitNeeded) {
        d->items = arg;
        emit itemsChanged(arg);
    }
}

DeliveryParamsSP DeliveryParams::create()
{
    DeliveryParamsSP result(new DeliveryParams());
    initSelfWeakPtr(result);
    return result;
}

DeliveryParamsSP DeliveryParams::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    DeliveryParamsSP params;

    if (reader.isStartElement() && reader.name() == QStringLiteral("DeliveryParams")) {
        params = create();
        params->d_func()->document = document;
        params->setRequired(
            QDateTime::fromString(reader.attributes().value(QStringLiteral("Required")).toString(), Qt::ISODate));
        QVector<DropItemSP> items;
        while (!reader.atEnd() && !reader.hasError()) {
            if (reader.isStartElement() && reader.name() == QStringLiteral("DropItem")) {
                items << DropItem::fromXJdf(reader, document);
            } else if (reader.isEndElement() && reader.name() == QStringLiteral("DeliveryParams")) {
                break;
            }
            reader.readNext();
        }
        params->setItems(items);
        params->setFetched(true);
    }
    return params;
}

void DeliveryParams::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(DeliveryParams);
    AbstractNode::WriterGuard guard(writeFieldsToXJdf(writer));
    writer.writeStartElement(QStringLiteral("DeliveryParams"));
    if (d->required.isValid())
        writer.writeAttribute(QStringLiteral("Required"), d->required.toString(Qt::ISODate));
    for (const auto &item : d->items)
        item->toXJdf(writer);
    writer.writeEndElement();
}

DeliveryParams::DeliveryParams() : Resource(*new DeliveryParamsPrivate)
{}

void DeliveryParams::updateSelf(const NetworkDataEntitySP &other)
{
    DeliveryParamsSP castedOther = qSharedPointerCast<DeliveryParams>(other);
    setItems(castedOther->items());
    setRequired(castedOther->required());
    Resource::updateSelf(other);
}
