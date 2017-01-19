#include "cuttingparams.h"

#include "cutblock.h"
#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"

namespace Proof {
namespace Jdf {

class CuttingParamsPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(CuttingParams)

    CuttingParamsPrivate()
        : AbstractResourcePrivate(ApiHelper::ResourceClass::ParameterClass)
    {
        registerChildren(cutBlocks);
    }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    bool partsAreValid(QList<ApiHelper::ResourcePartType> partsToCheck = QList<ApiHelper::ResourcePartType>()) const;

    QList<CutBlockSP> cutBlocks;
    QList<CuttingParamsSP> parts;
};

ObjectsCache<QString, CuttingParams> &cuttingParamsCache()
{
    return WeakObjectsCache<QString, CuttingParams>::instance();
}

}
}

using namespace Proof::Jdf;

CuttingParams::CuttingParams()
    : AbstractResource(*new CuttingParamsPrivate)
{
}

QList<CutBlockSP> CuttingParams::cutBlocks() const
{
    Q_D(const CuttingParams);
    return d->cutBlocks;
}

QList<CuttingParamsSP> CuttingParams::parts() const
{
    Q_D(const CuttingParams);
    return d->parts;
}

CuttingParamsQmlWrapper *CuttingParams::toQmlWrapper(QObject *parent) const
{
    Q_D(const CuttingParams);
    CuttingParamsSP castedSelf = qSharedPointerCast<CuttingParams>(d->weakSelf);
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

    QList<CutBlockSP> cutBlocks;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "CuttingParams" && xmlReader.isStartElement() && !cuttingParams->isFetched()) {
            cuttingParams->setFetched(true);

            AbstractResourceSP castedCuttingParams = qSharedPointerCast<AbstractResource>(cuttingParams);
            AbstractResource::fromJdf(xmlReader, castedCuttingParams);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "CuttingParams") {
                CuttingParamsSP part = CuttingParams::fromJdf(xmlReader, jobId, sanitize);
                if (!part) {
                    qCCritical(proofNetworkJdfDataLog) << "CuttingParams not created. Part is not valid";
                    return CuttingParamsSP();
                }
                cuttingParams->addPart(part);
            } else if (xmlReader.name() == "CutBlock") {
                CutBlockSP cutBlock = CutBlock::fromJdf(xmlReader, jobId, sanitize);
                if (!cutBlock) {
                    qCCritical(proofNetworkJdfDataLog) << "CuttingParams not created. Invalid CutBlock found";
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
        qCCritical(proofNetworkJdfDataLog) << "CuttingParams not created. Partioning is not valid";
        return CuttingParamsSP();
    }

    cuttingParams->updateCutBlocks(cutBlocks);

    return cuttingParams;
}

void CuttingParams::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(CuttingParams);

    jdfWriter.writeStartElement("CuttingParams");

    AbstractResource::toJdf(jdfWriter);

    for (const CutBlockSP &cutBlock : d->cutBlocks) {
        if (cutBlock->isDirty())
            cutBlock->toJdf(jdfWriter);
    }
    for (const auto &part : d->parts) {
        if (part->isDirty())
            part->toJdf(jdfWriter);
    }

    jdfWriter.writeEndElement();
}

CuttingParamsLinkSP CuttingParams::toLink(ApiHelper::Usage usage) const
{
    CuttingParamsLinkSP link = CuttingParamsLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

QList<CutBlockSP> CuttingParams::updateCutBlocks(const QList<CutBlockSP> &arg)
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

QList<CuttingParamsSP> CuttingParams::updateParts(const QList<CuttingParamsSP> &arg)
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


void CuttingParamsPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(CuttingParams);
    CuttingParamsSP castedOther = qSharedPointerCast<CuttingParams>(other);
    q->updateCutBlocks(castedOther->cutBlocks());

    AbstractResourcePrivate::updateFrom(other);
}

bool CuttingParamsPrivate::partsAreValid(QList<ApiHelper::ResourcePartType> partsToCheck) const
{
    if (partsToCheck.isEmpty() && !partIdKeys.isEmpty())
        partsToCheck = partIdKeys;
    if (partsToCheck.isEmpty()) {
        if (parts.count())
            qCCritical(proofNetworkJdfDataLog) << "CuttingParams partioning is not valid. Extra parts found";
        return parts.isEmpty();
    }

    auto currentPart = partsToCheck.takeFirst();

    for (const auto &part : parts) {
        if (!part->hasPartAttribute(currentPart)) {
            qCCritical(proofNetworkJdfDataLog) << "CuttingParams partioning is not valid. Part" << ApiHelper::resourcePartTypeToString(currentPart) << "not found";
            return false;
        }
        if (!part->d_func()->partsAreValid(partsToCheck))
            return false;
    }
    return true;
}
