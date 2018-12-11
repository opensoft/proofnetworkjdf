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
#ifndef PROOF_JDF_COMPONENTQMLWRAPPER_H
#define PROOF_JDF_COMPONENTQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class Component;
class BundleQmlWrapper;

class ComponentQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT ComponentQmlWrapper : public AbstractPhysicalResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::ComponentType componentType READ componentType NOTIFY componentTypeChanged)
    Q_PROPERTY(Proof::Jdf::ProductType productType READ productType NOTIFY productTypeChanged)
    Q_PROPERTY(QString productTypeDetails READ productTypeDetails NOTIFY productTypeDetailsChanged)
    Q_PROPERTY(Proof::Jdf::BundleQmlWrapper *bundle READ bundle NOTIFY bundleChanged)
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> parts READ parts NOTIFY partsChanged)

    Q_DECLARE_PRIVATE(ComponentQmlWrapper)
public:
    explicit ComponentQmlWrapper(const ComponentSP &component, QObject *parent = nullptr);
    ~ComponentQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(Component)

    Proof::Jdf::ComponentType componentType() const;
    Proof::Jdf::ProductType productType() const;
    QString productTypeDetails() const;
    Proof::Jdf::BundleQmlWrapper *bundle() const;
    QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> parts() const;

signals:
    void componentTypeChanged(Proof::Jdf::ComponentType componentType);
    void productTypeChanged(Proof::Jdf::ProductType productType);
    void productTypeDetailsChanged(const QString &productTypeDetails);
    void bundleChanged(Proof::Jdf::BundleQmlWrapper *bundle);
    void partsChanged(const QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> &parts);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_COMPONENTQMLWRAPPER_H
