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
#ifndef JDFMEDIA_H
#define JDFMEDIA_H

#include "proofcore/objectscache.h"

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractphysicalresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

using JdfMediaDataKey = QPair<QString, QString>;

class MediaPrivate;
class PROOF_NETWORK_JDF_EXPORT Media : public AbstractPhysicalResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Media)
public:
    Media(const Media &) = delete;
    Media &operator=(const Media &) = delete;
    Media(Media &&) = delete;
    Media &operator=(Media &&) = delete;
    ~Media() = default;

    QVector<MediaSP> layers() const;
    double thickness() const;
    CoatingType frontCoating() const;
    CoatingDetail frontCoatingDetail() const;
    CoatingType backCoating() const;
    CoatingDetail backCoatingDetail() const;
    MediaUnit mediaUnit() const;
    MediaType mediaType() const;
    double height() const;
    double width() const;

    void setLayers(const QVector<MediaSP> &layers);
    void setThickness(double microns);
    void setFrontCoating(CoatingType coating);
    void setFrontCoatingDetail(CoatingDetail coatingDetail);
    void setBackCoating(CoatingType coating);
    void setBackCoatingDetail(CoatingDetail coatingDetail);
    void setMediaUnit(MediaUnit mediaUnit);
    void setMediaType(MediaType mediaType);
    void setHeight(double arg);
    void setWidth(double arg);

    MediaQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static MediaSP create();

    static MediaSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    MediaLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

signals:
    void layersChanged(const QVector<Proof::Jdf::MediaSP> &arg);
    void thicknessChanged(double arg);
    void heightChanged(double arg);
    void widthChanged(double arg);
    void frontCoatingChanged(Proof::Jdf::CoatingType arg);
    void frontCoatingDetailChanged(Proof::Jdf::CoatingDetail arg);
    void backCoatingChanged(Proof::Jdf::CoatingType arg);
    void backCoatingDetailChanged(Proof::Jdf::CoatingDetail arg);
    void mediaUnitChanged(Proof::Jdf::MediaUnit arg);
    void mediaTypeChanged(Proof::Jdf::MediaType arg);

protected:
    explicit Media();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

PROOF_NETWORK_JDF_EXPORT ObjectsCache<JdfMediaDataKey, Media> &mediaCache();

} // namespace Jdf
} // namespace Proof

#endif // JDFMEDIA_H
