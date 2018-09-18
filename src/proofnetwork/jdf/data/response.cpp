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
#include "proofnetwork/jdf/data/response.h"

#include "proofnetwork/jdf/data/response_p.h"

namespace Proof {
namespace Jdf {

NotificationSP Response::notification() const
{
    Q_D_CONST(Response);
    return d->notification;
}

void Response::setNotification(const NotificationSP &arg)
{
    Q_D(Response);
    if (d->notification != arg) {
        d->notification = arg;
        emit notificationChanged(d->notification);
    }
}

Response::Response(ResponsePrivate &dd) : Message(dd)
{}

void Response::updateSelf(const NetworkDataEntitySP &other)
{
    ResponseSP castedOther = qSharedPointerCast<Response>(other);
    setNotification(castedOther->notification());
    Message::updateSelf(other);
}

void ResponsePrivate::specificMessageFromJmf(QXmlStreamReader &xmlReader)
{
    Q_Q(Response);
    if (xmlReader.name() == "Notification")
        q->setNotification(Notification::fromJdf(xmlReader));
    else
        xmlReader.skipCurrentElement();
}

QString ResponsePrivate::tagName() const
{
    return QStringLiteral("Response");
}

void ResponsePrivate::specificMessageToJmf(QXmlStreamWriter &xmlWriter) const
{
    if (notification != nullptr)
        notification->toJdf(xmlWriter);
}

} // namespace Jdf
} // namespace Proof
