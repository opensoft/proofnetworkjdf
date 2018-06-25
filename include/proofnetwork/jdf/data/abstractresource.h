#ifndef PROOF_JDF_ABSTRACTRESOURCE_H
#define PROOF_JDF_ABSTRACTRESOURCE_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractResourcePrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractResource : public NetworkDataEntity // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractResource)
public:
    QString id() const;
    ResourceStatus resourceStatus() const;
    ResourceClass resourceClass() const;
    QVector<ResourcePartType> partIdKeys() const;

    void setId(const QString &arg);
    void setResourceStatus(ResourceStatus arg);
    void setResourceClass(ResourceClass arg);
    void setPartIdKeys(const QVector<ResourcePartType> &arg);

    QString partAttribute(ResourcePartType attribute) const;
    bool hasPartAttribute(ResourcePartType attribute) const;
    void setPartAttribute(ResourcePartType attribute, const QString &value);

    static bool fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

    void refToJdf(QXmlStreamWriter &jdfWriter);

    //TODO: 1.0 think about proper way to do it
    QString jdfNodeName() const;
    QString jdfNodeRefName() const;

signals:
    void idChanged(const QString &arg);
    void statusChanged(Proof::Jdf::ResourceStatus arg);
    void resourceClassChanged(Proof::Jdf::ResourceClass arg);
    void partIdKeysChanged(const QVector<Proof::Jdf::ResourcePartType> &arg);
    void partAttributeChanged(ResourcePartType attribute, const QString &value);

protected:
    explicit AbstractResource() = delete;
    AbstractResource(AbstractResourcePrivate &dd, QObject *parent = nullptr);
    void setupLink(const AbstractResourceLinkSP &abstractLink, LinkUsage usage) const;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_ABSTRACTRESOURCE_H
