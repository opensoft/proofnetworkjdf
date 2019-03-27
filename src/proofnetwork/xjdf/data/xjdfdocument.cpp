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
#include "proofnetwork/xjdf/data/xjdfdocument.h"

#include "proofnetwork/xjdf/data/graybox_p.h"
#include <proofnetwork/xjdf/data/auditpool.h>
#include <proofnetwork/xjdf/data/productlist.h>

#include <QBuffer>
#include <QFile>

namespace Proof {
namespace XJdf {

class XJdfDocumentPrivate : public GrayBoxPrivate
{
    Q_DECLARE_PUBLIC(XJdfDocument)

    QString jobId;
    QString jobPartId;
    AuditPoolSP auditPool;
    ProductListSP productList;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

QString XJdfDocument::jobId() const
{
    Q_D_CONST(XJdfDocument);
    return d->jobId;
}

QString XJdfDocument::jobPartId() const
{
    Q_D_CONST(XJdfDocument);
    return d->jobPartId;
}

AuditPoolSP XJdfDocument::auditPool() const
{
    Q_D_CONST(XJdfDocument);
    return d->auditPool;
}

ProductListSP XJdfDocument::productList() const
{
    Q_D_CONST(XJdfDocument);
    return d->productList;
}

void XJdfDocument::setJobId(const QString &arg)
{
    Q_D(XJdfDocument);
    if (arg != d->jobId) {
        d->jobId = arg;
        emit jobIdChanged(arg);
    }
}

void XJdfDocument::setJobPartId(const QString &arg)
{
    Q_D(XJdfDocument);
    if (arg != d->jobPartId) {
        d->jobPartId = arg;
        emit jobPartIdChanged(arg);
    }
}

void XJdfDocument::setAuditPool(const AuditPoolSP &arg)
{
    Q_D(XJdfDocument);
    if (arg != d->auditPool) {
        d->auditPool = arg;
        emit auditPoolChanged(arg);
    }
}

void XJdfDocument::setProductList(const ProductListSP &arg)
{
    Q_D(XJdfDocument);
    if (arg != d->productList) {
        d->productList = arg;
        emit productListChanged(arg);
    }
}

XJdfDocumentSP XJdfDocument::create()
{
    XJdfDocumentSP result(new XJdfDocument());
    initSelfWeakPtr(result);
    return result;
}

XJdfDocumentSP XJdfDocument::fromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly))
        return XJdfDocumentSP();

    QXmlStreamReader reader(&file);
    return fromXJdf(reader);
}

XJdfDocumentSP XJdfDocument::fromXJdf(QXmlStreamReader &reader)
{
    XJdfDocumentSP document = create();
    document->d_func()->document = document;

    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.isStartElement()) {
            if (reader.name() == QStringLiteral("XJDF")) {
                document->readAttributesFromXJdf(reader);
                auto attributes = reader.attributes();
                document->setJobId(attributes.value(QStringLiteral("JobID")).toString());
                if (attributes.hasAttribute(QStringLiteral("JobPartID")))
                    document->setJobPartId(attributes.value(QStringLiteral("JobPartID")).toString());
            } else if (reader.name() == QStringLiteral("ProductList")) {
                document->setProductList(ProductList::fromXJdf(reader, document));
            } else if (reader.name() == QStringLiteral("AuditPool")) {
                document->setAuditPool(AuditPool::fromXJdf(reader, document));
            } else {
                document->fillFromXJdf(reader);
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
        return XJdfDocumentSP();
    }

    return document;
}

void XJdfDocument::toXJdf(QXmlStreamWriter &writer, bool) const
{
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement(QStringLiteral("XJDF"));

    writer.writeDefaultNamespace(QStringLiteral("http://www.CIP4.org/JDFSchema_2_0"));
    writer.writeNamespace(QStringLiteral("https://www.opensoftdev.com/profit"), QStringLiteral("profit"));
    writer.writeAttribute(QStringLiteral("JobID"), jobId());
    writer.writeAttribute(QStringLiteral("JobPartID"), jobPartId());
    GrayBox::toXJdf(writer);
    auditPool()->toXJdf(writer);
    productList()->toXJdf(writer);
    writer.writeEndElement();
    writer.writeEndDocument();
}

bool XJdfDocument::toFile(const QString &fileName) const
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

XJdfDocument::XJdfDocument() : GrayBox(*new XJdfDocumentPrivate)
{}

void XJdfDocument::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    XJdfDocumentSP castedOther = qSharedPointerCast<XJdfDocument>(other);
    setJobId(castedOther->jobId());
    setJobPartId(castedOther->jobPartId());
    setAuditPool(castedOther->auditPool());
    setProductList(castedOther->productList());

    GrayBox::updateSelf(other);
}
