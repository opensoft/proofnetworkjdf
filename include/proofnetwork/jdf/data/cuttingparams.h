#ifndef PROOF_JDF_CUTTINGPARAMS_H
#define PROOF_JDF_CUTTINGPARAMS_H

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingparamsqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofcore/objectscache.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class CuttingParamsPrivate;
class PROOF_NETWORK_JDF_EXPORT CuttingParams : public AbstractResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CuttingParams)
public:
    QList<CutBlockSP> cutBlocks() const;
    //TODO: add to qml wrapper
    //TODO: add to tests
    QList<CuttingParamsSP> parts() const;

    QList<CutBlockSP> updateCutBlocks(const QList<CutBlockSP> &arg);
    QList<CuttingParamsSP> updateParts(const QList<CuttingParamsSP> &arg);
    void addPart(const CuttingParamsSP &arg);

    CuttingParamsQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static CuttingParamsSP create();

    static CuttingParamsSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    CuttingParamsLinkSP toLink(ApiHelper::Usage usage = ApiHelper::Usage::InputUsage) const;

signals:
    void cutBlocksChanged();
    void partsChanged();

protected:
    explicit CuttingParams();

};

}
}

#endif // PROOF_JDF_CUTTINGPARAMS_H
