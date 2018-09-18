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
#ifndef JDFMEDIAQMLWRAPPER_H
#define JDFMEDIAQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class Media;

class MediaQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT MediaQmlWrapper : public AbstractPhysicalResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(double thickness READ thickness NOTIFY thicknessChanged)
    Q_PROPERTY(double height READ height NOTIFY heightChanged)
    Q_PROPERTY(double width READ width NOTIFY widthChanged)
    Q_PROPERTY(Proof::Jdf::CoatingType frontCoating READ frontCoating NOTIFY frontCoatingChanged)
    Q_PROPERTY(Proof::Jdf::CoatingDetail frontCoatingDetail READ frontCoatingDetail NOTIFY frontCoatingDetailChanged)
    Q_PROPERTY(Proof::Jdf::CoatingType backCoating READ backCoating NOTIFY backCoatingChanged)
    Q_PROPERTY(Proof::Jdf::CoatingDetail backCoatingDetail READ backCoatingDetail NOTIFY backCoatingDetailChanged)
    Q_PROPERTY(Proof::Jdf::MediaUnit mediaUnit READ mediaUnit NOTIFY mediaUnitChanged)
    Q_PROPERTY(Proof::Jdf::MediaType mediaType READ mediaType NOTIFY mediaTypeChanged)
    Q_DECLARE_PRIVATE(MediaQmlWrapper)
public:
    explicit MediaQmlWrapper(const MediaSP &media, QObject *parent = nullptr);
    ~MediaQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(Media)

    double thickness() const;
    double height() const;
    double width() const;
    CoatingType frontCoating() const;
    CoatingDetail frontCoatingDetail() const;
    CoatingType backCoating() const;
    CoatingDetail backCoatingDetail() const;
    MediaUnit mediaUnit() const;
    MediaType mediaType() const;

signals:
    void thicknessChanged(double thickness);
    void heightChanged(double height);
    void widthChanged(double width);
    void frontCoatingChanged(Proof::Jdf::CoatingType frontCoating);
    void frontCoatingDetailChanged(Proof::Jdf::CoatingDetail frontCoating);
    void backCoatingChanged(Proof::Jdf::CoatingType backCoating);
    void backCoatingDetailChanged(Proof::Jdf::CoatingDetail backCoating);
    void mediaUnitChanged(Proof::Jdf::MediaUnit mediaUnit);
    void mediaTypeChanged(Proof::Jdf::MediaType mediaType);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFMEDIAQMLWRAPPER_H
