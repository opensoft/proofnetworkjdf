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
#include "proofnetwork/jdf/data/layout.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/media.h"

namespace Proof {
namespace Jdf {

class LayoutPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(Layout)

    LayoutPrivate() : AbstractResourcePrivate(ResourceClass::ParameterClass) { registerChildren(media); }

    bool partsAreValid(QVector<ResourcePartType> partsToCheck = QVector<ResourcePartType>()) const;

    QVector<MediaSP> media;
    QVector<LayoutSP> parts;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

Layout::Layout() : AbstractResource(*new LayoutPrivate)
{}

QVector<MediaSP> Layout::media() const
{
    Q_D_CONST(Layout);
    return d->media;
}

QVector<LayoutSP> Layout::parts() const
{
    Q_D_CONST(Layout);
    return d->parts;
}

void Layout::setMedia(const QVector<MediaSP> &arg)
{
    Q_D(Layout);
    bool emitNeeded = arg.count() != d->media.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->media[i]->id();
    if (emitNeeded) {
        d->media = arg;
        emit mediaChanged();
    }
}

void Layout::addMedia(const MediaSP &arg)
{
    Q_D(Layout);
    if (!arg)
        return;
    d->media << arg;
    emit mediaChanged();
}

LayoutQmlWrapper *Layout::toQmlWrapper(QObject *parent) const
{
    LayoutSP castedSelf = castedSelfPtr<Layout>();
    Q_ASSERT(castedSelf);
    return new LayoutQmlWrapper(castedSelf, parent);
}

LayoutSP Layout::create()
{
    LayoutSP result(new Layout());
    initSelfWeakPtr(result);
    return result;
}

LayoutSP Layout::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    LayoutSP layout = create();

    QVector<MediaSP> mediaList;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Layout" && xmlReader.isStartElement() && !layout->isFetched()) {
            layout->setFetched(true);
            AbstractResourceSP castedComponent = qSharedPointerCast<AbstractResource>(layout);
            AbstractResource::fromJdf(xmlReader, castedComponent);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Layout") {
                LayoutSP part = Layout::fromJdf(xmlReader, jobId, sanitize);
                if (!part) {
                    qCWarning(proofNetworkJdfDataLog) << "Layout not created. Part is not valid";
                    return LayoutSP();
                }
                layout->addPart(part);
            } else if (xmlReader.name() == "Media") {
                MediaSP media = Media::fromJdf(xmlReader, jobId, sanitize);
                if (!media) {
                    qCWarning(proofNetworkJdfDataLog) << "Layout not created. Media is invalid.";
                    return LayoutSP();
                }
                mediaList << media;
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    if (layout->d_func()->partIdKeys.count() && !layout->d_func()->partsAreValid()) {
        qCWarning(proofNetworkJdfDataLog) << "Layout not created. Partioning is not valid";
        return LayoutSP();
    }

    layout->setMedia(mediaList);

    return layout;
}

void Layout::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Layout);
    jdfWriter.writeStartElement(QStringLiteral("Layout"));
    AbstractResource::toJdf(jdfWriter);

    for (const MediaSP &media : qAsConst(d->media)) {
        if (isValidAndDirty(media))
            media->toJdf(jdfWriter);
    }

    for (const auto &part : qAsConst(d->parts)) {
        if (part->isDirty())
            part->toJdf(jdfWriter);
    }

    jdfWriter.writeEndElement();
}

QVector<LayoutSP> Layout::updateParts(const QVector<LayoutSP> &arg)
{
    Q_D(Layout);
    bool emitNeeded = arg.count() != d->parts.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->parts[i]->id();
    if (emitNeeded) {
        d->parts = arg;
        emit partsChanged();
    }
    return d->parts;
}

void Layout::addPart(const LayoutSP &arg)
{
    Q_D(Layout);
    d->parts << arg;
    emit partsChanged();
}

void Layout::updateSelf(const NetworkDataEntitySP &other)
{
    LayoutSP castedOther = qSharedPointerCast<Layout>(other);
    setMedia(castedOther->media());

    AbstractResource::updateSelf(other);
}

bool LayoutPrivate::partsAreValid(QVector<ResourcePartType> partsToCheck) const
{
    if (partsToCheck.isEmpty() && !partIdKeys.isEmpty())
        partsToCheck = partIdKeys;
    if (partsToCheck.isEmpty()) {
        if (parts.count())
            qCWarning(proofNetworkJdfDataLog) << "Layout partioning is not valid. Extra parts found";
        return parts.isEmpty();
    }

    auto currentPart = partsToCheck.takeFirst();

    for (const auto &part : parts) {
        if (!part->hasPartAttribute(currentPart)) {
            qCWarning(proofNetworkJdfDataLog)
                << "Layout partioning is not valid. Part" << resourcePartTypeToString(currentPart) << "not found";
            return false;
        }
        if (!part->d_func()->partsAreValid(partsToCheck))
            return false;
    }
    return true;
}
