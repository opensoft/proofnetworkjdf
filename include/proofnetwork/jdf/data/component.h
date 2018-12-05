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
#ifndef PROOF_JDF_COMPONENT_H
#define PROOF_JDF_COMPONENT_H

#include "proofcore/objectscache.h"

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractphysicalresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/componentqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

using JdfComponentDataKey = QPair<QString, QString>;

class ComponentPrivate;
class PROOF_NETWORK_JDF_EXPORT Component : public AbstractPhysicalResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Component)
public:
    ComponentType componentType() const;
    ProductType productType() const;
    QString productTypeDetails() const;
    double width() const;
    double height() const;
    double depth() const;
    BundleSP bundle() const;
    QVector<CutBlockSP> cutBlocks() const;
    QVector<ComponentSP> parts() const;

    void setComponentType(ComponentType arg);
    void setProductType(ProductType arg);
    void setProductTypeDetails(const QString &arg);
    void setWidth(double arg);
    void setHeight(double arg);
    void setDepth(double arg);
    void setBundle(const BundleSP &arg);
    QVector<CutBlockSP> updateCutBlocks(const QVector<CutBlockSP> &arg);
    QVector<ComponentSP> updateParts(const QVector<ComponentSP> &arg);
    void addPart(const ComponentSP &arg);

    ComponentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static ComponentSP create(const QString &id = QString());

    static ComponentSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    ComponentLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

signals:
    void componentTypeChanged(Proof::Jdf::ComponentType arg);
    void productTypeChanged(Proof::Jdf::ProductType arg);
    void productTypeDetailsChanged(const QString &arg);
    void widthChanged(double arg);
    void heightChanged(double arg);
    void depthChanged(double arg);
    void bundleChanged(const Proof::Jdf::BundleSP &bundle);
    void cutBlocksChanged();
    void partsChanged();

protected:
    explicit Component(const QString &id);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

PROOF_NETWORK_JDF_EXPORT ObjectsCache<JdfComponentDataKey, Component> &componentsCache();

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_COMPONENT_H
