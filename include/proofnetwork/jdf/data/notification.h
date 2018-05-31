#ifndef PROOF_JDF_NOTIFICATION_H
#define PROOF_JDF_NOTIFICATION_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class NotificationPrivate;
class PROOF_NETWORK_JDF_EXPORT Notification : public NetworkDataEntity // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Notification)
public:
    NotificationClass notificationClass() const;
    QString comment() const;

    void setNotificationClass(NotificationClass arg);
    void setComment(const QString &arg);

    static NotificationSP create();

    NetworkDataEntityQmlWrapper *toQmlWrapper(QObject *parent) const override;

    void toJdf(QXmlStreamWriter &xmlWriter);
    static NotificationSP fromJdf(QXmlStreamReader &xmlReader);

signals:
    void notificationClassChanged(Proof::Jdf::NotificationClass arg);
    void commentChanged(const QString &arg);

protected:
    explicit Notification();
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_NOTIFICATION_H
