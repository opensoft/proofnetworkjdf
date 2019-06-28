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
#include "proofnetwork/xjdf/data/foldingparams.h"

#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/data/resource_p.h"

namespace Proof {
namespace XJdf {

class FoldingParamsPrivate : public ResourcePrivate
{
    Q_DECLARE_PUBLIC(FoldingParams)
    FoldingParamsPrivate() {}

    QString foldCatalog;
    QString foldingDetails;
};

} // namespace XJdf
} // namespace Proof

using namespace Proof;
using namespace Proof::XJdf;

bool verifyFoldCatalog(const QString &foldCatalog)
{
    QRegExp regexp("F(\\d?[02468])-(\\d{1,2}|X)");
    if (!regexp.exactMatch(foldCatalog))
        return false;

    return (regexp.cap(1).toInt() && (regexp.cap(2).toInt() || regexp.cap(2).toLower() == QLatin1String("x")));
}

ResourceSP FoldingParams::cloneTo(const DocumentSP &document)
{
    auto newParams = document->createNode<FoldingParams>();
    newParams->updateFrom(qSharedPointerCast<FoldingParams>(selfPtr()));
    return std::move(newParams);
}

QString FoldingParams::foldCatalog() const
{
    Q_D_CONST(FoldingParams);
    return d->foldCatalog;
}

QString FoldingParams::foldingDetails() const
{
    Q_D_CONST(FoldingParams);
    return d->foldingDetails;
}

void FoldingParams::setFoldCatalog(const QString &arg)
{
    Q_D(FoldingParams);

    if (!verifyFoldCatalog(arg)) {
        qCDebug(proofNetworkXJdfDataLog) << "Wrong format of FoldCatalog: " << arg;
        d->foldCatalog = QString();
        return;
    }
    if (d->foldCatalog != arg) {
        d->foldCatalog = arg;
        emit foldCatalogChanged(d->foldCatalog);
    }
}

void FoldingParams::setFoldingDetails(const QString &arg)
{
    Q_D(FoldingParams);
    if (arg != d->foldingDetails) {
        d->foldingDetails = arg;
        emit foldingDetailsChanged(arg);
    }
}

FoldingParamsSP FoldingParams::create(const DocumentSP &document)
{
    FoldingParamsSP result(new FoldingParams());
    result->d_func()->document = document;
    initSelfWeakPtr(result);
    return result;
}

FoldingParamsSP FoldingParams::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    FoldingParamsSP params;
    if (reader.isStartElement() && reader.name() == QStringLiteral("FoldingParams")) {
        params = create(document);
        params->d_func()->document = document;

        params->setFoldCatalog(reader.attributes().value(QStringLiteral("FoldCatalog")).toString());
        params->setFoldingDetails(reader.attributes().value(QStringLiteral("FoldingDetails")).toString());
        params->setFetched(true);
        reader.readNext();
    }
    return params;
}

void FoldingParams::toXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(FoldingParams);
    NodeWriterGuard guard(writeFieldsToXJdf(writer));

    writer.writeStartElement(QStringLiteral("FoldingParams"));
    if (!d->foldingDetails.isEmpty())
        writer.writeAttribute(QStringLiteral("FoldingDetails"), d->foldingDetails);

    writer.writeAttribute(QStringLiteral("FoldCatalog"), d->foldCatalog);
    writer.writeEndElement();
}

FoldingParams::FoldingParams() : Resource(*new FoldingParamsPrivate)
{}

void FoldingParams::updateSelf(const NetworkDataEntitySP &other)
{
    FoldingParamsSP castedOther = qSharedPointerCast<FoldingParams>(other);
    setFoldCatalog(castedOther->foldCatalog());
    setFoldingDetails(castedOther->foldingDetails());

    Resource::updateSelf(other);
}
