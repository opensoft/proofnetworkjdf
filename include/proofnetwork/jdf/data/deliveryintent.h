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
    void deliveryChargeChanged(const EnumerationSpan &deliveryCharge);
    void earliestChanged(const TimeSpan &arg);
    void earliestDurationChanged(const DurationSpan &arg);
    void methodChanged(const NameSpan &method);
    void overageChanged(const NumberSpan &overage);
    void requiredChanged(const TimeSpan &arg);
    void requiredDurationChanged(const DurationSpan &arg);
    void returnMethodChanged(const NameSpan &arg);
    void serviceLevelChanged(const StringSpan &arg);
    void surplusHandlingChanged(const EnumerationSpan &arg);
    void transferChanged(const EnumerationSpan &arg);
    void underageChanged(const NumberSpan &arg);
    void dropIntentsChanged();

protected:
    explicit DeliveryIntent();
};

} // namespace Jdf
} // namespace Proof

#endif // JDFDELIVERYINTENT_H
