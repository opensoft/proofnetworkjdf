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
#include "proofnetwork/jdf/data/devicefilter.h"

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DeviceFilterPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DeviceFilter)

    DeviceFilterDetails details = DeviceFilterDetails::NoneDeviceFilterDetails;
};

DeviceFilterDetails DeviceFilter::details() const
{
    Q_D_CONST(DeviceFilter);
    return d->details;
}

void DeviceFilter::setDetails(DeviceFilterDetails arg)
{
    Q_D(DeviceFilter);
    if (d->details != arg) {
        d->details = arg;
        emit detailsChanged(d->details);
    }
}

NetworkDataEntityQmlWrapper *DeviceFilter::toQmlWrapper(QObject *) const
{
    Q_ASSERT(false);
    return nullptr;
}

DeviceFilterSP DeviceFilter::create()
{
    DeviceFilterSP result(new DeviceFilter());
    initSelfWeakPtr(result);
    return result;
}

void DeviceFilter::toJmf(QXmlStreamWriter &xmlWriter)
{
    xmlWriter.writeStartElement(QStringLiteral("DeviceFilter"));
    xmlWriter.writeAttribute(QStringLiteral("DeviceDetails"), deviceFilterDetailsToString(details()));
    xmlWriter.writeEndElement();
}

DeviceFilterSP DeviceFilter::fromJmf(QXmlStreamReader &xmlReader)
{
    DeviceFilterSP result;
    if (xmlReader.isStartElement() && xmlReader.name() == "DeviceFilter") {
        result = create();
        result->setFetched(true);
        auto attributes = xmlReader.attributes();
        result->setDetails(deviceFilterDetailsFromString(attributes.value(QStringLiteral("DeviceDetails")).toString()));
        xmlReader.skipCurrentElement();
    }
    return result;
}

DeviceFilter::DeviceFilter() : NetworkDataEntity(*new DeviceFilterPrivate)
{}

void DeviceFilter::updateSelf(const NetworkDataEntitySP &other)
{
    DeviceFilterSP castedOther = qSharedPointerCast<DeviceFilter>(other);
    setDetails(castedOther->details());
    NetworkDataEntity::updateSelf(other);
}

} // namespace Jdf
} // namespace Proof
