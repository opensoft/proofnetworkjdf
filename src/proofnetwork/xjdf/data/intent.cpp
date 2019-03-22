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
#include "proofnetwork/xjdf/data/intent.h"

#include "proofnetwork/xjdf/data/intent_p.h"

using namespace Proof;
using namespace Proof::XJdf;

QMap<QString, std::function<IntentSP(QXmlStreamReader &)>> IntentPrivate::creators;

QString Intent::name() const
{
    Q_D_CONST(Intent);
    return d->name;
}

void Intent::setName(const QString &arg)
{
    Q_D(Intent);
    if (arg != d->name) {
        d->name = arg;
        emit nameChanged(arg);
    }
}

bool Intent::fillFromXJdf(QXmlStreamReader &)
{
    //NOTE: Nothing there for now, but it can be fill later
    return false;
}

void Intent::readAttributesFromXJdf(QXmlStreamReader &xjdfReader)
{
    auto attributes = xjdfReader.attributes();
    if (attributes.hasAttribute("Name")) {
        auto name = attributes.value("name").toString();
        setName(name);
    }
}

void Intent::toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd) const
{
    Q_D_CONST(Intent);
    if (writeEnd) {
        xjdfWriter.writeEndElement();
        return;
    }

    xjdfWriter.writeStartElement("Intent");
    if (!d->name.isEmpty())
        xjdfWriter.writeAttribute("Name", d->name);
}

IntentSP Intent::fromXJdf(QXmlStreamReader &xjdfReader)
{
    if (xjdfReader.isStartElement() && xjdfReader.name() == "Intent") {
        auto attributes = xjdfReader.attributes();
        QString name;
        if (attributes.hasAttribute("Name"))
            name = attributes.value("Name").toString();

        xjdfReader.readNextStartElement();
        if (!xjdfReader.atEnd() && !xjdfReader.hasError()) {
            auto creator = resourceCreator(xjdfReader.name().toString());
            if (creator) {
                auto intent = creator(xjdfReader);
                intent->setName(name);
            }
        }
    }

    return IntentSP();
}

Intent::Intent() : Intent(*new IntentPrivate)
{}

Intent::Intent(IntentPrivate &dd) : XJdfAbstractNode(dd)
{}

void Intent::updateSelf(const NetworkDataEntitySP &other)
{
    IntentSP castedOther = qSharedPointerCast<Intent>(other);
    setName(castedOther->name());
    XJdfAbstractNode::updateSelf(other);
}

void Intent::addResourceCreator(const QString &name, std::function<IntentSP(QXmlStreamReader &)> &&creator)
{
    IntentPrivate::creators[name] = creator;
}

std::function<IntentSP(QXmlStreamReader &)> &Intent::resourceCreator(const QString &name)
{
    return IntentPrivate::creators[name];
}
