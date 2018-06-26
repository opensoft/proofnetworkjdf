#ifndef JDFJDFNODE_P_H
#define JDFJDFNODE_P_H

#include "proofnetwork/jdf/data/auditpool.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/networkdataentity_p.h"

#include <QVector>

namespace Proof {
namespace Jdf {

class JdfNodePrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(JdfNode)

public:
    JdfNodePrivate();

    QString id;
    QString jobId;
    QString jobPartId;
    AuditPoolSP auditPool = AuditPool::create();
    ResourcePoolSP resourcePool = ResourcePool::create();
    ResourceLinkPoolSP resourceLinkPool = ResourceLinkPool::create();
    QVector<JdfNodeSP> jdfNodes;
    QString type = QLatin1String("");
    QStringList types;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFJDFNODE_P_H
