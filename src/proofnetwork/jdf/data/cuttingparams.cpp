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
#include "proofnetwork/jdf/data/cuttingparams.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"

namespace Proof {
namespace Jdf {

class CuttingParamsPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(CuttingParams)

    CuttingParamsPrivate() : AbstractResourcePrivate(ResourceClass::ParameterClass) { registerChildren(cutBlocks); }

    bool partsAreValid(QVector<ResourcePartType> partsToCheck = QVector<ResourcePartType>()) const;

    QVector<CutBlockSP> cutBlocks;
    QVector<CuttingParamsSP> parts;
};

ObjectsCache<QString, CuttingParams> &cuttingParamsCache()
{
    return WeakObjectsCache<QString, CuttingParams>::instance();
}

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

CuttingParams::CuttingParams() : AbstractResource(*new CuttingParamsPrivate)
{}

QVector<CutBlockSP> CuttingParams::cutBlocks() const
{
    Q_D_CONST(CuttingParams);
    return d->cutBlocks;
}

QVector<CuttingParamsSP> CuttingParams::parts() const
{
    Q_D_CONST(CuttingParams);
    return d->parts;
}

CuttingParamsQmlWrapper *CuttingParams::toQmlWrapper(QObject *parent) const
{
    CuttingParamsSP castedSelf = castedSelfPtr<CuttingParams>();
    Q_ASSERT(castedSelf);
    return new CuttingParamsQmlWrapper(castedSelf, parent);
}

CuttingParamsSP CuttingParams::create()
{
    CuttingParamsSP result(new CuttingParams());
    initSelfWeakPtr(result);
    return result;
}

CuttingParamsSP CuttingParams::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    CuttingParamsSP cuttingParams = create();

    QVector<CutBlockSP> cutBlocks;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "CuttingParams" && xmlReader.isStartElement() && !cuttingParams->isFetched()) {
            cuttingParams->setFetched(true);

            AbstractResourceSP castedCuttingParams = qSharedPointerCast<AbstractResource>(cuttingParams);
            AbstractResource::fromJdf(xmlReader, castedCuttingParams);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "CuttingParams") {
                CuttingParamsSP part = CuttingParams::fromJdf(xmlReader, jobId, sanitize);
                if (!part) {
                    qCWarning(proofNetworkJdfDataLog) << "CuttingParams not created. Part is not valid";
                    return CuttingParamsSP();
                }
                cuttingParams->addPart(part);
            } else if (xmlReader.name() == "CutBlock") {
                CutBlockSP cutBlock = CutBlock::fromJdf(xmlReader, jobId, sanitize);
                if (!cutBlock) {
                    qCWarning(proofNetworkJdfDataLog) << "CuttingParams not created. Invalid CutBlock found";
                    return CuttingParamsSP();
                }
                cutBlocks.append(cutBlock);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    if (cuttingParams->d_func()->partIdKeys.count() && !cuttingParams->d_func()->partsAreValid()) {
        qCWarning(proofNetworkJdfDataLog) << "CuttingParams not created. Partioning is not valid";
        return CuttingParamsSP();
    }

    cuttingParams->updateCutBlocks(cutBlocks);

    return cuttingParams;
}

void CuttingParams::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(CuttingParams);

    jdfWriter.writeStartElement(QStringLiteral("CuttingParams"));

    AbstractResource::toJdf(jdfWriter);

    for (const CutBlockSP &cutBlock : qAsConst(d->cutBlocks)) {
        if (cutBlock->isDirty())
            cutBlock->toJdf(jdfWriter);
    }
    for (const auto &part : qAsConst(d->parts)) {
        if (part->isDirty())
            part->toJdf(jdfWriter);
    }

    jdfWriter.writeEndElement();
}

CuttingParamsLinkSP CuttingParams::toLink(LinkUsage usage) const
{
    CuttingParamsLinkSP link = CuttingParamsLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

QVector<CutBlockSP> CuttingParams::updateCutBlocks(const QVector<CutBlockSP> &arg)
{
    Q_D(CuttingParams);
    bool emitNeeded = arg.count() != d->cutBlocks.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->blockName() != d->cutBlocks[i]->blockName();
    if (emitNeeded) {
        d->cutBlocks = arg;
        emit cutBlocksChanged();
    }
    return d->cutBlocks;
}

QVector<CuttingParamsSP> CuttingParams::updateParts(const QVector<CuttingParamsSP> &arg)
{
    Q_D(CuttingParams);
    bool emitNeeded = arg.count() != d->parts.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->parts[i]->id();
    if (emitNeeded) {
        d->parts = arg;
        emit partsChanged();
    }
    return d->parts;
}

void CuttingParams::addPart(const CuttingParamsSP &arg)
{
    Q_D(CuttingParams);
    d->parts << arg;
    emit partsChanged();
}

void CuttingParams::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    CuttingParamsSP castedOther = qSharedPointerCast<CuttingParams>(other);
    updateCutBlocks(castedOther->cutBlocks());

    AbstractResource::updateSelf(other);
}

bool CuttingParamsPrivate::partsAreValid(QVector<ResourcePartType> partsToCheck) const
{
    if (partsToCheck.isEmpty() && !partIdKeys.isEmpty())
        partsToCheck = partIdKeys;
    if (partsToCheck.isEmpty()) {
        if (parts.count())
            qCWarning(proofNetworkJdfDataLog) << "CuttingParams partioning is not valid. Extra parts found";
        return parts.isEmpty();
    }

    auto currentPart = partsToCheck.takeFirst();

    for (const auto &part : parts) {
        if (!part->hasPartAttribute(currentPart)) {
            qCWarning(proofNetworkJdfDataLog) << "CuttingParams partioning is not valid. Part"
                                              << resourcePartTypeToString(currentPart) << "not found";
            return false;
        }
        if (!part->d_func()->partsAreValid(partsToCheck))
            return false;
    }
    return true;
}
