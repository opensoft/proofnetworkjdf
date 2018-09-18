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
#ifndef JDFCUTBLOCKQMLWRAPPER_H
#define JDFCUTBLOCKQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"

namespace Proof {
namespace Jdf {

class CutBlockQmlWrapperPrivate;

class PROOF_NETWORK_JDF_EXPORT CutBlockQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString blockName READ blockName CONSTANT)
    Q_PROPERTY(double width READ width CONSTANT)
    Q_PROPERTY(double height READ height CONSTANT)
    Q_PROPERTY(QString transformationMatrix READ transformationMatrix CONSTANT)
    Q_PROPERTY(Proof::Jdf::BlockType blockType READ blockType NOTIFY blockTypeChanged)
    Q_DECLARE_PRIVATE(CutBlockQmlWrapper)
public:
    explicit CutBlockQmlWrapper(const CutBlockSP &cutBlock, QObject *parent = nullptr);
    ~CutBlockQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(CutBlock)

    QString blockName() const;
    double width() const;
    double height() const;
    QString transformationMatrix() const;
    Proof::Jdf::BlockType blockType() const;

signals:
    void blockNameChanged(const QString &blockName);
    void widthChanged(double width);
    void heightChanged(double height);
    void transformationMatrixChanged(const QString &transformationMatrix);
    void blockTypeChanged(Proof::Jdf::BlockType blockType);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFCUTBLOCKQMLWRAPPER_H
