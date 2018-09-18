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
#include "proofnetwork/jdf/data/abstractresource.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"

using namespace Proof::Jdf;

QString AbstractResource::id() const
{
    Q_D_CONST(AbstractResource);
    return d->id;
}

ResourceStatus AbstractResource::resourceStatus() const
{
    Q_D_CONST(AbstractResource);
    return d->resourceStatus;
}

ResourceClass AbstractResource::resourceClass() const
{
    Q_D_CONST(AbstractResource);
    return d->resourceClass;
}

QVector<ResourcePartType> AbstractResource::partIdKeys() const
{
    Q_D_CONST(AbstractResource);
    return d->partIdKeys;
}

void AbstractResource::setId(const QString &arg)
{
    Q_D(AbstractResource);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void AbstractResource::setResourceStatus(ResourceStatus arg)
{
    Q_D(AbstractResource);
    if (d->resourceStatus != arg) {
        d->resourceStatus = arg;
        emit statusChanged(d->resourceStatus);
    }
}

void AbstractResource::setResourceClass(ResourceClass arg)
{
    Q_D(AbstractResource);
    if (d->resourceClass != arg) {
        d->resourceClass = arg;
        emit resourceClassChanged(d->resourceClass);
    }
}

void AbstractResource::setPartIdKeys(const QVector<ResourcePartType> &arg)
{
    Q_D(AbstractResource);
    if (d->partIdKeys != arg) {
        d->partIdKeys = arg;
        emit partIdKeysChanged(d->partIdKeys);
    }
}

QString AbstractResource::partAttribute(ResourcePartType attribute) const
{
    Q_D_CONST(AbstractResource);
    return d->partAttributes.value(attribute, QString());
}

bool AbstractResource::hasPartAttribute(ResourcePartType attribute) const
{
    Q_D_CONST(AbstractResource);
    return d->partAttributes.contains(attribute);
}

void AbstractResource::setPartAttribute(ResourcePartType attribute, const QString &value)
{
    Q_D(AbstractResource);
    d->partAttributes[attribute] = value;
    emit partAttributeChanged(attribute, value);
}

bool AbstractResource::fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    QStringList partIdKeysStringified =
        attributes.value(QStringLiteral("PartIDKeys")).toString().split(QStringLiteral(" "), QString::SkipEmptyParts);
    QVector<ResourcePartType> partIdKeys;
    for (const QString &partName : partIdKeysStringified) {
        bool ok = false;
        ResourcePartType part = resourcePartTypeFromString(partName, &ok);
        if (!ok)
            return false;
        partIdKeys << part;
    }
    abstractResource->setPartIdKeys(partIdKeys);
    abstractResource->setId(attributes.value(QStringLiteral("ID")).toString());
    abstractResource->setResourceStatus(resourceStatusFromString(attributes.value(QStringLiteral("Status")).toString()));

    for (const auto &attribute : attributes) {
        bool isPartAttribute = false;
        auto part = resourcePartTypeFromString(attribute.name().toString(), &isPartAttribute);
        if (!isPartAttribute)
            continue;
        abstractResource->setPartAttribute(part, attribute.value().toString());
    }

    return true;
}

void AbstractResource::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResource);
    if (!d->id.isEmpty())
        jdfWriter.writeAttribute(QStringLiteral("ID"), d->id);
    if (d->resourceStatus != ResourceStatus::NoStatus)
        jdfWriter.writeAttribute(QStringLiteral("Status"), resourceStatusToString(d->resourceStatus));
    if (d->resourceClass != ResourceClass::NoClass)
        jdfWriter.writeAttribute(QStringLiteral("Class"), resourceClassToString(d->resourceClass));
    const auto partIdKeysStringified = algorithms::map(d->partIdKeys,
                                                       [](auto part) { return resourcePartTypeToString(part); },
                                                       QStringList());
    if (partIdKeysStringified.count())
        jdfWriter.writeAttribute(QStringLiteral("PartIDKeys"), partIdKeysStringified.join(QStringLiteral(" ")));
    for (auto it = d->partAttributes.cbegin(); it != d->partAttributes.cend(); ++it)
        jdfWriter.writeAttribute(resourcePartTypeToString(it.key()), it.value());
}

void AbstractResource::refToJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResource);
    jdfWriter.writeStartElement(jdfNodeRefName());
    jdfWriter.writeAttribute(QStringLiteral("rRef"), d->id);
    jdfWriter.writeEndElement();
}

QString AbstractResource::jdfNodeName() const
{
    Q_D_CONST(AbstractResource);
    if (d->jdfNodeName.isEmpty())
        d->jdfNodeName = QString(metaObject()->className())
                             .remove(0, QString(metaObject()->className()).lastIndexOf(QLatin1String(":")) + 1);
    return d->jdfNodeName;
}

QString AbstractResource::jdfNodeRefName() const
{
    Q_D_CONST(AbstractResource);
    if (d->jdfNodeRefName.isEmpty())
        d->jdfNodeRefName = QStringLiteral("%1Ref").arg(jdfNodeName());
    return d->jdfNodeRefName;
}

AbstractResource::AbstractResource(AbstractResourcePrivate &dd) : NetworkDataEntity(dd)
{}

void AbstractResource::setupLink(const AbstractResourceLinkSP &abstractLink, LinkUsage usage) const
{
    abstractLink->setRRef(id());
    abstractLink->setUsage(usage);
}

void AbstractResource::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AbstractResourceSP castedOther = qSharedPointerCast<AbstractResource>(other);
    setId(castedOther->id());
    setResourceStatus(castedOther->resourceStatus());
    setResourceClass(castedOther->resourceClass());
    setPartIdKeys(castedOther->partIdKeys());

    NetworkDataEntity::updateSelf(other);
}
