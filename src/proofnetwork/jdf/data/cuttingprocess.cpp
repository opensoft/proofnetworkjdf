#include "cuttingprocess.h"
#include "cutblock.h"
#include "media.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class CuttingProcessPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(CuttingProcess)

    QString id;
    double pressSheetWidth;
    double pressSheetHeight;
    QList<CutBlockSP> cutBlocks;
    MediaSP media;

};

ObjectsCache<QString, CuttingProcess> &cuttingProcessCache()
{
    return WeakObjectsCache<QString, CuttingProcess>::instance();
}

}
}

using namespace Proof::Jdf;

CuttingProcess::CuttingProcess()
    : NetworkDataEntity(*new CuttingProcessPrivate)
{
}

QString CuttingProcess::id() const
{
    Q_D(const CuttingProcess);
    return d->id;
}

double CuttingProcess::pressSheetWidth() const
{
    Q_D(const CuttingProcess);
    return d->pressSheetWidth;
}

double CuttingProcess::pressSheetHeight() const
{
    Q_D(const CuttingProcess);
    return d->pressSheetHeight;
}

QList<CutBlockSP> CuttingProcess::cutBlocks() const
{
    Q_D(const CuttingProcess);
    return d->cutBlocks;
}

MediaSP CuttingProcess::media() const
{
    Q_D(const CuttingProcess);
    return d->media;
}

void CuttingProcess::updateFrom(const NetworkDataEntitySP &other)
{
    CuttingProcessSP castedOther = qSharedPointerCast<CuttingProcess>(other);
    setId(castedOther->id());
    setPressSheetWidth(castedOther->pressSheetWidth());
    setPressSheetHeight(castedOther->pressSheetHeight());
    updateCutBlocks(castedOther->cutBlocks());
    setMedia(castedOther->media());

    NetworkDataEntity::updateFrom(other);
}

CuttingProcessQmlWrapper *CuttingProcess::toQmlWrapper(QObject *parent) const
{
    Q_D(const CuttingProcess);
    CuttingProcessSP castedSelf = qSharedPointerCast<CuttingProcess>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new CuttingProcessQmlWrapper(castedSelf, parent);
}

CuttingProcessSP CuttingProcess::create()
{
    CuttingProcessSP result(new CuttingProcess());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

CuttingProcessSP CuttingProcess::fromJdf(QXmlStreamReader &xmlReader)
{
    CuttingProcessSP cutProcess = create();
    cutProcess->setFetched(true);

    QList<CutBlockSP> cutBlocks;

    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "Media")
                cutProcess->setMedia(Media::fromJdf(xmlReader));
            if (xmlReader.name() == "Component") {
                QXmlStreamAttributes attributes = xmlReader.attributes();
                if (attributes.value("ComponentType").toString() == "Sheet") {
                    cutProcess->setId(attributes.value("ID").toString());
                    QStringList dimensionsList = attributes.value("Dimensions").toString().split(" ",QString::SkipEmptyParts);
                    if (dimensionsList.count() >= 2) {
                        cutProcess->setPressSheetWidth(dimensionsList.at(0).toDouble());
                        cutProcess->setPressSheetHeight(dimensionsList.at(1).toDouble());
                    }
                }
            }
            if (xmlReader.name() == "CutBlock") {
                CutBlockSP cutBlock = CutBlock::fromJdf(xmlReader);
                cutBlocks.append(cutBlock);
            }
        }
    }
    cutProcess->updateCutBlocks(cutBlocks);
    return cutProcess;
}

QString CuttingProcess::toJdf()
{
    Q_D(CuttingProcess);
    QString jdf;
    QXmlStreamWriter jdfWriter(&jdf);

    jdfWriter.setAutoFormatting(true);
    jdfWriter.writeStartDocument();

    jdfWriter.writeStartElement("ResourcePool");
    if (d->media != nullptr)
        d->media->toJdf(jdfWriter);
    {
        jdfWriter.writeEmptyElement("Component");
        jdfWriter.writeAttribute("Class", "Quantity");
        jdfWriter.writeAttribute("ComponentType", "Sheet");
        jdfWriter.writeAttribute("Dimensions", QString::number(d->pressSheetWidth) + " "
                                 + QString::number(d->pressSheetHeight) + " 0");
        jdfWriter.writeAttribute("ID", d->id);
        jdfWriter.writeAttribute("IsWaste", "False");
        jdfWriter.writeAttribute("Status", "Available");

        jdfWriter.writeStartElement("CuttingParams");
        {
            jdfWriter.writeAttribute("Status", "Available");

            for (CutBlockSP cutBlock : d->cutBlocks)
                cutBlock->toJdf(jdfWriter);
        }
        jdfWriter.writeEndElement();

    }
    jdfWriter.writeEndElement();

    jdfWriter.writeEndDocument();

    return jdf;
}

CuttingProcessSP CuttingProcess::defaultObject()
{
    static CuttingProcessSP entity = create();
    return entity;
}

QList<CutBlockSP> CuttingProcess::updateCutBlocks(const QList<CutBlockSP> &arg)
{
    Q_D(CuttingProcess);
    bool emitNeeded = arg.count() != d->cutBlocks.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->cutBlocks[i]->id();
    if (emitNeeded) {
        d->cutBlocks = arg;
        emit cutBlocksChanged();
    }
    return d->cutBlocks;
}

void CuttingProcess::setMedia(const MediaSP &media)
{
    Q_D(CuttingProcess);
    if (d->media != media) {
        d->media = media;
        emit mediaChanged(d->media);
    }
}

void CuttingProcess::setId(const QString &arg)
{
    Q_D(CuttingProcess);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void CuttingProcess::setPressSheetWidth(double arg)
{
    Q_D(CuttingProcess);
    if (d->pressSheetWidth != arg) {
        d->pressSheetWidth = arg;
        emit pressSheetWidthChanged(d->pressSheetWidth);
    }
}

void CuttingProcess::setPressSheetHeight(double arg)
{
    Q_D(CuttingProcess);
    if (d->pressSheetHeight != arg) {
        d->pressSheetHeight = arg;
        emit pressSheetHeightChanged(d->pressSheetHeight);
    }
}
