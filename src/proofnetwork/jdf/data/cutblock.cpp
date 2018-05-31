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

    explicit CutBlockPrivate(const QString &blockName) : blockName(blockName) { setDirty(!blockName.isEmpty()); }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    void setX(double arg);
    void setY(double arg);
    void setRotation(double arg);
    QString createRotationMatrixString(double angle);
    double rotationFromTransformationMatrix(const QString &transformationMatrix);

    QString blockName;
    double width = 0.0;
    double height = 0.0;
    double x = 0.0;
    double y = 0.0;
    double rotation = 0.0;
    QString transformationMatrix;
    BlockType blockType = BlockType::CutBlock;
};

ObjectsCache<JdfCutBlockDataKey, CutBlock> &cutBlockCache()
{
    return WeakObjectsCache<JdfCutBlockDataKey, CutBlock>::instance();
}

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

CutBlock::CutBlock(const QString &blockName) : NetworkDataEntity(*new CutBlockPrivate(blockName))
{}

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

double CutBlock::x() const
{
    Q_D(const CutBlock);
    return d->x;
}

double CutBlock::y() const
{
    Q_D(const CutBlock);
    return d->y;
}

double CutBlock::rotation() const
{
    Q_D(const CutBlock);
    return d->rotation;
}

QString CutBlock::transformationMatrix() const
{
    Q_D(const CutBlock);
    return d->transformationMatrix;
}

BlockType CutBlock::blockType() const
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
    initSelfWeakPtr(result);
    return result;
}

CutBlockSP CutBlock::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    CutBlockSP cutBlock = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "CutBlock" && xmlReader.isStartElement()) {
            QXmlStreamAttributes attributes = xmlReader.attributes();

            QString blockName = attributes.value(QStringLiteral("BlockName")).toString();
            cutBlock->setBlockName(blockName);
            if (sanitize) {
                CutBlockSP cutBlockFromCache = cutBlockCache().add({jobId, cutBlock->blockName()}, cutBlock);
                int index = 0;
                while (cutBlockFromCache != cutBlock && cutBlockFromCache->isFetched()) {
                    cutBlock->setBlockName(QStringLiteral("%1_%2").arg(blockName).arg(++index));
                    cutBlockFromCache = cutBlockCache().add({jobId, cutBlock->blockName()}, cutBlock);
                }
            } else {
                cutBlock = cutBlockCache().add({jobId, cutBlock->blockName()}, cutBlock);
            }
            cutBlock->setFetched(true);

            QStringList blockSizeList = attributes.value(QStringLiteral("BlockSize"))
                                            .toString()
                                            .split(QStringLiteral(" "), QString::SkipEmptyParts);
            if (blockSizeList.count() >= 2) {
                cutBlock->setWidth(blockSizeList.at(0).toDouble());
                cutBlock->setHeight(blockSizeList.at(1).toDouble());
            } else {
                qCWarning(proofNetworkJdfDataLog) << "CutBlock not created. BlockSize is not valid";
                return CutBlockSP();
            }
            cutBlock->setTransformationMatrix(attributes.value(QStringLiteral("BlockTrf")).toString());
            cutBlock->setBlockType(blockTypeFromString(attributes.value(QStringLiteral("BlockType")).toString()));
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

    jdfWriter.writeStartElement(QStringLiteral("CutBlock"));
    jdfWriter.writeAttribute(QStringLiteral("BlockName"), d->blockName);
    jdfWriter.writeAttribute(QStringLiteral("BlockSize"),
                             QString::number(d->width, 'f', 4) + " " + QString::number(d->height, 'f', 4));
    jdfWriter.writeAttribute(QStringLiteral("BlockTrf"), d->transformationMatrix);
    jdfWriter.writeAttribute(QStringLiteral("BlockType"), blockTypeToString(d->blockType));
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

void CutBlock::setX(double arg)
{
    setTransformationMatrix(arg, y(), rotation());
}

void CutBlock::setY(double arg)
{
    setTransformationMatrix(x(), arg, rotation());
}

void CutBlock::setRotation(double arg)
{
    setTransformationMatrix(x(), y(), arg);
}

void CutBlock::setTransformationMatrix(const QString &arg)
{
    Q_D(CutBlock);
    if (d->transformationMatrix != arg) {
        QStringList transformationMatrix = arg.split(QStringLiteral(" "), QString::SkipEmptyParts);
        double x = 0.0;
        double y = 0.0;
        double rotation = d->rotationFromTransformationMatrix(arg);
        if (transformationMatrix.count() == 6) {
            x = transformationMatrix.at(4).toDouble();
            y = transformationMatrix.at(5).toDouble();
        }

        d->setX(x);
        d->setY(y);
        d->setRotation(rotation);
        d->transformationMatrix = arg;
        emit transformationMatrixChanged(d->transformationMatrix);
    }
}

void CutBlock::setTransformationMatrix(double x, double y, double rotation)
{
    Q_D(CutBlock);
    QString transformationMatrix = QStringLiteral("%1 %2 %3").arg(d->createRotationMatrixString(rotation)).arg(x).arg(y);

    setTransformationMatrix(transformationMatrix);
}

void CutBlock::setBlockType(BlockType arg)
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

void CutBlockPrivate::setX(double arg)
{
    Q_Q(CutBlock);
    if (!qFuzzyCompare(x, arg)) {
        x = arg;
        emit q->xChanged(x);
    }
}

void CutBlockPrivate::setY(double arg)
{
    Q_Q(CutBlock);
    if (!qFuzzyCompare(y, arg)) {
        y = arg;
        emit q->yChanged(y);
    }
}

void CutBlockPrivate::setRotation(double arg)
{
    Q_Q(CutBlock);
    if (!qFuzzyCompare(rotation, arg)) {
        rotation = arg;
        emit q->rotationChanged(rotation);
    }
}

QString CutBlockPrivate::createRotationMatrixString(double angle)
{
    if (angle < 0)
        angle += 360;
    double radian = (angle * PI) / 180;

    return QStringLiteral("%1 %2 %3 %4")
        .arg(qRound(std::cos(radian)))
        .arg(qRound(-std::sin(radian)))
        .arg(qRound(std::sin(radian)))
        .arg(qRound(std::cos(radian)));
}

double CutBlockPrivate::rotationFromTransformationMatrix(const QString &transformationMatrix)
{
    QStringList transformationMatrixList = transformationMatrix.split(QStringLiteral(" "), QString::SkipEmptyParts);
    double cutBlockRotation = 0.0;
    if (transformationMatrixList.count() == 6) {
        if (qFuzzyIsNull(transformationMatrixList.at(0).toDouble()))
            cutBlockRotation = std::asin(transformationMatrixList.at(2).toDouble()) * 180 / PI;
        else
            cutBlockRotation = std::acos(transformationMatrixList.at(0).toDouble()) * 180 / PI;
    }
    if (cutBlockRotation < 0)
        cutBlockRotation += 360;
    return cutBlockRotation;
}
