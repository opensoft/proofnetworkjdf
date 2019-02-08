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
#ifndef DELIVERYINTENTLINK_H
#define DELIVERYINTENTLINK_H

#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/deliveryintentlinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT DeliveryIntentLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeliveryIntentLink)
public:
    DeliveryIntentLink(const DeliveryIntentLink &) = delete;
    DeliveryIntentLink &operator=(const DeliveryIntentLink &) = delete;
    DeliveryIntentLink(DeliveryIntentLink &&) = delete;
    DeliveryIntentLink &operator=(DeliveryIntentLink &&) = delete;
    ~DeliveryIntentLink() = default;

    DeliveryIntentLinkQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DeliveryIntentLinkSP create();

    static DeliveryIntentLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;

protected:
    DeliveryIntentLink();
};

} // namespace Jdf
} // namespace Proof

#endif // DELIVERYINTENTLINK_H
