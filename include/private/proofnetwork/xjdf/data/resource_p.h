#ifndef XJDF_RESOURCEPRIVATE_H
#define XJDF_RESOURCEPRIVATE_H

#include "xjdfabstractnode_p.h"

#include "proofnetwork/xjdf/data/resource.h"

namespace Proof {
namespace XJdf {
class ResourcePrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(Resource)

public:
    ResourcePrivate() = default;
    QString id;
    ResourceOrientation orientation = ResourceOrientation::Rotate0Orientation;
    QVector<PartSP> parts;
    AmountPoolSP amountPool;

    static QMap<QString, std::function<ResourceSP(QXmlStreamReader &, const XJdfDocumentSP &)>> *creators;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_RESOURCEPRIVATE_H
