#ifndef JDFJDFNODE_P_H
#define JDFJDFNODE_P_H

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"

#include <QList>

namespace Proof {
namespace Jdf {

class JdfNodePrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(JdfNode)

public:
    JdfNodePrivate();

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    QString id;
    QString jobId;
    QString jobPartId;
    ResourcePoolSP resourcePool = ResourcePool::create();
    ResourceLinkPoolSP resourceLinkPool = ResourceLinkPool::create();
    QList<JdfNodeSP> jdfNodes;
    QString type = QLatin1String("");
};

}
}

#endif // JDFJDFNODE_P_H
