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
#include "proofnetwork/xjdf/data/cutblock.h"

#include "proofnetwork/xjdf/data/xjdfabstractnode_p.h"

#include <QStringList>

namespace Proof {
namespace XJdf {

class CutBlockPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(CutBlock)

    explicit CutBlockPrivate(const QString &blockName) : blockName(blockName) { setDirty(!blockName.isEmpty()); }

    QString blockName;
    double width = 0.0;
    double height = 0.0;
    double x = 0.0;
    double y = 0.0;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof::XJdf;

CutBlock::CutBlock(const QString &blockName) : XJdfAbstractNode(*new CutBlockPrivate(blockName))
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

double CutBlock::x() const
{
    Q_D_CONST(CutBlock);
    return d->x;
}

double CutBlock::y() const
{
    Q_D_CONST(CutBlock);
    return d->y;
}

CutBlockSP CutBlock::create(const QString &blockName)
{
    CutBlockSP result(new CutBlock(blockName));
    initSelfWeakPtr(result);
    return result;
}

CutBlockSP CutBlock::fromXJdf(QXmlStreamReader &reader)
{
    CutBlockSP cutBlock = create();

    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.name() == "CutBlock" && reader.isStartElement()) {
            QXmlStreamAttributes attributes = reader.attributes();

            QString blockName = attributes.value(QStringLiteral("BlockName")).toString();
            cutBlock->setBlockName(blockName);
            cutBlock->setFetched(true);

            QStringList boxList =
                attributes.value(QStringLiteral("Box")).toString().split(QStringLiteral(" "), QString::SkipEmptyParts);
            if (boxList.count() < 4) {
                qCWarning(proofNetworkXJdfDataLog) << "CutBlock not created. BlockSize is not valid";
                return CutBlockSP();
            }
            cutBlock->setX(boxList.at(0).toDouble());
            cutBlock->setY(boxList.at(1).toDouble());
            cutBlock->setWidth(boxList.at(2).toDouble());
            cutBlock->setHeight(boxList.at(3).toDouble());

        } else if (reader.isEndElement()) {
            break;
        }
        reader.readNext();
    }

    return cutBlock;
}

void CutBlock::toXJdf(QXmlStreamWriter &writer, bool) const
{
    Q_D_CONST(CutBlock);

    writer.writeStartElement(QStringLiteral("CutBlock"));
    writer.writeAttribute(QStringLiteral("BlockName"), d->blockName);
    writer.writeAttribute(QStringLiteral("Box"), QString("%1 %2 %3 %4").arg(d->x).arg(d->y).arg(d->width).arg(d->height));
    writer.writeEndElement();
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
    Q_D(CutBlock);
    if (!qFuzzyCompare(d->height, arg)) {
        d->height = arg;
        emit heightChanged(d->height);
    }
}

void CutBlock::setY(double arg)
{
    Q_D(CutBlock);
    if (!qFuzzyCompare(d->height, arg)) {
        d->height = arg;
        emit heightChanged(d->height);
    }
}

void CutBlock::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    CutBlockSP castedOther = qSharedPointerCast<CutBlock>(other);
    setBlockName(castedOther->blockName());
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setX(castedOther->x());
    setY(castedOther->y());

    XJdfAbstractNode::updateSelf(other);
}
