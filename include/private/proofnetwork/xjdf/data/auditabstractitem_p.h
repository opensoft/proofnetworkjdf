#ifndef XJDF_AUDITABSTRACTITEM_P_H
#define XJDF_AUDITABSTRACTITEM_P_H

#include "proofnetwork/xjdf/data/auditabstractitem.h"
#include "proofnetwork/xjdf/data/xjdfabstractnode_p.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class AuditAbstractItemPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(AuditAbstractItem)

public:
    AuditAbstractItemPrivate() {}

    QString agentName;
    QString agentVersion;
    QDateTime timestamp;
    QString id;
    QString deviceId;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_AUDITABSTRACTITEM_P_H
