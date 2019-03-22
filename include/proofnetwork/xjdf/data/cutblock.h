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
#ifndef XJDFCUTBLOCK_H
#define XJDFCUTBLOCK_H

#include "proofcore/objectscache.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/xjdfabstractnode.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_global.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace XJdf {

using XJdfCutBlockDataKey = QPair<QString, QString>;

class CutBlockPrivate;
class PROOF_NETWORK_XJDF_EXPORT CutBlock : public XJdfAbstractNode
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
    double rotation() const;
    QString transformationMatrix() const;

    void setBlockName(const QString &arg);
    void setWidth(double arg);
    void setHeight(double arg);
    void setX(double arg);
    void setY(double arg);
    void setRotation(double arg);
    void setTransformationMatrix(const QString &arg);
    void setTransformationMatrix(double x, double y, double rotation);

    void normalizeTransformation();

    static CutBlockSP create(const QString &blockName = QString());

    static CutBlockSP fromXJdf(QXmlStreamReader &xjdfReader);
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;

signals:
    void blockNameChanged(const QString &arg);
    void widthChanged(double arg);
    void heightChanged(double arg);
    void xChanged(double arg);
    void yChanged(double arg);
    void rotationChanged(double arg);
    void transformationMatrixChanged(const QString &arg);

protected:
    explicit CutBlock(const QString &blockName = QString());
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

PROOF_NETWORK_XJDF_EXPORT ObjectsCache<XJdfCutBlockDataKey, CutBlock> &cutBlockCache();

} // namespace XJdf
} // namespace Proof

#endif // XJDFCUTBLOCK_H
