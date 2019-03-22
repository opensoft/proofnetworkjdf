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

    QXmlStreamReader xjdfReader(&file);
    return fromXJdf(xjdfReader);
}

XJdfDocumentSP XJdfDocument::fromXJdf(QXmlStreamReader &xjdfReader)
{
    XJdfDocumentSP document = create();

    while (!xjdfReader.atEnd() && !xjdfReader.hasError()) {
        if (xjdfReader.isStartElement()) {
            if (xjdfReader.name() == "XJDF") {
                document->readAttributesFromXJdf(xjdfReader);
                auto attributes = xjdfReader.attributes();
                document->setJobId(attributes.value("JobID").toString());
                if (attributes.hasAttribute("JobPartID"))
                    document->setJobPartId(attributes.value("JobPartID").toString());
            } else if (xjdfReader.name() == "ProductList") {
                document->setProductList(ProductList::fromXJdf(xjdfReader));
            } else if (xjdfReader.name() == "AuditPool") {
                document->setAuditPool(AuditPool::fromXJdf(xjdfReader));
            } else {
                document->fillFromXJdf(xjdfReader);
            }
        } else if (xjdfReader.isEndElement()) {
            if (xjdfReader.name() == "JDF")
                break;
        }
        xjdfReader.readNext();
    }
    document->setFetched(true);
    return document;

    if (document->jobId().isEmpty() || !document->auditPool() || !document->productList()) {
        qCWarning(proofNetworkXJdfDataLog) << "XJDF Document not created. XML is corrupted.";
        return XJdfDocumentSP();
    }

    return document;
}

void XJdfDocument::toXJdf(QXmlStreamWriter &xjdfWriter, bool) const
{
    xjdfWriter.setAutoFormatting(true);
    xjdfWriter.writeStartDocument();
    xjdfWriter.writeDefaultNamespace(QStringLiteral("http://www.CIP4.org/JDFSchema_2_0"));
    xjdfWriter.writeNamespace(QStringLiteral("https://www.opensoftdev.com/profit"), QStringLiteral("profit"));
    xjdfWriter.writeAttribute("JobID", jobId());
    xjdfWriter.writeAttribute("JobPartID", jobPartId());
    GrayBox::toXJdf(xjdfWriter);
    auditPool()->toXJdf(xjdfWriter);
    productList()->toXJdf(xjdfWriter);
    xjdfWriter.writeEndDocument();
}

bool XJdfDocument::toFile(const QString fileName) const
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
        return false;
    QString jdf;
    QXmlStreamWriter xxjdfWriter(&jdf);
    toXJdf(xxjdfWriter);
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

    NetworkDataEntity::updateSelf(other);
    GrayBox::updateSelf(other);
}
