#ifndef PROOF_JDF_CUTTINGPARAMS_H
#define PROOF_JDF_CUTTINGPARAMS_H

#include "proofcore/objectscache.h"

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingparamsqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class CuttingParamsPrivate;
class PROOF_NETWORK_JDF_EXPORT CuttingParams : public AbstractResource // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CuttingParams)
public:
    QVector<CutBlockSP> cutBlocks() const;
    QVector<CuttingParamsSP> parts() const;

    QVector<CutBlockSP> updateCutBlocks(const QVector<CutBlockSP> &arg);
    QVector<CuttingParamsSP> updateParts(const QVector<CuttingParamsSP> &arg);
    void addPart(const CuttingParamsSP &arg);

    CuttingParamsQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static CuttingParamsSP create();

    static CuttingParamsSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    CuttingParamsLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

signals:
    void cutBlocksChanged();
    void partsChanged();

protected:
    explicit CuttingParams();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_CUTTINGPARAMS_H
