#include "proofnetwork/jdf/data/qmlwrappers/componentqmlwrapper.h"

#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper_p.h"
#include "proofnetwork/jdf/data/qmlwrappers/bundleqmlwrapper.h"

namespace Proof {
namespace Jdf {

class ComponentQmlWrapperPrivate : public AbstractPhysicalResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(ComponentQmlWrapper)

    void updateBundle();
    void updateParts();

    static ComponentQmlWrapper *partAt(QQmlListProperty<ComponentQmlWrapper> *property, int index);
    static int partsCount(QQmlListProperty<ComponentQmlWrapper> *property);

    BundleQmlWrapper *bundle = nullptr;
    QVector<ComponentQmlWrapper *> parts;
    QQmlListProperty<Proof::Jdf::ComponentQmlWrapper> qmlPartsList;
};

ComponentQmlWrapper::ComponentQmlWrapper(const ComponentSP &component, QObject *parent)
    : AbstractPhysicalResourceQmlWrapper(component, *new ComponentQmlWrapperPrivate, parent)
{
    setupEntity();
}

ComponentQmlWrapper::~ComponentQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Component)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Component, Proof::Jdf::ComponentType, componentType)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Component, Proof::Jdf::ProductType, productType)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Component, QString, productTypeDetails)

BundleQmlWrapper *ComponentQmlWrapper::bundle() const
{
    Q_D_CONST(ComponentQmlWrapper);
    return d->bundle;
}

QQmlListProperty<ComponentQmlWrapper> ComponentQmlWrapper::parts()
{
    Q_D(ComponentQmlWrapper);
    return d->qmlPartsList;
}

void ComponentQmlWrapperPrivate::updateBundle()
{
    Q_Q(ComponentQmlWrapper);
    ComponentSP component = q->entity<Component>();
    if (!bundle)
        bundle = component->bundle()->toQmlWrapper(q);
    else
        bundle->setEntity(component->bundle());
    emit q->bundleChanged(bundle);
}

void ComponentQmlWrapperPrivate::updateParts()
{
    Q_Q(ComponentQmlWrapper);
    ComponentSP component = q->entity<Component>();
    for (ComponentQmlWrapper *wrapper : qAsConst(parts))
        wrapper->deleteLater();

    parts.clear();
    const auto ndeParts = component->parts();
    for (const ComponentSP &part : ndeParts)
        parts << part->toQmlWrapper(q);

    qmlPartsList = QQmlListProperty<Proof::Jdf::ComponentQmlWrapper>(q, &parts, &ComponentQmlWrapperPrivate::partsCount,
                                                                     &ComponentQmlWrapperPrivate::partAt);
    emit q->partsChanged(qmlPartsList);
}

ComponentQmlWrapper *ComponentQmlWrapperPrivate::partAt(QQmlListProperty<ComponentQmlWrapper> *property, int index)
{
    return static_cast<QVector<ComponentQmlWrapper *> *>(property->data)->at(index);
}

int ComponentQmlWrapperPrivate::partsCount(QQmlListProperty<ComponentQmlWrapper> *property)
{
    return static_cast<QVector<ComponentQmlWrapper *> *>(property->data)->count();
}

void ComponentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(ComponentQmlWrapper);
    ComponentSP component = entity<Component>();
    Q_ASSERT(component);

    connect(component.data(), &Component::componentTypeChanged, this, &ComponentQmlWrapper::componentTypeChanged);
    connect(component.data(), &Component::productTypeChanged, this, &ComponentQmlWrapper::productTypeChanged);
    connect(component.data(), &Component::productTypeDetailsChanged, this,
            &ComponentQmlWrapper::productTypeDetailsChanged);
    connect(component.data(), &Component::bundleChanged, entityConnectContext(), [d]() { d->updateBundle(); });
    connect(component.data(), &Component::partsChanged, entityConnectContext(), [d]() { d->updateParts(); });

    ComponentSP oldComponent = qSharedPointerCast<Component>(old);
    if (oldComponent) {
        if (component->componentType() != oldComponent->componentType())
            emit componentTypeChanged(component->componentType());
        if (component->productType() != oldComponent->productType())
            emit productTypeChanged(component->productType());
        if (component->productTypeDetails() != oldComponent->productTypeDetails())
            emit productTypeDetailsChanged(component->productTypeDetails());
    }

    d->updateBundle();
}

} // namespace Jdf
} // namespace Proof
