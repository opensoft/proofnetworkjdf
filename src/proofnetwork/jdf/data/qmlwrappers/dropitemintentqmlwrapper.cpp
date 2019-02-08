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
#include "proofnetwork/jdf/data/qmlwrappers/dropitemintentqmlwrapper.h"

#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/dropitemintent.h"
#include "proofnetwork/jdf/data/span.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class DropItemIntentQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(DropItemIntentQmlWrapper)

    void updateComponent();

    ComponentQmlWrapper *component = nullptr;
};

DropItemIntentQmlWrapper::DropItemIntentQmlWrapper(const DropItemIntentSP &dropItemIntent, QObject *parent)
    : NetworkDataEntityQmlWrapper(dropItemIntent, *new DropItemIntentQmlWrapperPrivate, parent)
{
    setupEntity(); // NOLINT
}

DropItemIntentQmlWrapper::~DropItemIntentQmlWrapper()
{}

ComponentQmlWrapper *DropItemIntentQmlWrapper::component() const
{
    Q_D_CONST(DropItemIntentQmlWrapper);
    return d->component;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(DropItemIntent)

void DropItemIntentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(DropItemIntentQmlWrapper);
    Q_UNUSED(old)
    DropItemIntentSP dropItemIntent = entity<DropItemIntent>();
    Q_ASSERT(dropItemIntent);

    connect(dropItemIntent.data(), &DropItemIntent::componentChanged, entityConnectContext(),
            [d]() { d->updateComponent(); });

    d->updateComponent();
}

void DropItemIntentQmlWrapperPrivate::updateComponent()
{
    Q_Q(DropItemIntentQmlWrapper);
    DropItemIntentSP dropItemIntent = q->entity<DropItemIntent>();
    if (component == nullptr)
        component = dropItemIntent->component()->toQmlWrapper(q);
    else
        component->setEntity(dropItemIntent->component());
    emit q->componentChanged(component);
}

} // namespace Jdf
} // namespace Proof
