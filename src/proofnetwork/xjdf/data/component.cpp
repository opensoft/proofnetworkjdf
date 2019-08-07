/* Copyright 2019, OpenSoft Inc.
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
#include "proofnetwork/xjdf/data/component.h"

#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/data/media.h"
#include "proofnetwork/xjdf/data/resource_p.h"
#include "proofnetwork/xjdf/data/resourceset.h"

namespace Proof {
namespace XJdf {
class ComponentPrivate : public ResourcePrivate
{
    Q_DECLARE_PUBLIC(Component)

public:
    ComponentPrivate() { registerChildren(lazyMedia); }
    QString mediaRef;
    mutable MediaSP lazyMedia;

    double width = 0.0;
    double height = 0.0;
    double thickness = 0.0;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

ResourceSP Component::cloneTo(const DocumentSP &document)
{
    auto newComponent = create(document);
    newComponent->updateFrom(qSharedPointerCast<Component>(selfPtr()));
    return qSharedPointerCast<Resource>(newComponent);
}

ComponentSP Component::create(const DocumentSP &document)
{
    ComponentSP result(new Component());
    const auto *constEntity = result.data();
    constEntity->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

MediaSP Component::mediaRef() const
{
    Q_D_CONST(Component);

    if (d->lazyMedia)
        return d->lazyMedia;

    auto document = d->document.toStrongRef();
    if (document) {
        auto set = algorithms::findIf(document->resourceSets(),
                                      [d](const auto &set) {
                                          return algorithms::findIf(set->resources(),
                                                                    [d](const auto &resource) {
                                                                        return resource->id() == d->mediaRef;
                                                                    },
                                                                    ResourceSP());
                                      },
                                      ResourceSetSP());
        if (set) {
            d->lazyMedia = algorithms::findIf(set->resourcesByType<Media>(),
                                              [d](const auto &media) { return media->id() == d->mediaRef; }, MediaSP());
            if (d->lazyMedia)
                return d->lazyMedia;
        }
    }

    auto dummy = document->createNode<Media>(d->mediaRef);
    return dummy;
}

double Component::width() const
{
    Q_D_CONST(Component);
    return d->width;
}

double Component::height() const
{
    Q_D_CONST(Component);
    return d->height;
}

double Component::thickness() const
{
    Q_D_CONST(Component);
    return d->thickness;
}

void Component::updateMediaRef(const QString &arg)
{
    Q_D(Component);
    if (arg != d->mediaRef) {
        d->lazyMedia.reset();
        d->mediaRef = arg;
        emit mediaRefChanged(mediaRef());
    }
}

void Component::setWidth(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(arg, d->width)) {
        d->width = arg;
        emit widthChanged(d->width);
    }
}

void Component::setHeight(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(arg, d->height)) {
        d->height = arg;
        emit heightChanged(d->height);
    }
}
void Component::setThickness(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(arg, d->thickness)) {
        d->thickness = arg;
        emit thicknessChanged(d->thickness);
    }
}

ComponentSP Component::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    ComponentSP component;
    if (reader.isStartElement() && reader.name() == QStringLiteral("Component")) {
        component = create(document);
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("Dimensions"))) {
            auto dimension = attributes.value(QStringLiteral("Dimensions")).toString().split(' ', QString::SkipEmptyParts);
            if (dimension.count() < 3)
                return ComponentSP();
            component->setWidth(dimension[0].toDouble());
            component->setHeight(dimension[1].toDouble());
            component->setThickness(dimension[2].toDouble());
        }
        if (attributes.hasAttribute(QStringLiteral("MediaRef")))
            component->updateMediaRef(attributes.value(QStringLiteral("MediaRef")).toString());

        reader.readNext();
        component->setFetched(true);
    }
    return component;
}

void Component::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(Component);
    NodeWriterGuard guard(writeFieldsToXJdf(writer));
    writer.writeStartElement(QStringLiteral("Component"));
    if (!qIsNull(d->width) && !qIsNull(d->height)) {
        auto dimensions =
            QStringLiteral("%1 %2 %3").arg(d->width, 0, 'f', 2).arg(d->height, 0, 'f', 2).arg(d->thickness, 0, 'f', 2);
        writer.writeAttribute(QStringLiteral("Dimensions"), dimensions);
    }
    auto mediaRef = this->mediaRef();
    if (isValidAndDirty(mediaRef))
        writer.writeAttribute(QStringLiteral("MediaRef"), mediaRef->id());

    writer.writeEndElement();
}

Component::Component() : Resource(*new ComponentPrivate)
{}

void Component::updateSelf(const NetworkDataEntitySP &other)
{
    ComponentSP castedOther = qSharedPointerCast<Component>(other);
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setThickness(castedOther->thickness());
    updateMediaRef(castedOther->mediaRef()->id());
    Resource::updateSelf(other);
}
