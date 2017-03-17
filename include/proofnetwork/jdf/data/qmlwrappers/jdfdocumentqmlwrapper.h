#ifndef JDFDOCUMENTQMLWRAPPER_H
#define JDFDOCUMENTQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/jdfnodeqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

namespace Proof {
namespace Jdf {

class JdfDocumentQmlWrapperPrivate;
class JdfDocumentQmlWrapper : public JdfNodeQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(JdfDocumentQmlWrapper)
public:
    explicit JdfDocumentQmlWrapper(const JdfDocumentSP &jdfDoc, QObject *parent = nullptr);
    PROOF_NDE_WRAPPER_TOOLS(JdfDocument)
};

}
}
#endif // JDFDOCUMENTQMLWRAPPER_H
