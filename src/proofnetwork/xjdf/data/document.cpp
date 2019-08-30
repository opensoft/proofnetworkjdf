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
#include "proofnetwork/xjdf/data/document.h"

#include "proofnetwork/xjdf/data/abstractnode_p.h"
#include <proofnetwork/xjdf/data/auditpool.h>
#include <proofnetwork/xjdf/data/productlist.h>
#include <proofnetwork/xjdf/data/resourceset.h>

#include <QBuffer>
#include <QFile>

namespace Proof {
namespace XJdf {

class DocumentPrivate : public AbstractNodePrivate
{
    Q_DECLARE_PUBLIC(Document)
    DocumentPrivate() { registerChildren(auditPool, productList, resourceSets); }

    QString jobId;
    QString jobPartId;
    mutable AuditPoolSP auditPool;
    mutable ProductListSP productList;
    QVector<ProcessType> types;
    QVector<ResourceSetSP> resourceSets;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QString Document::jobId() const
{
    Q_D_CONST(Document);
    return d->jobId;
}

QString Document::jobPartId() const
{
    Q_D_CONST(Document);
    return d->jobPartId;
}

AuditPoolSP Document::auditPool() const
{
    Q_D_CONST(Document);
    if (!d->auditPool)
        d->auditPool = d->document.toStrongRef()->createNode<AuditPool>();
    return d->auditPool;
}

ProductListSP Document::productList() const
{
    Q_D_CONST(Document);
    if (!d->productList)
        d->productList = d->document.toStrongRef()->createNode<ProductList>();
    return d->productList;
}

void Document::setJobId(const QString &arg)
{
    Q_D(Document);
    if (arg != d->jobId) {
        d->jobId = arg;
        emit jobIdChanged(arg);
    }
}

void Document::setJobPartId(const QString &arg)
{
    Q_D(Document);
    if (arg != d->jobPartId) {
        d->jobPartId = arg;
        emit jobPartIdChanged(arg);
    }
}

void Document::setAuditPool(const AuditPoolSP &arg)
{
    Q_D(Document);
    if (arg != d->auditPool) {
        auto newPool = d->document.toStrongRef()->createNode<AuditPool>();
        newPool->updateFrom(arg);
        d->auditPool = newPool;
        emit auditPoolChanged(d->auditPool);
    }
}

void Document::setProductList(const ProductListSP &arg)
{
    Q_D(Document);
    if (arg != d->productList) {
        auto newProductList = d->document.toStrongRef()->createNode<ProductList>();
        newProductList->updateFrom(arg);
        d->productList = newProductList;
        emit productListChanged(d->productList);
    }
}

QVector<ProcessType> Document::types() const
{
    Q_D_CONST(Document);
    return d->types;
}

QVector<ResourceSetSP> Document::resourceSets() const
{
    Q_D_CONST(Document);
    return d->resourceSets;
}

void Document::setTypes(const QVector<ProcessType> &arg)
{
    Q_D(Document);
    if (arg != d->types) {
        d->types = arg;
        emit typesChanged(arg);
    }
}

void Document::addType(ProcessType arg)
{
    Q_D(Document);
    d->types.append(arg);
    emit typesChanged(d->types);
}

void Document::setResourceSets(const QVector<ResourceSetSP> &arg)
{
    Q_D(Document);
    if (arg != d->resourceSets) {
        d->resourceSets = algorithms::map(arg, [&d](const auto &e) {
            auto newResourceSet = d->document.toStrongRef()->createNode<ResourceSet>();
            newResourceSet->updateFrom(e);
            return newResourceSet;
        });
        emit resourceSetsChanged(d->resourceSets);
    }
}

ResourceSetSP Document::addResourceSet(const ResourceSetSP &arg)
{
    Q_D(Document);
    if (!arg)
        return ResourceSetSP();

    auto newResourceSet = d->document.toStrongRef()->createNode<ResourceSet>();
    newResourceSet->updateFrom(arg);
    d->resourceSets << newResourceSet;
    emit resourceSetsChanged(d->resourceSets);
    return newResourceSet;
}

DocumentSP Document::create()
{
    DocumentSP result(new Document());
    initSelfWeakPtr(result);
    const Document *constDocument = result.data();
    constDocument->d_func()->document = result;
    return result;
}

DocumentSP Document::fromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly))
        return DocumentSP();

    QXmlStreamReader reader(&file);
    return fromXJdf(reader);
}

DocumentSP Document::fromXJdf(QXmlStreamReader &reader)
{
    DocumentSP document = create();

    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.isStartElement()) {
            if (reader.name() == QStringLiteral("XJDF")) {
                document->setNamespaces(reader.namespaceDeclarations());

                auto attributes = reader.attributes();
                document->setJobId(attributes.value(QStringLiteral("JobID")).toString());
                if (attributes.hasAttribute(QStringLiteral("JobPartID")))
                    document->setJobPartId(attributes.value(QStringLiteral("JobPartID")).toString());
                auto types = reader.attributes().value(QStringLiteral("Types")).toString().split(' ');
                document->setTypes(algorithms::map(types, &Proof::XJdf::processTypeFromString, QVector<ProcessType>()));

            } else if (reader.name() == QStringLiteral("ProductList")) {
                document->setProductList(ProductList::fromXJdf(reader, document));
            } else if (reader.name() == QStringLiteral("AuditPool")) {
                document->setAuditPool(AuditPool::fromXJdf(reader, document));
            } else if (reader.name() == QStringLiteral("ResourceSet")) {
                auto resourceSet = ResourceSet::fromXJdf(reader, document);
                if (resourceSet)
                    document->addResourceSet(resourceSet);
            } else {
                document->readFieldsFromXJdf(reader);
            }
        } else if (reader.isEndElement()) {
            if (reader.name() == QStringLiteral("XJDF"))
                break;
        }
        reader.readNext();
    }
    document->setFetched(true);

    if (document->jobId().isEmpty() || !document->auditPool() || !document->productList()) {
        qCWarning(proofNetworkXJdfDataLog) << "XJDF Document not created. XML is corrupted.";
        return DocumentSP();
    }

    return document;
}

void Document::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(Document);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement(QStringLiteral("XJDF"));

    writer.writeDefaultNamespace(QStringLiteral("http://www.CIP4.org/JDFSchema_2_0"));

    for (const auto &ns : qAsConst(d->namespaces))
        writer.writeNamespace(ns.namespaceUri().toString(), ns.prefix().toString());

    writer.writeAttribute(QStringLiteral("JobID"), jobId());
    if (!jobPartId().isEmpty())
        writer.writeAttribute(QStringLiteral("JobPartID"), jobPartId());
    QStringList types = algorithms::map(this->types(), &Proof::XJdf::processTypeToString, QStringList());
    writer.writeAttribute(QStringLiteral("Types"), types.join(' '));
    if (isValidAndDirty(d->auditPool))
        d->auditPool->toXJdf(writer);
    if (isValidAndDirty(d->productList))
        d->productList->toXJdf(writer);

    for (const auto &set : qAsConst(d->resourceSets))
        set->toXJdf(writer);
    writer.writeEndElement();
    writer.writeEndDocument();
}

bool Document::toFile(const QString &fileName) const
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
        return false;
    QString jdf;
    QXmlStreamWriter xwriter(&jdf);
    toXJdf(xwriter);
    file.write(jdf.toUtf8());
    return true;
}

Document::Document() : AbstractNode(*new DocumentPrivate)
{}

void Document::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    DocumentSP castedOther = qSharedPointerCast<Document>(other);
    setNamespaces(castedOther->namespaces());
    setJobId(castedOther->jobId());
    setJobPartId(castedOther->jobPartId());
    setTypes(castedOther->types());
    setAuditPool(castedOther->auditPool());
    setProductList(castedOther->productList());
    setResourceSets(castedOther->resourceSets());

    AbstractNode::updateSelf(other);
}
