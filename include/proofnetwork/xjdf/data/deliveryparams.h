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
#ifndef XJDF_DELIVERYPARAMS_H
#define XJDF_DELIVERYPARAMS_H

#include "resource.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class DeliveryParamsPrivate;
class PROOF_NETWORK_XJDF_EXPORT DeliveryParams : public Resource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeliveryParams)
public:
    DeliveryParams(const DeliveryParams &) = delete;
    DeliveryParams &operator=(const DeliveryParams &) = delete;
    DeliveryParams(DeliveryParams &&) = delete;
    DeliveryParams &operator=(DeliveryParams &&) = delete;
    ~DeliveryParams() = default;

    QDateTime required() const;
    QVector<DropItemSP> items() const;

    void setRequired(const QDateTime &arg);
    void setItems(const QVector<DropItemSP> &arg);

    static DeliveryParamsSP create();

    static DeliveryParamsSP fromXJdf(QXmlStreamReader &reader, const DocumentSP &document = DocumentSP());
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void requiredChanged(const QDateTime &arg);
    void itemsChanged(const QVector<Proof::XJdf::DropItemSP> &arg);

protected:
    explicit DeliveryParams();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_DELIVERYPARAMS_H