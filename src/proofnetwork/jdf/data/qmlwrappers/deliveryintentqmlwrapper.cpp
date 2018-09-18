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
#include "proofnetwork/jdf/data/qmlwrappers/deliveryintentqmlwrapper.h"

#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/dropintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class DeliveryIntentQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(DeliveryIntentQmlWrapper)

    void updateDropIntents();

    QVector<DropIntentQmlWrapper *> dropIntents;
    QQmlListProperty<Proof::Jdf::DropIntentQmlWrapper> qmlDropIntentsList;
    static DropIntentQmlWrapper *dropIntentAt(QQmlListProperty<DropIntentQmlWrapper> *property, int index);
    static int dropIntentsCount(QQmlListProperty<DropIntentQmlWrapper> *property);
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

DeliveryIntentQmlWrapper::DeliveryIntentQmlWrapper(const DeliveryIntentSP &deliveryIntent, QObject *parent)
    : AbstractResourceQmlWrapper(deliveryIntent, *new DeliveryIntentQmlWrapperPrivate, parent)
{
    setupEntity();
}

DeliveryIntentQmlWrapper::~DeliveryIntentQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(DeliveryIntent)

QQmlListProperty<DropIntentQmlWrapper> DeliveryIntentQmlWrapper::dropIntents() const
{
    Q_D_CONST(DeliveryIntentQmlWrapper);
    return d->qmlDropIntentsList;
}

void DeliveryIntentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> & /*old*/)
{
    Q_D(DeliveryIntentQmlWrapper);
    DeliveryIntentSP deliveryIntent = entity<DeliveryIntent>();
    Q_ASSERT(deliveryIntent);

    connect(deliveryIntent.data(), &DeliveryIntent::dropIntentsChanged, entityConnectContext(),
            [d]() { d->updateDropIntents(); });

    d->updateDropIntents();
}

void DeliveryIntentQmlWrapperPrivate::updateDropIntents()
{
    Q_Q(DeliveryIntentQmlWrapper);
    DeliveryIntentSP resourcePool = q->entity<DeliveryIntent>();
    for (DropIntentQmlWrapper *wrapper : qAsConst(dropIntents))
        wrapper->deleteLater();

    dropIntents.clear();
    const auto ndeIntents = resourcePool->dropIntents();
    for (const DropIntentSP &dropIntent : ndeIntents)
        dropIntents << dropIntent->toQmlWrapper(q);

    qmlDropIntentsList =
        QQmlListProperty<Proof::Jdf::DropIntentQmlWrapper>(q, &dropIntents,
                                                           &DeliveryIntentQmlWrapperPrivate::dropIntentsCount,
                                                           &DeliveryIntentQmlWrapperPrivate::dropIntentAt);
    emit q->dropIntentsChanged(qmlDropIntentsList);
}

DropIntentQmlWrapper *DeliveryIntentQmlWrapperPrivate::dropIntentAt(QQmlListProperty<DropIntentQmlWrapper> *property,
                                                                    int index)
{
    return static_cast<QVector<DropIntentQmlWrapper *> *>(property->data)->at(index);
}

int DeliveryIntentQmlWrapperPrivate::dropIntentsCount(QQmlListProperty<DropIntentQmlWrapper> *property)
{
    return static_cast<QVector<DropIntentQmlWrapper *> *>(property->data)->count();
}
