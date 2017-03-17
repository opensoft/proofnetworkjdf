#ifndef PROOF_JDF_DEVICEFILTER_H
#define PROOF_JDF_DEVICEFILTER_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class DeviceFilterPrivate;
class PROOF_NETWORK_JDF_EXPORT DeviceFilter : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DeviceFilter)
public:
    ApiHelper::DeviceFilterDetails details() const;

    void setDetails(ApiHelper::DeviceFilterDetails arg);

    NetworkDataEntityQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DeviceFilterSP create();

    void toJmf(QXmlStreamWriter &xmlWriter);
    static DeviceFilterSP fromJmf(QXmlStreamReader &xmlReader);

signals:
    void detailsChanged(Proof::Jdf::ApiHelper::DeviceFilterDetails arg);

protected:
    DeviceFilter();
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_DEVICEFILTER_H
