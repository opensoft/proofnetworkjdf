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
#include "proofnetwork/jdf/data/boxpackingparams.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/boxpackingparamslink.h"

namespace Proof {
namespace Jdf {

class BoxPackingParamsPrivate : AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(BoxPackingParams)

    BoxPackingParamsPrivate() : AbstractResourcePrivate(ResourceClass::ParameterClass) {}
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

BoxPackingParamsQmlWrapper *BoxPackingParams::toQmlWrapper(QObject *parent) const
{
    BoxPackingParamsSP castedSelf = castedSelfPtr<BoxPackingParams>();
    Q_ASSERT(castedSelf);
    return new BoxPackingParamsQmlWrapper(castedSelf, parent);
}

BoxPackingParamsSP BoxPackingParams::create()
{
    BoxPackingParamsSP result(new BoxPackingParams());
    initSelfWeakPtr(result);
    return result;
}

BoxPackingParamsSP BoxPackingParams::fromJdf(QXmlStreamReader &xmlReader)
{
    BoxPackingParamsSP boxPackingParams = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "BoxPackingParams" && xmlReader.isStartElement() && !boxPackingParams->isFetched()) {
            boxPackingParams->setFetched(true);
            AbstractResourceSP castedBoxPackingParams = qSharedPointerCast<AbstractResource>(boxPackingParams);
            AbstractResource::fromJdf(xmlReader, castedBoxPackingParams);

        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return boxPackingParams;
}

void BoxPackingParams::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement(jdfNodeName());
    AbstractResource::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

BoxPackingParamsLinkSP BoxPackingParams::toLink(LinkUsage usage) const
{
    BoxPackingParamsLinkSP link = BoxPackingParamsLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

BoxPackingParams::BoxPackingParams() : AbstractResource(*new BoxPackingParamsPrivate)
{}

void BoxPackingParams::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AbstractResource::updateSelf(other);
}
