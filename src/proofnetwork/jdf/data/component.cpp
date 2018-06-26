#include "component.h"

#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"
#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/cutblock.h"

namespace Proof {
namespace Jdf {

class ComponentPrivate : AbstractPhysicalResourcePrivate
{
    Q_DECLARE_PUBLIC(Component)

    ComponentPrivate() : AbstractPhysicalResourcePrivate(ResourceClass::QuantityClass)
    {
        registerChildren(bundle, cutBlocks);
    }

    bool partsAreValid(QVector<ResourcePartType> partsToCheck = QVector<ResourcePartType>()) const;

    ResourceOrientation orientation = ResourceOrientation::Rotate0Orientation;
    ComponentType componentType = ComponentType::NotTypedComponent;
    ProductType productType = ProductType::NoProduct;
    QString productTypeDetails;

    double width = 0.0;
    double height = 0.0;
    double length = 0.0;
    BundleSP bundle = Bundle::create();
    QVector<CutBlockSP> cutBlocks;
    QVector<ComponentSP> parts;
};

ObjectsCache<JdfComponentDataKey, Component> &componentsCache()
{
    return WeakObjectsCache<JdfComponentDataKey, Component>::instance();
}

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ComponentType Component::componentType() const
{
    Q_D(const Component);
    return d->componentType;
}

ProductType Component::productType() const
{
    Q_D(const Component);
    return d->productType;
}

QString Component::productTypeDetails() const
{
    Q_D(const Component);
    return d->productTypeDetails;
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

QVector<CutBlockSP> Component::cutBlocks() const
{
    Q_D(const Component);
    return d->cutBlocks;
}

QVector<ComponentSP> Component::parts() const
{
    Q_D(const Component);
    return d->parts;
}

void Component::setComponentType(ComponentType arg)
{
    Q_D(Component);
    if (d->componentType != arg) {
        d->componentType = arg;
        emit componentTypeChanged(arg);
    }
}

void Component::setProductType(ProductType arg)
{
    Q_D(Component);
    if (d->productType != arg) {
        d->productType = arg;
        emit productTypeChanged(arg);
    }
}

void Component::setProductTypeDetails(const QString &arg)
{
    Q_D(Component);
    if (d->productTypeDetails != arg) {
        d->productTypeDetails = arg;
        emit productTypeDetailsChanged(arg);
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
    Q_ASSERT(arg);
    Q_D(Component);
    if (d->bundle != arg) {
        d->bundle = arg;
        emit bundleChanged(arg);
    }
}

QVector<CutBlockSP> Component::updateCutBlocks(const QVector<CutBlockSP> &arg)
{
    Q_D(Component);
    bool emitNeeded = arg.count() != d->cutBlocks.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->blockName() != d->cutBlocks[i]->blockName();
    if (emitNeeded) {
        d->cutBlocks = arg;
        emit cutBlocksChanged();
    }
    if (d->cutBlocks.count() > 0 && !partIdKeys().contains(ResourcePartType::BlockNamePart)) {
        QVector<ResourcePartType> partIdKeysOther = partIdKeys();
        partIdKeysOther.append(ResourcePartType::BlockNamePart);
        setPartIdKeys(partIdKeysOther);
    } else if (d->cutBlocks.count() == 0 && partIdKeys().contains(ResourcePartType::BlockNamePart)) {
        QVector<ResourcePartType> partIdKeysOther = partIdKeys();
        partIdKeysOther.removeAll(ResourcePartType::BlockNamePart);
        setPartIdKeys(partIdKeysOther);
    }

    return d->cutBlocks;
}

QVector<ComponentSP> Component::updateParts(const QVector<ComponentSP> &arg)
{
    Q_D(Component);
    bool emitNeeded = arg.count() != d->parts.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->parts[i]->id();
    if (emitNeeded) {
        d->parts = arg;
        emit partsChanged();
    }
    return d->parts;
}

void Component::addPart(const ComponentSP &arg)
{
    Q_D(Component);
    d->parts << arg;
    emit partsChanged();
}

ComponentQmlWrapper *Component::toQmlWrapper(QObject *parent) const
{
    ComponentSP castedSelf = castedSelfPtr<Component>();
    Q_ASSERT(castedSelf);
    return new ComponentQmlWrapper(castedSelf, parent);
}

ComponentSP Component::create(const QString &id)
{
    ComponentSP result(new Component(id));
    initSelfWeakPtr(result);
    return result;
}

ComponentSP Component::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    ComponentSP component = create();
    QVector<CutBlockSP> cutBlocks;

    bool isRef = false;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (!xmlReader.name().compare(component->jdfNodeName(), Qt::CaseInsensitive) && xmlReader.isStartElement()
            && !component->isFetched()) {
            component->setFetched(true);
            AbstractPhysicalResourceSP castedComponent = qSharedPointerCast<AbstractPhysicalResource>(component);
            AbstractPhysicalResource::fromJdf(xmlReader, castedComponent);

            QXmlStreamAttributes attributes = xmlReader.attributes();
            component->setComponentType(
                componentTypeFromString(attributes.value(QStringLiteral("ComponentType")).toString()));
            component->setProductType(productTypeFromString(attributes.value(QStringLiteral("ProductType")).toString()));
            component->setProductTypeDetails(attributes.value(QStringLiteral("ProductTypeDetails")).toString());

            QStringList dimensionsList = attributes.value(QStringLiteral("Dimensions"))
                                             .toString()
                                             .split(QStringLiteral(" "), QString::SkipEmptyParts);
            if (dimensionsList.count() >= 3) {
                component->setWidth(dimensionsList.at(0).toDouble());
                component->setHeight(dimensionsList.at(1).toDouble());
                component->setLength(dimensionsList.at(2).toDouble());
            }
        } else if (!xmlReader.name().compare(component->jdfNodeRefName(), Qt::CaseInsensitive)
                   && xmlReader.isStartElement() && !component->isFetched()) {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            QString componentId = attributes.value(QStringLiteral("rRef")).toString();
            component->setId(componentId);
            isRef = true;
        } else if (xmlReader.isStartElement()) {
            if (!xmlReader.name().compare(component->jdfNodeName(), Qt::CaseInsensitive)) {
                QXmlStreamAttributes attributes = xmlReader.attributes();

                bool partitionedComponent = true;
                if (component->partIdKeys().count() == 0) {
                    if (attributes.hasAttribute(resourcePartTypeToString(ResourcePartType::BlockNamePart))) {
                        QString blockName =
                            attributes.value(resourcePartTypeToString(ResourcePartType::BlockNamePart)).toString();
                        cutBlocks << cutBlockCache().add({jobId, blockName}, CutBlock::create(blockName));
                        partitionedComponent = false;
                    }
                } else if (component->partIdKeys().count() == 1) {
                    switch (component->partIdKeys()[0]) {
                    case ResourcePartType::BlockNamePart: {
                        QString blockName =
                            attributes.value(resourcePartTypeToString(ResourcePartType::BlockNamePart)).toString();
                        cutBlocks << cutBlockCache().add({jobId, blockName}, CutBlock::create(blockName));
                        partitionedComponent = false;
                        break;
                    }
                    case ResourcePartType::BundleItemIndexPart:
                    case ResourcePartType::CellIndexPart:
                        partitionedComponent = false;
                        break;
                    default:
                        break;
                    }
                }
                if (partitionedComponent) {
                    ComponentSP part = Component::fromJdf(xmlReader, jobId, sanitize);
                    if (!part) {
                        qCWarning(proofNetworkJdfDataLog) << "Component not created. Part is not valid";
                        return ComponentSP();
                    }
                    component->addPart(part);
                } else {
                    xmlReader.skipCurrentElement();
                }
            } else if (xmlReader.name() == "Bundle") {
                BundleSP bundle = Bundle::fromJdf(xmlReader, jobId, sanitize);
                if (!bundle) {
                    qCWarning(proofNetworkJdfDataLog) << "Bundle not created.";
                    return ComponentSP();
                }
                component->setBundle(bundle);
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    if (component->d_func()->partIdKeys.count() && !component->d_func()->partsAreValid()) {
        qCWarning(proofNetworkJdfDataLog) << "Component not created. Partioning is not valid";
        return ComponentSP();
    }

    component->updateCutBlocks(cutBlocks);

    if (!component->id().isEmpty()) {
        auto componentFromCache = componentsCache().add({jobId, component->id()}, component);
        if (component != componentFromCache && !sanitize && !isRef)
            componentFromCache->updateFrom(component);
        component = componentFromCache;
    }

    return component;
}

void Component::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Component);
    jdfWriter.writeStartElement(QStringLiteral("Component"));
    if (d->componentType != ComponentType::NotTypedComponent)
        jdfWriter.writeAttribute(QStringLiteral("ComponentType"), componentTypeToString(d->componentType));
    if (d->productType != ProductType::NoProduct)
        jdfWriter.writeAttribute(QStringLiteral("ProductType"), productTypeToString(d->productType));
    if (!d->productTypeDetails.isEmpty())
        jdfWriter.writeAttribute(QStringLiteral("ProductTypeDetails"), d->productTypeDetails);
    if (!qFuzzyIsNull(d->width) || !qFuzzyIsNull(d->height) || !qFuzzyIsNull(d->length)) {
        jdfWriter.writeAttribute(QStringLiteral("Dimensions"), QStringLiteral("%1 %2 %3")
                                                                   .arg(d->width, 0, 'f', 4)
                                                                   .arg(d->height, 0, 'f', 4)
                                                                   .arg(d->length, 0, 'f', 4));
    }

    AbstractPhysicalResource::toJdf(jdfWriter);

    for (const CutBlockSP &cutBlock : qAsConst(d->cutBlocks)) {
        jdfWriter.writeStartElement(QStringLiteral("Component"));
        jdfWriter.writeAttribute(resourcePartTypeToString(ResourcePartType::BlockNamePart), cutBlock->blockName());
        jdfWriter.writeEndElement();
    }

    for (const auto &part : qAsConst(d->parts)) {
        if (part->isDirty())
            part->toJdf(jdfWriter);
    }

    if (d->bundle->isDirty())
        d->bundle->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

ComponentLinkSP Component::toLink(LinkUsage usage) const
{
    ComponentLinkSP link = ComponentLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

Component::Component(const QString &id) : AbstractPhysicalResource(*new ComponentPrivate)
{
    if (!id.isEmpty())
        setId(id);
}

void Component::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    ComponentSP castedOther = qSharedPointerCast<Component>(other);
    setComponentType(castedOther->componentType());
    setProductType(castedOther->productType());
    setProductTypeDetails(castedOther->productTypeDetails());
    setWidth(castedOther->width());
    setHeight(castedOther->height());
    setLength(castedOther->length());
    setBundle(castedOther->bundle());
    setPartIdKeys(castedOther->partIdKeys());
    updateCutBlocks(castedOther->cutBlocks());

    AbstractPhysicalResource::updateSelf(other);
}

bool ComponentPrivate::partsAreValid(QVector<ResourcePartType> partsToCheck) const
{
    if (partsToCheck.isEmpty() && !partIdKeys.isEmpty())
        partsToCheck = partIdKeys;
    if (partsToCheck.isEmpty()) {
        if (parts.count())
            qCWarning(proofNetworkJdfDataLog) << "Component partioning is not valid. Extra parts found";
        return parts.isEmpty();
    }

    auto currentPart = partsToCheck.takeFirst();

    for (const auto &part : parts) {
        if (!part->hasPartAttribute(currentPart)) {
            qCWarning(proofNetworkJdfDataLog)
                << "Component partioning is not valid. Part" << resourcePartTypeToString(currentPart) << "not found";
            return false;
        }
        if (!part->d_func()->partsAreValid(partsToCheck))
            return false;
    }
    return true;
}
