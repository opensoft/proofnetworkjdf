#include "cuttingparams.h"

#include "cutblock.h"
#include "proofnetwork/jdf/data/abstractresource_p.h"

namespace Proof {
namespace Jdf {

class CuttingParamsPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(CuttingParams)

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
    setResourceClass(ApiHelper::ParameterClass);
}

QList<CutBlockSP> CuttingParams::cutBlocks() const
{
    Q_D(const CuttingParams);
    return d->cutBlocks;
}

void CuttingParams::updateFrom(const NetworkDataEntitySP &other)
{
    CuttingParamsSP castedOther = qSharedPointerCast<CuttingParams>(other);
    updateCutBlocks(castedOther->cutBlocks());

    AbstractResource::updateFrom(other);
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
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

CuttingParamsSP CuttingParams::fromJdf(QXmlStreamReader &xmlReader)
{
    CuttingParamsSP cuttingParams = create();
    cuttingParams->setFetched(true);

    while (xmlReader.name() != "CuttingParams" && !xmlReader.atEnd() && !xmlReader.hasError())
        xmlReader.readNext();

    AbstractResourceSP castedCuttingParams = qSharedPointerCast<AbstractResource>(cuttingParams);
    AbstractResource::fromJdf(xmlReader, castedCuttingParams);

    uint elementsCounter = 1;
    QList<CutBlockSP> cutBlocks;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            ++elementsCounter;
            if (xmlReader.name() == "CutBlock") {
                CutBlockSP cutBlock = CutBlock::fromJdf(xmlReader);
                cutBlocks.append(cutBlock);
            }
        }
        if (token == QXmlStreamReader::EndElement) {
            --elementsCounter;
            if (elementsCounter == 0)
                break;
        }
    }
    cuttingParams->updateCutBlocks(cutBlocks);

    return cuttingParams;
}

void CuttingParams::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(CuttingParams);

    jdfWriter.writeStartElement("CuttingParams");

    AbstractResource::toJdf(jdfWriter);

    for (const CutBlockSP &cutBlock : d->cutBlocks)
        cutBlock->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

CuttingParamsSP CuttingParams::defaultObject()
{
    static CuttingParamsSP entity = create();
    return entity;
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
