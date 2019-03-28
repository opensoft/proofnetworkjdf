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
#include "proofnetwork/xjdf/data/resourceset.h"

#include "proofnetwork/xjdf/data/resource_p.h"

namespace Proof {
namespace XJdf {

class ResourceSetPrivate : public AbstractNodePrivate
{
    Q_DECLARE_PUBLIC(ResourceSet)
    ResourceSetPrivate() { registerChildren(resources); }

    QString name;
    QVector<qulonglong> combinedProcessIndexes;
    UsageType usage = UsageType::NoUsageType;
    QVector<ResourceSP> resources;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof::XJdf;

ResourceSet::ResourceSet() : AbstractNode(*new ResourceSetPrivate)
{}

QString ResourceSet::name() const
{
    Q_D_CONST(ResourceSet);
    return d->name;
}

QVector<qulonglong> ResourceSet::combinedProcessIndexes() const
{
    Q_D_CONST(ResourceSet);
    return d->combinedProcessIndexes;
}

UsageType ResourceSet::usage() const
{
    Q_D_CONST(ResourceSet);
    return d->usage;
}

QVector<ResourceSP> ResourceSet::resources() const
{
    Q_D_CONST(ResourceSet);
    return d->resources;
}

void ResourceSet::setName(const QString &arg)
{
    Q_D(ResourceSet);
    if (d->name != arg) {
        d->name = arg;
        emit nameChanged(arg);
    }
}

void ResourceSet::setCombinedProcessIndexes(const QVector<qulonglong> &arg)
{
    Q_D(ResourceSet);
    bool emitNeeded = arg.count() != d->combinedProcessIndexes.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i] != d->combinedProcessIndexes[i];
    if (emitNeeded) {
        d->combinedProcessIndexes = arg;
        emit combinedProcessIndexesChanged(d->combinedProcessIndexes);
    }
}

void ResourceSet::setUsage(UsageType arg)
{
    Q_D(ResourceSet);
    if (d->usage != arg) {
        d->usage = arg;
        emit usageChanged(arg);
    }
}

ResourceSetSP ResourceSet::create()
{
    ResourceSetSP result(new ResourceSet());
    initSelfWeakPtr(result);
    return result;
}

ResourceSetSP ResourceSet::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    ResourceSetSP resourceSet = create();
    resourceSet->d_func()->document = document;

    QVector<ResourceSP> resourceList;

    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.name() == QStringLiteral("ResourceSet") && reader.isStartElement() && !resourceSet->isFetched()) {
            resourceSet->setFetched(true);
            auto attributes = reader.attributes();
            if (attributes.hasAttribute(QStringLiteral("Name")))
                resourceSet->setName(attributes.value(QStringLiteral("Name")).toString());
            if (attributes.hasAttribute(QStringLiteral("Usage")))
                resourceSet->setUsage(usageTypeFromString(attributes.value(QStringLiteral("Usage")).toString()));
            if (attributes.hasAttribute(QStringLiteral("CombinedProcessIndex"))) {
                auto indexesString = attributes.value(QStringLiteral("CombinedProcessIndex")).toString();
                auto indexes = algorithms::map(indexesString.split(' '),
                                               [](const auto &index) { return index.toULongLong(); },
                                               QVector<qulonglong>());
                resourceSet->setCombinedProcessIndexes(indexes);
            }
        } else if (reader.isStartElement()) {
            if (reader.name() == QStringLiteral("Resource")) {
                ResourceSP resource = Resource::fromXJdf(reader, document);
                if (!resource) {
                    qCWarning(proofNetworkXJdfDataLog) << "ResourcSet not created. XML is invalid.";
                    return ResourceSetSP();
                }
                resourceList.append(resource);
            }
        } else if (reader.isEndElement()) {
            if (reader.name() == QStringLiteral("ResourceSet"))
                break;
        }
        reader.readNext();
    }

    resourceSet->setResources(resourceList);

    return resourceSet;
}

void ResourceSet::toXJdf(QXmlStreamWriter &writer, bool) const
{
    Q_D_CONST(ResourceSet);

    writer.writeStartElement(QStringLiteral("ResourceSet"));
    if (!d->name.isEmpty())
        writer.writeAttribute(QStringLiteral("Name"), d->name);
    if (!d->combinedProcessIndexes.isEmpty())
        writer.writeAttribute(QStringLiteral("CombinedProcessIndex"),
                              algorithms::map(d->combinedProcessIndexes,
                                              [](const auto &index) { return QString::number(index); }, QStringList())
                                  .join(' '));
    if (d->usage != UsageType::NoUsageType)
        writer.writeAttribute(QStringLiteral("Usage"), usageTypeToString(d->usage));

    for (const ResourceSP &resource : qAsConst(d->resources)) {
        if (isValidAndDirty(resource))
            resource->toXJdf(writer);
    }

    writer.writeEndElement();
}

void ResourceSet::setResources(const QVector<ResourceSP> &arg)
{
    Q_D(ResourceSet);
    bool emitNeeded = arg.count() != d->resources.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->resources[i]->id();
    if (emitNeeded) {
        d->resources = arg;
        emit resourcesChanged(d->resources);
    }
}

void ResourceSet::addResource(const ResourceSP &arg)
{
    Q_D(ResourceSet);
    if (!arg)
        return;
    d->resources << arg;
    emit resourcesChanged(d->resources);
}

void ResourceSet::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    ResourceSetSP castedOther = qSharedPointerCast<ResourceSet>(other);
    setResources(castedOther->resources());
    setName(castedOther->name());
    setCombinedProcessIndexes(castedOther->combinedProcessIndexes());
    setUsage(castedOther->usage());
    AbstractNode::updateSelf(other);
}
