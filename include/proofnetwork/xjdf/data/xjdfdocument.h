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
#ifndef XJDFDOCUMENT_H
#define XJDFDOCUMENT_H

#include "graybox.h"

namespace Proof {
namespace XJdf {

class XJdfDocumentPrivate;
class PROOF_NETWORK_XJDF_EXPORT XJdfDocument : public GrayBox
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(XJdfDocument)
public:
    XJdfDocument(const XJdfDocument &) = delete;
    XJdfDocument &operator=(const XJdfDocument &) = delete;
    XJdfDocument(XJdfDocument &&) = delete;
    XJdfDocument &operator=(XJdfDocument &&) = delete;
    ~XJdfDocument() = default;

    QString jobId() const;
    QString jobPartId() const;
    AuditPoolSP auditPool() const;
    ProductListSP productList() const;

    void setJobId(const QString &arg);
    void setJobPartId(const QString &arg);
    void setAuditPool(const AuditPoolSP &arg);
    void setProductList(const ProductListSP &arg);

    static XJdfDocumentSP create();

    static XJdfDocumentSP fromXJdf(QXmlStreamReader &reader);
    static XJdfDocumentSP fromFile(const QString &filePath);

    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

    bool toFile(const QString &fileName) const;

signals:
    void jobIdChanged(const QString &arg);
    void jobPartIdChanged(const QString &arg);
    void auditPoolChanged(const Proof::XJdf::AuditPoolSP &arg);
    void productListChanged(const Proof::XJdf::ProductListSP &arg);

protected:
    explicit XJdfDocument();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDFDOCUMENT_H
