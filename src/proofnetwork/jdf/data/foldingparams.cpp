#include "foldingparams.h"
#include "proofnetwork/jdf/data/abstractresource_p.h"

#include <QRegExp>

namespace Proof {
namespace Jdf {

class FoldingParamsPrivate : AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(FoldingParams)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString foldCatalog = QString();
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

QString FoldingParams::foldCatalog() const
{
    Q_D(const FoldingParams);
    return d->foldCatalog;
}

bool verifyFoldCatalog(const QString &foldCatalog)
{
    // http://www.cip4.org/documents/jdf_specifications/html/Resources.html#0_FoldingParams
    QRegExp regexp("F(\\d?[02468])-(\\d{1,2}|X)");
    if (!regexp.exactMatch(foldCatalog))
        return false;

    return (regexp.cap(1).toInt() && regexp.cap(2).toInt() ||  regexp.cap(2).toLower() == "x");
}
/*!
 *    \brief sets FoldCatalog resource
 *
 *    Describes the type of fold according to the folding catalog
 *    Value format is: " Fn-i " where “n” is the number of finished
 *    pages and “i” is either an integer, which identifies a particular
 *    fold or the letter "X" , which identifies a generic fold.
 *    E.g., "F6-2" describes a Z-fold of 6 finished pages, and "F6-X . "
 *    describes a generic fold with 6 finished pages.
 *    Reference: http://www.cip4.org/documents/jdf_specifications/html/Resources.html#0_FoldingParams
 */
void FoldingParams::setFoldCatalog(const QString &foldCatalog)
{
    Q_D(FoldingParams);

    if (!verifyFoldCatalog(foldCatalog)) {
        qCWarning(proofNetworkJdfDataLog) << "Wrong format of FoldCatalog: " << foldCatalog;
        d->foldCatalog = QString();
        return;
    }
    if (d->foldCatalog != foldCatalog) {
        d->foldCatalog = foldCatalog;
        emit foldCatalogChanged(d->foldCatalog);
    }
}

FoldingParamsQmlWrapper *FoldingParams::toQmlWrapper(QObject *parent) const
{
    Q_D(const FoldingParams);
    FoldingParamsSP castedSelf = qSharedPointerCast<FoldingParams>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new FoldingParamsQmlWrapper(castedSelf, parent);
}

FoldingParamsSP FoldingParams::create()
{
    FoldingParamsSP result(new FoldingParams());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

FoldingParamsSP FoldingParams::defaultObject()
{
    static FoldingParamsSP entity = create();
    return entity;
}

FoldingParamsSP FoldingParams::fromJdf(QXmlStreamReader &xmlReader)
{
    FoldingParamsSP foldingParams = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "FoldingParams" && xmlReader.isStartElement() && !foldingParams->isFetched()) {
            foldingParams->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            QString value = attributes.value("FoldCatalog").toString();
            foldingParams->setFoldCatalog(value);
            if (foldingParams->foldCatalog().isEmpty()) {
                qCCritical(proofNetworkJdfDataLog) << "FoldingParams not created.";
                return FoldingParamsSP();
            }
            AbstractResourceSP castedFoldingParams = qSharedPointerCast<AbstractResource>(foldingParams);
            AbstractResource::fromJdf(xmlReader, castedFoldingParams);

        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return foldingParams;
}

void FoldingParams::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(FoldingParams);

    jdfWriter.writeStartElement("FoldingParams");
    jdfWriter.writeAttribute("FoldCatalog", d->foldCatalog);
    AbstractResource::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

FoldingParams::FoldingParams()
    : AbstractResource(*new FoldingParamsPrivate)
{
    setResourceClass(ApiHelper::ParameterClass);
}

void FoldingParamsPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(FoldingParams);
    FoldingParamsSP castedOther = qSharedPointerCast<FoldingParams>(other);
    q->setFoldCatalog(castedOther->foldCatalog());

    AbstractResourcePrivate::updateFrom(other);
}
