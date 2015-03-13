#ifndef JDFCUTTINGPROCESS_H
#define JDFCUTTINGPROCESS_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingprocessqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofcore/objectscache.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class CuttingProcessPrivate;
class PROOF_NETWORK_JDF_EXPORT CuttingProcess : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CuttingProcess)
public:

    QString id() const;
    double pressSheetWidth() const;
    double pressSheetHeight() const;
    quint32 amount() const;
    CuttingParamsSP cuttingParams() const;
    MediaSP media() const;

    void setId(const QString &arg);
    void setPressSheetWidth(double arg);
    void setPressSheetHeight(double arg);
    void setAmount(quint32 arg);
    void setCuttingParams(const CuttingParamsSP &arg);
    void setMedia(const MediaSP &media);

    void updateFrom(const NetworkDataEntitySP &other) override;
    CuttingProcessQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static CuttingProcessSP create();

    static CuttingProcessSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);
    static CuttingProcessSP defaultObject();

signals:
    void idChanged(const QString &arg);
    void pressSheetWidthChanged(double arg);
    void pressSheetHeightChanged(double arg);
    void amountChanged(quint32 arg);
    void cuttingParamsChanged(const Proof::Jdf::CuttingParamsSP &arg);
    void mediaChanged(const Proof::Jdf::MediaSP &arg);

protected:
    explicit CuttingProcess();

};

}
}

#endif // JDFCUTTINGPROCESS_H
