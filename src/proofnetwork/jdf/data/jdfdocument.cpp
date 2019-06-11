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
#include "proofnetwork/jdf/data/jdfdocument.h"

#include "proofnetwork/jdf/data/jdfnode_p.h"

namespace Proof {
namespace Jdf {

class JdfDocumentPrivate : public JdfNodePrivate
{
    Q_DECLARE_PUBLIC(JdfDocument)
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

JdfDocument::JdfDocument() : JdfNode(*new JdfDocumentPrivate)
{}

JdfDocumentQmlWrapper *JdfDocument::toQmlWrapper(QObject *parent) const
{
    JdfDocumentSP castedSelf = castedSelfPtr<JdfDocument>();
    Q_ASSERT(castedSelf);
    return new JdfDocumentQmlWrapper(castedSelf, parent);
}

JdfDocumentSP JdfDocument::create()
{
    JdfDocumentSP result(new JdfDocument());
    initSelfWeakPtr(result);
    return result;
}

JdfDocumentSP JdfDocument::fromJdf(QXmlStreamReader &xmlReader, const QString &forceJobId,
                                   const QStringList &alternativeIdAttributes, bool sanitize)
{
    JdfDocumentSP document = create();
    JdfNodeSP node = JdfNode::fromJdf(xmlReader, forceJobId, alternativeIdAttributes, sanitize);
    if (!node) {
        qCWarning(proofNetworkJdfDataLog) << "JDF Document not created. Root JDF node is invalid.";
        return JdfDocumentSP();
    }
    //We should be now at EndElement, we should read it and check what is after it
    if (!xmlReader.isEndElement() || xmlReader.hasError()) {
        qCWarning(proofNetworkJdfDataLog) << "JDF Document not created. XML is corrupted." << xmlReader.errorString();
        return JdfDocumentSP();
    }
    xmlReader.readNext();
    while (!xmlReader.atEnd() && xmlReader.isWhitespace())
        xmlReader.readNext();
    if (!xmlReader.atEnd() || xmlReader.hasError()) {
        qCWarning(proofNetworkJdfDataLog) << "JDF Document not created. XML is corrupted." << xmlReader.errorString();
        return JdfDocumentSP();
    }
    document->updateFrom(node);
    return document;
}

QString JdfDocument::toJdf()
{
    QString jdf;
    QXmlStreamWriter jdfWriter(&jdf);

    jdfWriter.setAutoFormatting(true);
    jdfWriter.writeStartDocument();
    jdfWriter.writeDefaultNamespace(QStringLiteral("http://www.CIP4.org/JDFSchema_1_1"));
    JdfNode::toJdf(jdfWriter, true);
    jdfWriter.writeEndDocument();
    return jdf;
}
