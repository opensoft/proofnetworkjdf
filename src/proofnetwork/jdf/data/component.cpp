#include "component.h"

#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"

namespace Proof {
namespace Jdf {

class ComponentPrivate : AbstractPhysicalResourcePrivate
{
    Q_DECLARE_PUBLIC(Component)

    ComponentPrivate()
        : AbstractPhysicalResourcePrivate(ApiHelper::ResourceClass::QuantityClass)
    {
        registerChildren(bundle, cutBlocks);
    }

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    bool partsAreValid(QList<ApiHelper::ResourcePartType> partsToCheck = QList<ApiHelper::ResourcePartType>()) const;

    ApiHelper::ResourceOrientation orientation = ApiHelper::ResourceOrientation::Rotate0Orientation;
    ApiHelper::ComponentType componentType = ApiHelper::ComponentType::NotTypedComponent;

    double width = 0.0;
    double height = 0.0;
    double length = 0.0;
    BundleSP bundle = Bundle::create();
    QList<CutBlockSP> cutBlocks;
    QList<ComponentSP> parts;
};

ObjectsCache<JdfComponentDataKey, Component> &componentsCache()
{
    return WeakObjectsCache<JdfComponentDataKey, Component>::instance();
}

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

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

QList<ComponentSP> Component::parts() const
{
    Q_D(const Component);
    return d->parts;
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
    Q_ASSERT(arg);
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
    if (d->cutBlocks.count() > 0 && !partIdKeys().contains(ApiHelper::ResourcePartType::BlockNamePart)) {
        QList<ApiHelper::ResourcePartType> partIdKeysOther = partIdKeys();
        partIdKeysOther.append(ApiHelper::ResourcePartType::BlockNamePart);
        setPartIdKeys(partIdKeysOther);
    } else if (d->cutBlocks.count() == 0 && partIdKeys().contains(ApiHelper::ResourcePartType::BlockNamePart)) {
        QList<ApiHelper::ResourcePartType> partIdKeysOther = partIdKeys();
        partIdKeysOther.removeAll(ApiHelper::ResourcePartType::BlockNamePart);
        setPartIdKeys(partIdKeysOther);
    }

    return d->cutBlocks;
}

QList<ComponentSP> Component::updateParts(const QList<ComponentSP> &arg)
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
    Q_D(const Component);
    ComponentSP castedSelf = qSharedPointerCast<Component>(d->weakSelf);
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
    QList<CutBlockSP> cutBlocks;
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Component" && xmlReader.isStartElement() && !component->isFetched()) {
            component->setFetched(true);
            AbstractPhysicalResourceSP castedComponent = qSharedPointerCast<AbstractPhysicalResource>(component);
            AbstractPhysicalResource::fromJdf(xmlReader, castedComponent);

            QXmlStreamAttributes attributes = xmlReader.attributes();
            component->setComponentType(ApiHelper::componentTypeFromString(attributes.value("ComponentType").toString()));

            QStringList dimensionsList = attributes.value("Dimensions").toString().split(" ", QString::SkipEmptyParts);
            if (dimensionsList.count() >= 3) {
                component->setWidth(dimensionsList.at(0).toDouble());
                component->setHeight(dimensionsList.at(1).toDouble());
                component->setLength(dimensionsList.at(2).toDouble());
            }
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Component") {
                QXmlStreamAttributes attributes = xmlReader.attributes();

