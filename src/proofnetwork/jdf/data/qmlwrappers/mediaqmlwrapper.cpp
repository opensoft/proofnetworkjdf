#include "mediaqmlwrapper.h"

#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class MediaQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(MediaQmlWrapper)
};

MediaQmlWrapper::MediaQmlWrapper(const MediaSP &media, QObject *parent)
    : NetworkDataEntityQmlWrapper(media, *new MediaQmlWrapperPrivate, parent)
{
    setupEntity();
}

MediaQmlWrapper::~MediaQmlWrapper()
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Media)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, double, thickness)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, double, height)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, double, width)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, Proof::Jdf::ApiHelper::Coating, frontCoating)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Media, Proof::Jdf::ApiHelper::Coating, backCoating)

void MediaQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(MediaQmlWrapper);
    MediaSP media = d->entity<Media>();
    Q_ASSERT(media);

    connect(media.data(), &Media::idChanged, this, &MediaQmlWrapper::idChanged);
    connect(media.data(), &Media::thicknessChanged, this, &MediaQmlWrapper::thicknessChanged);
    connect(media.data(), &Media::heightChanged, this, &MediaQmlWrapper::heightChanged);
    connect(media.data(), &Media::widthChanged, this, &MediaQmlWrapper::widthChanged);
    connect(media.data(), &Media::frontCoatingChanged, this, &MediaQmlWrapper::frontCoatingChanged);
    connect(media.data(), &Media::backCoatingChanged, this, &MediaQmlWrapper::backCoatingChanged);

    MediaSP oldMedia = qSharedPointerCast<Media>(old);
    if (oldMedia) {
        if (media->id() != oldMedia->id())
            emit idChanged(media->id());
        if (media->thickness() != oldMedia->thickness())
            emit thicknessChanged(media->thickness());
        if (media->height() != oldMedia->height())
            emit heightChanged(media->height());
        if (media->width() != oldMedia->width())
            emit widthChanged(media->width());
        if (media->frontCoating() != oldMedia->frontCoating())
            emit frontCoatingChanged(media->frontCoating());
        if (media->backCoating() != oldMedia->backCoating())
            emit backCoatingChanged(media->backCoating());
    }
}

}
}
