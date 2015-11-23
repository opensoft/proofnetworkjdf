#ifndef FOLDINGPARAMSQMLWRAPPER_H
#define FOLDINGPARAMSQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

namespace Proof {
namespace Jdf {

class FoldingParams;

class FoldingParamsQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT FoldingParamsQmlWrapper : public AbstractResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString foldCatalog READ foldCatalog NOTIFY foldCatalogChanged)
    Q_DECLARE_PRIVATE(FoldingParamsQmlWrapper)
public:
    explicit FoldingParamsQmlWrapper(const FoldingParamsSP &foldingParams, QObject *parent = 0);
    ~FoldingParamsQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(FoldingParams)

    QString foldCatalog() const;

signals:
    void foldCatalogChanged(const QString &foldCatalog);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}
#endif // FOLDINGPARAMSQMLWRAPPER_H
