#ifndef JDFCUTTINGPROCESSQMLWRAPPER_H
#define JDFCUTTINGPROCESSQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QSize>
#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class CuttingParamsQmlWrapper;
class MediaQmlWrapper;

class CuttingProcessQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT CuttingProcessQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(double pressSheetWidth READ pressSheetWidth NOTIFY pressSheetWidthChanged)
    Q_PROPERTY(double pressSheetHeight READ pressSheetHeight NOTIFY pressSheetHeightChanged)
    Q_PROPERTY(quint32 amount READ amount NOTIFY amountChanged)
    Q_PROPERTY(Proof::Jdf::CuttingParamsQmlWrapper *cuttingParams READ cuttingParams NOTIFY cuttingParamsChanged)
    Q_PROPERTY(Proof::Jdf::MediaQmlWrapper *media READ media NOTIFY mediaChanged)

    Q_DECLARE_PRIVATE(CuttingProcessQmlWrapper)
public:
    explicit CuttingProcessQmlWrapper(const CuttingProcessSP &cuttingProcess, QObject *parent = 0);
    ~CuttingProcessQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(CuttingProcess)

    QString id() const;
    double pressSheetWidth() const;
    double pressSheetHeight() const;
    quint32 amount() const;
    CuttingParamsQmlWrapper *cuttingParams() const;
    MediaQmlWrapper *media() const;

signals:  
    void idChanged(const QString &arg);
    void pressSheetWidthChanged(double arg);
    void pressSheetHeightChanged(double arg);
    void amountChanged(quint32 arg);
    void cuttingParamsChanged(Proof::Jdf::CuttingParamsQmlWrapper *arg);
    void mediaChanged(Proof::Jdf::MediaQmlWrapper *arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // JDFCUTTINGPROCESSQMLWRAPPER_H
