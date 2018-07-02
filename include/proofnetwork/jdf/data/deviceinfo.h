#ifndef PROOF_JDF_DEVICEINFO_H
#define PROOF_JDF_DEVICEINFO_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/networkdataentity.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class DeviceInfoPrivate;
class PROOF_NETWORK_JDF_EXPORT DeviceInfo : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeviceInfo)

public:
    QString deviceId() const;
    DeviceStatus status() const;
    DeviceCondition condition() const;

    void setDeviceId(const QString &arg);
    void setStatus(DeviceStatus arg);
    void setCondition(DeviceCondition arg);

    NetworkDataEntityQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DeviceInfoSP create();

    static DeviceInfoSP fromJmf(QXmlStreamReader &xmlReader);
    void toJmf(QXmlStreamWriter &xmlWriter);

signals:
    void deviceIdChanged(const QString &arg);
    void statusChanged(Proof::Jdf::DeviceStatus arg);
    void conditionChanged(Proof::Jdf::DeviceCondition arg);

protected:
    explicit DeviceInfo();
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_DEVICEINFO_H
