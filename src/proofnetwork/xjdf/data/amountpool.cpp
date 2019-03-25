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
#include "proofnetwork/xjdf/data/amountpool.h"

#include "proofnetwork/xjdf/data/partamount.h"
#include "proofnetwork/xjdf/data/xjdfabstractnode_p.h"

namespace Proof {
namespace XJdf {
class AmountPoolPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(AmountPool)

public:
    AmountPoolPrivate() = default;

    QVector<PartAmountSP> parts;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QVector<PartAmountSP> AmountPool::parts() const
{
    Q_D_CONST(AmountPool);
    return d->parts;
}

void AmountPool::setParts(const QVector<PartAmountSP> &arg)
{
    Q_D(AmountPool);
    bool emitNeeded = arg.count() != d->parts.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->amount() != d->parts[i]->amount();
    if (emitNeeded) {
        d->parts = arg;
        emit partsChanged(d->parts);
    }
}

AmountPoolSP AmountPool::create()
{
    AmountPoolSP result(new AmountPool());
    initSelfWeakPtr(result);
    return result;
}

AmountPoolSP AmountPool::fromXJdf(QXmlStreamReader &xjdfReader)
{
    AmountPoolSP pool;
    if (xjdfReader.isStartElement() && xjdfReader.name() == "AmountPool") {
        pool = create();
        QVector<PartAmountSP> parts;
        while (!xjdfReader.atEnd() && !xjdfReader.hasError()) {
            if (xjdfReader.isStartElement() && xjdfReader.name() == "PartAmount") {
                parts << PartAmount::fromXJdf(xjdfReader);
            } else if (xjdfReader.isEndElement() && xjdfReader.name() == "AmountPool") {
                break;
            }
            xjdfReader.readNext();
        }
        pool->setParts(parts);
        pool->setFetched(true);
    }
    return pool;
}

void AmountPool::toXJdf(QXmlStreamWriter &xjdfWriter, bool) const
{
    Q_D_CONST(AmountPool);
    xjdfWriter.writeStartElement(QStringLiteral("AmountPool"));
    for (const auto &part : d->parts)
        part->toXJdf(xjdfWriter);
    xjdfWriter.writeEndElement();
}

AmountPool::AmountPool() : XJdfAbstractNode(*new AmountPoolPrivate)
{}

void AmountPool::updateSelf(const NetworkDataEntitySP &other)
{
    AmountPoolSP castedOther = qSharedPointerCast<AmountPool>(other);
    setParts(castedOther->parts());

    XJdfAbstractNode::updateSelf(other);
}
