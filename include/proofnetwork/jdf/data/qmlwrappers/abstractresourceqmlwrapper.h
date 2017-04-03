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
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(Proof::Jdf::ResourceStatus resourceStatus READ resourceStatus NOTIFY resourceStatusChanged)
    Q_PROPERTY(Proof::Jdf::ResourceClass resourceClass READ resourceClass NOTIFY resourceClassChanged)
    Q_PROPERTY(QList<ResourcePartType> partIdKeys READ partIdKeys NOTIFY partIdKeysChanged)

    Q_DECLARE_PRIVATE(AbstractResourceQmlWrapper)
public:
    explicit AbstractResourceQmlWrapper(const QSharedPointer<AbstractResource> &abstractResource,
                                        AbstractResourceQmlWrapperPrivate &dd, QObject *parent = nullptr);
    ~AbstractResourceQmlWrapper();

    QString id() const;
    ResourceStatus resourceStatus() const;
    ResourceClass resourceClass() const;
    QList<ResourcePartType> partIdKeys() const;

signals:
    void idChanged(const QString &id);
    void resourceStatusChanged(Proof::Jdf::ResourceStatus resourceStatus);
    void resourceClassChanged(Proof::Jdf::ResourceClass resourceClass);
    void partIdKeysChanged(const QList<ResourcePartType> &partIdKeys);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // PROOF_JDF_ABSTRACTRESOURCEQMLWRAPPER_H
