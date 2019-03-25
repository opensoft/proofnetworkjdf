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
#include "proofnetwork/xjdf/data/resourceset.h"

#include "proofnetwork/xjdf/data/resource_p.h"

namespace Proof {
namespace XJdf {

class ResourceSetPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(ResourceSet)
    ResourceSetPrivate() { registerChildren(resources); }

    QString name;
    QVector<qulonglong> combinedProcessIndexes;
    UsageType usage;
    QVector<ResourceSP> resources;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof::XJdf;

ResourceSet::ResourceSet() : XJdfAbstractNode(*new ResourceSetPrivate)
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

ResourceSetSP ResourceSet::fromXJdf(QXmlStreamReader &xjdfReader)
{
    ResourceSetSP resourceSet = create();

    QVector<ResourceSP> resourceList;

    while (!xjdfReader.atEnd() && !xjdfReader.hasError()) {
        if (xjdfReader.name() == "ResourceSet" && xjdfReader.isStartElement() && !resourceSet->isFetched()) {
            resourceSet->setFetched(true);
            auto attributes = xjdfReader.attributes();
            if (attributes.hasAttribute("Name"))
                resourceSet->setName(attributes.value("Name").toString());
            if (attributes.hasAttribute("Usage"))
                resourceSet->setUsage(usageTypeFromString(attributes.value("Usage").toString()));
            if (attributes.hasAttribute("CombinedProcessIndex")) {
                auto indexesString = attributes.value("CombinedProcessIndex").toString();
                auto indexes = algorithms::map(indexesString.split(' '),
                                               [](const auto &index) { return index.toULongLong(); },
                                               QVector<qulonglong>());
                resourceSet->setCombinedProcessIndexes(indexes);
            }
        } else if (xjdfReader.isStartElement()) {
            if (xjdfReader.name() == "Resource") {
                ResourceSP resource = Resource::fromXJdf(xjdfReader);
                if (!resource) {
                    qCWarning(proofNetworkXJdfDataLog) << "ResourcSet not created. XML is invalid.";
                    return ResourceSetSP();
                }
                resourceList.append(resource);
            }
        } else if (xjdfReader.isEndElement()) {
            if (xjdfReader.name() == "ResourceSet")
                break;
        }
        xjdfReader.readNext();
    }

    resourceSet->setResources(resourceList);

    return resourceSet;
}

void ResourceSet::toXJdf(QXmlStreamWriter &xjdfWriter, bool) const
{
    Q_D_CONST(ResourceSet);

    xjdfWriter.writeStartElement(QStringLiteral("ResourceSet"));

    for (const ResourceSP &resource : qAsConst(d->resources)) {
        if (isValidAndDirty(resource))
            resource->toXJdf(xjdfWriter);
    }

    xjdfWriter.writeEndElement();
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

    XJdfAbstractNode::updateSelf(other);
}
