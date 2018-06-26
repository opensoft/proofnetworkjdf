#include "abstractresource.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"

using namespace Proof::Jdf;

QString AbstractResource::id() const
{
    Q_D(const AbstractResource);
    return d->id;
}

ResourceStatus AbstractResource::resourceStatus() const
{
    Q_D(const AbstractResource);
    return d->resourceStatus;
}

ResourceClass AbstractResource::resourceClass() const
{
    Q_D(const AbstractResource);
    return d->resourceClass;
}

QVector<ResourcePartType> AbstractResource::partIdKeys() const
{
    Q_D(const AbstractResource);
    return d->partIdKeys;
}

void AbstractResource::setId(const QString &arg)
{
    Q_D(AbstractResource);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void AbstractResource::setResourceStatus(ResourceStatus arg)
{
    Q_D(AbstractResource);
    if (d->resourceStatus != arg) {
        d->resourceStatus = arg;
        emit statusChanged(d->resourceStatus);
    }
}

void AbstractResource::setResourceClass(ResourceClass arg)
{
    Q_D(AbstractResource);
    if (d->resourceClass != arg) {
        d->resourceClass = arg;
        emit resourceClassChanged(d->resourceClass);
    }
}

void AbstractResource::setPartIdKeys(const QVector<ResourcePartType> &arg)
{
    Q_D(AbstractResource);
    if (d->partIdKeys != arg) {
        d->partIdKeys = arg;
        emit partIdKeysChanged(d->partIdKeys);
    }
}

QString AbstractResource::partAttribute(ResourcePartType attribute) const
{
    Q_D(const AbstractResource);
    return d->partAttributes.value(attribute, QString());
}

bool AbstractResource::hasPartAttribute(ResourcePartType attribute) const
{
    Q_D(const AbstractResource);
    return d->partAttributes.contains(attribute);
}

void AbstractResource::setPartAttribute(ResourcePartType attribute, const QString &value)
{
    Q_D(AbstractResource);
    d->partAttributes[attribute] = value;
    emit partAttributeChanged(attribute, value);
}

bool AbstractResource::fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    QStringList partIdKeysStringified =
        attributes.value(QStringLiteral("PartIDKeys")).toString().split(QStringLiteral(" "), QString::SkipEmptyParts);
    QVector<ResourcePartType> partIdKeys;
    for (const QString &partName : partIdKeysStringified) {
        bool ok = false;
        ResourcePartType part = resourcePartTypeFromString(partName, &ok);
        if (!ok)
            return false;
        partIdKeys << part;
    }
    abstractResource->setPartIdKeys(partIdKeys);
    abstractResource->setId(attributes.value(QStringLiteral("ID")).toString());
    abstractResource->setResourceStatus(resourceStatusFromString(attributes.value(QStringLiteral("Status")).toString()));

    for (const auto &attribute : attributes) {
        bool isPartAttribute = false;
        auto part = resourcePartTypeFromString(attribute.name().toString(), &isPartAttribute);
        if (!isPartAttribute)
            continue;
        abstractResource->setPartAttribute(part, attribute.value().toString());
    }

    return true;
}

void AbstractResource::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResource);
    if (!d->id.isEmpty())
        jdfWriter.writeAttribute(QStringLiteral("ID"), d->id);
    if (d->resourceStatus != ResourceStatus::NoStatus)
        jdfWriter.writeAttribute(QStringLiteral("Status"), resourceStatusToString(d->resourceStatus));
    if (d->resourceClass != ResourceClass::NoClass)
        jdfWriter.writeAttribute(QStringLiteral("Class"), resourceClassToString(d->resourceClass));
    QStringList partIdKeysStringified;
    for (auto part : qAsConst(d->partIdKeys))
        partIdKeysStringified += resourcePartTypeToString(part);
    if (partIdKeysStringified.count())
        jdfWriter.writeAttribute(QStringLiteral("PartIDKeys"), partIdKeysStringified.join(QStringLiteral(" ")));
    for (auto it = d->partAttributes.cbegin(); it != d->partAttributes.cend(); ++it)
        jdfWriter.writeAttribute(resourcePartTypeToString(it.key()), it.value());
}

void AbstractResource::refToJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResource);
    jdfWriter.writeStartElement(jdfNodeRefName());
    jdfWriter.writeAttribute(QStringLiteral("rRef"), d->id);
    jdfWriter.writeEndElement();
}

QString AbstractResource::jdfNodeName() const
{
    Q_D(const AbstractResource);
    if (d->jdfNodeName.isEmpty())
        d->jdfNodeName = QString(metaObject()->className())
                             .remove(0, QString(metaObject()->className()).lastIndexOf(QLatin1String(":")) + 1);
    return d->jdfNodeName;
}

QString AbstractResource::jdfNodeRefName() const
{
    Q_D(const AbstractResource);
    if (d->jdfNodeRefName.isEmpty())
        d->jdfNodeRefName = QStringLiteral("%1Ref").arg(jdfNodeName());
    return d->jdfNodeRefName;
}

AbstractResource::AbstractResource(AbstractResourcePrivate &dd) : NetworkDataEntity(dd)
{}

void AbstractResource::setupLink(const AbstractResourceLinkSP &abstractLink, LinkUsage usage) const
{
    abstractLink->setRRef(id());
    abstractLink->setUsage(usage);
}

void AbstractResource::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    AbstractResourceSP castedOther = qSharedPointerCast<AbstractResource>(other);
    setId(castedOther->id());
    setResourceStatus(castedOther->resourceStatus());
    setResourceClass(castedOther->resourceClass());
    setPartIdKeys(castedOther->partIdKeys());

    NetworkDataEntity::updateSelf(other);
}
