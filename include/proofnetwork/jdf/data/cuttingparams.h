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
#ifndef PROOF_JDF_CUTTINGPARAMS_H
#define PROOF_JDF_CUTTINGPARAMS_H

#include "proofcore/objectscache.h"

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingparamsqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class CuttingParamsPrivate;
class PROOF_NETWORK_JDF_EXPORT CuttingParams : public AbstractResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CuttingParams)
public:
    CuttingParams(const CuttingParams &) = delete;
    CuttingParams &operator=(const CuttingParams &) = delete;
    CuttingParams(CuttingParams &&) = delete;
    CuttingParams &operator=(CuttingParams &&) = delete;
    ~CuttingParams() = default;

    QVector<CutBlockSP> cutBlocks() const;
    QVector<CuttingParamsSP> parts() const;

    QVector<CutBlockSP> updateCutBlocks(const QVector<CutBlockSP> &arg);
    QVector<CuttingParamsSP> updateParts(const QVector<CuttingParamsSP> &arg);
    void addPart(const CuttingParamsSP &arg);

    CuttingParamsQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static CuttingParamsSP create();

    static CuttingParamsSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    CuttingParamsLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

signals:
    void cutBlocksChanged();
    void partsChanged();

protected:
    explicit CuttingParams();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_CUTTINGPARAMS_H
