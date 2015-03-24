#include "jdfdocumentqmlwrapper.h"

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"
#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/qmlwrappers/resourcepoolqmlwrapper.h"

namespace Proof {
namespace Jdf {

class JdfDocumentQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(JdfDocumentQmlWrapper)

    void updateResourcePool();

    ResourcePoolQmlWrapper *resourcePool = nullptr;
};

JdfDocumentQmlWrapper::JdfDocumentQmlWrapper(const JdfDocumentSP &jdfDoc, QObject *parent)
    : NetworkDataEntityQmlWrapper(jdfDoc, *new JdfDocumentQmlWrapperPrivate, parent)
{
    setupEntity();
}

JdfDocumentQmlWrapper::~JdfDocumentQmlWrapper()
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(JdfDocument)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(JdfDocument, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(JdfDocument, QString, jobId)

ResourcePoolQmlWrapper *JdfDocumentQmlWrapper::resourcePool() const
{
    Q_D(const JdfDocumentQmlWrapper);
    return d->resourcePool;
}

void JdfDocumentQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    Q_D(JdfDocumentQmlWrapper);
    JdfDocumentSP jdfDoc = entity<JdfDocument>();
    Q_ASSERT(jdfDoc);

    connect(jdfDoc.data(), &JdfDocument::idChanged, this, &JdfDocumentQmlWrapper::idChanged);
    connect(jdfDoc.data(), &JdfDocument::jobIdChanged, this, &JdfDocumentQmlWrapper::jobIdChanged);
    connect(jdfDoc.data(), &JdfDocument::resourcePoolChanged, d->lambdaConnectContext, [d]{d->updateResourcePool();});

    d->updateResourcePool();

    JdfDocumentSP oldJdfDoc = qSharedPointerCast<JdfDocument>(old);
    if (oldJdfDoc) {
        if (jdfDoc->id() != oldJdfDoc->id())
            emit idChanged(jdfDoc->id());
        if (oldJdfDoc->jobId() != oldJdfDoc->jobId())
            emit jobIdChanged(oldJdfDoc->jobId());
    }
}

void JdfDocumentQmlWrapperPrivate::updateResourcePool()
{
    Q_Q(JdfDocumentQmlWrapper);
    JdfDocumentSP jdfDoc = entity<JdfDocument>();
    if (resourcePool == nullptr)
        resourcePool = jdfDoc->resourcePool()->toQmlWrapper(q);
    else
        resourcePool->setEntity(jdfDoc->resourcePool());
    emit q->resourcePoolChanged(resourcePool);
}

}
}
