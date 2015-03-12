#include "cutblock.h"
#include "proofnetwork/jdf/data/abstractresource_p.h"

#include <QStringList>

#include <cmath>

static const double PI = 3.14159265358979323846;

namespace Proof {
namespace Jdf {

class CutBlockPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(CutBlock)

    QString createRotationMatrixString(double angle);

    QString blockName;
    double width;
    double height;
    QString transformationMatrix;

};

ObjectsCache<QString, CutBlock> &cutBlockCache()
{
    return WeakObjectsCache<QString, CutBlock>::instance();
}

}
}

using namespace Proof::Jdf;

CutBlock::CutBlock()
    : AbstractResource(*new CutBlockPrivate)
{
    setResourceClass(ApiHelper::ParameterClass);
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

void CutBlock::updateFrom(const NetworkDataEntitySP &other)
{
    CutBlockSP castedOther = qSharedPointerCast<CutBlock>(other);
    setBlockName(castedOther->blockName());
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setTransformationMatrix(castedOther->transformationMatrix());
    AbstractResource::updateFrom(other);
}

CutBlockQmlWrapper *CutBlock::toQmlWrapper(QObject *parent) const
{
    Q_D(const CutBlock);
    CutBlockSP castedSelf = qSharedPointerCast<CutBlock>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new CutBlockQmlWrapper(castedSelf, parent);
}

CutBlockSP CutBlock::create()
{
    CutBlockSP result(new CutBlock());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

CutBlockSP CutBlock::fromJdf(QXmlStreamReader &xmlReader)
{
    CutBlockSP cutBlock = create();
    cutBlock->setFetched(true);

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "CutBlock" && xmlReader.isStartElement()) {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            cutBlock->setBlockName(attributes.value("BlockName").toString());
            QStringList blockSizeList = attributes.value("BlockSize").toString().split(" ", QString::SkipEmptyParts);
            if (blockSizeList.count() >= 2) {
                cutBlock->setWidth(blockSizeList.at(0).toDouble());
                cutBlock->setHeight(blockSizeList.at(1).toDouble());
            }
            cutBlock->setTransformationMatrix(attributes.value("BlockTrf").toString());
            break;
        } else {
            xmlReader.readNext();
        }
    }

    AbstractResourceSP castedCutBlock = qSharedPointerCast<AbstractResource>(cutBlock);
    AbstractResource::fromJdf(xmlReader, castedCutBlock);

    return cutBlock;
}

void CutBlock::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(CutBlock);

    jdfWriter.writeEmptyElement("CutBlock");
    jdfWriter.writeAttribute("BlockName", d->blockName);
    jdfWriter.writeAttribute("BlockSize", QString::number(d->width,'f', 4) + " " + QString::number(d->height,'f', 4));
    jdfWriter.writeAttribute("BlockTrf", d->transformationMatrix);
    jdfWriter.writeAttribute("BlockType", "CutBlock");

    AbstractResource::toJdf(jdfWriter);
}

CutBlockSP CutBlock::defaultObject()
{
    static CutBlockSP entity = create();
    return entity;
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
    if (d->width != arg) {
        d->width = arg;
        emit widthChanged(d->width);
    }
}

void CutBlock::setHeight(double arg)
{
    Q_D(CutBlock);
    if (d->height != arg) {
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
