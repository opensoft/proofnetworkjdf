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
#ifndef XJDF_FOLDINGINTENT_H
#define XJDF_FOLDINGINTENT_H

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/intent.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class FoldingIntentPrivate;
class PROOF_NETWORK_XJDF_EXPORT FoldingIntent : public Intent
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FoldingIntent)
    friend Document;

public:
    FoldingIntent(const FoldingIntent &) = delete;
    FoldingIntent &operator=(const FoldingIntent &) = delete;
    FoldingIntent(FoldingIntent &&) = delete;
    FoldingIntent &operator=(FoldingIntent &&) = delete;
    ~FoldingIntent() = default;

    IntentSP cloneTo(const DocumentSP &document) const override;

    FoldType foldCatalog() const;
    void setFoldCatalog(FoldType arg);

    static FoldingIntentSP fromXJdf(QXmlStreamReader &reader, const DocumentSP &document);
    void toXJdf(QXmlStreamWriter &writer) const override;
signals:
    void foldCatalogChanged(Proof::XJdf::FoldType type);

protected:
    explicit FoldingIntent();
    static FoldingIntentSP create(const DocumentSP &document);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_FOLDINGINTENT_H
