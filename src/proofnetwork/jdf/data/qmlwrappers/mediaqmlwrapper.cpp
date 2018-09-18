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
