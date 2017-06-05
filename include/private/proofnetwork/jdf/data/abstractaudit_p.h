#ifndef PROOF_JDF_ABSTRACTAUDIT_P_H
#define PROOF_JDF_ABSTRACTAUDIT_P_H

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class AbstractAuditPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractAudit)
public:
    AbstractAuditPrivate() : NetworkDataEntityPrivate() {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString id;
    QString agentName;
    QString agentVersion;
    QDateTime timeStamp;
};

}
}

#endif // ABSTRACTAUDIT_P_H
