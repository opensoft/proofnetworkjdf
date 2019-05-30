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
#include "proofnetwork/jdf/data/cutblock.h"

#include "proofnetwork/networkdataentity_p.h"

#include <QStringList>

#include <cmath>

namespace Proof {
namespace Jdf {

class CutBlockPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(CutBlock)

    explicit CutBlockPrivate(const QString &blockName) : blockName(blockName) { setDirty(!blockName.isEmpty()); }

    QString blockName;
    double width = 0.0;
    double height = 0.0;
    QTransform transformationMatrix;
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
    Q_D_CONST(CutBlock);
    return d->blockName;
}

double CutBlock::width() const
{
    Q_D_CONST(CutBlock);
    return d->width;
}

double CutBlock::height() const
{
    Q_D_CONST(CutBlock);
    return d->height;
}

QRectF CutBlock::boundingRect() const
{
    Q_D_CONST(CutBlock);
    return d->transformationMatrix.mapRect(QRectF(0.0, 0.0, d->width, d->height));
}

QTransform CutBlock::transformationMatrix() const
{
    Q_D_CONST(CutBlock);
    return d->transformationMatrix;
}

BlockType CutBlock::blockType() const
{
    Q_D_CONST(CutBlock);
    return d->blockType;
}

CutBlockQmlWrapper *CutBlock::toQmlWrapper(QObject *parent) const
{
    CutBlockSP castedSelf = castedSelfPtr<CutBlock>();
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
            QStringList trf = attributes.value(QStringLiteral("BlockTrf")).toString().split(' ');
            QTransform matrix;
            if (trf.size() >= 6) {
                matrix = QTransform(trf[0].toDouble(), trf[1].toDouble(), trf[2].toDouble(), trf[3].toDouble(),
                                    trf[4].toDouble(), trf[5].toDouble());
            } else if (trf.size() >= 4) {
                matrix = QTransform(trf[0].toDouble(), trf[1].toDouble(), trf[2].toDouble(), trf[3].toDouble(), 0, 0);
            }
            cutBlock->setTransformationMatrix(matrix);
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
    jdfWriter.writeAttribute(QStringLiteral("BlockTrf"), QStringLiteral("%1 %2 %3 %4 %5 %6")
                                                             .arg(transformationMatrix().m11(), 0, 'f', 4)
                                                             .arg(transformationMatrix().m12(), 0, 'f', 4)
                                                             .arg(transformationMatrix().m21(), 0, 'f', 4)
                                                             .arg(transformationMatrix().m22(), 0, 'f', 4)
                                                             .arg(transformationMatrix().m31(), 0, 'f', 4)
                                                             .arg(transformationMatrix().m32(), 0, 'f', 4));
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

void CutBlock::setTransformationMatrix(const QTransform &arg)
{
    Q_D(CutBlock);
    if (d->transformationMatrix != arg) {
        d->transformationMatrix = arg;
        emit transformationMatrixChanged(d->transformationMatrix);
    }
}

void CutBlock::setBlockType(BlockType arg)
{
    Q_D(CutBlock);
    if (d->blockType != arg) {
        d->blockType = arg;
        emit blockTypeChanged(d->blockType);
    }
}

void CutBlock::moveBoundingRectTo(double x, double y)
{
    Q_D(CutBlock);
    QRectF rect = boundingRect();
    setTransformationMatrix(QTransform(d->transformationMatrix.m11(), d->transformationMatrix.m12(),
                                       d->transformationMatrix.m21(), d->transformationMatrix.m22(),
                                       d->transformationMatrix.m31() + x - rect.x(),
                                       d->transformationMatrix.m32() + y - rect.y()));
}

void CutBlock::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    CutBlockSP castedOther = qSharedPointerCast<CutBlock>(other);
    setBlockName(castedOther->blockName());
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setTransformationMatrix(castedOther->transformationMatrix());
    setBlockType(castedOther->blockType());

    NetworkDataEntity::updateSelf(other);
}
