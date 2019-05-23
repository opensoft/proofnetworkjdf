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
#include "proofnetwork/jdf/data/qmlwrappers/cutblockqmlwrapper.h"

#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class CutBlockQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CutBlockQmlWrapper)
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

CutBlockQmlWrapper::CutBlockQmlWrapper(const CutBlockSP &cutBlock, QObject *parent)
    : NetworkDataEntityQmlWrapper(cutBlock, *new CutBlockQmlWrapperPrivate, parent)
{
    setupEntity(); // NOLINT
}

CutBlockQmlWrapper::~CutBlockQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(CutBlock)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, QString, blockName)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, double, width)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, double, height)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, Proof::Jdf::BlockType, blockType)

void CutBlockQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    CutBlockSP cutBlock = entity<CutBlock>();
    Q_ASSERT(cutBlock);

    connect(cutBlock.data(), &CutBlock::blockNameChanged, this, &CutBlockQmlWrapper::blockNameChanged);
    connect(cutBlock.data(), &CutBlock::widthChanged, this, &CutBlockQmlWrapper::widthChanged);
    connect(cutBlock.data(), &CutBlock::heightChanged, this, &CutBlockQmlWrapper::heightChanged);
    connect(cutBlock.data(), &CutBlock::blockTypeChanged, this, &CutBlockQmlWrapper::blockTypeChanged);

    CutBlockSP oldCutBlock = qSharedPointerCast<CutBlock>(old);
    if (oldCutBlock) {
        if (cutBlock->blockName() != oldCutBlock->blockName())
            emit blockNameChanged(cutBlock->blockName());
        if (cutBlock->width() != oldCutBlock->width())
            emit widthChanged(cutBlock->width());
        if (cutBlock->height() != oldCutBlock->height())
            emit heightChanged(cutBlock->height());
        if (cutBlock->blockType() != oldCutBlock->blockType())
            emit blockTypeChanged(cutBlock->blockType());
    }
}
