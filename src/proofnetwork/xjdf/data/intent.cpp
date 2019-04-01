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
#include "proofnetwork/xjdf/data/intent.h"

#include "proofnetwork/xjdf/data/intent_p.h"

using namespace Proof;
using namespace Proof::XJdf;

namespace {
using Creator = std::function<IntentSP(QXmlStreamReader &, const DocumentSP &)>;

QMap<QString, std::function<IntentSP(QXmlStreamReader &, const DocumentSP &)>> &creators()
{
    static QMap<QString, std::function<IntentSP(QXmlStreamReader &, const DocumentSP &)>> creators;
    return creators;
}

IntentSP createIntent(const QString &name, QXmlStreamReader &reader, const DocumentSP &document)
{
    auto creator = creators().find(name);
    return creator == creators().end() ? IntentSP() : creator.value()(reader, document);
}

} // namespace

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

bool Intent::fillCommonFields(QXmlStreamReader &)
{
    //NOTE: Nothing there for now, but it can be fill later
    return false;
}

AbstractNode::WriterGuard Intent::writeFieldsToXJdf(QXmlStreamWriter &writer) const
{
    Q_D_CONST(Intent);

    writer.writeStartElement(QStringLiteral("Intent"));
    if (!d->name.isEmpty())
        writer.writeAttribute(QStringLiteral("Name"), d->name);
    return AbstractNode::WriterGuard(&writer);
}

IntentSP Intent::fromXJdf(QXmlStreamReader &reader, const DocumentSP &document)
{
    if (reader.isStartElement() && reader.name() == QStringLiteral("Intent")) {
        auto attributes = reader.attributes();
        QString name;
        if (attributes.hasAttribute(QStringLiteral("Name")))
            name = attributes.value(QStringLiteral("Name")).toString();

        reader.readNextStartElement();
        if (!reader.atEnd() && !reader.hasError()) {
            auto intent = createIntent(reader.name().toString(), reader, document);
            if (intent) {
                intent->setName(name);
                reader.skipCurrentElement();
                return intent;
            }
        }
    }

    return IntentSP();
}

Intent::Intent(IntentPrivate &dd) : AbstractNode(dd)
{}

void Intent::updateSelf(const NetworkDataEntitySP &other)
{
    IntentSP castedOther = qSharedPointerCast<Intent>(other);
    setName(castedOther->name());
    AbstractNode::updateSelf(other);
}

void Intent::addIntentCreator(const QString &name,
                              std::function<IntentSP(QXmlStreamReader &, const DocumentSP &)> &&creator)
{
    creators()[name] = std::forward<Creator>(creator);
}
