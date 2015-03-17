#include "component.h"

#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"

namespace Proof {
namespace Jdf {

class ComponentPrivate : AbstractPhysicalResourcePrivate
{
    Q_DECLARE_PUBLIC(Component)

    ApiHelper::ComponentType componentType = ApiHelper::SheetComponent;
    double width = 0.0;
    double height = 0.0;
    double length = 0.0;
};

ApiHelper::ComponentType Component::componentType() const
{
    Q_D(const Component);
    return d->componentType;
}

double Component::width() const
{
    Q_D(const Component);
    return d->width;
}

double Component::height() const
{
    Q_D(const Component);
    return d->height;
}

double Component::length() const
{
    Q_D(const Component);
    return d->length;
}

void Component::setComponentType(ApiHelper::ComponentType arg)
{
    Q_D(Component);
    if (d->componentType != arg) {
        d->componentType = arg;
        emit componentTypeChanged(arg);
    }
}

void Component::setWidth(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(d->width, arg)) {
        d->width = arg;
        emit widthChanged(d->width);
    }
}

void Component::setHeight(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(d->height, arg)) {
        d->height = arg;
        emit heightChanged(d->height);
    }
}

void Component::setLength(double arg)
{
    Q_D(Component);
    if (!qFuzzyCompare(d->length, arg)) {
        d->length = arg;
        emit lengthChanged(d->length);
    }
}

void Component::updateFrom(const NetworkDataEntitySP &other)
{
    ComponentSP castedOther = qSharedPointerCast<Component>(other);
    setComponentType(castedOther->componentType());

    AbstractPhysicalResource::updateFrom(other);
}

ComponentQmlWrapper *Component::toQmlWrapper(QObject *parent) const
{
    Q_D(const Component);
    ComponentSP castedSelf = qSharedPointerCast<Component>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new ComponentQmlWrapper(castedSelf, parent);
}

ComponentSP Component::create()
{
    ComponentSP result(new Component());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

ComponentSP Component::fromJdf(QXmlStreamReader &xmlReader)
{
    ComponentSP component = create();
    component->setFetched(true);

    if (xmlReader.name() == "Component") {
        QXmlStreamAttributes attributes = xmlReader.attributes();
        component->setComponentType(ApiHelper::componentTypeFromString(attributes.value("ComponentType").toString()));
        QStringList dimensionsList = attributes.value("Dimensions").toString().split(" ",QString::SkipEmptyParts);
        if (dimensionsList.count() >= 3) {
            component->setWidth(dimensionsList.at(0).toDouble());
            component->setHeight(dimensionsList.at(1).toDouble());
            component->setLength(dimensionsList.at(2).toDouble());
        }

        AbstractPhysicalResourceSP castedComponent = qSharedPointerCast<AbstractPhysicalResource>(component);
        AbstractPhysicalResource::fromJdf(xmlReader, castedComponent);
    }

    return component;
}

void Component::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Component);
    jdfWriter.writeAttribute("ComponentType", ApiHelper::componentTypeToString(d->componentType));
    jdfWriter.writeAttribute("Dimensions", QString::number(d->width) + " "
                                     + QString::number(d->height) + " "
                             + QString::number(d->length));
    AbstractPhysicalResource::toJdf(jdfWriter);
}

ComponentSP Component::defaultObject()
{
    static ComponentSP entity = create();
    return entity;
}

Component::Component()
    : AbstractPhysicalResource(*new ComponentPrivate)
{
    setResourceClass(ApiHelper::QuantityClass);
}

} // namespace Jdf
} // namespace Proof


