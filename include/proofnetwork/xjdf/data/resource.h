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
#ifndef XJDF_RESOURCE_H
#define XJDF_RESOURCE_H

#include "abstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class ResourcePrivate;
class PROOF_NETWORK_XJDF_EXPORT Resource : public AbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Resource)
public:
    Resource(const Resource &) = delete;
    Resource &operator=(const Resource &) = delete;
    Resource(Resource &&) = delete;
    Resource &operator=(Resource &&) = delete;
    ~Resource() = default;

    QString id() const;
    ResourceOrientation orientation() const;
    QVector<PartSP> parts() const;
    AmountPoolSP amountPool() const;

    void setId(const QString &arg);
    void setOrientation(ResourceOrientation arg);
    void setParts(const QVector<PartSP> &arg);
    void setAmountPool(const AmountPoolSP &arg);

    bool fillCommonFields(QXmlStreamReader &reader) override final;
    static ResourceSP fromXJdf(QXmlStreamReader &reader, const DocumentSP &document = DocumentSP());

    template <class T>
    inline static void registerResourceCreator(const QString &name)
    {
        addResourceCreator(name, [](QXmlStreamReader &reader, const DocumentSP &document) -> ResourceSP {
            return qSharedPointerCast<Resource>(T::fromXJdf(reader, document));
        });
    }

signals:
    void idChanged(const QString &arg);
    void orientationChanged(Proof::XJdf::ResourceOrientation arg);
    void partsChanged(const QVector<Proof::XJdf::PartSP> &arg);
    void amountPoolChanged(const Proof::XJdf::AmountPoolSP &arg);

protected:
    AbstractNode::WriterGuard writeFieldsToXJdf(QXmlStreamWriter &writer) const;
    explicit Resource(const QString &id = QString());
    explicit Resource(ResourcePrivate &dd, const QString &id = QString());
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
    static void addResourceCreator(const QString &name,
                                   std::function<ResourceSP(QXmlStreamReader &, const DocumentSP &)> &&creator);
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_RESOURCE_H
