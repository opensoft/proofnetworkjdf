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
#include "proofnetwork/jdf/data/qmlwrappers/layoutqmlwrapper.h"

#include "proofnetwork/jdf/data/layout.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"
#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"

namespace Proof {
namespace Jdf {
class LayoutQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(LayoutQmlWrapper)
    void updateMedia();
    void updateParts();

    static MediaQmlWrapper *mediaAt(QQmlListProperty<MediaQmlWrapper> *property, int index);
    static int mediaCount(QQmlListProperty<MediaQmlWrapper> *property);
    static LayoutQmlWrapper *partAt(QQmlListProperty<LayoutQmlWrapper> *property, int index);
    static int partsCount(QQmlListProperty<LayoutQmlWrapper> *property);

    QVector<MediaQmlWrapper *> media;
    QQmlListProperty<Proof::Jdf::MediaQmlWrapper> qmlMediaList;
    QVector<LayoutQmlWrapper *> parts;
    QQmlListProperty<Proof::Jdf::LayoutQmlWrapper> qmlPartsList;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

LayoutQmlWrapper::LayoutQmlWrapper(const LayoutSP &layout, QObject *parent)
    : AbstractResourceQmlWrapper(layout, *new LayoutQmlWrapperPrivate, parent)
{
    setupEntity(); // NOLINT
}

LayoutQmlWrapper::~LayoutQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Layout)

QQmlListProperty<Proof::Jdf::MediaQmlWrapper> LayoutQmlWrapper::media() const
{
    Q_D_CONST(LayoutQmlWrapper);
    return d->qmlMediaList;
}

QQmlListProperty<Proof::Jdf::LayoutQmlWrapper> LayoutQmlWrapper::parts() const
{
    Q_D_CONST(LayoutQmlWrapper);
    return d->qmlPartsList;
}

void LayoutQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    Q_D(LayoutQmlWrapper);
    Q_UNUSED(old)
    LayoutSP layout = entity<Layout>();
    Q_ASSERT(layout);

    connect(layout.data(), &Layout::mediaChanged, entityConnectContext(), [d]() { d->updateMedia(); });
    connect(layout.data(), &Layout::partsChanged, entityConnectContext(), [d]() { d->updateParts(); });

    d->updateMedia();
    d->updateParts();

    AbstractResourceQmlWrapper::setupEntity(old);
}

void LayoutQmlWrapperPrivate::updateMedia()
{
    Q_Q(LayoutQmlWrapper);
    LayoutSP layout = q->entity<Layout>();
    algorithms::forEach(media, [](const auto &x) { x->deleteLater(); });
    media = algorithms::map(layout->media(), [q](const auto &x) { return x->toQmlWrapper(q); });
    qmlMediaList = QQmlListProperty<Proof::Jdf::MediaQmlWrapper>(q, &media, &LayoutQmlWrapperPrivate::mediaCount,
                                                                 &LayoutQmlWrapperPrivate::mediaAt);
    emit q->mediaChanged(qmlMediaList);
}

void LayoutQmlWrapperPrivate::updateParts()
{
    Q_Q(LayoutQmlWrapper);
    LayoutSP layout = q->entity<Layout>();
    algorithms::forEach(parts, [](const auto &x) { x->deleteLater(); });
    parts = algorithms::map(layout->parts(), [q](const auto &x) { return x->toQmlWrapper(q); });
    qmlPartsList = QQmlListProperty<Proof::Jdf::LayoutQmlWrapper>(q, &parts, &LayoutQmlWrapperPrivate::partsCount,
                                                                  &LayoutQmlWrapperPrivate::partAt);
    emit q->partsChanged(qmlPartsList);
}

MediaQmlWrapper *LayoutQmlWrapperPrivate::mediaAt(QQmlListProperty<MediaQmlWrapper> *property, int index)
{
    return static_cast<QVector<MediaQmlWrapper *> *>(property->data)->at(index);
}

int LayoutQmlWrapperPrivate::mediaCount(QQmlListProperty<MediaQmlWrapper> *property)
{
    return static_cast<QVector<MediaQmlWrapper *> *>(property->data)->count();
}

LayoutQmlWrapper *LayoutQmlWrapperPrivate::partAt(QQmlListProperty<LayoutQmlWrapper> *property, int index)
{
    return static_cast<QVector<LayoutQmlWrapper *> *>(property->data)->at(index);
}

int LayoutQmlWrapperPrivate::partsCount(QQmlListProperty<LayoutQmlWrapper> *property)
{
    return static_cast<QVector<LayoutQmlWrapper *> *>(property->data)->count();
}
