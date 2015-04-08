#ifndef PROOF_JDF_ABSTRACTRESOURCEQMLWRAPPER_H
#define PROOF_JDF_ABSTRACTRESOURCEQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class AbstractResourceQmlWrapperPrivate;

class PROOF_NETWORK_JDF_EXPORT AbstractResourceQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(Proof::Jdf::ApiHelper::ResourceStatus status READ status CONSTANT)
    Q_PROPERTY(Proof::Jdf::ApiHelper::ResourceClass resourceClass READ resourceClass CONSTANT)

    Q_PROPERTY(Proof::Jdf::ApiHelper::Usage usage READ usage CONSTANT)

    Q_DECLARE_PRIVATE(AbstractResourceQmlWrapper)
public:
    explicit AbstractResourceQmlWrapper(const QSharedPointer<AbstractResource> &abstractResource,
                                        AbstractResourceQmlWrapperPrivate &dd, QObject *parent = 0);
    ~AbstractResourceQmlWrapper();

    QString id() const;
    ApiHelper::ResourceStatus status() const;
    ApiHelper::ResourceClass resourceClass() const;

    ApiHelper::Usage usage() const;

signals:
    void idChanged(const QString &arg);
    void statusChanged(Proof::Jdf::ApiHelper::ResourceStatus arg);
    void resourceClassChanged(Proof::Jdf::ApiHelper::ResourceClass arg);

    void usageChanged(Proof::Jdf::ApiHelper::Usage arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // PROOF_JDF_ABSTRACTRESOURCEQMLWRAPPER_H
