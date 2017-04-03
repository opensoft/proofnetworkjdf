#ifndef PROOF_JDF_ABSTRACTRESOURCE_H
#define PROOF_JDF_ABSTRACTRESOURCE_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractResourcePrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractResource : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractResource)
public:

    QString id() const;
    ResourceStatus resourceStatus() const;
    ResourceClass resourceClass() const;
    QList<ResourcePartType> partIdKeys() const;

    void setId(const QString &arg);
    void setResourceStatus(ResourceStatus arg);
    void setResourceClass(ResourceClass arg);
    void setPartIdKeys(const QList<ResourcePartType> &arg);

    QString partAttribute(ResourcePartType attribute) const;
    bool hasPartAttribute(ResourcePartType attribute) const;
    void setPartAttribute(ResourcePartType attribute, const QString &value);

    static bool fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void idChanged(const QString &arg);
    void statusChanged(Proof::Jdf::ResourceStatus arg);
    void resourceClassChanged(Proof::Jdf::ResourceClass arg);
    void partIdKeysChanged(const QList<Proof::Jdf::ResourcePartType> &arg);
    void partAttributeChanged(ResourcePartType attribute, const QString &value);

protected:
    explicit AbstractResource() = delete;
    AbstractResource(AbstractResourcePrivate &dd, QObject *parent = nullptr);
    void setupLink(const AbstractResourceLinkSP &abstractLink, Usage usage) const;
};

}
}

#endif // PROOF_JDF_ABSTRACTRESOURCE_H
