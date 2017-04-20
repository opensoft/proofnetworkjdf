#include "media.h"

#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"

namespace Proof {
namespace Jdf {

class MediaPrivate : AbstractPhysicalResourcePrivate
{
    Q_DECLARE_PUBLIC(Media)

    MediaPrivate() : AbstractPhysicalResourcePrivate(ResourceClass::ConsumableClass) {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

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

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

double Media::thickness() const
{
    Q_D(const Media);
    return d->thickness;
}

CoatingType Media::frontCoating() const
{
    Q_D(const Media);
    return d->frontCoating;
}

CoatingDetail Media::frontCoatingDetail() const
{
    Q_D(const Media);
    return d->frontCoatingDetail;
}

CoatingType Media::backCoating() const
{
    Q_D(const Media);
    return d->backCoating;
}

CoatingDetail Media::backCoatingDetail() const
{
    Q_D(const Media);
    return d->backCoatingDetail;
}

MediaUnit Media::mediaUnit() const
{
    Q_D(const Media);
    return d->mediaUnit;
}

MediaType Media::mediaType() const
{
    Q_D(const Media);
    return d->mediaType;
}

double Media::height() const
{
    Q_D(const Media);
    return d->height;
}

double Media::width() const
{
    Q_D(const Media);
    return d->width;
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
    Q_D(const Media);
    MediaSP castedSelf = qSharedPointerCast<Media>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new MediaQmlWrapper(castedSelf, parent);
}

MediaSP Media::create()
{
    MediaSP result(new Media());
    initSelfWeakPtr(result);
    return result;
}

MediaSP Media::fromJdf(QXmlStreamReader &xmlReader)
{
    MediaSP media = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Media" && xmlReader.isStartElement() && !media->isFetched()) {
            media->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            media->setId(attributes.value("ID").toString());
            media->setFrontCoating(coatingFromString(attributes.value("FrontCoatings").toString()));
            media->setFrontCoatingDetail(coatingDetailFromString(attributes.value("FrontCoatingDetail").toString()));
            media->setBackCoating(coatingFromString(attributes.value("BackCoatings").toString()));
            media->setBackCoatingDetail(coatingDetailFromString(attributes.value("BackCoatingDetail").toString()));
            media->setMediaUnit(mediaUnitFromString(attributes.value("MediaUnit").toString()));
            media->setMediaType(mediaTypeFromString(attributes.value("MediaType").toString()));
            media->setThickness(attributes.value("Thickness").toDouble());
            QStringList dimensions = attributes.value("Dimension").toString().split(' ', QString::SkipEmptyParts);
            if (dimensions.size() >= 2) {
                media->setWidth(dimensions[0].toDouble());
                media->setHeight(dimensions[1].toDouble());
            }

            AbstractPhysicalResourceSP castedMedia = qSharedPointerCast<AbstractPhysicalResource>(media);
            AbstractPhysicalResource::fromJdf(xmlReader, castedMedia);

        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return media;
}

void Media::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Media);
    jdfWriter.writeStartElement("Media");
    if (!qFuzzyIsNull(d->width) || !qFuzzyIsNull(d->height))
        jdfWriter.writeAttribute("Dimension", QString("%1 %2").arg(d->width, 0, 'f', 4).arg(d->height, 0, 'f', 4));
    if (d->frontCoating != CoatingType::NoCoating)
        jdfWriter.writeAttribute("FrontCoatings", coatingToString(d->frontCoating));
    if (d->frontCoatingDetail != CoatingDetail::NoCoatingDetail)
        jdfWriter.writeAttribute("FrontCoatingDetail", coatingDetailToString(d->frontCoatingDetail));
    if (d->backCoating != CoatingType::NoCoating)
        jdfWriter.writeAttribute("BackCoatings", coatingToString(d->backCoating));
    if (d->backCoatingDetail != CoatingDetail::NoCoatingDetail)
        jdfWriter.writeAttribute("BackCoatingDetail", coatingDetailToString(d->backCoatingDetail));
    jdfWriter.writeAttribute("MediaUnit", mediaUnitToString(d->mediaUnit));
    jdfWriter.writeAttribute("MediaType", mediaTypeToString(d->mediaType));
    if (d->thickness > 0)
        jdfWriter.writeAttribute("Thickness", QString::number(d->thickness,'f', 4));

    AbstractPhysicalResource::toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

MediaLinkSP Media::toLink(LinkUsage usage) const
{
    MediaLinkSP link = MediaLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

Media::Media()
    : AbstractPhysicalResource(*new MediaPrivate)
{
}

void MediaPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(Media);
    MediaSP castedOther = qSharedPointerCast<Media>(other);
    q->setThickness(castedOther->thickness());
    q->setFrontCoating(castedOther->frontCoating());
    q->setFrontCoatingDetail(castedOther->frontCoatingDetail());
    q->setBackCoating(castedOther->backCoating());
    q->setBackCoatingDetail(castedOther->backCoatingDetail());
    q->setMediaUnit(castedOther->mediaUnit());
    q->setMediaType(castedOther->mediaType());
    q->setHeight(castedOther->height());
    q->setWidth(castedOther->width());

    AbstractPhysicalResourcePrivate::updateFrom(other);
}
