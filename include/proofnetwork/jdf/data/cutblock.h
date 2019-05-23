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
#ifndef JDFCUTBLOCK_H
#define JDFCUTBLOCK_H

#include "proofcore/objectscache.h"

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/cutblockqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QTransform>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

using JdfCutBlockDataKey = QPair<QString, QString>;

class CutBlockPrivate;
class PROOF_NETWORK_JDF_EXPORT CutBlock : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CutBlock)
public:
    CutBlock(const CutBlock &) = delete;
    CutBlock &operator=(const CutBlock &) = delete;
    CutBlock(CutBlock &&) = delete;
    CutBlock &operator=(CutBlock &&) = delete;
    ~CutBlock() = default;

    QString blockName() const;
    double width() const;
    double height() const;
    double x() const;
    double y() const;
    QRectF boundingRect() const;
    QTransform transformationMatrix() const;
    BlockType blockType() const;

    void setBlockName(const QString &arg);
    void setWidth(double arg);
    void setHeight(double arg);
    void setX(double arg);
    void setY(double arg);
    void setTransformationMatrix(const QTransform &arg);
    void setBlockType(BlockType arg);

    CutBlockQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static CutBlockSP create(const QString &blockName = QString());

    static CutBlockSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void blockNameChanged(const QString &arg);
    void widthChanged(double arg);
    void heightChanged(double arg);
    void xChanged(double arg);
    void yChanged(double arg);
    void transformationMatrixChanged(const QTransform &arg);
    void blockTypeChanged(Proof::Jdf::BlockType arg);

protected:
    explicit CutBlock(const QString &blockName = QString());
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

PROOF_NETWORK_JDF_EXPORT ObjectsCache<JdfCutBlockDataKey, CutBlock> &cutBlockCache();

} // namespace Jdf
} // namespace Proof

#endif // JDFCUTBLOCK_H
