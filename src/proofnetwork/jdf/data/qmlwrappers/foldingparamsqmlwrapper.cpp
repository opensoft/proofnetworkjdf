#include "foldingparamsqmlwrapper.h"

#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class FoldingParamsQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(FoldingParamsQmlWrapper)
};

FoldingParamsQmlWrapper::FoldingParamsQmlWrapper(const FoldingParamsSP &foldingParams, QObject *parent)
    : AbstractResourceQmlWrapper(foldingParams, *new FoldingParamsQmlWrapperPrivate, parent)
{
    setupEntity();
}

FoldingParamsQmlWrapper::~FoldingParamsQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(FoldingParams)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(FoldingParams, QString, foldCatalog)

void FoldingParamsQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    FoldingParamsSP foldingParams = entity<FoldingParams>();
    Q_ASSERT(foldingParams);

    connect(foldingParams.data(), &FoldingParams::foldCatalogChanged, this, &FoldingParamsQmlWrapper::foldCatalogChanged);

    FoldingParamsSP oldFoldingParams = qSharedPointerCast<FoldingParams>(old);
    if (oldFoldingParams) {
        if (foldingParams->foldCatalog() != oldFoldingParams->foldCatalog())
            emit foldCatalogChanged(foldingParams->foldCatalog());
    }
}

} // namespace Jdf
} // namespace Proof
