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
#include "proofnetwork/xjdf/data/laminatingintent.h"

#include "proofnetwork/xjdf/data/intent_p.h"

namespace Proof {
namespace XJdf {
class LaminatingIntentPrivate : public IntentPrivate
{
    Q_DECLARE_PUBLIC(LaminatingIntent)

public:
    LaminatingIntentPrivate() = default;

    Side surface = Side::Front;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

Side LaminatingIntent::surface() const
{
    Q_D_CONST(LaminatingIntent);
    return d->surface;
}

void LaminatingIntent::setSurface(Side surface)
{
    Q_D(LaminatingIntent);
    if (d->surface != surface) {
        d->surface = surface;
        emit surfaceChanged(surface);
    }
}

LaminatingIntentSP LaminatingIntent::create(const DocumentSP &document)
{
    LaminatingIntentSP result(new LaminatingIntent());
    result->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

LaminatingIntentSP LaminatingIntent::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    LaminatingIntentSP intent;

    if (reader.isStartElement() && reader.name() == QStringLiteral("LaminatingIntent")) {
        intent = create(document);
        auto side = sideTypeFromString(reader.attributes().value(QStringLiteral("Surface")).toString());
        intent->setSurface(side);
        intent->setFetched(true);
        reader.skipCurrentElement();
    }
    return intent;
}

void LaminatingIntent::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(LaminatingIntent);
    NodeWriterGuard guard(Intent::writeFieldsToXJdf(writer));

    writer.writeStartElement(QStringLiteral("LaminatingIntent"));
    writer.writeAttribute(QStringLiteral("Surface"), sideTypeToString(d->surface));
    writer.writeEndElement();
}

LaminatingIntent::LaminatingIntent() : Intent(*new LaminatingIntentPrivate)
{}

void LaminatingIntent::updateSelf(const NetworkDataEntitySP &other)
{
    LaminatingIntentSP castedOther = qSharedPointerCast<LaminatingIntent>(other);
    setSurface(castedOther->surface());
    Intent::updateSelf(other);
}
