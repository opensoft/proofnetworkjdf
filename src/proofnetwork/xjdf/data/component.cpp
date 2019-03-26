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
#include "proofnetwork/xjdf/data/component.h"

#include "proofnetwork/xjdf/data/media.h"
#include "proofnetwork/xjdf/data/resource_p.h"

namespace Proof {
namespace XJdf {
class ComponentPrivate : public ResourcePrivate
{
    Q_DECLARE_PUBLIC(Component)

public:
    ComponentPrivate() = default;
    MediaWP mediaRef;

    double width = 0.0;
    double height = 0.0;
    double thickness = 0.0;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

ComponentSP Component::create()
{
    ComponentSP result(new Component());
    initSelfWeakPtr(result);
    return result;
}

MediaSP Component::mediaRef() const
{
    Q_D_CONST(Component);
    return d->mediaRef.toStrongRef();
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

void Component::setMediaRef(const MediaSP &arg)
{
    Q_D(Component);
    if (arg && arg != d->mediaRef.toStrongRef()) {
        d->mediaRef = arg.toWeakRef();
        emit mediaRefChanged(arg);
    }
}

void Component::setWidth(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(arg, d->width)) {
        d->width = arg;
        emit widthChanged(arg);
    }
}

void Component::setHeight(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(arg, d->height)) {
        d->height = arg;
        emit heightChanged(arg);
    }
}
void Component::setThickness(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(arg, d->thickness)) {
        d->thickness = arg;
        emit thicknessChanged(arg);
    }
}

ComponentSP Component::fromXJdf(QXmlStreamReader &reader)
{
    ComponentSP component;
    if (reader.isStartElement() && reader.name() == QStringLiteral("Component")) {
        component = create();
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("Dimensions"))) {
            auto dimension = attributes.value(QStringLiteral("Dimensions")).toString().split(' ', QString::SkipEmptyParts);
            if (dimension.count() < 3)
                return ComponentSP();
            component->setWidth(dimension[0].toDouble());
            component->setHeight(dimension[1].toDouble());
            component->setThickness(dimension[2].toDouble());
        }
        if (attributes.hasAttribute(QStringLiteral("MediaRef"))) {
            auto media = Media::create(attributes.value(QStringLiteral("MediaRef")).toString());
            component->setMediaRef(media);
        }

        reader.readNext();
        component->setFetched(true);
    }
    return component;
}

void Component::toXJdf(QXmlStreamWriter &writer, bool) const
{
    Q_D_CONST(Component);
    Resource::toXJdf(writer);

    writer.writeStartElement(QStringLiteral("Component"));
    auto dimensions = QString("%1 %2 %3").arg(d->width).arg(d->height).arg(d->thickness);
    writer.writeAttribute(QStringLiteral("Dimensions"), dimensions);
    auto mediaRef = d->mediaRef.toStrongRef();
    if (mediaRef)
        writer.writeAttribute(QStringLiteral("MediaRef"), mediaRef->id());

    writer.writeEndElement();
    Resource::toXJdf(writer, true);
}

Component::Component() : Resource(*new ComponentPrivate)
{}

void Component::updateSelf(const NetworkDataEntitySP &other)
{
    ComponentSP castedOther = qSharedPointerCast<Component>(other);
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setThickness(castedOther->thickness());

    Resource::updateSelf(other);
}
