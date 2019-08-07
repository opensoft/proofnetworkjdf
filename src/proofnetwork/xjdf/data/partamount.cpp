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
#include "proofnetwork/xjdf/data/partamount.h"

#include "proofnetwork/xjdf/data/abstractnode_p.h"
#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/data/part.h"
#include "proofnetwork/xjdf/data/partwaste.h"

namespace Proof {
namespace XJdf {
class PartAmountPrivate : public AbstractNodePrivate
{
    Q_DECLARE_PUBLIC(PartAmount)

public:
    PartAmountPrivate() { registerChildren(parts, partsWaste); }

    qulonglong amount = 0;
    QVector<PartSP> parts;
    QVector<PartWasteSP> partsWaste;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

qulonglong PartAmount::amount() const
{
    Q_D_CONST(PartAmount);
    return d->amount;
}

QVector<PartSP> PartAmount::parts() const
{
    Q_D_CONST(PartAmount);
    return d->parts;
}

QVector<PartWasteSP> PartAmount::partsWaste() const
{
    Q_D_CONST(PartAmount);
    return d->partsWaste;
}

void PartAmount::setAmount(qulonglong arg)
{
    Q_D(PartAmount);
    if (arg != d->amount) {
        d->amount = arg;
        emit amountChanged(d->amount);
    }
}

void PartAmount::setParts(const QVector<PartSP> &arg)
{
    Q_D(PartAmount);
    bool emitNeeded = arg.count() != d->parts.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->blockName() != d->parts[i]->blockName()
                     || arg[i]->productPart() != d->parts[i]->productPart();
    if (emitNeeded) {
        d->parts = algorithms::map(arg, [&d](const auto &part) {
            auto newPart = d->document.toStrongRef()->createNode<Part>();
            newPart->updateFrom(part);
            return newPart;
        });
        emit partsChanged(d->parts);
    }
}

void PartAmount::setPartsWaste(const QVector<PartWasteSP> &arg)
{
    Q_D(PartAmount);
    bool emitNeeded = arg.count() != d->partsWaste.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->waste() != d->partsWaste[i]->waste()
                     || arg[i]->wasteDetails() != d->partsWaste[i]->wasteDetails();
    if (emitNeeded) {
        d->partsWaste = algorithms::map(arg, [&d](const auto &part) {
            auto newPartWaste = d->document.toStrongRef()->createNode<PartWaste>();
            newPartWaste->updateFrom(part);
            return newPartWaste;
        });
        emit partsWasteChanged(d->partsWaste);
    }
}

PartAmountSP PartAmount::create(const DocumentSP &document)
{
    PartAmountSP result(new PartAmount());
    const auto *constEntity = result.data();
    constEntity->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

PartAmountSP PartAmount::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    PartAmountSP partAmount;
    QVector<PartSP> parts;
    QVector<PartWasteSP> partsWaste;

    if (reader.isStartElement() && reader.name() == QStringLiteral("PartAmount")) {
        partAmount = create(document);
        partAmount->setFetched(true);
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("Amount")))
            partAmount->setAmount(attributes.value(QStringLiteral("Amount")).toULongLong());

        while (!reader.atEnd() && !reader.hasError()) {
            if (reader.isStartElement() && reader.name() == QStringLiteral("Part")) {
                auto part = Part::fromXJdf(reader, document);
                if (part)
                    parts << part;
            } else if (reader.isStartElement() && reader.name() == QStringLiteral("PartWaste")) {
                auto partWaste = PartWaste::fromXJdf(reader, document);
                if (partWaste)
                    partsWaste << partWaste;
            } else if (reader.isEndElement() && reader.name() == QStringLiteral("PartAmount")) {
                break;
            }
            reader.readNext();
        }
    }

    if (partAmount) {
        partAmount->setParts(parts);
        partAmount->setPartsWaste(partsWaste);
    }

    return partAmount;
}

void PartAmount::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(PartAmount);
    writer.writeStartElement(QStringLiteral("PartAmount"));
    if (d->amount > 0)
        writer.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount));
    for (const auto &part : d->parts)
        part->toXJdf(writer);
    for (const auto &partWaste : d->partsWaste)
        partWaste->toXJdf(writer);
    writer.writeEndElement();
}

PartAmount::PartAmount() : AbstractNode(*new PartAmountPrivate)
{}

void PartAmount::updateSelf(const NetworkDataEntitySP &other)
{
    PartAmountSP castedOther = qSharedPointerCast<PartAmount>(other);
    setAmount(castedOther->amount());
    setParts(castedOther->parts());
    setPartsWaste(castedOther->partsWaste());
    AbstractNode::updateSelf(other);
}
