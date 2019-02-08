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
#ifndef ABSTRACTRESOURCELINK_H
#define ABSTRACTRESOURCELINK_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractResourceLinkPrivate;

class PROOF_NETWORK_JDF_EXPORT AbstractResourceLink : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractResourceLink)
public:
    explicit AbstractResourceLink() = delete;
    AbstractResourceLink(const AbstractResourceLink &) = delete;
    AbstractResourceLink &operator=(const AbstractResourceLink &) = delete;
    AbstractResourceLink(AbstractResourceLink &&) = delete;
    AbstractResourceLink &operator=(AbstractResourceLink &&) = delete;
    ~AbstractResourceLink() = default;

    LinkUsage usage() const;
    ProcessUsage processUsage() const;
    QString rRef() const;

    void setUsage(LinkUsage arg);
    void setProcessUsage(ProcessUsage arg);
    void setRRef(const QString &arg);

    static bool fromJdf(const QXmlStreamReader &xmlReader, const AbstractResourceLinkSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

    QString jdfNodeName() const;
    QString jdfNodeRefName() const;

signals:
    void usageChanged(Proof::Jdf::LinkUsage arg);
    void processUsageChanged(Proof::Jdf::ProcessUsage arg);
    void rRefChanged(const QString &arg);

protected:
    explicit AbstractResourceLink(AbstractResourceLinkPrivate &dd);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof
#endif // ABSTRACTRESOURCELINK_H
