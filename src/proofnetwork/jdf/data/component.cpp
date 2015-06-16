#include "component.h"

#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/cutblock.h"

#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"

namespace Proof {
namespace Jdf {

class ComponentPrivate : AbstractPhysicalResourcePrivate
{
    Q_DECLARE_PUBLIC(Component)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    ApiHelper::ComponentOrientation orientation = ApiHelper::Rotate0Orientaiton;
    ApiHelper::ComponentType componentType = ApiHelper::ComponentType::SheetComponent;
    double width = 0.0;
    double height = 0.0;
    double length = 0.0;
    BundleSP bundle = Bundle::defaultObject();
    QList<CutBlockSP> cutBlocks;
};

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

ApiHelper::ComponentOrientation Component::orientation() const
{
    Q_D(const Component);
    return d->orientation;
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

void Component::setOrientation(ApiHelper::ComponentOrientation arg)
{
    Q_D(Component);
    if (d->orientation != arg) {
        d->orientation = arg;
        emit orientationChanged(arg);
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
    ApiHelper::PartIdKeysType partIDKeys = ApiHelper::PartIdKeysType::BlockNameKey;

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
            } else if (component->componentType() == ApiHelper::ComponentType::SheetComponent || dimensionsList.count()) {
                qCCritical(proofNetworkJdfDataLog) << "Component not created. Dimensions is not valid";
                return ComponentSP();
            }

            partIDKeys = ApiHelper::partIdKeysTypeFromString(attributes.value("PartIDKeys").toString());

            AbstractPhysicalResourceSP castedComponent = qSharedPointerCast<AbstractPhysicalResource>(component);
            AbstractPhysicalResource::fromJdf(xmlReader, castedComponent);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Component") {
                QXmlStreamAttributes attributes = xmlReader.attributes();

                switch (partIDKeys) {
                case ApiHelper::PartIdKeysType::BlockNameKey: {
                    QString blockName = attributes.value(ApiHelper::partIdKeysTypeToString(ApiHelper::PartIdKeysType::BlockNameKey)).toString();
                    cutBlocks << cutBlockCache().add({jdfId, blockName}, CutBlock::create(blockName));
                    break;
                }
                case ApiHelper::PartIdKeysType::BundleItemIndexKey:
                case ApiHelper::PartIdKeysType::CellIndexKey:
                default:
                    break;
                }
                xmlReader.skipCurrentElement();
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

    component->updateCutBlocks(cutBlocks);

    return component;
}

void Component::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Component);
    jdfWriter.writeStartElement("Component");
    jdfWriter.writeAttribute("ComponentType", ApiHelper::componentTypeToString(d->componentType));
    if (!qFuzzyCompare(1.0 + d->width, 1.0) || !qFuzzyCompare(1.0 + d->height, 1.0) || !qFuzzyCompare(1.0 + d->length, 1.0)) {
        jdfWriter.writeAttribute("Dimensions", QString("%1 %2 %3")
                                 .arg(d->width, 0, 'f', 4)
                                 .arg(d->height, 0, 'f', 4)
                                 .arg(d->length, 0, 'f', 4));
    }

    AbstractPhysicalResource::toJdf(jdfWriter);

    if (d->cutBlocks.count()) {
        QString blockNameText = ApiHelper::partIdKeysTypeToString(ApiHelper::PartIdKeysType::BlockNameKey);
        jdfWriter.writeAttribute("PartIDKeys", blockNameText);
        for (const CutBlockSP &cutBlock : d->cutBlocks) {
            jdfWriter.writeStartElement("Component");
            jdfWriter.writeAttribute(blockNameText, cutBlock->blockName());
            jdfWriter.writeEndElement();
        }
    }

    if (d->bundle != Bundle::defaultObject())
        d->bundle->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

void Component::toJdfLink(QXmlStreamWriter &jdfWriter)
{
    Q_D(Component);
    QString className =  QString(metaObject()->className()).remove(0, QString(metaObject()->className()).lastIndexOf(":") + 1);
    jdfWriter.writeStartElement(className + QString("Link"));
    jdfWriter.writeAttribute("Usage", ApiHelper::usageToString(d->usage));
    if (d->orientation != ApiHelper::Rotate0Orientaiton)
        jdfWriter.writeAttribute("Orientation", ApiHelper::componentOrientationToString(d->orientation));
    jdfWriter.writeAttribute("rRef", d->id);
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
    setResourceClass(ApiHelper::ResourceClass::QuantityClass);
}

void ComponentPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(Component);
    ComponentSP castedOther = qSharedPointerCast<Component>(other);
    q->setComponentType(castedOther->componentType());
    q->setWidth(castedOther->width());
    q->setHeight(castedOther->height());
    q->setLength(castedOther->length());
    q->setBundle(castedOther->bundle());
    q->updateCutBlocks(castedOther->cutBlocks());

    AbstractPhysicalResourcePrivate::updateFrom(other);
}

