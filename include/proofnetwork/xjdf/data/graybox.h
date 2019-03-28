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
#ifndef XJDF_GRAYBOX_H
#define XJDF_GRAYBOX_H

#include "abstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class GrayBoxPrivate;
class PROOF_NETWORK_XJDF_EXPORT GrayBox : public AbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GrayBox)
public:
    GrayBox(const GrayBox &) = delete;
    GrayBox &operator=(const GrayBox &) = delete;
    GrayBox(GrayBox &&) = delete;
    GrayBox &operator=(GrayBox &&) = delete;
    ~GrayBox() = default;

    QVector<ProcessType> types() const;
    QVector<ResourceSetSP> resourceSets() const;
    void setTypes(const QVector<ProcessType> &arg);
    void setResourceSets(const QVector<ResourceSetSP> &arg);
    void addResourceSet(const ResourceSetSP &arg);

    bool fillFromXJdf(QXmlStreamReader &reader) override;
    void readAttributesFromXJdf(QXmlStreamReader &reader) override;
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void typesChanged(const QVector<Proof::XJdf::ProcessType> &arg);
    void resourceSetsChanged(const QVector<Proof::XJdf::ResourceSetSP> &arg);

protected:
    explicit GrayBox();
    explicit GrayBox(GrayBoxPrivate &dd);
    void updateSelf(const NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_GRAYBOX_H
