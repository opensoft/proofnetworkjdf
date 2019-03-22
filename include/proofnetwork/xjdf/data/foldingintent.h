#ifndef XJDF_FOLDINGINTENT_H
#define XJDF_FOLDINGINTENT_H

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/intent.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class FoldingIntentPrivate;
class PROOF_NETWORK_XJDF_EXPORT FoldingIntent : public Intent
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FoldingIntent)
public:
    FoldingIntent(const FoldingIntent &) = delete;
    FoldingIntent &operator=(const Intent &) = delete;
    FoldingIntent(Intent &&) = delete;
    FoldingIntent &operator=(FoldingIntent &&) = delete;
    ~FoldingIntent() = default;

    FoldType foldCatalog() const;
    void setFoldCatalog(FoldType arg);

    static FoldingIntentSP create();

    static FoldingIntentSP fromXJdf(QXmlStreamReader &xjdfReader);
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;
signals:
    void foldCatalogChanged(FoldType type);

protected:
    FoldingIntent();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_FOLDINGINTENT_H
