#ifndef AUDITPOOLQMLWRAPPER_H
#define AUDITPOOLQMLWRAPPER_H

#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class CreatedAuditQmlWrapper;
class ModifiedAuditQmlWrapper;

class AuditPoolQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT AuditPoolQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(Proof::Jdf::CreatedAuditQmlWrapper *created READ created NOTIFY createdChanged)
    Q_PROPERTY(Proof::Jdf::ModifiedAuditQmlWrapper *modified READ modified NOTIFY modifiedChanged)

    Q_DECLARE_PRIVATE(AuditPoolQmlWrapper)

public:
    explicit AuditPoolQmlWrapper(const AuditPoolSP &auditPool, QObject *parent = nullptr);
    ~AuditPoolQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(AuditPool)

    CreatedAuditQmlWrapper *created() const;
    ModifiedAuditQmlWrapper *modified() const;

signals:
    void createdChanged(Proof::Jdf::CreatedAuditQmlWrapper *created);
    void modifiedChanged(Proof::Jdf::ModifiedAuditQmlWrapper *modified);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // AUDITPOOLQMLWRAPPER_H
