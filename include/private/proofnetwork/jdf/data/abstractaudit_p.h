#ifndef PROOF_JDF_ABSTRACTAUDIT_P_H
#define PROOF_JDF_ABSTRACTAUDIT_P_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class AbstractAuditPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(AbstractAudit)
public:
    AbstractAuditPrivate() : NetworkDataEntityPrivate() {}

    QString id;
    QString agentName;
    QString agentVersion;
    QDateTime timeStamp;
};

} // namespace Jdf
} // namespace Proof

#endif // ABSTRACTAUDIT_P_H
