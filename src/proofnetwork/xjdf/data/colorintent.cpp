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
#include "proofnetwork/xjdf/data/colorintent.h"

#include "proofnetwork/xjdf/data/intent_p.h"

namespace Proof {
namespace XJdf {
class ColorIntentPrivate : public IntentPrivate
{
    Q_DECLARE_PUBLIC(ColorIntent)

public:
    ColorIntentPrivate() = default;
    QMap<Side, QVector<CoatingType>> coatings;
    QMap<Side, bool> spots;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QMap<Side, QVector<CoatingType>> ColorIntent::coatings() const
{
    Q_D_CONST(ColorIntent);
    return d->coatings;
}

QMap<Side, bool> ColorIntent::spots() const
{
    Q_D_CONST(ColorIntent);
    return d->spots;
}

void ColorIntent::setCoatings(const QMap<Side, QVector<CoatingType>> &arg)
{
    Q_D(ColorIntent);
    //TODO: make it right way, if needed
    d->coatings = arg;
    emit coatingsChanged(d->coatings);
}

void ColorIntent::addCoating(Side side, CoatingType arg)
{
    Q_D(ColorIntent);
    d->coatings[side] << arg;
    emit coatingsChanged(d->coatings);
}

void ColorIntent::setSpots(const QMap<Side, bool> &arg)
{
    Q_D(ColorIntent);
    //TODO: make it right way, if needed
    d->spots = arg;
    emit spotsChanged(d->spots);
}

void ColorIntent::addSpot(Side side, bool arg)
{
    Q_D(ColorIntent);
    d->spots[side] = arg;
    emit spotsChanged(d->spots);
}

ColorIntentSP ColorIntent::create()
{
    ColorIntentSP result(new ColorIntent());
    initSelfWeakPtr(result);
    return result;
}

ColorIntentSP ColorIntent::fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document)
{
    ColorIntentSP intent;
    if (reader.isStartElement() && reader.name() == QStringLiteral("ColorIntent")) {
        intent = create();
        intent->d_func()->document = document;

        QMap<Side, QVector<CoatingType>> coatings;
        QMap<Side, bool> spots;
        while (!reader.atEnd() && !reader.hasError()) {
            if (reader.isStartElement() && reader.name() == QStringLiteral("SurfaceColor")) {
                auto attributes = reader.attributes();
                auto side = sideTypeFromString(attributes.value(QStringLiteral("Surface")).toString());
                auto coatingsVector = algorithms::map(attributes.value(QStringLiteral("Coatings")).toString().split(' '),
                                                      [](const QString &coating) {
                                                          return coatingTypeFromString(coating);
                                                      },
                                                      QVector<CoatingType>());
                auto spot = !attributes.value(QStringLiteral("ColorsUsed")).toString().isEmpty();

                coatings[side] = coatingsVector;
                spots[side] = spot;
            } else if (reader.isEndElement() && reader.name() == QStringLiteral("ColorIntent")) {
                break;
            }
            reader.readNext();
        }
        intent->setCoatings(coatings);
        intent->setSpots(spots);
        intent->setFetched(true);
    }
    return intent;
}

void ColorIntent::toXJdf(QXmlStreamWriter &writer, bool) const
{
    Q_D_CONST(ColorIntent);
    Intent::toXJdf(writer);
    writer.writeStartElement(QStringLiteral("ColorIntent"));

    for (auto it = d->coatings.begin(); it != d->coatings.end(); ++it) {
        writer.writeStartElement(QStringLiteral("SurfaceColor"));
        writer.writeAttribute(QStringLiteral("Surface"), sideTypeToString(it.key()));

        auto coatings = algorithms::map(it.value(), [](const auto &coating) { return coatingTypeToString(coating); },
                                        QStringList())
                            .join(' ');

        writer.writeAttribute(QStringLiteral("Coatings"), coatings);
        if (d->spots.contains(it.key()) && d->spots[it.key()])
            writer.writeAttribute(QStringLiteral("ColorsUsed"), QStringLiteral("Spot"));

        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndElement();
}

ColorIntent::ColorIntent() : Intent(*new ColorIntentPrivate)
{}

void ColorIntent::updateSelf(const NetworkDataEntitySP &other)
{
    ColorIntentSP castedOther = qSharedPointerCast<ColorIntent>(other);
    setSpots(castedOther->spots());
    setCoatings(castedOther->coatings());

    Intent::updateSelf(other);
}
