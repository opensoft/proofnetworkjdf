#include "foldingparams.h"
#include "proofnetwork/jdf/data/abstractresource_p.h"

namespace Proof {
namespace Jdf {

class FoldingParamsPrivate : AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(FoldingParams)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString foldCatalog = "F2-1"; //without folding by default
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

QString FoldingParams::foldCatalog() const
{
    Q_D(const FoldingParams);
    return d->foldCatalog;
}

void FoldingParams::setFoldCatalog(const QString &foldCatalog)
{
    Q_D(FoldingParams);
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
            foldingParams->setFoldCatalog( attributes.value("FoldCatalog").toString());
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
