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
#include "proofnetwork/jdf/data/knowndevicesquery.h"

#include "proofnetwork/jdf/data/devicefilter.h"
#include "proofnetwork/jdf/data/query_p.h"

namespace Proof {
namespace Jdf {

class KnownDevicesQueryPrivate : public QueryPrivate
{
    Q_DECLARE_PUBLIC(KnownDevicesQuery)

protected:
    KnownDevicesQueryPrivate() { registerChildren(deviceFilter); }

    void specificMessageFromJmf(QXmlStreamReader &xmlReader) override;
    QString typeName() const override;
    void specificMessageToJmf(QXmlStreamWriter &xmlWriter) const override;

private:
    DeviceFilterSP deviceFilter = DeviceFilter::create();
};

DeviceFilterSP KnownDevicesQuery::deviceFilter() const
{
    Q_D_CONST(KnownDevicesQuery);
    return d->deviceFilter;
}

void KnownDevicesQuery::setDeviceFilter(const DeviceFilterSP &arg)
{
    Q_D(KnownDevicesQuery);
    if (d->deviceFilter != arg) {
        d->deviceFilter = arg;
        emit deviceFilterChanged(d->deviceFilter);
    }
}

KnownDevicesQuerySP KnownDevicesQuery::create()
{
    KnownDevicesQuerySP result(new KnownDevicesQuery());
    initSelfWeakPtr(result);
    return result;
}

KnownDevicesQuery::KnownDevicesQuery() : Query(*new KnownDevicesQueryPrivate)
{}

void KnownDevicesQuery::updateSelf(const NetworkDataEntitySP &other)
{
    KnownDevicesQuerySP castedOther = qSharedPointerCast<KnownDevicesQuery>(other);
    setDeviceFilter(castedOther->deviceFilter());
    Query::updateSelf(other);
}

void KnownDevicesQueryPrivate::specificMessageFromJmf(QXmlStreamReader &xmlReader)
{
    Q_Q(KnownDevicesQuery);
    while (xmlReader.readNextStartElement()) {
        if (xmlReader.name() == "DeviceFilter") {
            auto filter = DeviceFilter::fromJmf(xmlReader);
            if (filter != nullptr)
                q->setDeviceFilter(filter);
            else
                xmlReader.skipCurrentElement();
        } else {
            QueryPrivate::specificMessageFromJmf(xmlReader);
        }
    }
}

QString KnownDevicesQueryPrivate::typeName() const
{
    return QStringLiteral("KnownDevices");
}

void KnownDevicesQueryPrivate::specificMessageToJmf(QXmlStreamWriter &xmlWriter) const
{
    if (deviceFilter != nullptr)
        deviceFilter->toJmf(xmlWriter);
    QueryPrivate::specificMessageToJmf(xmlWriter);
}

} // namespace Jdf
} // namespace Proof
