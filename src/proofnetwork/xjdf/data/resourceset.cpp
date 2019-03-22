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
    QVector<ResourceSP> resources;
};

ObjectsCache<QString, ResourceSet> &cuttingProcessCache()
{
    return WeakObjectsCache<QString, ResourceSet>::instance();
}

} // namespace XJdf
} // namespace Proof

using namespace Proof::XJdf;

ResourceSet::ResourceSet() : XJdfAbstractNode(*new ResourceSetPrivate)
{}

QVector<ResourceSP> ResourceSet::resources() const
{
    Q_D_CONST(ResourceSet);
    return d->resources;
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
        } else if (xjdfReader.isStartElement()) {
            if (xjdfReader.name() == "Resource") {
                ResourceSP resource = Resource::fromXJdf(xjdfReader);
                if (!resource) {
                    qCWarning(proofNetworkXJdfDataLog) << "ResourcePool not created. Component is invalid.";
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

void ResourceSet::toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd) const
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
        emit resourcesChanged();
    }
}

void ResourceSet::addResource(const ResourceSP &arg)
{
    Q_D(ResourceSet);
    if (!arg)
        return;
    d->resources << arg;
    emit resourcesChanged();
}

void ResourceSet::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    ResourceSetSP castedOther = qSharedPointerCast<ResourceSet>(other);
    setResources(castedOther->resources());

    XJdfAbstractNode::updateSelf(other);
}
