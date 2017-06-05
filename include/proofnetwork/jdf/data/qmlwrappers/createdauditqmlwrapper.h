#ifndef PROOF_JDF_CREATEDAUDITQMLWRAPPER_H
#define PROOF_JDF_CREATEDAUDITQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractauditqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

namespace Proof {
namespace Jdf {

class CreatedAudit;

class CreatedAuditQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT CreatedAuditQmlWrapper : public AbstractAuditQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString templateId READ templateId NOTIFY templateIdChanged)
    Q_PROPERTY(QString templateVersion READ templateVersion NOTIFY templateVersionChanged)
    Q_DECLARE_PRIVATE(CreatedAuditQmlWrapper)
public:
    explicit CreatedAuditQmlWrapper(const CreatedAuditSP &createdAudit, QObject *parent = nullptr);
    ~CreatedAuditQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(CreatedAudit)

    QString templateId() const;
    QString templateVersion() const;

signals:
    void templateIdChanged(const QString &arg);
    void templateVersionChanged(const QString &arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}

#endif // PROOF_JDF_CREATEDAUDITQMLWRAPPER_H
