#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"

#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class MediaQmlWrapperPrivate : public AbstractPhysicalResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(MediaQmlWrapper)
};

MediaQmlWrapper::MediaQmlWrapper(const MediaSP &media, QObject *parent)
    : AbstractPhysicalResourceQmlWrapper(media, *new MediaQmlWrapperPrivate, parent)
{
    setupEntity();
}

MediaQmlWrapper::~MediaQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Media)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, double, thickness)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, double, height)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, double, width)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, Proof::Jdf::CoatingType, frontCoating)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, Proof::Jdf::CoatingDetail, frontCoatingDetail)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, Proof::Jdf::CoatingType, backCoating)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, Proof::Jdf::CoatingDetail, backCoatingDetail)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, Proof::Jdf::MediaUnit, mediaUnit)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, Proof::Jdf::MediaType, mediaType)

void MediaQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    MediaSP media = entity<Media>();
    Q_ASSERT(media);

    connect(media.data(), &Media::thicknessChanged, this, &MediaQmlWrapper::thicknessChanged);
    connect(media.data(), &Media::heightChanged, this, &MediaQmlWrapper::heightChanged);
    connect(media.data(), &Media::widthChanged, this, &MediaQmlWrapper::widthChanged);
    connect(media.data(), &Media::frontCoatingChanged, this, &MediaQmlWrapper::frontCoatingChanged);
    connect(media.data(), &Media::frontCoatingDetailChanged, this, &MediaQmlWrapper::frontCoatingDetailChanged);
    connect(media.data(), &Media::backCoatingChanged, this, &MediaQmlWrapper::backCoatingChanged);
    connect(media.data(), &Media::backCoatingDetailChanged, this, &MediaQmlWrapper::backCoatingDetailChanged);
    connect(media.data(), &Media::mediaUnitChanged, this, &MediaQmlWrapper::mediaUnitChanged);
    connect(media.data(), &Media::mediaTypeChanged, this, &MediaQmlWrapper::mediaTypeChanged);

    MediaSP oldMedia = qSharedPointerCast<Media>(old);
    if (oldMedia) {
        if (media->thickness() != oldMedia->thickness())
            emit thicknessChanged(media->thickness());
        if (media->height() != oldMedia->height())
            emit heightChanged(media->height());
        if (media->width() != oldMedia->width())
            emit widthChanged(media->width());
        if (media->frontCoating() != oldMedia->frontCoating())
            emit frontCoatingChanged(media->frontCoating());
        if (media->frontCoatingDetail() != oldMedia->frontCoatingDetail())
            emit frontCoatingDetailChanged(media->frontCoatingDetail());
        if (media->backCoating() != oldMedia->backCoating())
            emit backCoatingChanged(media->backCoating());
        if (media->backCoatingDetail() != oldMedia->backCoatingDetail())
            emit backCoatingDetailChanged(media->backCoatingDetail());
        if (media->mediaUnit() != oldMedia->mediaUnit())
            emit mediaUnitChanged(media->mediaUnit());
        if (media->mediaType() != oldMedia->mediaType())
            emit mediaTypeChanged(media->mediaType());
    }

    AbstractPhysicalResourceQmlWrapper::setupEntity(old);
}

} // namespace Jdf
} // namespace Proof
