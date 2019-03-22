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
#include "proofnetwork/xjdf/data/partamount.h"

#include "proofnetwork/xjdf/data/xjdfabstractnode_p.h"

namespace Proof {
namespace XJdf {
class PartAmountPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(PartAmount)

public:
    PartAmountPrivate() = default;

    qulonglong amount = 0;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

qulonglong PartAmount::amount() const
{
    Q_D_CONST(PartAmount);
    return d->amount;
}

void PartAmount::setAmount(qulonglong arg)
{
    Q_D(PartAmount);
    if (arg != d->amount) {
        d->amount = arg;
        emit amountChanged(arg);
    }
}

PartAmountSP PartAmount::create()
{
    PartAmountSP result(new PartAmount());
    initSelfWeakPtr(result);
    return result;
}

PartAmountSP PartAmount::fromXJdf(QXmlStreamReader &xjdfReader)
{
    PartAmountSP part;
    if (xjdfReader.isStartElement() && xjdfReader.name() == "PartAmount") {
        part = create();
        part->setFetched(true);
        auto attributes = xjdfReader.attributes();
        if (attributes.hasAttribute(QStringLiteral("Amount")))
            part->setAmount(attributes.value(QStringLiteral("Amount")).toULongLong());
    }
    xjdfReader.skipCurrentElement();
    return part;
}

void PartAmount::toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd) const
{
    Q_D_CONST(PartAmount);
    xjdfWriter.writeStartElement(QStringLiteral("PartAmount"));
    xjdfWriter.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount));
    xjdfWriter.writeEndElement();
}

PartAmount::PartAmount() : XJdfAbstractNode(*new PartAmountPrivate)
{}

void PartAmount::updateSelf(const NetworkDataEntitySP &other)
{
    PartAmountSP castedOther = qSharedPointerCast<PartAmount>(other);
    setAmount(castedOther->amount());
    XJdfAbstractNode::updateSelf(other);
}
