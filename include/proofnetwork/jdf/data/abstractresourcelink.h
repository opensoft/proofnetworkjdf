#ifndef ABSTRACTRESOURCELINK_H
#define ABSTRACTRESOURCELINK_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractResourceLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractResourceLink : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractResourceLink)
public:
    ApiHelper::Usage usage() const;
    QString rRef() const;

    void setUsage(ApiHelper::Usage arg);
    void setRRef(const QString &arg);

    static void fromJdf(const QXmlStreamReader &xmlReader, const AbstractResourceLinkSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void usageChanged(ApiHelper::Usage arg);
    void rRefChanged(const QString &arg);
protected:
    explicit AbstractResourceLink() = delete;
    AbstractResourceLink(AbstractResourceLinkPrivate &dd, QObject *parent = nullptr);
};

}
}
#endif // ABSTRACTRESOURCELINK_H
