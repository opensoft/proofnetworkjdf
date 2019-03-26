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
#include "proofnetwork/xjdf/data/graybox.h"

#include "proofnetwork/xjdf/data/graybox_p.h"
#include "proofnetwork/xjdf/data/resourceset.h"

using namespace Proof;
using namespace Proof::XJdf;

QVector<ProcessType> GrayBox::types() const
{
    Q_D_CONST(GrayBox);
    return d->types;
}

QVector<ResourceSetSP> GrayBox::resourceSets() const
{
    Q_D_CONST(GrayBox);
    return d->resourceSets;
}

void GrayBox::setTypes(const QVector<ProcessType> &arg)
{
    Q_D(GrayBox);
    if (arg != d->types) {
        d->types = arg;
        emit typesChanged(arg);
    }
}

void GrayBox::setResourceSets(const QVector<ResourceSetSP> &arg)
{
    Q_D(GrayBox);
    if (arg != d->resourceSets) {
        d->resourceSets = arg;
        emit resourceSetsChanged(arg);
    }
}

void GrayBox::addResourceSet(const ResourceSetSP &arg)
{
    Q_D(GrayBox);
    d->resourceSets.append(arg);
    emit resourceSetsChanged(d->resourceSets);
}

bool GrayBox::fillFromXJdf(QXmlStreamReader &reader)
{
    if (reader.isStartElement() && reader.name() == QStringLiteral("ResourceSet")) {
        auto resourceSet = ResourceSet::fromXJdf(reader);
        if (resourceSet)
            addResourceSet(resourceSet);
        return true;
    }
    return false;
}

void GrayBox::readAttributesFromXJdf(QXmlStreamReader &reader)
{
    auto types = reader.attributes().value(QStringLiteral("Types")).toString().split(' ');
    setTypes(algorithms::map(types, [](const auto &type) { return processTypeFromString(type); }, QVector<ProcessType>()));
}

void GrayBox::toXJdf(QXmlStreamWriter &writer, bool) const
{
    Q_D_CONST(GrayBox);
    QStringList types = algorithms::map(d->types, [](ProcessType type) { return processTypeToString(type); },
                                        QStringList());
    writer.writeAttribute(QStringLiteral("Types"), types.join(' '));
    for (const auto &set : d->resourceSets)
        set->toXJdf(writer);
}

GrayBox::GrayBox() : GrayBox(*new GrayBoxPrivate)
{}

GrayBox::GrayBox(GrayBoxPrivate &dd) : XJdfAbstractNode(dd)
{}

void GrayBox::updateSelf(const NetworkDataEntitySP &other)
{
    GrayBoxSP castedOther = qSharedPointerCast<GrayBox>(other);
    setTypes(castedOther->types());
    setResourceSets(castedOther->resourceSets());
    XJdfAbstractNode::updateSelf(other);
}
