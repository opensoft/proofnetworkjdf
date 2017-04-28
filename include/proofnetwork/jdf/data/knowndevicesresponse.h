#ifndef PROOF_JDF_KNOWNDEVICESRESPONSE_H
#define PROOF_JDF_KNOWNDEVICESRESPONSE_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/response.h"

namespace Proof {
namespace Jdf {

class KnownDevicesResponsePrivate;
class PROOF_NETWORK_JDF_EXPORT KnownDevicesResponse : public Response // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KnownDevicesResponse)

public:
    QList<DeviceInfoSP> deviceInfos() const;

    void setDeviceInfos(const QList<DeviceInfoSP> &arg);
    void addDeviceInfo(const DeviceInfoSP &arg);

    static KnownDevicesResponseSP create();

signals:
    void deviceInfosChanged(const QList<Proof::Jdf::DeviceInfoSP> &arg);

protected:
    KnownDevicesResponse();
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_KNOWNDEVICESRESPONSE_H
