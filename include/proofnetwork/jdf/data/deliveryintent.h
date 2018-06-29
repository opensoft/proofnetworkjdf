#ifndef JDFDELIVERYINTENT_H
#define JDFDELIVERYINTENT_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/deliveryintentqmlwrapper.h"
#include "proofnetwork/jdf/data/span.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QDateTime>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class DeliveryIntentPrivate;
class PROOF_NETWORK_JDF_EXPORT DeliveryIntent : public AbstractResource // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeliveryIntent)
public:
    EnumerationSpan deliveryCharge() const;
    TimeSpan earliest() const;
    DurationSpan earliestDuration() const;
    NameSpan method() const;
    NumberSpan overage() const;
    TimeSpan required() const;
    DurationSpan requiredDuration() const;
    NameSpan returnMethod() const;
    StringSpan serviceLevel() const;
    EnumerationSpan surplusHandling() const;
    EnumerationSpan transfer() const;
    NumberSpan underage() const;

    QVector<DropIntentSP> dropIntents() const;

    void setDeliveryCharge(const EnumerationSpan &arg);
    void setEarliest(const TimeSpan &arg);
    void setEarliestDuration(const DurationSpan &arg);
    void setMethod(const NameSpan &arg);
    void setOverage(const NumberSpan &arg);
    void setRequired(const TimeSpan &arg);
    void setRequiredDuration(const DurationSpan &arg);
    void setReturnMethod(const NameSpan &arg);
    void setServiceLevel(const StringSpan &arg);
    void setSurplusHandling(const EnumerationSpan &arg);
    void setTransfer(const EnumerationSpan &arg);
    void setUnderage(const NumberSpan &arg);

    void setDropIntents(const QVector<DropIntentSP> &arg);
    void addDropIntent(const DropIntentSP &arg);

    DeliveryIntentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DeliveryIntentSP create();

    static DeliveryIntentSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    DeliveryIntentLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

signals:
    void deliveryChargeChanged(const Proof::Jdf::EnumerationSpan &deliveryCharge);
    void earliestChanged(const Proof::Jdf::TimeSpan &arg);
    void earliestDurationChanged(const Proof::Jdf::DurationSpan &arg);
    void methodChanged(const Proof::Jdf::NameSpan &method);
    void overageChanged(const Proof::Jdf::NumberSpan &overage);
    void requiredChanged(const Proof::Jdf::TimeSpan &arg);
    void requiredDurationChanged(const Proof::Jdf::DurationSpan &arg);
    void returnMethodChanged(const Proof::Jdf::NameSpan &arg);
    void serviceLevelChanged(const Proof::Jdf::StringSpan &arg);
    void surplusHandlingChanged(const Proof::Jdf::EnumerationSpan &arg);
    void transferChanged(const Proof::Jdf::EnumerationSpan &arg);
    void underageChanged(const Proof::Jdf::NumberSpan &arg);
    void dropIntentsChanged();

protected:
    explicit DeliveryIntent();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFDELIVERYINTENT_H
