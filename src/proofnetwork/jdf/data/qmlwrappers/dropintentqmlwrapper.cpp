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
#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"

#include "proofnetwork/jdf/data/dropintent.h"
#include "proofnetwork/jdf/data/dropitemintent.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class DropIntentQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(DropIntentQmlWrapper)

    void updateDropItemIntents();

    QVector<DropItemIntentQmlWrapper *> dropItemIntents;
    QQmlListProperty<Proof::Jdf::DropItemIntentQmlWrapper> qmlDropItemIntentsList;
    static DropItemIntentQmlWrapper *dropItemIntentAt(QQmlListProperty<DropItemIntentQmlWrapper> *property, int index);
    static int dropItemIntentsCount(QQmlListProperty<DropItemIntentQmlWrapper> *property);
};

DropIntentQmlWrapper::DropIntentQmlWrapper(const DropIntentSP &dropIntent, QObject *parent)
    : NetworkDataEntityQmlWrapper(dropIntent, *new DropIntentQmlWrapperPrivate, parent)
{
    setupEntity(); // NOLINT
}

DropIntentQmlWrapper::~DropIntentQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(DropIntent)

QQmlListProperty<DropItemIntentQmlWrapper> DropIntentQmlWrapper::dropItemIntents() const
{
    Q_D_CONST(DropIntentQmlWrapper);
    return d->qmlDropItemIntentsList;
}

void DropIntentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> & /*old*/)
{
    Q_D(DropIntentQmlWrapper);
    DropIntentSP dropIntent = entity<DropIntent>();
    Q_ASSERT(dropIntent);

    connect(dropIntent.data(), &DropIntent::dropItemIntentsChanged, entityConnectContext(),
            [d]() { d->updateDropItemIntents(); });

    d->updateDropItemIntents();
}

void DropIntentQmlWrapperPrivate::updateDropItemIntents()
{
    Q_Q(DropIntentQmlWrapper);
    DropIntentSP dropIntent = q->entity<DropIntent>();
    for (DropItemIntentQmlWrapper *wrapper : qAsConst(dropItemIntents))
        wrapper->deleteLater();

    dropItemIntents.clear();
    const auto ndeIntents = dropIntent->dropItemIntents();
    for (const DropItemIntentSP &dropItemIntent : ndeIntents)
        dropItemIntents << dropItemIntent->toQmlWrapper(q);

    qmlDropItemIntentsList =
        QQmlListProperty<Proof::Jdf::DropItemIntentQmlWrapper>(q, &dropItemIntents,
                                                               &DropIntentQmlWrapperPrivate::dropItemIntentsCount,
                                                               &DropIntentQmlWrapperPrivate::dropItemIntentAt);
    emit q->dropItemIntentsChanged(qmlDropItemIntentsList);
}

DropItemIntentQmlWrapper *
DropIntentQmlWrapperPrivate::dropItemIntentAt(QQmlListProperty<DropItemIntentQmlWrapper> *property, int index)
{
    return static_cast<QVector<DropItemIntentQmlWrapper *> *>(property->data)->at(index);
}

int DropIntentQmlWrapperPrivate::dropItemIntentsCount(QQmlListProperty<DropItemIntentQmlWrapper> *property)
{
    return static_cast<QVector<DropItemIntentQmlWrapper *> *>(property->data)->count();
}

} // namespace Jdf
} // namespace Proof
