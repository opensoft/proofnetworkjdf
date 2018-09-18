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
#include "proofnetwork/jdf/data/abstractphysicalresourcelink.h"

#include "proofnetwork/jdf/data/abstractphysicalresourcelink_p.h"

namespace Proof {
namespace Jdf {

AbstractPhysicalResourceLink::AbstractPhysicalResourceLink(AbstractPhysicalResourceLinkPrivate &dd)
    : AbstractResourceLink(dd)
{}

ResourceOrientation AbstractPhysicalResourceLink::orientation() const
{
    Q_D_CONST(AbstractPhysicalResourceLink);
    return d->orientation;
}

double AbstractPhysicalResourceLink::amount() const
{
    Q_D_CONST(AbstractPhysicalResourceLink);
    return d->amount;
}

void AbstractPhysicalResourceLink::setOrientation(ResourceOrientation arg)
{
    Q_D(AbstractPhysicalResourceLink);
    if (d->orientation != arg) {
        d->orientation = arg;
        emit orientationChanged(arg);
    }
}

void AbstractPhysicalResourceLink::setAmount(double arg)
{
    Q_D(AbstractPhysicalResourceLink);
    if (d->amount != arg) {
        d->amount = arg;
        emit amountChanged(d->amount);
    }
}

bool AbstractPhysicalResourceLink::fromJdf(const QXmlStreamReader &xmlReader,
                                           const AbstractPhysicalResourceLinkSP &resource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString value = attributes.value(QStringLiteral("Orientation")).toString();
    resource->setOrientation(resourceOrientationFromString(value));
    resource->setAmount(attributes.value(QStringLiteral("Amount")).toDouble());

    return AbstractResourceLink::fromJdf(xmlReader, resource);
}

void AbstractPhysicalResourceLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractPhysicalResourceLink);
    if (d->orientation != ResourceOrientation::Rotate0Orientation)
        jdfWriter.writeAttribute(QStringLiteral("Orientation"), resourceOrientationToString(d->orientation));
    if (d->amount != 0)
        jdfWriter.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount, 'f', 4));
    AbstractResourceLink::toJdf(jdfWriter);
}

void AbstractPhysicalResourceLink::updateSelf(const NetworkDataEntitySP &other)
{
    AbstractPhysicalResourceLinkSP castedOther = qSharedPointerCast<AbstractPhysicalResourceLink>(other);
    setOrientation(castedOther->orientation());
    setAmount(castedOther->amount());

    AbstractResourceLink::updateSelf(other);
}

} // namespace Jdf
} // namespace Proof
