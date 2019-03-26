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
    ColorIntent &operator=(const ColorIntent &) = delete;
    ColorIntent(ColorIntent &&) = delete;
    ColorIntent &operator=(ColorIntent &&) = delete;
    ~ColorIntent() = default;

    QMap<Side, QVector<CoatingType>> coatings() const;
    QMap<Side, bool> spots() const;

    void setCoatings(const QMap<Side, QVector<CoatingType>> &arg);
    void addCoating(Side side, CoatingType arg);

    void setSpots(const QMap<Side, bool> &arg);
    void addSpot(Side side, bool arg);

    static ColorIntentSP create();

    static ColorIntentSP fromXJdf(QXmlStreamReader &reader);
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void coatingsChanged(const QMap<Proof::XJdf::Side, QVector<Proof::XJdf::CoatingType>> &arg);
    void spotsChanged(const QMap<Proof::XJdf::Side, bool> &arg);

protected:
    explicit ColorIntent();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_COLORINTENT_H
