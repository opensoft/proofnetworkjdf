#include "proofnetwork/jdf/data/media.h"

#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"

namespace Proof {
namespace Jdf {

class MediaPrivate : AbstractPhysicalResourcePrivate
{
    Q_DECLARE_PUBLIC(Media)

    MediaPrivate() : AbstractPhysicalResourcePrivate(ResourceClass::ConsumableClass) {}

    QVector<MediaSP> layers;
    double thickness = 0.0;
    double height = 0.0;
    double width = 0.0;
    CoatingType frontCoating = CoatingType::NoCoating;
    CoatingDetail frontCoatingDetail = CoatingDetail::NoCoatingDetail;
    CoatingType backCoating = CoatingType::NoCoating;
    CoatingDetail backCoatingDetail = CoatingDetail::NoCoatingDetail;
    MediaUnit mediaUnit = MediaUnit::SheetMediaUnit;
    MediaType mediaType = MediaType::OtherMedia;
};

ObjectsCache<JdfMediaDataKey, Media> &mediaCache()
{
    return WeakObjectsCache<JdfMediaDataKey, Media>::instance();
}

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

QVector<MediaSP> Media::layers() const
{
    Q_D_CONST(Media);
    return d->layers;
}

double Media::thickness() const
{
    Q_D_CONST(Media);
    return d->thickness;
}

CoatingType Media::frontCoating() const
{
    Q_D_CONST(Media);
    return d->frontCoating;
}

CoatingDetail Media::frontCoatingDetail() const
{
    Q_D_CONST(Media);
    return d->frontCoatingDetail;
}

CoatingType Media::backCoating() const
{
    Q_D_CONST(Media);
    return d->backCoating;
}

CoatingDetail Media::backCoatingDetail() const
{
    Q_D_CONST(Media);
    return d->backCoatingDetail;
}

MediaUnit Media::mediaUnit() const
{
    Q_D_CONST(Media);
    return d->mediaUnit;
}

MediaType Media::mediaType() const
{
    Q_D_CONST(Media);
    return d->mediaType;
}

double Media::height() const
{
    Q_D_CONST(Media);
    return d->height;
}

double Media::width() const
{
    Q_D_CONST(Media);
    return d->width;
}

void Media::setLayers(const QVector<MediaSP> &layers)
{
    Q_D(Media);
    if (d->layers != layers) {
        d->layers = layers;
        emit layersChanged(d->layers);
    }
}

void Media::setThickness(double microns)
{
    Q_D(Media);
    if (d->thickness != microns) {
        d->thickness = microns;
        emit thicknessChanged(d->thickness);
    }
}

void Media::setFrontCoating(CoatingType coating)
{
    Q_D(Media);
    if (d->frontCoating != coating) {
        d->frontCoating = coating;
        emit frontCoatingChanged(coating);
    }
}

void Media::setFrontCoatingDetail(CoatingDetail coatingDetail)
{
    Q_D(Media);
    if (d->frontCoatingDetail != coatingDetail) {
        d->frontCoatingDetail = coatingDetail;
        emit frontCoatingDetailChanged(coatingDetail);
    }
}

void Media::setBackCoating(CoatingType coating)
{
    Q_D(Media);
    if (d->backCoating != coating) {
        d->backCoating = coating;
        emit backCoatingChanged(coating);
    }
}

void Media::setBackCoatingDetail(CoatingDetail coatingDetail)
{
    Q_D(Media);
    if (d->backCoatingDetail != coatingDetail) {
        d->backCoatingDetail = coatingDetail;
        emit backCoatingDetailChanged(coatingDetail);
    }
}

void Media::setMediaUnit(MediaUnit mediaUnit)
{
    Q_D(Media);
    if (d->mediaUnit != mediaUnit) {
        d->mediaUnit = mediaUnit;
        emit mediaUnitChanged(mediaUnit);
    }
}

void Media::setMediaType(MediaType mediaType)
{
    Q_D(Media);
    if (d->mediaType != mediaType) {
        d->mediaType = mediaType;
        emit mediaTypeChanged(mediaType);
    }
}

void Media::setHeight(double arg)
{
    Q_D(Media);
    if (d->height != arg) {
        d->height = arg;
        emit heightChanged(d->height);
    }
}

void Media::setWidth(double arg)
{
    Q_D(Media);
    if (d->width != arg) {
        d->width = arg;
        emit widthChanged(d->width);
    }
}

MediaQmlWrapper *Media::toQmlWrapper(QObject *parent) const
{
    MediaSP castedSelf = castedSelfPtr<Media>();
    Q_ASSERT(castedSelf);
    return new MediaQmlWrapper(castedSelf, parent);
}

MediaSP Media::create()
{
    MediaSP result(new Media());
    initSelfWeakPtr(result);
    return result;
}

MediaSP Media::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    MediaSP media = create();
    QVector<MediaSP> layers;

    bool inLayers = false;
    bool isRef = false;

