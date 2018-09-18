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
#include "proofnetwork/jdf/data/qmlwrappers/cuttingparamsqmlwrapper.h"

#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"
#include "proofnetwork/jdf/data/qmlwrappers/cutblockqmlwrapper.h"

namespace Proof {
namespace Jdf {
class CuttingParamsQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CuttingParamsQmlWrapper)
    void updateCutBlocks();
    void updateParts();

    static CutBlockQmlWrapper *cutBlockAt(QQmlListProperty<CutBlockQmlWrapper> *property, int index);
    static int cutBlocksCount(QQmlListProperty<CutBlockQmlWrapper> *property);

    static CuttingParamsQmlWrapper *partAt(QQmlListProperty<CuttingParamsQmlWrapper> *property, int index);
    static int partsCount(QQmlListProperty<CuttingParamsQmlWrapper> *property);

    QVector<CutBlockQmlWrapper *> cutBlocks;
    QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper> qmlCutBlocksList;

    QVector<CuttingParamsQmlWrapper *> parts;
    QQmlListProperty<Proof::Jdf::CuttingParamsQmlWrapper> qmlPartsList;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

CuttingParamsQmlWrapper::CuttingParamsQmlWrapper(const CuttingParamsSP &cuttingParams, QObject *parent)
    : AbstractResourceQmlWrapper(cuttingParams, *new CuttingParamsQmlWrapperPrivate, parent)
{
    setupEntity();
}

CuttingParamsQmlWrapper::~CuttingParamsQmlWrapper()
{}

QQmlListProperty<CutBlockQmlWrapper> CuttingParamsQmlWrapper::cutBlocks()
{
    Q_D(CuttingParamsQmlWrapper);
    return d->qmlCutBlocksList;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(CuttingParams)

QQmlListProperty<CuttingParamsQmlWrapper> CuttingParamsQmlWrapper::parts()
{
    Q_D(CuttingParamsQmlWrapper);
    return d->qmlPartsList;
}

void CuttingParamsQmlWrapperPrivate::updateParts()
{
    Q_Q(CuttingParamsQmlWrapper);
    CuttingParamsSP cuttingParams = q->entity<CuttingParams>();
    for (CuttingParamsQmlWrapper *wrapper : qAsConst(parts))
        wrapper->deleteLater();

    parts.clear();
    const auto ndeParts = cuttingParams->parts();
    for (const CuttingParamsSP &part : ndeParts)
        parts << part->toQmlWrapper(q);

    qmlPartsList = QQmlListProperty<Proof::Jdf::CuttingParamsQmlWrapper>(q, &parts,
                                                                         &CuttingParamsQmlWrapperPrivate::partsCount,
                                                                         &CuttingParamsQmlWrapperPrivate::partAt);
    emit q->partsChanged(qmlPartsList);
}

CuttingParamsQmlWrapper *CuttingParamsQmlWrapperPrivate::partAt(QQmlListProperty<CuttingParamsQmlWrapper> *property,
                                                                int index)
{
    return static_cast<QVector<CuttingParamsQmlWrapper *> *>(property->data)->at(index);
}

int CuttingParamsQmlWrapperPrivate::partsCount(QQmlListProperty<CuttingParamsQmlWrapper> *property)
{
    return static_cast<QVector<CuttingParamsQmlWrapper *> *>(property->data)->count();
}

void CuttingParamsQmlWrapperPrivate::updateCutBlocks()
{
    Q_Q(CuttingParamsQmlWrapper);
    CuttingParamsSP cuttingParam = q->entity<CuttingParams>();
    for (CutBlockQmlWrapper *wrapper : qAsConst(cutBlocks))
        wrapper->deleteLater();

    cutBlocks.clear();
    const auto ndeBlocks = cuttingParam->cutBlocks();
    for (const CutBlockSP &cutBlock : ndeBlocks)
        cutBlocks << cutBlock->toQmlWrapper(q);

    qmlCutBlocksList = QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>(q, &cutBlocks,
                                                                        &CuttingParamsQmlWrapperPrivate::cutBlocksCount,
                                                                        &CuttingParamsQmlWrapperPrivate::cutBlockAt);
    emit q->cutBlocksChanged(qmlCutBlocksList);
}

CutBlockQmlWrapper *CuttingParamsQmlWrapperPrivate::cutBlockAt(QQmlListProperty<CutBlockQmlWrapper> *property, int index)
{
    return static_cast<QVector<CutBlockQmlWrapper *> *>(property->data)->at(index);
}

int CuttingParamsQmlWrapperPrivate::cutBlocksCount(QQmlListProperty<CutBlockQmlWrapper> *property)
{
    return static_cast<QVector<CutBlockQmlWrapper *> *>(property->data)->count();
}

void CuttingParamsQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(CuttingParamsQmlWrapper);
    CuttingParamsSP cuttingParams = entity<CuttingParams>();
    Q_ASSERT(cuttingParams);

    connect(cuttingParams.data(), &CuttingParams::cutBlocksChanged, entityConnectContext(),
            [d]() { d->updateCutBlocks(); });
    connect(cuttingParams.data(), &CuttingParams::partsChanged, entityConnectContext(), [d]() { d->updateParts(); });

    d->updateCutBlocks();
    d->updateParts();

    CuttingParamsSP oldCuttingParams = qSharedPointerCast<CuttingParams>(old);
    if (oldCuttingParams) {
        bool equal = cuttingParams->cutBlocks().count() == oldCuttingParams->cutBlocks().count();
        for (int i = 0; equal && i < cuttingParams->cutBlocks().count(); ++i) {
            if (oldCuttingParams->cutBlocks()[i]->blockName() != cuttingParams->cutBlocks()[i]->blockName())
                equal = false;
        }
        if (!equal)
            emit cutBlocksChanged(cuttingParams->toQmlWrapper()->cutBlocks());
    }
}
