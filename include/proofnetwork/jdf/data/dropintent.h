#ifndef JDFDROPINTENT_H
#define JDFDROPINTENT_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"
#include "proofnetwork/jdf/data/span.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QDateTime>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class DropIntentPrivate;
class PROOF_NETWORK_JDF_EXPORT DropIntent : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DropIntent)
public:
    TimeSpan earliest() const;
    DurationSpan earliestDuration() const;
    TimeSpan required() const;
    DurationSpan requiredDuration() const;
    NameSpan returnMethod() const;
    StringSpan serviceLevel() const;
    EnumerationSpan surplusHandling() const;
    EnumerationSpan transfer() const;

    QVector<DropItemIntentSP> dropItemIntents() const;

    void setEarliest(const TimeSpan &arg);
    void setEarliestDuration(const DurationSpan &arg);
    void setRequired(const TimeSpan &arg);
    void setRequiredDuration(const DurationSpan &arg);
    void setReturnMethod(const NameSpan &arg);
    void setServiceLevel(const StringSpan &arg);
    void setSurplusHandling(const EnumerationSpan &arg);
    void setTransfer(const EnumerationSpan &arg);

    void setDropItemIntents(const QVector<DropItemIntentSP> &arg);
    void addDropItemIntent(const DropItemIntentSP &arg);

    DropIntentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DropIntentSP create();

    static DropIntentSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void earliestChanged(const Proof::Jdf::TimeSpan &arg);
    void earliestDurationChanged(const Proof::Jdf::DurationSpan &arg);
    void requiredChanged(const Proof::Jdf::TimeSpan &arg);
    void requiredDurationChanged(const Proof::Jdf::DurationSpan &arg);
    void returnMethodChanged(const Proof::Jdf::NameSpan &arg);
    void serviceLevelChanged(const Proof::Jdf::StringSpan &arg);
    void surplusHandlingChanged(const Proof::Jdf::EnumerationSpan &arg);
    void transferChanged(const Proof::Jdf::EnumerationSpan &arg);
    void dropItemIntentsChanged();

protected:
    explicit DropIntent();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFDROPINTENT_H
