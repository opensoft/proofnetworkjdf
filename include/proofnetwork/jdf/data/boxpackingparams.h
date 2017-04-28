#ifndef PROOF_JDF_BOXPACKINGPARAMS_H
#define PROOF_JDF_BOXPACKINGPARAMS_H

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/boxpackingparamsqmlwrapper.h"
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class BoxPackingParamsPrivate;
class PROOF_NETWORK_JDF_EXPORT BoxPackingParams : public AbstractResource // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BoxPackingParams)
public:
    BoxPackingParamsQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static BoxPackingParamsSP create();

    static BoxPackingParamsSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    BoxPackingParamsLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

protected:
    explicit BoxPackingParams();

};

}
}

#endif // PROOF_JDF_BOXPACKINGPARAMS_H
