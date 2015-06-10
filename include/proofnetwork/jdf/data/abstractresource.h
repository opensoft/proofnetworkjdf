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

    void setId(const QString &arg);
    void setResourceStatus(ApiHelper::ResourceStatus arg);
    void setResourceClass(ApiHelper::ResourceClass arg);

    static void fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void idChanged(const QString &arg);
    void statusChanged(Proof::Jdf::ApiHelper::ResourceStatus arg);
    void resourceClassChanged(Proof::Jdf::ApiHelper::ResourceClass arg);

protected:
    explicit AbstractResource() = delete;
    AbstractResource(AbstractResourcePrivate &dd, QObject *parent = 0);

};

}
}


#endif // PROOF_JDF_ABSTRACTRESOURCE_H
