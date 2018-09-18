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
#include "proofnetwork/jdf/data/dropitemintent.h"

#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DropItemIntentPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DropItemIntent)

    DropItemIntentPrivate() : NetworkDataEntityPrivate() { registerChildren(component); }

    ComponentSP component = Component::create();
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ComponentSP DropItemIntent::component() const
{
    Q_D_CONST(DropItemIntent);
    return d->component;
}

void DropItemIntent::setComponent(const ComponentSP &arg)
{
    Q_D(DropItemIntent);
    if (d->component != arg) {
        d->component = arg;
        emit componentChanged(arg);
    }
}

DropItemIntentQmlWrapper *DropItemIntent::toQmlWrapper(QObject *parent) const
{
    DropItemIntentSP castedSelf = castedSelfPtr<DropItemIntent>();
    Q_ASSERT(castedSelf);
    return new DropItemIntentQmlWrapper(castedSelf, parent);
}

DropItemIntentSP DropItemIntent::create()
{
    DropItemIntentSP result(new DropItemIntent());
    initSelfWeakPtr(result);
    return result;
}

DropItemIntentSP DropItemIntent::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    DropItemIntentSP dropItemIntent = create();
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "DropItemIntent" && xmlReader.isStartElement() && !dropItemIntent->isFetched()) {
            dropItemIntent->setFetched(true);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "ComponentRef") {
                ComponentSP component = Component::fromJdf(xmlReader, jobId, sanitize);
                dropItemIntent->setComponent(component);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return dropItemIntent;
}

void DropItemIntent::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(DropItemIntent);
    jdfWriter.writeStartElement(QStringLiteral("DropItemIntent"));
    if (isValidAndDirty(d->component))
        d->component->refToJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

DropItemIntent::DropItemIntent() : NetworkDataEntity(*new DropItemIntentPrivate)
{}

void DropItemIntent::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    DropItemIntentSP castedOther = qSharedPointerCast<DropItemIntent>(other);
    setComponent(castedOther->component());

    NetworkDataEntity::updateSelf(other);
}
