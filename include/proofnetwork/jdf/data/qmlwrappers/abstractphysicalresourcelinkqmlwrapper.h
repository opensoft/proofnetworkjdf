#ifndef ABSTRACTPHYSICALRESOURCELINKQMLWRAPPER_H
#define ABSTRACTPHYSICALRESOURCELINKQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourceLinkQmlWrapperPrivate;
class AbstractPhysicalResourceLinkQmlWrapper : public AbstractResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::ResourceOrientation orientation READ orientation NOTIFY orientationChanged)
    Q_PROPERTY(double amount READ amount NOTIFY amountChanged)

    Q_DECLARE_PRIVATE(AbstractPhysicalResourceLinkQmlWrapper)
public:
    AbstractPhysicalResourceLinkQmlWrapper(const QSharedPointer<AbstractPhysicalResourceLink> &link,
                                           AbstractPhysicalResourceLinkQmlWrapperPrivate &dd, QObject *parent = nullptr);
    ResourceOrientation orientation() const;
    double amount() const;

signals:
    void orientationChanged(ResourceOrientation orientation);
    void amountChanged(double amount);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof
#endif // ABSTRACTPHYSICALRESOURCELINKQMLWRAPPER_H
