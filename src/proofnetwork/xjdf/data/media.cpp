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
    MediaUnit unit = MediaUnit::NoMediaUnit;
    MediaType type = MediaType::NoMediaType;
    QVector<MediaSP> layers;
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

MediaUnit Media::unit() const
{
    Q_D_CONST(Media);
    return d->unit;
}

MediaType Media::type() const
{
    Q_D_CONST(Media);
    return d->type;
}

QVector<MediaSP> Media::layers() const
{
    Q_D_CONST(Media);
    return d->layers;
}

void Media::setUnit(MediaUnit arg)
{
    Q_D(Media);
    if (d->unit != arg) {
        d->unit = arg;
        emit unitChanged(arg);
    }
}

void Media::setType(MediaType arg)
{
    Q_D(Media);
    if (d->type != arg) {
        d->type = arg;
        emit typeChanged(arg);
    }
}

void Media::setLayers(const QVector<MediaSP> &arg)
{
    Q_D(Media);
    if (d->layers != arg) {
        d->layers = arg;
        emit layersChanged(d->layers);
    }
}

MediaSP Media::create(const QString &id)
{
    MediaSP result(new Media(id));
    initSelfWeakPtr(result);
    return result;
}

MediaSP Media::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    MediaSP media = create();
    QVector<MediaSP> layers;

    bool inLayers = false;
    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.name().compare(QLatin1String("MediaLayers"), Qt::CaseInsensitive) == 0 && media->isFetched()) {
            inLayers = reader.isStartElement();
        } else if (reader.name().compare(QLatin1String("Media"), Qt::CaseInsensitive) == 0 && !media->isFetched()) {
            media->d_func()->document = document;
            media->setFetched(true);
            auto attributes = reader.attributes();
            if (attributes.hasAttribute(QStringLiteral("Dimension"))) {
                auto dimension =
                    attributes.value(QStringLiteral("Dimension")).toString().split(' ', QString::SkipEmptyParts);
                if (dimension.count() < 2)
                    return MediaSP();
                media->setWidth(dimension[0].toDouble());
                media->setHeight(dimension[1].toDouble());
            }
            if (attributes.hasAttribute(QStringLiteral("Thickness")))
                media->setThickness(attributes.value(QStringLiteral("Thickness")).toDouble());
            if (attributes.hasAttribute(QStringLiteral("MediaUnit")))
                media->setUnit(mediaUnitFromString(attributes.value(QStringLiteral("MediaUnit")).toString()));
            if (attributes.hasAttribute(QStringLiteral("MediaType")))
                media->setType(mediaTypeFromString(attributes.value(QStringLiteral("MediaType")).toString()));
        } else if (reader.name().compare(QLatin1String("Media"), Qt::CaseInsensitive) == 0 && inLayers) {
            layers << Media::fromXJdf(reader, document);
        } else if (reader.isStartElement()) {
            reader.skipCurrentElement();
        } else if (reader.isEndElement() && !inLayers) {
            break;
        }
        reader.readNext();
    }
    media->setLayers(layers);

    return media;
}

void Media::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(Media);
    NodeWriterGuard guard(writeFieldsToXJdf(writer));

    auto mediaWriter = [&writer](const auto &media, bool withStartElement = false) {
        if (withStartElement)
            writer.writeStartElement(QStringLiteral("Media"));
        writer.writeAttribute(QStringLiteral("Dimension"),
                              QStringLiteral("%1 %2").arg(media->width(), 0, 'f', 2).arg(media->height(), 0, 'f', 2));
        writer.writeAttribute(QStringLiteral("Thickness"), QStringLiteral("%1").arg(media->thickness(), 0, 'f', 2));
        if (media->unit() != MediaUnit::NoMediaUnit)
            writer.writeAttribute(QStringLiteral("MediaUnit"), mediaUnitToString(media->unit()));
        if (media->type() != MediaType::NoMediaType)
            writer.writeAttribute(QStringLiteral("MediaType"), mediaTypeToString(media->type()));
        if (withStartElement)
            writer.writeEndElement();
    };

    writer.writeStartElement(QStringLiteral("Media"));
    mediaWriter(qSharedPointerCast<Media>(selfPtr()));

    if (!d->layers.isEmpty()) {
        writer.writeStartElement(QStringLiteral("MediaLayers"));
        for (const auto &layer : d->layers)
            mediaWriter(layer, true);
        writer.writeEndElement();
    }

    writer.writeEndElement();
}

Media::Media(const QString &id) : Resource(*new MediaPrivate, id)
{}

void Media::updateSelf(const NetworkDataEntitySP &other)
{
    MediaSP castedOther = qSharedPointerCast<Media>(other);
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setThickness(castedOther->thickness());
    setUnit(castedOther->unit());
    setType(castedOther->type());
    setLayers(castedOther->layers());
    Resource::updateSelf(other);
}
