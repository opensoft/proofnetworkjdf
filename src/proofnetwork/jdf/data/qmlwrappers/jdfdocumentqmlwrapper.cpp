#include "jdfdocumentqmlwrapper.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"
#include "proofnetwork/jdf/data/jdfnode.h"
#include "proofnetwork/jdf/data/jdfdocument.h"

namespace Proof {
namespace Jdf {

class JdfDocumentQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(JdfDocumentQmlWrapper)
};

}
}

using namespace Proof::Jdf;

JdfDocumentQmlWrapper::JdfDocumentQmlWrapper(const JdfDocumentSP &jdfDoc, QObject *parent)
    : JdfNodeQmlWrapper(jdfDoc.dynamicCast<JdfNode>(), parent)
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(JdfDocument)
