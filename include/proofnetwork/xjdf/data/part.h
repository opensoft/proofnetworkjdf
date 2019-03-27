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
#ifndef XJDF_PART_H
#define XJDF_PART_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

    namespace Proof
{
    namespace XJdf {

    class PartPrivate;
    class PROOF_NETWORK_XJDF_EXPORT Part : public XJdfAbstractNode
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(Part)
    public:
        Part(const Part &) = delete;
        Part &operator=(const Part &) = delete;
        Part(Part &&) = delete;
        Part &operator=(Part &&) = delete;
        ~Part() = default;

        ProductSP product() const;
        CutBlockSP block() const;

        void updateProduct(const QString &arg);
        void updateBlock(const QString &arg);

        static PartSP create();

        static PartSP fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document = XJdfDocumentSP());
        void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

    signals:
        void productChanged(const Proof::XJdf::ProductSP &arg);
        void blockChanged(const Proof::XJdf::CutBlockSP &arg);

    protected:
        explicit Part();
        void updateSelf(const Proof::NetworkDataEntitySP &other) override;
    };

    } // namespace XJdf
} // namespace Proof

#endif // XJDF_PART_H
