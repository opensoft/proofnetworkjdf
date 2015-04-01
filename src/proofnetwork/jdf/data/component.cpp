#include "component.h"

#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/cutblock.h"

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
    BundleSP bundle = Bundle::defaultObject();
    QList<CutBlockSP> cutBlocks;
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

BundleSP Component::bundle() const
{
    Q_D(const Component);
    return d->bundle;
}

QList<CutBlockSP> Component::cutBlocks() const
{
    Q_D(const Component);
    return d->cutBlocks;
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

void Component::setBundle(const BundleSP &arg)
{
    Q_D(Component);
    if (d->bundle != arg) {
        d->bundle = arg;
        emit bundleChanged(arg);
    }
}

QList<CutBlockSP> Component::updateCutBlocks(const QList<CutBlockSP> &arg)
{
    Q_D(Component);
    bool emitNeeded = arg.count() != d->cutBlocks.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->blockName() != d->cutBlocks[i]->blockName();
    if (emitNeeded) {
        d->cutBlocks = arg;
        emit cutBlocksChanged();
    }
    return d->cutBlocks;
}

void Component::updateFrom(const NetworkDataEntitySP &other)
{
    ComponentSP castedOther = qSharedPointerCast<Component>(other);
    setComponentType(castedOther->componentType());
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setLength(castedOther->length());
    setBundle(castedOther->bundle());
    updateCutBlocks(castedOther->cutBlocks());

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

ComponentSP Component::fromJdf(QXmlStreamReader &xmlReader, const QString &jdfId)
{
    ComponentSP component = create();

    QList<CutBlockSP> cutBlocks;
    ApiHelper::PartIDKeysType partIDKeys = ApiHelper::BlockName;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Component" && xmlReader.isStartElement() && !component->isFetched()) {
            component->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            component->setComponentType(ApiHelper::componentTypeFromString(attributes.value("ComponentType").toString()));
            QStringList dimensionsList = attributes.value("Dimensions").toString().split(" ",QString::SkipEmptyParts);
            if (dimensionsList.count() >= 3) {
                component->setWidth(dimensionsList.at(0).toDouble());
                component->setHeight(dimensionsList.at(1).toDouble());
                component->setLength(dimensionsList.at(2).toDouble());
            }

            partIDKeys = ApiHelper::partIdKeysTypeFromString(attributes.value("PartIDKeys").toString());

            AbstractPhysicalResourceSP castedComponent = qSharedPointerCast<AbstractPhysicalResource>(component);
            AbstractPhysicalResource::fromJdf(xmlReader, castedComponent);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Component") {
                QXmlStreamAttributes attributes = xmlReader.attributes();

                switch (partIDKeys) {
                case ApiHelper::BlockName: {
                    QString blockName = attributes.value(ApiHelper::partIdKeysTypeToString(ApiHelper::BlockName)).toString();
                    if (cutBlockCache().contains({jdfId, blockName})) {
                        cutBlocks.append(cutBlockCache().value({jdfId, blockName}));
                    } else {
                        CutBlockSP cutBlock = CutBlock::create(blockName);
                        cutBlockCache().add({jdfId, blockName}, cutBlock);
                        cutBlocks.append(cutBlock);
                    }
                    break; }
                case ApiHelper::BundleItemIndex:
                case ApiHelper::CellIndex:
                default:
                    break;
                }
                xmlReader.skipCurrentElement();
            } else if (xmlReader.name() == "Bundle") {
                BundleSP bundle = Bundle::fromJdf(xmlReader);
                Q_ASSERT(bundle);
                component->setBundle(bundle);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    component->updateCutBlocks(cutBlocks);

    return component;
}

void Component::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Component);
    jdfWriter.writeStartElement("Component");
    jdfWriter.writeAttribute("ComponentType", ApiHelper::componentTypeToString(d->componentType));
    jdfWriter.writeAttribute("Dimensions", QString("%1 %2 %3").arg(d->width).arg(d->height).arg(d->length));

    AbstractPhysicalResource::toJdf(jdfWriter);

    if (d->bundle != Bundle::defaultObject())
        d->bundle->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
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

