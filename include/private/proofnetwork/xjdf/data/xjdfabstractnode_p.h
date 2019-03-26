#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/xjdf/data/xjdfabstractnode.h"

namespace Proof {
namespace XJdf {
class XJdfAbstractNodePrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(XJdfAbstractNode)

public:
    XJdfAbstractNodePrivate() = default;

    XJdfDocumentWP document;
};

} // namespace XJdf
} // namespace Proof
