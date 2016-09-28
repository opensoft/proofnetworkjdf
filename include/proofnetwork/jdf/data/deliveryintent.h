#ifndef JDFDELIVERYINTENT_H
#define JDFDELIVERYINTENT_H

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/deliveryintentqmlwrapper.h"
#include "proofnetwork/jdf/data/span.h"

#include <QXmlStreamReader>
#include <QDateTime>

namespace Proof {
namespace Jdf {

class DeliveryIntentPrivate;
class PROOF_NETWORK_JDF_EXPORT DeliveryIntent : public AbstractResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeliveryIntent)
public:

    TimeSpan required() const;
    QList<DropIntentSP> dropIntents() const;

    void setRequired(const TimeSpan &arg);
    void setDropIntents(const QList<DropIntentSP> &arg);
    void addDropIntent(const DropIntentSP &arg);

    DeliveryIntentQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static DeliveryIntentSP create();

    static DeliveryIntentSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    DeliveryIntentLinkSP toLink(ApiHelper::Usage usage = ApiHelper::Usage::InputUsage) const;

signals:
    void requiredChanged(const TimeSpan &required);
    void dropIntentsChanged();

protected:
    explicit DeliveryIntent();

};

}
}

#endif // JDFDELIVERYINTENT_H
