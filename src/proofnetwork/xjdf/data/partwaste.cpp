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
#include "proofnetwork/xjdf/data/partwaste.h"

#include "proofnetwork/xjdf/data/abstractnode_p.h"
#include "proofnetwork/xjdf/data/cutblock.h"
#include "proofnetwork/xjdf/data/cuttingparams.h"
#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/data/product.h"
#include "proofnetwork/xjdf/data/productlist.h"
#include "proofnetwork/xjdf/data/resourceset.h"

namespace Proof {
namespace XJdf {
class PartWastePrivate : public AbstractNodePrivate
{
    Q_DECLARE_PUBLIC(PartWaste)

public:
    PartWastePrivate() = default;

    qulonglong waste = 0;
    WasteDetails wasteDetails = WasteDetails::NoWasteDetails;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

qulonglong PartWaste::waste() const
{
    Q_D_CONST(PartWaste);
    return d->waste;
}

WasteDetails PartWaste::wasteDetails() const
{
    Q_D_CONST(PartWaste);
    return d->wasteDetails;
}

void PartWaste::setWaste(qulonglong arg)
{
    Q_D(PartWaste);
    if (arg != d->waste) {
        d->waste = arg;
        emit wasteChanged(arg);
    }
}

void PartWaste::setWasteDetails(WasteDetails arg)
{
    Q_D(PartWaste);
    if (arg != d->wasteDetails) {
        d->wasteDetails = arg;
        emit wasteDetailsChanged(arg);
    }
}

PartWasteSP PartWaste::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    PartWasteSP part;

    if (reader.isStartElement() && reader.name() == QStringLiteral("PartWaste")) {
        part = create(document);
        part->setFetched(true);
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("Waste")))
            part->setWaste(attributes.value(QStringLiteral("Waste")).toULongLong());
        if (attributes.hasAttribute(QStringLiteral("WasteDetails")))
            part->setWasteDetails(wasteDetailsFromString(attributes.value(QStringLiteral("WasteDetails")).toString()));
    }
    reader.skipCurrentElement();
    return part;
}

void PartWaste::toXJdf(QXmlStreamWriter &writer) const
{
    writer.writeStartElement(QStringLiteral("PartWaste"));
    if (waste() > 0)
        writer.writeAttribute(QStringLiteral("Waste"), QString::number(waste()));
    if (wasteDetails() != WasteDetails::NoWasteDetails)
        writer.writeAttribute(QStringLiteral("WasteDetails"), wasteDetailsToString(wasteDetails()));
    writer.writeEndElement();
}

PartWaste::PartWaste() : AbstractNode(*new PartWastePrivate)
{}

PartWasteSP PartWaste::create(const DocumentSP &document)
{
    PartWasteSP result(new PartWaste());
    const auto *constEntity = result.data();
    constEntity->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

void PartWaste::updateSelf(const NetworkDataEntitySP &other)
{
    PartWasteSP castedOther = qSharedPointerCast<PartWaste>(other);
    setWaste(castedOther->waste());
    setWasteDetails(castedOther->wasteDetails());
    AbstractNode::updateSelf(other);
}
