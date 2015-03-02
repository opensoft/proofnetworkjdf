#include "jdfdocument.h"

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/data/cuttingprocess.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfdocumentqmlwrapper.h"

namespace Proof {
namespace Jdf {

class JdfDocumentPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(JdfDocument)

    QString id;
    QString jobId;
    CuttingProcessSP cuttingProcess = CuttingProcess::defaultObject();
};

QString JdfDocument::id() const
{
    Q_D(const JdfDocument);
    return d->id;
}

QString JdfDocument::jobId() const
{
    Q_D(const JdfDocument);
    return d->jobId;
}

CuttingProcessSP JdfDocument::cuttingProcess() const
{
    Q_D(const JdfDocument);
    return d->cuttingProcess;
}

void JdfDocument::setId(const QString &arg)
{
    Q_D(JdfDocument);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void JdfDocument::setJobId(const QString &arg)
{
    Q_D(JdfDocument);
    if (d->jobId != arg) {
        d->jobId = arg;
        emit jobIdChanged(d->jobId);
    }
}

void JdfDocument::setCuttingProcess(const CuttingProcessSP &arg)
{
    Q_D(JdfDocument);
    if (arg == nullptr)
        setCuttingProcess(CuttingProcess::defaultObject());
    else if (d->cuttingProcess != arg) {
        d->cuttingProcess = arg;
        emit cuttingProcessChanged(d->cuttingProcess);
    }
}

void JdfDocument::updateFrom(const NetworkDataEntitySP &other)
{
    JdfDocumentSP castedOther = qSharedPointerCast<JdfDocument>(other);
    setId(castedOther->id());
    setJobId(castedOther->jobId());
    setCuttingProcess(castedOther->cuttingProcess());

    NetworkDataEntity::updateFrom(other);
}

JdfDocumentQmlWrapper *JdfDocument::toQmlWrapper(QObject *parent) const
{
    Q_D(const JdfDocument);
    JdfDocumentSP castedSelf = qSharedPointerCast<JdfDocument>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new JdfDocumentQmlWrapper(castedSelf, parent);
}

JdfDocumentSP JdfDocument::create()
{
    JdfDocumentSP result(new JdfDocument());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

JdfDocumentSP JdfDocument::fromJdf(QXmlStreamReader &xmlReader)
{
    JdfDocumentSP document = create();
    document->setFetched(true);

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "JDF") {
                QXmlStreamAttributes attributes = xmlReader.attributes();
                if (attributes.value("Type").toString() == "Product") {
                    document->setId(attributes.value("ID").toString());
                    document->setJobId(attributes.value("JobID").toString());
                }
            }
            if (xmlReader.name() == "ResourcePool")
                document->setCuttingProcess(CuttingProcess::fromJdf(xmlReader));
        }
    }

    return document;
}

QString JdfDocument::toJdf()
{
    Q_D(JdfDocument);
    QString jdf;
    QXmlStreamWriter jdfWriter(&jdf);

    jdfWriter.setAutoFormatting(true);
    jdfWriter.writeStartDocument();

    jdfWriter.writeStartElement("JDF");
    {
        jdfWriter.writeDefaultNamespace("http://www.CIP4.org/JDFSchema_1_1");
        jdfWriter.writeAttribute("ID", d->id);
        jdfWriter.writeAttribute("JobID", d->jobId);
        jdfWriter.writeAttribute("Status", "Waiting");
        jdfWriter.writeAttribute("Type", "Product");
        jdfWriter.writeAttribute("Version", "1.4");
        d->cuttingProcess->toJdf(jdfWriter);
    }
    jdfWriter.writeEndElement();

    jdfWriter.writeEndDocument();

    return jdf;
}

JdfDocumentSP JdfDocument::defaultObject()
{
    static JdfDocumentSP entity = create();
    return entity;
}

JdfDocument::JdfDocument()
    : NetworkDataEntity(*new JdfDocumentPrivate)
{
}

}
}
