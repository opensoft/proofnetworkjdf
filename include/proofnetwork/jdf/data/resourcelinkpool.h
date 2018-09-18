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
#ifndef RESOURCELINKPOOL_H
#define RESOURCELINKPOOL_H

#include "proofnetwork/jdf/data/qmlwrappers/resourcelinkpoolqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QVector>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class ResourceLinkPoolPrivate;
class PROOF_NETWORK_JDF_EXPORT ResourceLinkPool : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ResourceLinkPool)
public:
    QVector<ComponentLinkSP> componentLinks() const;
    CuttingParamsLinkSP cuttingParamsLink() const;
    QVector<MediaLinkSP> mediaLinks() const;
    LaminatingIntentLinkSP laminatingIntentLink() const;
    DeliveryIntentLinkSP deliveryIntentLink() const;
    FoldingParamsLinkSP foldingParamsLink() const;
    BoxPackingParamsLinkSP boxPackingParamsLink() const;

    void setComponentLinks(const QVector<ComponentLinkSP> &componentLinks);
    void addComponentLink(const ComponentLinkSP &componentLink);
    void setCuttingParamsLink(const CuttingParamsLinkSP &cuttingParams);
    void setMediaLinks(const QVector<MediaLinkSP> &mediaLinks);
    void addMediaLink(const MediaLinkSP &mediaLink);
    void setLaminatingIntentLink(const LaminatingIntentLinkSP &laminatingIntent);
    void setDeliveryIntentLink(const DeliveryIntentLinkSP &deliveryIntent);
    void setFoldingParamsLink(const FoldingParamsLinkSP &foldingParamsLink);
    void setBoxPackingParamsLink(const BoxPackingParamsLinkSP &boxPackingParamsLink);

    ResourceLinkPoolQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static ResourceLinkPoolSP create();

    static ResourceLinkPoolSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void componentLinksChanged();
    void cuttingParamsLinkChanged(const Proof::Jdf::CuttingParamsLinkSP &arg);
    void mediaLinksChanged();
    void laminatingIntentLinkChanged(const Proof::Jdf::LaminatingIntentLinkSP &arg);
    void deliveryIntentLinkChanged(const Proof::Jdf::DeliveryIntentLinkSP &arg);
    void foldingParamsLinkChanged(const Proof::Jdf::FoldingParamsLinkSP &arg);
    void boxPackingParamsLinkChanged(const Proof::Jdf::BoxPackingParamsLinkSP &arg);

protected:
    explicit ResourceLinkPool();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof
#endif // RESOURCELINKPOOL_H
