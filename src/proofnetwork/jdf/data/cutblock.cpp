#include "cutblock.h"

#include "proofnetwork/networkdataentity_p.h"

#include <QStringList>

#include <cmath>

static const double PI = 3.14159265358979323846;

namespace Proof {
namespace Jdf {

class CutBlockPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(CutBlock)

    explicit CutBlockPrivate(const QString &blockName) : blockName(blockName) {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString createRotationMatrixString(double angle);

    QString blockName;
    double width = 0.0;
    double height = 0.0;
    QString transformationMatrix;
    ApiHelper::BlockType blockType = ApiHelper::BlockType::CutBlockType;

};

ObjectsCache<JdfCutBlockDataKey, CutBlock> &cutBlockCache()
{
    return WeakObjectsCache<JdfCutBlockDataKey, CutBlock>::instance();
}

}
}

using namespace Proof::Jdf;

CutBlock::CutBlock(const QString &blockName)
    : NetworkDataEntity(*new CutBlockPrivate(blockName))
{
}

QString CutBlock::blockName() const
{
    Q_D(const CutBlock);
    return d->blockName;
}

double CutBlock::width() const
{
    Q_D(const CutBlock);
    return d->width;
}

double CutBlock::height() const
{
    Q_D(const CutBlock);
    return d->height;
}

QString CutBlock::transformationMatrix() const
{
    Q_D(const CutBlock);
    return d->transformationMatrix;
}

ApiHelper::BlockType CutBlock::blockType() const
{
    Q_D(const CutBlock);
    return d->blockType;
}

CutBlockQmlWrapper *CutBlock::toQmlWrapper(QObject *parent) const
{
    Q_D(const CutBlock);
    CutBlockSP castedSelf = qSharedPointerCast<CutBlock>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new CutBlockQmlWrapper(castedSelf, parent);
}

CutBlockSP CutBlock::create(const QString &blockName)
{
    CutBlockSP result(new CutBlock(blockName));
    makeWeakSelf(result);
    return result;
}

CutBlockSP CutBlock::fromJdf(QXmlStreamReader &xmlReader, const QString &jdfId)
{
    CutBlockSP cutBlock = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "CutBlock" && xmlReader.isStartElement()) {
            cutBlock->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            cutBlock->setBlockName(attributes.value("BlockName").toString());
            cutBlock = cutBlockCache().add({jdfId, cutBlock->blockName()}, cutBlock);
            QStringList blockSizeList = attributes.value("BlockSize").toString().split(" ", QString::SkipEmptyParts);
            if (blockSizeList.count() >= 2) {
                cutBlock->setWidth(blockSizeList.at(0).toDouble());
                cutBlock->setHeight(blockSizeList.at(1).toDouble());
            } else {
                qCCritical(proofNetworkJdfDataLog) << "CutBlock not created. BlockSize is not valid";
                return CutBlockSP();
            }
            cutBlock->setTransformationMatrix(attributes.value("BlockTrf").toString());
            cutBlock->setBlockType(ApiHelper::blockTypeFromString(attributes.value("BlockType").toString()));
        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return cutBlock;
}

void CutBlock::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(CutBlock);

    jdfWriter.writeStartElement("CutBlock");
    jdfWriter.writeAttribute("BlockName", d->blockName);
    jdfWriter.writeAttribute("BlockSize", QString::number(d->width,'f', 4) + " " + QString::number(d->height,'f', 4));
    jdfWriter.writeAttribute("BlockTrf", d->transformationMatrix);
    jdfWriter.writeAttribute("BlockType", ApiHelper::blockTypeToString(d->blockType));
    jdfWriter.writeEndElement();
}

void CutBlock::setBlockName(const QString &arg)
{
    Q_D(CutBlock);
    if (d->blockName != arg) {
        d->blockName = arg;
        emit blockNameChanged(d->blockName);
    }
}

void CutBlock::setWidth(double arg)
{
    Q_D(CutBlock);
    if (!qFuzzyCompare(d->width, arg)) {
        d->width = arg;
        emit widthChanged(d->width);
    }
}

void CutBlock::setHeight(double arg)
{
    Q_D(CutBlock);
    if (!qFuzzyCompare(d->height, arg)) {
        d->height = arg;
        emit heightChanged(d->height);
    }
}

void CutBlock::setTransformationMatrix(const QString &arg)
{
    Q_D(CutBlock);
    if (d->transformationMatrix != arg) {
        d->transformationMatrix = arg;
        emit transformationMatrixChanged(d->transformationMatrix);
    }
}

void CutBlock::setTransformationMatrix(double x, double y, double rotation)
{
    Q_D(CutBlock);
    QString transformationMatrix = QString("%1 %2 %3")
            .arg(d->createRotationMatrixString(rotation))
            .arg(x)
            .arg(y);

    if (d->transformationMatrix != transformationMatrix) {
        d->transformationMatrix = transformationMatrix;
        emit transformationMatrixChanged(d->transformationMatrix);
    }
}

void CutBlock::setBlockType(ApiHelper::BlockType arg)
{
    Q_D(CutBlock);
    if (d->blockType != arg) {
        d->blockType = arg;
        emit blockTypeChanged(d->blockType);
    }
}

void CutBlockPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(CutBlock);
    CutBlockSP castedOther = qSharedPointerCast<CutBlock>(other);
    q->setBlockName(castedOther->blockName());
    q->setWidth(castedOther->width());
    q->setHeight(castedOther->height());
    q->setTransformationMatrix(castedOther->transformationMatrix());
    q->setBlockType(castedOther->blockType());

    NetworkDataEntityPrivate::updateFrom(other);
}

QString CutBlockPrivate::createRotationMatrixString(double angle)
{
    if (angle < 0)
        angle += 360;
    double radian = (angle * PI) / 180;

    return QString("%1 %2 %3 %4")
            .arg(qRound(std::cos(radian)))
            .arg(qRound(-std::sin(radian)))
            .arg(qRound(std::sin(radian)))
            .arg(qRound(std::cos(radian)));
}
