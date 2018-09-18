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
#include "proofnetwork/jdf/data/foldingparams.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/foldingparamslink.h"

#include <QRegExp>

namespace Proof {
namespace Jdf {

class FoldingParamsPrivate : AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(FoldingParams)

    FoldingParamsPrivate() : AbstractResourcePrivate(ResourceClass::ParameterClass) {}

    QString foldCatalog = QString();
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

QString FoldingParams::foldCatalog() const
{
    Q_D_CONST(FoldingParams);
    return d->foldCatalog;
}

bool verifyFoldCatalog(const QString &foldCatalog)
{
    // http://www.cip4.org/documents/jdf_specifications/html/Resources.html#0_FoldingParams
    QRegExp regexp("F(\\d?[02468])-(\\d{1,2}|X)");
    if (!regexp.exactMatch(foldCatalog))
        return false;

    return (regexp.cap(1).toInt() && (regexp.cap(2).toInt() || regexp.cap(2).toLower() == QLatin1String("x")));
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
        qCDebug(proofNetworkJdfDataLog) << "Wrong format of FoldCatalog: " << foldCatalog;
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
    FoldingParamsSP castedSelf = castedSelfPtr<FoldingParams>();
    Q_ASSERT(castedSelf);
    return new FoldingParamsQmlWrapper(castedSelf, parent);
}

FoldingParamsSP FoldingParams::create()
{
    FoldingParamsSP result(new FoldingParams());
    initSelfWeakPtr(result);
    return result;
}

FoldingParamsSP FoldingParams::fromJdf(QXmlStreamReader &xmlReader)
{
    FoldingParamsSP foldingParams = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "FoldingParams" && xmlReader.isStartElement() && !foldingParams->isFetched()) {
            foldingParams->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            QString value = attributes.value(QStringLiteral("FoldCatalog")).toString().trimmed();
            foldingParams->setFoldCatalog(value);
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

    jdfWriter.writeStartElement(QStringLiteral("FoldingParams"));
    jdfWriter.writeAttribute(QStringLiteral("FoldCatalog"), d->foldCatalog);
    AbstractResource::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

FoldingParamsLinkSP FoldingParams::toLink(LinkUsage usage) const
{
    FoldingParamsLinkSP link = FoldingParamsLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

FoldingParams::FoldingParams() : AbstractResource(*new FoldingParamsPrivate)
{}

void FoldingParams::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    FoldingParamsSP castedOther = qSharedPointerCast<FoldingParams>(other);
    setFoldCatalog(castedOther->foldCatalog());

    AbstractResource::updateSelf(other);
}
