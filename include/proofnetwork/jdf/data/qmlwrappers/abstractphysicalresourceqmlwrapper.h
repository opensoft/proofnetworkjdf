#ifndef PROOF_JDF_ABSTRACTPHYSICALRESOURCEQMLWRAPPER_H
#define PROOF_JDF_ABSTRACTPHYSICALRESOURCEQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourceQmlWrapperPrivate;

class PROOF_NETWORK_JDF_EXPORT AbstractPhysicalResourceQmlWrapper : public AbstractResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString amount READ amount NOTIFY amountChanged)
    Q_PROPERTY(QString resourceWeight READ resourceWeight NOTIFY resourceWeightChanged)

    Q_DECLARE_PRIVATE(AbstractPhysicalResourceQmlWrapper)
public:
    explicit AbstractPhysicalResourceQmlWrapper(const QSharedPointer<AbstractPhysicalResource> &abstractPhysicalResource,
                                        AbstractPhysicalResourceQmlWrapperPrivate &dd, QObject *parent = 0);
    ~AbstractPhysicalResourceQmlWrapper();

    double amount() const;
    double resourceWeight() const;

signals:
    void amountChanged(double arg);
    void resourceWeightChanged(double arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // PROOF_JDF_ABSTRACTPHYSICALRESOURCEQMLWRAPPER_H
