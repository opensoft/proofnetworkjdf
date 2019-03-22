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
#include "proofnetwork/xjdf/data/foldingintent.h"

#include "proofnetwork/xjdf/data/intent_p.h"

namespace Proof {
namespace XJdf {
class FoldingIntentPrivate : public IntentPrivate
{
    Q_DECLARE_PUBLIC(FoldingIntent)

public:
    FoldingIntentPrivate() = default;

    FoldType foldingCatalog = FoldType::NoFoldType;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

FoldType FoldingIntent::foldCatalog() const
{
    Q_D_CONST(FoldingIntent);
    return d->foldingCatalog;
}

void FoldingIntent::setFoldCatalog(FoldType arg)
{
    Q_D(FoldingIntent);
    if (arg != d->foldingCatalog) {
        d->foldingCatalog = arg;
        emit foldCatalogChanged(arg);
    }
}

FoldingIntentSP FoldingIntent::create()
{
    FoldingIntentSP result(new FoldingIntent());
    initSelfWeakPtr(result);
    return result;
}

FoldingIntentSP FoldingIntent::fromXJdf(QXmlStreamReader &xjdfReader)
{
    FoldingIntentSP intent;
    if (xjdfReader.isStartElement() && xjdfReader.name() == "FoldingIntent") {
        intent = create();
        auto catalog = foldTypeFromString(xjdfReader.attributes().value("FoldCatalog").toString());
        intent->setFoldCatalog(catalog);
        intent->setFetched(true);
        xjdfReader.skipCurrentElement();
    }
    return intent;
}

void FoldingIntent::toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd) const
{
    Q_D_CONST(FoldingIntent);
    Intent::toXJdf(xjdfWriter);
    xjdfWriter.writeStartElement(QStringLiteral("FoldingIntent"));
    xjdfWriter.writeAttribute("FoldCatalog", foldTypeToString(d->foldingCatalog));
    xjdfWriter.writeEndElement();
    xjdfWriter.writeEndElement();
}

FoldingIntent::FoldingIntent() : Intent(*new FoldingIntentPrivate)
{
    Intent::addResourceCreator(QStringLiteral("FoldingIntent"), [](QXmlStreamReader &xjdfReader) -> IntentSP {
        return qSharedPointerCast<Intent>(fromXJdf(xjdfReader));
    });
}

void FoldingIntent::updateSelf(const NetworkDataEntitySP &other)
{
    FoldingIntentSP castedOther = qSharedPointerCast<FoldingIntent>(other);
    setFoldCatalog(castedOther->foldCatalog());
    Intent::updateSelf(other);
}
