#ifndef ABSTRACTRESOURCELINK_H
#define ABSTRACTRESOURCELINK_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractResourceLinkPrivate;

class PROOF_NETWORK_JDF_EXPORT AbstractResourceLink : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractResourceLink)
public:
    LinkUsage usage() const;
    ProcessUsage processUsage() const;
    QString rRef() const;

    void setUsage(LinkUsage arg);
    void setProcessUsage(ProcessUsage arg);
    void setRRef(const QString &arg);

    static bool fromJdf(const QXmlStreamReader &xmlReader, const AbstractResourceLinkSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

    QString jdfNodeName() const;
    QString jdfNodeRefName() const;

signals:
    void usageChanged(Proof::Jdf::LinkUsage arg);
    void processUsageChanged(Proof::Jdf::ProcessUsage arg);
    void rRefChanged(const QString &arg);

protected:
    explicit AbstractResourceLink() = delete;
    AbstractResourceLink(AbstractResourceLinkPrivate &dd);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof
#endif // ABSTRACTRESOURCELINK_H
