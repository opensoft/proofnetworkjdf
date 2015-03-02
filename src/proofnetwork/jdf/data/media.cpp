#include "media.h"

#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class MediaPrivate : NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(Media)

    QString id;
    double thickness = 0.0;
    double height = 0.0;
    double width = 0.0;
    ApiHelper::Coating frontCoating = ApiHelper::None;
    ApiHelper::Coating backCoating = ApiHelper::None;
};

QString Media::id() const
{
    Q_D(const Media);
    return d->id;
}

double Media::thickness() const
{
    Q_D(const Media);
    return d->thickness;
}

ApiHelper::Coating Media::frontCoating() const
{
    Q_D(const Media);
    return d->frontCoating;
}

ApiHelper::Coating Media::backCoating() const
{
    Q_D(const Media);
    return d->backCoating;
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

void Media::setId(const QString &arg)
{
    Q_D(Media);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
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

void Media::setFrontCoating(ApiHelper::Coating coating)
{
    Q_D(Media);
    if (d->frontCoating != coating) {
        d->frontCoating = coating;
        emit frontCoatingChanged(coating);
    }
}

void Media::setBackCoating(ApiHelper::Coating coating)
{
    Q_D(Media);
    if (d->backCoating != coating) {
        d->backCoating = coating;
        emit backCoatingChanged(coating);
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

void Media::updateFrom(const NetworkDataEntitySP &other)
{
    MediaSP castedOther = qSharedPointerCast<Media>(other);
    setId(castedOther->id());
    setThickness(castedOther->thickness());
    setFrontCoating(castedOther->frontCoating());
    setBackCoating(castedOther->backCoating());
    setHeight(castedOther->height());
    setWidth(castedOther->width());
    NetworkDataEntity::updateFrom(other);
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
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

MediaSP Media::fromJdf(QXmlStreamReader &xmlReader)
{
    MediaSP result = create();
    result->setFetched(true);

    if (xmlReader.name() == "Media") {
        QXmlStreamAttributes attributes = xmlReader.attributes();
        result->setId(attributes.value("ID").toString());
        result->setBackCoating(ApiHelper::coatingFromString(attributes.value("BackCoatings").toString()));
        result->setFrontCoating(ApiHelper::coatingFromString(attributes.value("FrontCoatings").toString()));
        result->setThickness(attributes.value("Thickness").toDouble());
        QStringList dimensions = attributes.value("Dimension").toString().split(' ', QString::SkipEmptyParts);
        if (dimensions.size() >= 2) {
            result->setWidth(dimensions[0].toDouble());
            result->setHeight(dimensions[1].toDouble());
        }
    }

    return result;
}

void Media::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Media);
    jdfWriter.writeEmptyElement("Media");
    jdfWriter.writeAttribute("ID", d->id);
    jdfWriter.writeAttribute("Dimension", QString("%1 %2").arg(d->width).arg(d->height));
    jdfWriter.writeAttribute("BackCoatings", ApiHelper::coatingToString(d->backCoating));
    jdfWriter.writeAttribute("FrontCoatings", ApiHelper::coatingToString(d->frontCoating));
    jdfWriter.writeAttribute("Thickness", QString::number(d->thickness));
}

MediaSP Media::defaultObject()
{
    static MediaSP entity = create();
    return entity;
}

Media::Media()
    : NetworkDataEntity(*new MediaPrivate)
{
}

} // namespace Jdf
} // namespace Proof
