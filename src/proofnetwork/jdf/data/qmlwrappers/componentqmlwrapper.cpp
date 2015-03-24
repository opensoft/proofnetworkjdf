#include "componentqmlwrapper.h"

#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper_p.h"
#include "proofnetwork/jdf/data/qmlwrappers/bundleqmlwrapper.h"

namespace Proof {
namespace Jdf {

class ComponentQmlWrapperPrivate : public AbstractPhysicalResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ComponentQmlWrapper)

    void updateBundle();

    BundleQmlWrapper *bundle = nullptr;
};

ComponentQmlWrapper::ComponentQmlWrapper(const ComponentSP &component, QObject *parent)
    : AbstractPhysicalResourceQmlWrapper(component, *new ComponentQmlWrapperPrivate, parent)
{
    setupEntity();
}

ComponentQmlWrapper::~ComponentQmlWrapper()
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Component)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Component, Proof::Jdf::ApiHelper::ComponentType, componentType)


BundleQmlWrapper *ComponentQmlWrapper::bundle() const
{
    Q_D(const ComponentQmlWrapper);
    return d->bundle;
}

void ComponentQmlWrapperPrivate::updateBundle()
{
    Q_Q(ComponentQmlWrapper);
    ComponentSP component = entity<Component>();
    if (!bundle)
        bundle = component->bundle()->toQmlWrapper(q);
    else
        bundle->setEntity(component->bundle());
    q->bundleChanged(bundle);
}

void ComponentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(ComponentQmlWrapper);
    ComponentSP component = d->entity<Component>();
    Q_ASSERT(component);

    connect(component.data(), &Component::componentTypeChanged,
            this, &ComponentQmlWrapper::componentTypeChanged);
    connect(component.data(), &Component::bundleChanged,
            d->lambdaConnectContext, [d](){d->updateBundle();});

    ComponentSP oldComponent = qSharedPointerCast<Component>(old);
    if (oldComponent) {
        if (component->componentType() != oldComponent->componentType())
            emit componentTypeChanged(component->componentType());
    }

    d->updateBundle();
}

}
}