                bool partitionedComponent = true;
                if (component->partIdKeys().count() == 0) {
                    if (attributes.hasAttribute(ApiHelper::resourcePartTypeToString(ApiHelper::ResourcePartType::BlockNamePart))) {
                        QString blockName = attributes.value(ApiHelper::resourcePartTypeToString(ApiHelper::ResourcePartType::BlockNamePart)).toString();
                        cutBlocks << cutBlockCache().add({jobId, blockName}, CutBlock::create(blockName));
                        partitionedComponent = false;
                    }
                } else if (component->partIdKeys().count() == 1) {
                    switch (component->partIdKeys()[0]) {
                    case ApiHelper::ResourcePartType::BlockNamePart: {
                        QString blockName = attributes.value(ApiHelper::resourcePartTypeToString(ApiHelper::ResourcePartType::BlockNamePart)).toString();
                        cutBlocks << cutBlockCache().add({jobId, blockName}, CutBlock::create(blockName));
                        partitionedComponent = false;
                        break;
                    }
                    case ApiHelper::ResourcePartType::BundleItemIndexPart:
                    case ApiHelper::ResourcePartType::CellIndexPart:
                        partitionedComponent = false;
                        break;
                    default:
                        break;
                    }
                }
                if (partitionedComponent) {
                    ComponentSP part = Component::fromJdf(xmlReader, jobId, sanitize);
                    if (!part) {
                        qCCritical(proofNetworkJdfDataLog) << "Component not created. Part is not valid";
                        return ComponentSP();
                    }
                    component->addPart(part);
                } else {
                    xmlReader.skipCurrentElement();
                }
            } else if (xmlReader.name() == "Bundle") {
                BundleSP bundle = Bundle::fromJdf(xmlReader);
                if (!bundle) {
                    qCCritical(proofNetworkJdfDataLog) << "Bundle not created.";
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
        qCCritical(proofNetworkJdfDataLog) << "Component not created. Partioning is not valid";
        return ComponentSP();
    }

    component->updateCutBlocks(cutBlocks);

    ComponentSP componentFromCache = componentsCache().value({jobId, component->id()});
    if (!component->id().isEmpty()) {
        if (componentFromCache && !sanitize) {
            componentFromCache->updateFrom(component);
            component = componentFromCache;
        } else {
            componentFromCache = componentsCache().add({jobId, component->id()}, component);
            if (component != componentFromCache) {
                componentFromCache->updateFrom(component);
                component = componentFromCache;
            }
        }
    }

    return component;
}

void Component::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Component);
    jdfWriter.writeStartElement("Component");
    if (d->componentType != ApiHelper::ComponentType::NotTypedComponent)
        jdfWriter.writeAttribute("ComponentType", ApiHelper::componentTypeToString(d->componentType));
    if (!qFuzzyIsNull(d->width) || !qFuzzyIsNull(d->height) || !qFuzzyIsNull(d->length)) {
        jdfWriter.writeAttribute("Dimensions", QString("%1 %2 %3")
                                 .arg(d->width, 0, 'f', 4)
                                 .arg(d->height, 0, 'f', 4)
                                 .arg(d->length, 0, 'f', 4));
    }

    AbstractPhysicalResource::toJdf(jdfWriter);

    for (const CutBlockSP &cutBlock : d->cutBlocks) {
        jdfWriter.writeStartElement("Component");
        jdfWriter.writeAttribute(ApiHelper::resourcePartTypeToString(ApiHelper::ResourcePartType::BlockNamePart), cutBlock->blockName());
        jdfWriter.writeEndElement();
    }

    for (const auto &part : d->parts) {
        if (part->isDirty())
            part->toJdf(jdfWriter);
    }

    if (d->bundle->isDirty())
        d->bundle->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

ComponentLinkSP Component::toLink(ApiHelper::Usage usage) const
{
    ComponentLinkSP link = ComponentLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

Component::Component(const QString &id)
    : AbstractPhysicalResource(*new ComponentPrivate)
{
    setId(id);
}

void ComponentPrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(Component);
    ComponentSP castedOther = qSharedPointerCast<Component>(other);
    q->setComponentType(castedOther->componentType());
    q->setWidth(castedOther->width());
    q->setHeight(castedOther->height());
    q->setLength(castedOther->length());
    q->setBundle(castedOther->bundle());
    q->setPartIdKeys(castedOther->partIdKeys());
    q->updateCutBlocks(castedOther->cutBlocks());

    AbstractPhysicalResourcePrivate::updateFrom(other);
}

bool ComponentPrivate::partsAreValid(QList<ApiHelper::ResourcePartType> partsToCheck) const
{
    if (partsToCheck.isEmpty() && !partIdKeys.isEmpty())
        partsToCheck = partIdKeys;
    if (partsToCheck.isEmpty()) {
        if (parts.count())
            qCCritical(proofNetworkJdfDataLog) << "Component partioning is not valid. Extra parts found";
        return parts.isEmpty();
    }

    auto currentPart = partsToCheck.takeFirst();

    for (const auto &part : parts) {
        if (!part->hasPartAttribute(currentPart)) {
            qCCritical(proofNetworkJdfDataLog) << "Component partioning is not valid. Part" << ApiHelper::resourcePartTypeToString(currentPart) << "not found";
            return false;
        }
        if (!part->d_func()->partsAreValid(partsToCheck))
            return false;
    }
    return true;

}

