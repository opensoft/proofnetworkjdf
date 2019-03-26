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
 * FITNESS FOR A MediaICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "proofnetwork/xjdf/data/media.h"

#include "proofnetwork/xjdf/data/resource_p.h"

namespace Proof {
namespace XJdf {
class MediaPrivate : public ResourcePrivate
{
    Q_DECLARE_PUBLIC(Media)

public:
    MediaPrivate() = default;

    double width = 0.0;
    double height = 0.0;
    double thickness = 0.0;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

double Media::width() const
{
    Q_D_CONST(Media);
    return d->width;
}

double Media::height() const
{
    Q_D_CONST(Media);
    return d->height;
}

double Media::thickness() const
{
    Q_D_CONST(Media);
    return d->thickness;
}

void Media::setWidth(double arg)
{
    Q_D(Media);
    if (!qFuzzyCompare(arg, d->width)) {
        d->width = arg;
        emit widthChanged(arg);
    }
}

void Media::setHeight(double arg)
{
    Q_D(Media);
    if (!qFuzzyCompare(arg, d->height)) {
        d->height = arg;
        emit heightChanged(arg);
    }
}
void Media::setThickness(double arg)
{
    Q_D(Media);
    if (!qFuzzyCompare(arg, d->thickness)) {
        d->thickness = arg;
        emit thicknessChanged(arg);
    }
}

MediaSP Media::create(const QString &id)
{
    MediaSP result(new Media(id));
    initSelfWeakPtr(result);
    return result;
}

MediaSP Media::fromXJdf(QXmlStreamReader &reader)
{
    MediaSP media;
    if (reader.isStartElement() && reader.name() == QStringLiteral("Media")) {
        media = create();
        media->setFetched(true);
        auto attributes = reader.attributes();
        reader.skipCurrentElement();
        if (attributes.hasAttribute(QStringLiteral("Dimension"))) {
            auto dimension = attributes.value(QStringLiteral("Dimension")).toString().split(' ', QString::SkipEmptyParts);
            if (dimension.count() < 2)
                return MediaSP();
            media->setWidth(dimension[0].toDouble());
            media->setHeight(dimension[1].toDouble());
        }
        if (attributes.hasAttribute(QStringLiteral("Thickness")))
            media->setThickness(attributes.value(QStringLiteral("Thickness")).toDouble());
    }
    return media;
}

void Media::toXJdf(QXmlStreamWriter &writer, bool) const
{
    Q_D_CONST(Media);
    Resource::toXJdf(writer);
    writer.writeStartElement(QStringLiteral("Media"));
    writer.writeAttribute(QStringLiteral("Dimension"),
                          QStringLiteral("%1 %2").arg(d->width, 0, 'f', 2).arg(d->height, 0, 'f', 2));
    writer.writeAttribute(QStringLiteral("Thickness"), QStringLiteral("%1").arg(d->thickness, 0, 'f', 2));
    writer.writeEndElement();
    Resource::toXJdf(writer, true);
}

Media::Media(const QString &id) : Resource(*new MediaPrivate, id)
{}

void Media::updateSelf(const NetworkDataEntitySP &other)
{
    MediaSP castedOther = qSharedPointerCast<Media>(other);
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setThickness(castedOther->thickness());
    Resource::updateSelf(other);
}
