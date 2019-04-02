/* Copyright 2019, OpenSoft Inc.
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
#ifndef XJDF_BOXPACKINGPARAMS_H
#define XJDF_BOXPACKINGPARAMS_H

#include "resource.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class BoxPackingParamsPrivate;
class PROOF_NETWORK_XJDF_EXPORT BoxPackingParams : public Resource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BoxPackingParams)
public:
    BoxPackingParams(const BoxPackingParams &) = delete;
    BoxPackingParams &operator=(const BoxPackingParams &) = delete;
    BoxPackingParams(BoxPackingParams &&) = delete;
    BoxPackingParams &operator=(BoxPackingParams &&) = delete;
    ~BoxPackingParams() = default;

    BoxType boxType() const;
    QString boxTypeDetails() const;

    void setBoxType(BoxType arg);
    void setBoxTypeDetails(const QString &arg);

    static BoxPackingParamsSP create();

    static BoxPackingParamsSP fromXJdf(QXmlStreamReader &reader, const DocumentSP &document = DocumentSP());
    void toXJdf(QXmlStreamWriter &writer) const override;

signals:
    void boxTypeChanged(Proof::XJdf::BoxType arg);
    void boxTypeDetailsChanged(const QString &arg);

protected:
    BoxPackingParams();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_BOXPACKINGPARAMS_H
