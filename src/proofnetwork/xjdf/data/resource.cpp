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
#include "proofnetwork/xjdf/data/resource.h"

#include "proofnetwork/xjdf/data/amountpool.h"
#include "proofnetwork/xjdf/data/part.h"
#include "proofnetwork/xjdf/data/resource_p.h"

using namespace Proof;
using namespace Proof::XJdf;

QMap<QString, std::function<ResourceSP(QXmlStreamReader &, const XJdfDocumentSP &)>> *ResourcePrivate::creators = nullptr;

QString Resource::id() const
{
    Q_D_CONST(Resource);
    return d->id;
}

ResourceOrientation Resource::orientation() const
{
    Q_D_CONST(Resource);
    return d->orientation;
}

QVector<PartSP> Resource::parts() const
{
    Q_D_CONST(Resource);
    return d->parts;
}

AmountPoolSP Resource::amountPool() const
{
    Q_D_CONST(Resource);
    return d->amountPool;
}

void Resource::setId(const QString &arg)
{
    Q_D(Resource);
    if (arg != d->id) {
        d->id = arg;
        emit idChanged(arg);
    }
}

void Resource::setOrientation(ResourceOrientation arg)
{
    Q_D(Resource);
    if (arg != d->orientation) {
        d->orientation = arg;
        emit orientationChanged(arg);
    }
}

void Resource::setParts(const QVector<PartSP> &arg)
{
    Q_D(Resource);
    bool emitNeeded = arg.count() != d->parts.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->block() != d->parts[i]->block() || arg[i]->product() != d->parts[i]->product();
    if (emitNeeded) {
        d->parts = arg;
        emit partsChanged(arg);
    }
}

void Resource::setAmountPool(const AmountPoolSP &arg)
{
    Q_D(Resource);
    if (arg != d->amountPool) {
        d->amountPool = arg;
        emit amountPoolChanged(arg);
    }
}

bool Resource::fillFromXJdf(QXmlStreamReader &)
{
    //NOTE: Nothing there for now, but it can be fill later
    return false;
}

void Resource::readAttributesFromXJdf(QXmlStreamReader &reader)
{
    auto attributes = reader.attributes();
    if (attributes.hasAttribute(QStringLiteral("ID"))) {
        auto id = attributes.value(QStringLiteral("ID")).toString();
        setId(id);
    }
    if (attributes.hasAttribute(QStringLiteral("Orientation"))) {
        auto orientation = attributes.value(QStringLiteral("Orientation")).toString();
        setOrientation(resourceOrientationFromString(orientation));
    }
}

void Resource::toXJdf(QXmlStreamWriter &writer, bool writeEnd) const
{
    Q_D_CONST(Resource);
    if (writeEnd) {
        writer.writeEndElement();
        return;
    }

    writer.writeStartElement(QStringLiteral("Resource"));
    if (!d->id.isEmpty())
        writer.writeAttribute(QStringLiteral("ID"), d->id);
    if (d->orientation != ResourceOrientation::Rotate0Orientation)
        writer.writeAttribute(QStringLiteral("Orientation"), resourceOrientationToString(d->orientation));
    for (const auto &part : d->parts)
        part->toXJdf(writer);
    if (d->amountPool)
        d->amountPool->toXJdf(writer);
}

ResourceSP Resource::fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document)
{
    ResourceSP resource;
    QVector<PartSP> parts;
    AmountPoolSP amountPool;
    QString id;
    ResourceOrientation orientation = ResourceOrientation::Rotate0Orientation;

    if (reader.isStartElement() && reader.name() == QStringLiteral("Resource")) {
        auto attributes = reader.attributes();
        if (attributes.hasAttribute(QStringLiteral("ID")))
            id = attributes.value(QStringLiteral("ID")).toString();
        if (attributes.hasAttribute(QStringLiteral("Orientation")))
            orientation = resourceOrientationFromString(attributes.value(QStringLiteral("Orientation")).toString());
        reader.readNextStartElement();

        while (!reader.atEnd() && !reader.hasError()) {
            if (reader.isStartElement() && reader.name() == QStringLiteral("AmountPool")) {
                amountPool = AmountPool::fromXJdf(reader, document);
            } else if (reader.isStartElement() && reader.name() == QStringLiteral("Part")) {
                auto part = Part::fromXJdf(reader, document);
                if (part)
                    parts << part;
            } else if (reader.isStartElement()) {
                auto creator = resourceCreator(reader.name().toString());
                if (creator) {
                    resource = creator(reader, document);
                    reader.readNext();
                    continue;
                }
            } else if (reader.isEndElement() && reader.name() == QStringLiteral("Resource")) {
                break;
            }
            reader.readNext();
        }
    }

    if (resource) {
        resource->setId(id);
        resource->setOrientation(orientation);
        resource->setParts(parts);
        resource->setAmountPool(amountPool);
    }

    return resource;
}

Resource::Resource(const QString &id) : Resource(*new ResourcePrivate, id)
{}

Resource::Resource(ResourcePrivate &dd, const QString &id) : XJdfAbstractNode(dd)
{
    setId(id);
}

void Resource::addResourceCreator(const QString &name,
                                  std::function<ResourceSP(QXmlStreamReader &, const XJdfDocumentSP &)> &&creator)
{
    if (!ResourcePrivate::creators)
        ResourcePrivate::creators =
            new QMap<QString, std::function<ResourceSP(QXmlStreamReader &, const XJdfDocumentSP &)>>();
    (*ResourcePrivate::creators)[name] = creator;
}

void Resource::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    ResourceSP castedOther = qSharedPointerCast<Resource>(other);
    setId(castedOther->id());
    setParts(castedOther->parts());
    setAmountPool(castedOther->amountPool());

    XJdfAbstractNode::updateSelf(other);
}
std::function<ResourceSP(QXmlStreamReader &, const XJdfDocumentSP &)> &Resource::resourceCreator(const QString &name)
{
    return (*ResourcePrivate::creators)[name];
}
