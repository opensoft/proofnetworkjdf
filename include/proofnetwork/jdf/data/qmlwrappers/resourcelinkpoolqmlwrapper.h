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
#ifndef RESOURCELINKPOOLQMLWRAPPER_H
#define RESOURCELINKPOOLQMLWRAPPER_H

#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class ComponentLinkQmlWrapper;
class CuttingParamsLinkQmlWrapper;
class MediaLinkQmlWrapper;
class FoldingParamsLinkQmlWrapper;
class LaminatingIntentLinkQmlWrapper;

class ResourceLinkPoolQmlWrapperPrivate;
class ResourceLinkPoolQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper> componentLinks READ componentLinks NOTIFY componentLinksChanged)
    Q_PROPERTY(Proof::Jdf::CuttingParamsLinkQmlWrapper *cuttingParamsLink READ cuttingParamsLink NOTIFY cuttingParamsLinkChanged)
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::MediaLinkQmlWrapper> mediaLinks READ mediaLinks NOTIFY mediaLinksChanged)
    Q_PROPERTY(Proof::Jdf::FoldingParamsLinkQmlWrapper *foldingParamsLink READ foldingParamsLink NOTIFY foldingParamsLinkChanged)
    Q_PROPERTY(Proof::Jdf::LaminatingIntentLinkQmlWrapper *laminatingIntentLink READ laminatingIntentLink NOTIFY laminatingIntentLinkChanged)
    // clang-format on

    Q_DECLARE_PRIVATE(ResourceLinkPoolQmlWrapper)

public:
    explicit ResourceLinkPoolQmlWrapper(const ResourceLinkPoolSP &pool, QObject *parent = nullptr);
    ~ResourceLinkPoolQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(ResourceLinkPool)

    QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper> componentLinks() const;
    Proof::Jdf::CuttingParamsLinkQmlWrapper *cuttingParamsLink() const;
    QQmlListProperty<Proof::Jdf::MediaLinkQmlWrapper> mediaLinks() const;
    Proof::Jdf::FoldingParamsLinkQmlWrapper *foldingParamsLink() const;
    Proof::Jdf::LaminatingIntentLinkQmlWrapper *laminatingIntentLink() const;

signals:
    void componentLinksChanged(const QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper> &componentLinks);
    void cuttingParamsLinkChanged(Proof::Jdf::CuttingParamsLinkQmlWrapper *cuttingParamsLink);
    void mediaLinksChanged(const QQmlListProperty<Proof::Jdf::MediaLinkQmlWrapper> &mediaLinks);
    void foldingParamsLinkChanged(Proof::Jdf::FoldingParamsLinkQmlWrapper *foldingParamsLink);
    void laminatingIntentLinkChanged(Proof::Jdf::LaminatingIntentLinkQmlWrapper *laminatingIntentLink);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof
#endif // RESOURCELINKPOOLQMLWRAPPER_H
