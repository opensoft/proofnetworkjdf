#include "proofnetwork/jdf/data/qmlwrappers/jdfdocumentqmlwrapper.h"

#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/jdfnode.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class JdfDocumentQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(JdfDocumentQmlWrapper)
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

JdfDocumentQmlWrapper::JdfDocumentQmlWrapper(const JdfDocumentSP &jdfDoc, QObject *parent)
    : JdfNodeQmlWrapper(qSharedPointerCast<JdfNode>(jdfDoc), parent)
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(JdfDocument)
