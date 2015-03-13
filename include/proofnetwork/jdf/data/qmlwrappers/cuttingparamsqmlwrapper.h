#ifndef PROOF_JDF_CUTTINGPARAMSQMLWRAPPER_H
#define PROOF_JDF_CUTTINGPARAMSQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QSize>
#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {

class CutBlockQmlWrapper;

class CuttingParamsQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT CuttingParamsQmlWrapper : public AbstractResourceQmlWrapper
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper> cutBlocks READ cutBlocks NOTIFY cutBlocksChanged)

    Q_DECLARE_PRIVATE(CuttingParamsQmlWrapper)
public:
    explicit CuttingParamsQmlWrapper(const CuttingParamsSP &cuttingParams, QObject *parent = 0);
    ~CuttingParamsQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(CuttingParams)

    QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper> cutBlocks();

signals:
    void cutBlocksChanged(const QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper> &arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}


#endif // PROOF_JDF_CUTTINGPARAMSQMLWRAPPER_H
