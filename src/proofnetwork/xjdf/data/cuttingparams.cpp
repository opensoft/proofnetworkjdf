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
#include "proofnetwork/xjdf/data/cuttingparams.h"

#include "proofnetwork/xjdf/data/cutblock.h"
#include "proofnetwork/xjdf/data/resource_p.h"

namespace Proof {
namespace XJdf {

class CuttingParamsPrivate : public ResourcePrivate
{
    Q_DECLARE_PUBLIC(CuttingParams)
    CuttingParamsPrivate() {}

    QVector<CutBlockSP> blocks;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QVector<CutBlockSP> CuttingParams::cutBlocks() const
{
    Q_D_CONST(CuttingParams);
    return d->blocks;
}

void CuttingParams::setCutBlocks(const QVector<CutBlockSP> &arg)
{
    Q_D(CuttingParams);
    bool emitNeeded = arg.count() != d->blocks.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->blockName() != d->blocks[i]->blockName();
    if (emitNeeded) {
        d->blocks = arg;
        emit cutBlocksChanged(arg);
    }
}

CuttingParamsSP CuttingParams::create()
{
    CuttingParamsSP result(new CuttingParams());
    initSelfWeakPtr(result);
    return result;
}

CuttingParamsSP CuttingParams::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    CuttingParamsSP params;

    if (reader.isStartElement() && reader.name() == QStringLiteral("CuttingParams")) {
        params = create();
        params->d_func()->document = document;

        QVector<CutBlockSP> blocks;
        while (!reader.atEnd() && !reader.hasError()) {
            if (reader.isStartElement() && reader.name() == QStringLiteral("CutBlock")) {
                auto block = CutBlock::fromXJdf(reader, document);
                if (block)
                    blocks << block;
            } else if (reader.isEndElement() && reader.name() == QStringLiteral("CuttingParams")) {
                break;
            }
            reader.readNext();
        }
        params->setCutBlocks(blocks);
        params->setFetched(true);
    }
    return params;
}

void CuttingParams::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(CuttingParams);
    NodeWriterGuard guard(writeFieldsToXJdf(writer));
    writer.writeStartElement(QStringLiteral("CuttingParams"));
    for (const auto &block : d->blocks)
        block->toXJdf(writer);
    writer.writeEndElement();
}

CuttingParams::CuttingParams() : Resource(*new CuttingParamsPrivate)
{}

void CuttingParams::updateSelf(const NetworkDataEntitySP &other)
{
    CuttingParamsSP castedOther = qSharedPointerCast<CuttingParams>(other);
    setCutBlocks(castedOther->cutBlocks());
    Resource::updateSelf(other);
}
