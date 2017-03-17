#ifndef ABSTRACTRESOURCELINKQMLWRAPPER_H
#define ABSTRACTRESOURCELINKQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class AbstractResourceLinkQmlWrapperPrivate;
class AbstractResourceLinkQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::ApiHelper::Usage usage READ usage NOTIFY usageChanged)
    Q_PROPERTY(QString rRef READ rRef NOTIFY rRefChanged)
    Q_DECLARE_PRIVATE(AbstractResourceLinkQmlWrapper)
public:
    explicit AbstractResourceLinkQmlWrapper(const QSharedPointer<AbstractResourceLink> &link,
                                            AbstractResourceLinkQmlWrapperPrivate &dd,
                                            QObject *parent = nullptr);
    ~AbstractResourceLinkQmlWrapper();
    Proof::Jdf::ApiHelper::Usage usage() const;
    QString rRef() const;

signals:
    void usageChanged(Proof::Jdf::ApiHelper::Usage usage);
    void rRefChanged(const QString &rRef);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // ABSTRACTRESOURCELINKQMLWRAPPER_H
