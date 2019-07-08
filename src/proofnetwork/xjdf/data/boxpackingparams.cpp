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
#include "proofnetwork/xjdf/data/boxpackingparams.h"

#include "proofnetwork/xjdf/data/resource_p.h"

namespace Proof {
namespace XJdf {

class BoxPackingParamsPrivate : public ResourcePrivate
{
    Q_DECLARE_PUBLIC(BoxPackingParams)
    BoxPackingParamsPrivate() {}

    BoxType boxType = BoxType::NoBoxType;
    QString boxTypeDetails;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

ResourceSP BoxPackingParams::cloneTo(const DocumentSP &document)
{
    auto newParams = create(document);
    newParams->updateFrom(qSharedPointerCast<BoxPackingParams>(selfPtr()));
    return qSharedPointerCast<Resource>(newParams);
}

BoxType BoxPackingParams::boxType() const
{
    Q_D_CONST(BoxPackingParams);
    return d->boxType;
}

QString BoxPackingParams::boxTypeDetails() const
{
    Q_D_CONST(BoxPackingParams);
    return d->boxTypeDetails;
}

void BoxPackingParams::setBoxType(BoxType arg)
{
    Q_D(BoxPackingParams);
    if (arg != d->boxType) {
        d->boxType = arg;
        emit boxTypeChanged(d->boxType);
    }
}

void BoxPackingParams::setBoxTypeDetails(const QString &arg)
{
    Q_D(BoxPackingParams);
    if (arg != d->boxTypeDetails) {
        d->boxTypeDetails = arg;
        emit boxTypeDetailsChanged(d->boxTypeDetails);
    }
}

BoxPackingParamsSP BoxPackingParams::create(const DocumentSP &document)
{
    BoxPackingParamsSP result(new BoxPackingParams());
    const auto *constEntity = result.data();
    constEntity->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

BoxPackingParamsSP BoxPackingParams::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    BoxPackingParamsSP params;
    if (reader.isStartElement() && reader.name() == QStringLiteral("BoxPackingParams")) {
        params = create(document);

        auto boxType = boxTypeFromString(reader.attributes().value(QStringLiteral("BoxType")).toString());
        auto boxTypeDetails = reader.attributes().value(QStringLiteral("BoxTypeDetails")).toString();
        params->setBoxType(boxType);
        params->setBoxTypeDetails(boxTypeDetails);
        params->setFetched(true);
        reader.readNext();
    }
    return params;
}

void BoxPackingParams::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(BoxPackingParams);
    NodeWriterGuard guard(writeFieldsToXJdf(writer));

    writer.writeStartElement(QStringLiteral("BoxPackingParams"));
    if (!d->boxTypeDetails.isEmpty())
        writer.writeAttribute(QStringLiteral("BoxTypeDetails"), d->boxTypeDetails);

    writer.writeAttribute(QStringLiteral("BoxType"), boxTypeToString(d->boxType));
    writer.writeEndElement();
}

BoxPackingParams::BoxPackingParams() : Resource(*new BoxPackingParamsPrivate)
{}

void BoxPackingParams::updateSelf(const NetworkDataEntitySP &other)
{
    BoxPackingParamsSP castedOther = qSharedPointerCast<BoxPackingParams>(other);
    setBoxType(castedOther->boxType());
    setBoxTypeDetails(castedOther->boxTypeDetails());

    Resource::updateSelf(other);
}
