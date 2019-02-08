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
#ifndef ABSTRACTRESOURCELINKQMLWRAPPER_H
#define ABSTRACTRESOURCELINKQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"

namespace Proof {
namespace Jdf {

class AbstractResourceLinkQmlWrapperPrivate;
class AbstractResourceLinkQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::LinkUsage usage READ usage NOTIFY usageChanged)
    Q_PROPERTY(Proof::Jdf::ProcessUsage processUsage READ processUsage NOTIFY processUsageChanged)
    Q_PROPERTY(QString rRef READ rRef NOTIFY rRefChanged)
    Q_DECLARE_PRIVATE(AbstractResourceLinkQmlWrapper)
public:
    explicit AbstractResourceLinkQmlWrapper(const QSharedPointer<AbstractResourceLink> &link,
                                            AbstractResourceLinkQmlWrapperPrivate &dd, QObject *parent = nullptr);
    AbstractResourceLinkQmlWrapper(const AbstractResourceLinkQmlWrapper &) = delete;
    AbstractResourceLinkQmlWrapper &operator=(const AbstractResourceLinkQmlWrapper &) = delete;
    AbstractResourceLinkQmlWrapper(AbstractResourceLinkQmlWrapper &&) = delete;
    AbstractResourceLinkQmlWrapper &operator=(AbstractResourceLinkQmlWrapper &&) = delete;
    ~AbstractResourceLinkQmlWrapper();
    Proof::Jdf::LinkUsage usage() const;
    Proof::Jdf::ProcessUsage processUsage() const;
    QString rRef() const;

signals:
    void usageChanged(Proof::Jdf::LinkUsage usage);
    void processUsageChanged(Proof::Jdf::ProcessUsage processUsage);
    void rRefChanged(const QString &rRef);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // ABSTRACTRESOURCELINKQMLWRAPPER_H
