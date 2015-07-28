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

    QList<CutBlockSP> cutBlocks;
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

CuttingParamsSP CuttingParams::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId)
{
    CuttingParamsSP cuttingParams = create();

    QList<CutBlockSP> cutBlocks;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "CuttingParams" && xmlReader.isStartElement() && !cuttingParams->isFetched()) {
            cuttingParams->setFetched(true);

            AbstractResourceSP castedCuttingParams = qSharedPointerCast<AbstractResource>(cuttingParams);
            AbstractResource::fromJdf(xmlReader, castedCuttingParams);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "CutBlock") {
                CutBlockSP cutBlock = CutBlock::fromJdf(xmlReader, jobId);
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


void CuttingParamsPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(CuttingParams);
    CuttingParamsSP castedOther = qSharedPointerCast<CuttingParams>(other);
    q->updateCutBlocks(castedOther->cutBlocks());

    AbstractResourcePrivate::updateFrom(other);
}
