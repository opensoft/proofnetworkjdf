#ifndef XJDF_GRAYBOXPRIVATE_H
#define XJDF_GRAYBOXPRIVATE_H

#include "xjdfabstractnode_p.h"

#include "proofnetwork/xjdf/data/graybox.h"

namespace Proof {
namespace XJdf {
class GrayBoxPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(GrayBox)

public:
    GrayBoxPrivate() = default;

    QVector<ProcessType> types;
    QVector<ResourceSetSP> resourceSets;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_GRAYBOXPRIVATE_H
