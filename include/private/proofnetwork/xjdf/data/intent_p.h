#ifndef XJDF_GRAYBOXPRIVATE_H
#define XJDF_GRAYBOXPRIVATE_H

#include "xjdfabstractnode_p.h"

#include "proofnetwork/xjdf/data/graybox.h"

namespace Proof {
namespace XJdf {
class IntentPrivate : public XJdfAbstractNodePrivate
{
    Q_DECLARE_PUBLIC(Intent)

public:
    IntentPrivate() = default;
    QString name;

    static QMap<QString, std::function<IntentSP(QXmlStreamReader &)>> creators;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_GRAYBOXPRIVATE_H
