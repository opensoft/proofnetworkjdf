#ifndef XJDF_COLORINTENT_H
#define XJDF_COLORINTENT_H

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/intent.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class ColorIntentPrivate;
class PROOF_NETWORK_XJDF_EXPORT ColorIntent : public Intent
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ColorIntent)
public:
    ColorIntent(const ColorIntent &) = delete;
    ColorIntent &operator=(const Intent &) = delete;
    ColorIntent(Intent &&) = delete;
    ColorIntent &operator=(ColorIntent &&) = delete;
    ~ColorIntent() = default;

    QMap<Side, QVector<CoatingType>> coatings() const;
    QMap<Side, bool> spots() const;

    void setCoatings(const QMap<Side, QVector<CoatingType>> &arg);
    void addCoating(Side side, CoatingType type);

    void setSpots(const QMap<Side, bool> &arg);
    void addSpot(Side side, bool arg);

    static ColorIntentSP create();

    static ColorIntentSP fromXJdf(QXmlStreamReader &xjdfReader);
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;

signals:
    void coatingsChanged(const QMap<Side, QVector<CoatingType>> &arg);
    void spotsChanged(const QMap<Side, bool> &arg);

protected:
    ColorIntent();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_COLORINTENT_H
