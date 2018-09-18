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
#ifndef PROOF_JDF_RESOURCEPOOL_H
#define PROOF_JDF_RESOURCEPOOL_H

#include "proofcore/objectscache.h"

#include "proofnetwork/jdf/data/qmlwrappers/resourcepoolqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class ResourcePoolPrivate;
class PROOF_NETWORK_JDF_EXPORT ResourcePool : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ResourcePool)
public:
    QVector<ComponentSP> components() const;
    CuttingParamsSP cuttingParams() const;
    QVector<MediaSP> media() const;
    LaminatingIntentSP laminatingIntent() const;
    DeliveryIntentSP deliveryIntent() const;
    FoldingParamsSP foldingParams() const;
    BoxPackingParamsSP boxPackingParams() const;
    QVector<LayoutSP> layouts() const;

    void setComponents(const QVector<ComponentSP> &arg);
    void addComponent(const ComponentSP &arg);
    void setCuttingParams(const CuttingParamsSP &arg);
    void setMedia(const QVector<MediaSP> &arg);
    void addMedia(const MediaSP &arg);
    void setLaminatingIntent(const LaminatingIntentSP &laminatingIntent);
    void setDeliveryIntent(const DeliveryIntentSP &arg);
    void setFoldingParams(const FoldingParamsSP &foldingParams);
    void setBoxPackingParams(const BoxPackingParamsSP &boxPackingParams);
    void setLayouts(const QVector<LayoutSP> &arg);
    void addLayout(const LayoutSP &arg);

    ResourcePoolQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static ResourcePoolSP create();

    static ResourcePoolSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void componentsChanged();
    void cuttingParamsChanged(const Proof::Jdf::CuttingParamsSP &arg);
    void mediaChanged();
    void laminatingIntentChanged(const Proof::Jdf::LaminatingIntentSP &arg);
    void deliveryIntentChanged(const Proof::Jdf::DeliveryIntentSP &arg);
    void foldingParamsChanged(const Proof::Jdf::FoldingParamsSP &arg);
    void boxPackingParamsChanged(const Proof::Jdf::BoxPackingParamsSP &arg);
    void layoutsChanged();

protected:
    explicit ResourcePool();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_RESOURCEPOOL_H
