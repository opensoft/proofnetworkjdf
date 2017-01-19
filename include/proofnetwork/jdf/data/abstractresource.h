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
    ApiHelper::ResourceStatus resourceStatus() const;
    ApiHelper::ResourceClass resourceClass() const;
    QList<ApiHelper::ResourcePartType> partIdKeys() const;

    void setId(const QString &arg);
    void setResourceStatus(ApiHelper::ResourceStatus arg);
    void setResourceClass(ApiHelper::ResourceClass arg);
    void setPartIdKeys(const QList<ApiHelper::ResourcePartType> &arg);

    QString partAttribute(ApiHelper::ResourcePartType attribute) const;
    bool hasPartAttribute(ApiHelper::ResourcePartType attribute) const;
    void setPartAttribute(ApiHelper::ResourcePartType attribute, const QString &value);

    static bool fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void idChanged(const QString &arg);
    void statusChanged(Proof::Jdf::ApiHelper::ResourceStatus arg);
    void resourceClassChanged(Proof::Jdf::ApiHelper::ResourceClass arg);
    void partIdKeysChanged(const QList<Proof::Jdf::ApiHelper::ResourcePartType> &arg);
    void partAttributeChanged(ApiHelper::ResourcePartType attribute, const QString &value);

protected:
    explicit AbstractResource() = delete;
    AbstractResource(AbstractResourcePrivate &dd, QObject *parent = 0);
    void setupLink(const AbstractResourceLinkSP &abstractLink, ApiHelper::Usage usage) const;
};

}
}

#endif // PROOF_JDF_ABSTRACTRESOURCE_H
