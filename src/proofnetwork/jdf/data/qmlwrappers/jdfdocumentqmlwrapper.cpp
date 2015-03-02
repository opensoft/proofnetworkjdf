#include "jdfdocumentqmlwrapper.h"

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"
#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/cuttingprocess.h"
#include "proofnetwork/jdf/data/qmlwrappers/cuttingprocessqmlwrapper.h"

namespace Proof {
namespace Jdf {

class JdfDocumentQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(JdfDocumentQmlWrapper)

    void updateCuttingProcess();

    CuttingProcessQmlWrapper *cuttingProcess = nullptr;
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

CuttingProcessQmlWrapper *JdfDocumentQmlWrapper::cuttingProcess() const
{
    Q_D(const JdfDocumentQmlWrapper);
    return d->cuttingProcess;
}

void JdfDocumentQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    Q_D(JdfDocumentQmlWrapper);
    JdfDocumentSP jdfDoc = entity<JdfDocument>();
    Q_ASSERT(jdfDoc);

    connect(jdfDoc.data(), &JdfDocument::idChanged, this, &JdfDocumentQmlWrapper::idChanged);
    connect(jdfDoc.data(), &JdfDocument::jobIdChanged, this, &JdfDocumentQmlWrapper::jobIdChanged);
    connect(jdfDoc.data(), &JdfDocument::cuttingProcessChanged, d->lambdaConnectContext, [d]{d->updateCuttingProcess();});

    d->updateCuttingProcess();

    JdfDocumentSP oldJdfDoc = qSharedPointerCast<JdfDocument>(old);
    if (oldJdfDoc) {
        if (jdfDoc->id() != oldJdfDoc->id())
            emit idChanged(jdfDoc->id());
        if (oldJdfDoc->jobId() != oldJdfDoc->jobId())
            emit jobIdChanged(oldJdfDoc->jobId());
    }
}

void JdfDocumentQmlWrapperPrivate::updateCuttingProcess()
{
    Q_Q(JdfDocumentQmlWrapper);
    JdfDocumentSP jdfDoc = entity<JdfDocument>();
    if (cuttingProcess == nullptr)
        cuttingProcess = jdfDoc->cuttingProcess()->toQmlWrapper(q);
    else
        cuttingProcess->setEntity(jdfDoc->cuttingProcess());
    emit q->cuttingProcessChanged(cuttingProcess);
}

}
}
