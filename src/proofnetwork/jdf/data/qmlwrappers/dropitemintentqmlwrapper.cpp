#include "dropitemintentqmlwrapper.h"

#include "proofnetwork/jdf/data/dropitemintent.h"
#include "proofnetwork/jdf/data/span.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"
#include "proofnetwork/jdf/data/component.h"

namespace Proof {
namespace Jdf {

class DropItemIntentQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(DropItemIntentQmlWrapper)

    void updateComponent();

    ComponentQmlWrapper *component = nullptr;
};

DropItemIntentQmlWrapper::DropItemIntentQmlWrapper(const DropItemIntentSP &dropIntent, QObject *parent)
    : NetworkDataEntityQmlWrapper(dropIntent, *new DropItemIntentQmlWrapperPrivate, parent)
{
    setupEntity();
}

DropItemIntentQmlWrapper::~DropItemIntentQmlWrapper()
{
}

ComponentQmlWrapper *DropItemIntentQmlWrapper::component() const
{
    Q_D(const DropItemIntentQmlWrapper);
    return d->component;
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(DropItemIntent)

void DropItemIntentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(DropItemIntentQmlWrapper);
    Q_UNUSED(old)
    DropItemIntentSP dropItemIntent = d->entity<DropItemIntent>();
    Q_ASSERT(dropItemIntent);

    connect(dropItemIntent.data(), &DropItemIntent::componentChanged,
            d->lambdaConnectContext, [d](){d->updateComponent();});

    d->updateComponent();
}

void DropItemIntentQmlWrapperPrivate::updateComponent()
{
    Q_Q(DropItemIntentQmlWrapper);
    DropItemIntentSP dropItemIntent = entity<DropItemIntent>();
    if (component == nullptr)
        component = dropItemIntent->component()->toQmlWrapper(q);
    else
        component->setEntity(dropItemIntent->component());
    emit q->componentChanged(component);
}

}
}

