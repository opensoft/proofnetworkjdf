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
#ifndef XJDF_INTENT_H
#define XJDF_INTENT_H

#include "abstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class NodeWriterGuard;
class IntentPrivate;
class PROOF_NETWORK_XJDF_EXPORT Intent : public AbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Intent)
public:
    Intent(const Intent &) = delete;
    Intent &operator=(const Intent &) = delete;
    Intent(Intent &&) = delete;
    Intent &operator=(Intent &&) = delete;
    ~Intent() = default;

    virtual IntentSP cloneTo(const DocumentSP &document) const = 0;

    QString name() const;
    void setName(const QString &arg);

    bool readFieldsFromXJdf(QXmlStreamReader &reader) override final;
    static IntentSP fromXJdf(QXmlStreamReader &reader, const DocumentSP &document);

    template <class T>
    inline static void registerIntentCreator(const QString &name)
    {
        addIntentCreator(name, [](QXmlStreamReader &reader, const DocumentSP &document) -> IntentSP {
            return qSharedPointerCast<Intent>(T::fromXJdf(reader, document));
        });
    }

signals:
    void nameChanged(const QString &name);

protected:
    NodeWriterGuard writeFieldsToXJdf(QXmlStreamWriter &writer) const;

    explicit Intent(IntentPrivate &dd);
    void updateSelf(const NetworkDataEntitySP &other) override;
    static void addIntentCreator(const QString &name,
                                 std::function<IntentSP(QXmlStreamReader &, const DocumentSP &)> &&creator);
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_INTENT_H
