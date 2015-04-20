#include "laminatingintentqmlwrapper.h"

#include "proofnetwork/jdf/data/laminatingintent.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(LaminatingIntentQmlWrapper)
};

LaminatingIntentQmlWrapper::LaminatingIntentQmlWrapper(const LaminatingIntentSP &laminatingIntent, QObject *parent)
    : AbstractResourceQmlWrapper(laminatingIntent, *new LaminatingIntentQmlWrapperPrivate, parent)
{
    setupEntity();
}

LaminatingIntentQmlWrapper::~LaminatingIntentQmlWrapper()
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(LaminatingIntent)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(LaminatingIntent, Proof::Jdf::ApiHelper::LaminatingSurface, surface)

void LaminatingIntentQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(LaminatingIntentQmlWrapper);
    LaminatingIntentSP laminatingIntent = d->entity<LaminatingIntent>();
    Q_ASSERT(laminatingIntent);

    connect(laminatingIntent.data(), &LaminatingIntent::surfaceChanged, this, &LaminatingIntentQmlWrapper::surfaceChanged);

    LaminatingIntentSP oldLaminatingIntent = qSharedPointerCast<LaminatingIntent>(old);
    if (oldLaminatingIntent) {
        if (laminatingIntent->surface() != oldLaminatingIntent->surface())
            emit surfaceChanged(laminatingIntent->surface());
    }
}

}
}
