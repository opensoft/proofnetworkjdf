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
#include "proofnetwork/jdf/data/abstractphysicalresource.h"

#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"

using namespace Proof::Jdf;

double AbstractPhysicalResource::amount() const
{
    Q_D_CONST(AbstractPhysicalResource);
    return d->amount;
}

double AbstractPhysicalResource::resourceWeight() const
{
    Q_D_CONST(AbstractPhysicalResource);
    return d->resourceWeight;
}

void AbstractPhysicalResource::setAmount(double arg)
{
    Q_D(AbstractPhysicalResource);
    if (!qFuzzyCompare(d->amount, arg)) {
        d->amount = arg;
        emit amountChanged(d->amount);
    }
}

void AbstractPhysicalResource::setResourceWeight(double arg)
{
    Q_D(AbstractPhysicalResource);
    if (!qFuzzyCompare(d->resourceWeight, arg)) {
        d->resourceWeight = arg;
        emit resourceWeightChanged(d->resourceWeight);
    }
}

bool AbstractPhysicalResource::fromJdf(const QXmlStreamReader &xmlReader,
                                       AbstractPhysicalResourceSP &abstractPhysicalResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractPhysicalResource->setAmount(attributes.value(QStringLiteral("Amount")).toDouble());
    abstractPhysicalResource->setResourceWeight(attributes.value(QStringLiteral("ResourceWeight")).toDouble());

    AbstractResourceSP castedAbstractPhysicalResource = qSharedPointerCast<AbstractResource>(abstractPhysicalResource);
    return AbstractResource::fromJdf(xmlReader, castedAbstractPhysicalResource);
}

void AbstractPhysicalResource::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractPhysicalResource);
    if (!qFuzzyIsNull(d->amount))
        jdfWriter.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount, 'f', 4));
    if (!qFuzzyIsNull(d->resourceWeight))
        jdfWriter.writeAttribute(QStringLiteral("ResourceWeight"), QString::number(d->resourceWeight, 'f', 4));

    AbstractResource::toJdf(jdfWriter);
}

AbstractPhysicalResource::AbstractPhysicalResource(AbstractPhysicalResourcePrivate &dd) : AbstractResource(dd)
{}

void AbstractPhysicalResource::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AbstractPhysicalResourceSP castedOther = qSharedPointerCast<AbstractPhysicalResource>(other);
    setAmount(castedOther->amount());
    setResourceWeight(castedOther->resourceWeight());

    AbstractResource::updateSelf(other);
}
