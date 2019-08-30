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
#ifndef XJDFDOCUMENT_H
#define XJDFDOCUMENT_H

#include "abstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/resourceset.h"

namespace Proof {
namespace XJdf {

class DocumentPrivate;
class PROOF_NETWORK_XJDF_EXPORT Document : public AbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Document)
public:
    Document(const Document &) = delete;
    Document &operator=(const Document &) = delete;
    Document(Document &&) = delete;
    Document &operator=(Document &&) = delete;
    ~Document() = default;

    QString jobId() const;
    QString jobPartId() const;
    AuditPoolSP auditPool() const;
    ProductListSP productList() const;

    void setJobId(const QString &arg);
    void setJobPartId(const QString &arg);
    void setAuditPool(const AuditPoolSP &arg);
    void setProductList(const ProductListSP &arg);
    QVector<ProcessType> types() const;
    QVector<ResourceSetSP> resourceSets() const;
    void setTypes(const QVector<ProcessType> &arg);
    void addType(ProcessType arg);
    void setResourceSets(const QVector<ResourceSetSP> &arg);
    ResourceSetSP addResourceSet(const ResourceSetSP &arg);

    template <class T>
    QVector<QSharedPointer<T>> findResources(const std::function<bool(const QSharedPointer<T> &)> &predicate =
                                                 [](const QSharedPointer<T> &) { return true; }) const
    {
        return Proof::algorithms::reduce(resourceSets(),
                                         [predicate](QVector<QSharedPointer<T>> list, const auto &resourseSet) {
                                             list << Proof::algorithms::filter(resourseSet->template resourcesByType<T>(),
                                                                               predicate);
                                             return list;
                                         },
                                         QVector<QSharedPointer<T>>());
    }

    template <class NodeType, typename... Args>
    QSharedPointer<NodeType> createNode(Args &&... args)
    {
        return NodeType::create(qSharedPointerCast<Document>(selfPtr()), std::forward<Args>(args)...);
    }

    static DocumentSP create();

    static DocumentSP fromXJdf(QXmlStreamReader &reader);
    static DocumentSP fromFile(const QString &filePath);

    void toXJdf(QXmlStreamWriter &writer) const override;

    bool toFile(const QString &fileName) const;

signals:
    void jobIdChanged(const QString &arg);
    void jobPartIdChanged(const QString &arg);
    void auditPoolChanged(const Proof::XJdf::AuditPoolSP &arg);
    void productListChanged(const Proof::XJdf::ProductListSP &arg);
    void typesChanged(const QVector<Proof::XJdf::ProcessType> &arg);
    void resourceSetsChanged(const QVector<Proof::XJdf::ResourceSetSP> &arg);

protected:
    explicit Document();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDFDOCUMENT_H
