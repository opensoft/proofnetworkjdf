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
    QList<CutBlockSP> cutBlocks() const;

    void setId(const QString &arg);
    void setPressSheetWidth(double arg);
    void setPressSheetHeight(double arg);
    QList<CutBlockSP> updateCutBlocks(const QList<CutBlockSP> &arg);

    void updateFrom(const NetworkDataEntitySP &other) override;
    CuttingProcessQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static CuttingProcessSP create();

    static CuttingProcessSP fromJdf(QXmlStreamReader &xmlReader);
    QString toJdf();
    static CuttingProcessSP defaultObject();

signals:
    void idChanged(const QString &arg);
    void pressSheetWidthChanged(double arg);
    void pressSheetHeightChanged(double arg);
    void cutBlocksChanged();

protected:
    explicit CuttingProcess();

};

}
}

#endif // JDFCUTTINGPROCESS_H
