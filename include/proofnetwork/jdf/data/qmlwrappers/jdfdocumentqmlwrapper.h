#ifndef JDFJDFDOCUMENTQMLWRAPPER_H
#define JDFJDFDOCUMENTQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

namespace Proof {
namespace Jdf {

class ResourcePoolQmlWrapper;

class JdfDocumentQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT JdfDocumentQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(QString jobId READ jobId NOTIFY jobIdChanged)
    Q_PROPERTY(QString jobPartId READ jobPartId NOTIFY jobPartIdChanged)
    Q_PROPERTY(Proof::Jdf::ResourcePoolQmlWrapper *resourcePool READ resourcePool NOTIFY resourcePoolChanged)
    Q_DECLARE_PRIVATE(JdfDocumentQmlWrapper)
public:
    explicit JdfDocumentQmlWrapper(const JdfDocumentSP &jdfDoc, QObject *parent = 0);
    ~JdfDocumentQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(JdfDocument)

    QString id() const;
    QString jobId() const;
    QString jobPartId() const;
    ResourcePoolQmlWrapper *resourcePool() const;

signals:
    void idChanged(const QString &id);
    void jobIdChanged(const QString &jobId);
    void jobPartIdChanged(const QString &jobPartId);
    void resourcePoolChanged(Proof::Jdf::ResourcePoolQmlWrapper *resourcePool);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // JDFJDFDOCUMENTQMLWRAPPER_H
