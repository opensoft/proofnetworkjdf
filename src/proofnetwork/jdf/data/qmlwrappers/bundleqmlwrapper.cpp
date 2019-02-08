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
#include "proofnetwork/jdf/data/qmlwrappers/bundleqmlwrapper.h"

#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/bundleitem.h"
#include "proofnetwork/jdf/data/qmlwrappers/bundleitemqmlwrapper.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class BundleQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(BundleQmlWrapper)

    void updateBundleItems();

    QVector<BundleItemQmlWrapper *> bundleItems;
    QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper> qmlBundleItemsList;
    static BundleItemQmlWrapper *bundleItemAt(QQmlListProperty<BundleItemQmlWrapper> *property, int index);
    static int bundleItemsCount(QQmlListProperty<BundleItemQmlWrapper> *property);
};

BundleQmlWrapper::BundleQmlWrapper(const BundleSP &bundle, QObject *parent)
    : NetworkDataEntityQmlWrapper(bundle, *new BundleQmlWrapperPrivate, parent)
{
    setupEntity(); // NOLINT
}

BundleQmlWrapper::~BundleQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Bundle)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Bundle, Proof::Jdf::BundleType, bundleType)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Bundle, int, totalAmount)

QQmlListProperty<BundleItemQmlWrapper> BundleQmlWrapper::bundleItems() const
{
    Q_D_CONST(BundleQmlWrapper);
    return d->qmlBundleItemsList;
}

void BundleQmlWrapperPrivate::updateBundleItems()
{
    Q_Q(BundleQmlWrapper);
    for (BundleItemQmlWrapper *wrapper : qAsConst(bundleItems))
        wrapper->deleteLater();

    bundleItems.clear();

    BundleSP bundle = q->entity<Bundle>();
    const auto allNdeItems = bundle->bundleItems();
    for (const auto &bundleItem : allNdeItems)
        bundleItems << bundleItem->toQmlWrapper(q);

    qmlBundleItemsList = QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper>(q, &bundleItems,
                                                                            &BundleQmlWrapperPrivate::bundleItemsCount,
                                                                            &BundleQmlWrapperPrivate::bundleItemAt);
    emit q->bundleItemsChanged(qmlBundleItemsList);
}

void BundleQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(BundleQmlWrapper);
    BundleSP bundle = entity<Bundle>();
    Q_ASSERT(bundle);

    connect(bundle.data(), &Bundle::bundleTypeChanged, this, &BundleQmlWrapper::bundleTypeChanged);
    connect(bundle.data(), &Bundle::totalAmountChanged, this, &BundleQmlWrapper::totalAmountChanged);
    connect(bundle.data(), &Bundle::bundleItemsChanged, entityConnectContext(), [d]() { d->updateBundleItems(); });

    BundleSP oldBundle = qSharedPointerCast<Bundle>(old);
    if (oldBundle) {
        if (bundle->bundleType() != oldBundle->bundleType())
            emit bundleTypeChanged(bundle->bundleType());
        if (bundle->totalAmount() != oldBundle->totalAmount())
            emit totalAmountChanged(bundle->totalAmount());
    }

    d->updateBundleItems();
}

BundleItemQmlWrapper *BundleQmlWrapperPrivate::bundleItemAt(QQmlListProperty<BundleItemQmlWrapper> *property, int index)
{
    return static_cast<QVector<BundleItemQmlWrapper *> *>(property->data)->at(index);
}

int BundleQmlWrapperPrivate::bundleItemsCount(QQmlListProperty<BundleItemQmlWrapper> *property)
{
    return static_cast<QVector<BundleItemQmlWrapper *> *>(property->data)->count();
}

} // namespace Jdf
} // namespace Proof
