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
#include "proofnetwork/jdf/data/qmlwrappers/bundleitemqmlwrapper.h"

#include "proofnetwork/jdf/data/bundleitem.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class BundleItemQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(BundleItemQmlWrapper)
};

BundleItemQmlWrapper::BundleItemQmlWrapper(const BundleItemSP &bundleItem, QObject *parent)
    : NetworkDataEntityQmlWrapper(bundleItem, *new BundleItemQmlWrapperPrivate, parent)
{
    setupEntity();
}

BundleItemQmlWrapper::~BundleItemQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(BundleItem)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(BundleItem, int, amount)

void BundleItemQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    BundleItemSP bundleItem = entity<BundleItem>();
    Q_ASSERT(bundleItem);

    connect(bundleItem.data(), &BundleItem::amountChanged, this, &BundleItemQmlWrapper::amountChanged);

    BundleItemSP oldBundleItem = qSharedPointerCast<BundleItem>(old);
    if (oldBundleItem) {
        if (bundleItem->amount() != oldBundleItem->amount())
            emit amountChanged(bundleItem->amount());
    }
}

} // namespace Jdf
} // namespace Proof
