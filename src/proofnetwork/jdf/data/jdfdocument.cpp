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
        qCWarning(proofNetworkJdfDataLog) << "JDF Document not created. XML is corrupted.";
        return JdfDocumentSP();
    }
    xmlReader.readNext();
    while (!xmlReader.atEnd() && xmlReader.isWhitespace())
        xmlReader.readNext();
    if (!xmlReader.atEnd() || xmlReader.hasError()) {
        qCWarning(proofNetworkJdfDataLog) << "JDF Document not created. XML is corrupted.";
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