    auto mediaParser = [&xmlReader](MediaSP media) {
        media->setFetched(true);
        QXmlStreamAttributes attributes = xmlReader.attributes();
        media->setId(attributes.value(QStringLiteral("ID")).toString());
        media->setFrontCoating(coatingFromString(attributes.value(QStringLiteral("FrontCoatings")).toString()));
        media->setFrontCoatingDetail(
            coatingDetailFromString(attributes.value(QStringLiteral("FrontCoatingDetail")).toString()));
        media->setBackCoating(coatingFromString(attributes.value(QStringLiteral("BackCoatings")).toString()));
        media->setBackCoatingDetail(
            coatingDetailFromString(attributes.value(QStringLiteral("BackCoatingDetail")).toString()));
        media->setMediaUnit(mediaUnitFromString(attributes.value(QStringLiteral("MediaUnit")).toString()));
        media->setMediaType(mediaTypeFromString(attributes.value(QStringLiteral("MediaType")).toString()));
        media->setThickness(attributes.value(QStringLiteral("Thickness")).toDouble());
        QStringList dimensions =
            attributes.value(QStringLiteral("Dimension")).toString().split(' ', QString::SkipEmptyParts);
        if (dimensions.size() >= 2) {
            media->setWidth(dimensions[0].toDouble());
            media->setHeight(dimensions[1].toDouble());
        }

        AbstractPhysicalResourceSP castedMedia = qSharedPointerCast<AbstractPhysicalResource>(media);
        AbstractPhysicalResource::fromJdf(xmlReader, castedMedia);
    };

    //TODO: make comparisons in jdf parser more generic
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (!xmlReader.name().compare(QLatin1String("MediaLayers"), Qt::CaseInsensitive) && media->isFetched()) {
            inLayers = xmlReader.isStartElement();
        } else if (!xmlReader.name().compare(media->jdfNodeName(), Qt::CaseInsensitive) && xmlReader.isStartElement()
                   && media->isFetched() && inLayers) {
            MediaSP newLayer = create();
            mediaParser(newLayer);
            layers << newLayer;
        } else if (!xmlReader.name().compare(media->jdfNodeName(), Qt::CaseInsensitive) && xmlReader.isStartElement()
                   && !media->isFetched()) {
            mediaParser(media);
        } else if (!xmlReader.name().compare(media->jdfNodeRefName(), Qt::CaseInsensitive) && xmlReader.isStartElement()
                   && media->isFetched() && inLayers) {
            MediaSP newLayer = create();
            QXmlStreamAttributes attributes = xmlReader.attributes();
            QString mediaId = attributes.value(QStringLiteral("rRef")).toString();
            newLayer->setId(mediaId);
            newLayer = mediaCache().add({jobId, mediaId}, newLayer);
            layers << newLayer;
        } else if (!xmlReader.name().compare(media->jdfNodeRefName(), Qt::CaseInsensitive) && xmlReader.isStartElement()
                   && !media->isFetched()) {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            QString mediaId = attributes.value(QStringLiteral("rRef")).toString();
            media->setId(mediaId);
            isRef = true;
        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement() && !inLayers) {
            break;
        }
        xmlReader.readNext();
    }

    media->setLayers(layers);

    if (!media->id().isEmpty()) {
        auto mediaFromCache = mediaCache().add({jobId, media->id()}, media);
        if (media != mediaFromCache && !sanitize && !isRef)
            mediaFromCache->updateFrom(media);
        media = mediaFromCache;
    }

    return media;
}

void Media::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Media);
    jdfWriter.writeStartElement(QStringLiteral("Media"));
    if (!qFuzzyIsNull(d->width) || !qFuzzyIsNull(d->height))
        jdfWriter.writeAttribute(QStringLiteral("Dimension"),
                                 QStringLiteral("%1 %2").arg(d->width, 0, 'f', 4).arg(d->height, 0, 'f', 4));
    if (d->frontCoating != CoatingType::NoCoating)
        jdfWriter.writeAttribute(QStringLiteral("FrontCoatings"), coatingToString(d->frontCoating));
    if (d->frontCoatingDetail != CoatingDetail::NoCoatingDetail)
        jdfWriter.writeAttribute(QStringLiteral("FrontCoatingDetail"), coatingDetailToString(d->frontCoatingDetail));
    if (d->backCoating != CoatingType::NoCoating)
        jdfWriter.writeAttribute(QStringLiteral("BackCoatings"), coatingToString(d->backCoating));
    if (d->backCoatingDetail != CoatingDetail::NoCoatingDetail)
        jdfWriter.writeAttribute(QStringLiteral("BackCoatingDetail"), coatingDetailToString(d->backCoatingDetail));
    jdfWriter.writeAttribute(QStringLiteral("MediaUnit"), mediaUnitToString(d->mediaUnit));
    jdfWriter.writeAttribute(QStringLiteral("MediaType"), mediaTypeToString(d->mediaType));
    if (d->thickness > 0)
        jdfWriter.writeAttribute(QStringLiteral("Thickness"), QString::number(d->thickness, 'f', 4));

    AbstractPhysicalResource::toJdf(jdfWriter);

    //TODO: add proper check for layers media existing in document
    if (d->layers.count()) {
        jdfWriter.writeStartElement(QStringLiteral("MediaLayers"));
        for (const auto &layer : qAsConst(d->layers))
            layer->refToJdf(jdfWriter);
        jdfWriter.writeEndElement();
    }

    jdfWriter.writeEndElement();
}

MediaLinkSP Media::toLink(LinkUsage usage) const
{
    MediaLinkSP link = MediaLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

Media::Media() : AbstractPhysicalResource(*new MediaPrivate)
{}

void Media::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    MediaSP castedOther = qSharedPointerCast<Media>(other);
    setLayers(castedOther->layers());
    setThickness(castedOther->thickness());
    setFrontCoating(castedOther->frontCoating());
    setFrontCoatingDetail(castedOther->frontCoatingDetail());
    setBackCoating(castedOther->backCoating());
    setBackCoatingDetail(castedOther->backCoatingDetail());
    setMediaUnit(castedOther->mediaUnit());
    setMediaType(castedOther->mediaType());
    setHeight(castedOther->height());
    setWidth(castedOther->width());

    AbstractPhysicalResource::updateSelf(other);
}
