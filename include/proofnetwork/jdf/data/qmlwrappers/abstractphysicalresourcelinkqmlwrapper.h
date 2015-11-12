#ifndef ABSTRACTPHYSICALRESOURCELINKQMLWRAPPER_H
#define ABSTRACTPHYSICALRESOURCELINKQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourceLinkQmlWrapperPrivate;
class AbstractPhysicalResourceLinkQmlWrapper : public AbstractResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::ApiHelper::ResourceOrientation orientation READ orientation NOTIFY orientationChanged)
    Q_PROPERTY(double amount READ amount NOTIFY amountChanged)

    Q_DECLARE_PRIVATE(AbstractPhysicalResourceLinkQmlWrapper)
public:
    AbstractPhysicalResourceLinkQmlWrapper(const QSharedPointer<AbstractPhysicalResourceLink> &link,
                                           AbstractPhysicalResourceLinkQmlWrapperPrivate &dd, QObject *parent = 0);
    ApiHelper::ResourceOrientation orientation() const;
    double amount() const;

signals:
    void orientationChanged(ApiHelper::ResourceOrientation orientation);
    void amountChanged(double amount);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}
#endif // ABSTRACTPHYSICALRESOURCELINKQMLWRAPPER_H
