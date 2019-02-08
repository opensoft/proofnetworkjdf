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
#ifndef PROOF_JDF_ABSTRACTRESOURCE_H
#define PROOF_JDF_ABSTRACTRESOURCE_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractResourcePrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractResource : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractResource)
public:
    explicit AbstractResource() = delete;
    AbstractResource(const AbstractResource &) = delete;
    AbstractResource &operator=(const AbstractResource &) = delete;
    AbstractResource(AbstractResource &&) = delete;
    AbstractResource &operator=(AbstractResource &&) = delete;
    ~AbstractResource() = default;

    QString id() const;
    ResourceStatus resourceStatus() const;
    ResourceClass resourceClass() const;
    QVector<ResourcePartType> partIdKeys() const;

    void setId(const QString &arg);
    void setResourceStatus(ResourceStatus arg);
    void setResourceClass(ResourceClass arg);
    void setPartIdKeys(const QVector<ResourcePartType> &arg);

    QString partAttribute(ResourcePartType attribute) const;
    bool hasPartAttribute(ResourcePartType attribute) const;
    void setPartAttribute(ResourcePartType attribute, const QString &value);

    static bool fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

    void refToJdf(QXmlStreamWriter &jdfWriter);

    //TODO: 1.0 think about proper way to do it
    QString jdfNodeName() const;
    QString jdfNodeRefName() const;

signals:
    void idChanged(const QString &arg);
    void statusChanged(Proof::Jdf::ResourceStatus arg);
    void resourceClassChanged(Proof::Jdf::ResourceClass arg);
    void partIdKeysChanged(const QVector<Proof::Jdf::ResourcePartType> &arg);
    void partAttributeChanged(Proof::Jdf::ResourcePartType attribute, const QString &value);

protected:
    explicit AbstractResource(AbstractResourcePrivate &dd);
    void setupLink(const AbstractResourceLinkSP &abstractLink, LinkUsage usage) const;
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_ABSTRACTRESOURCE_H
