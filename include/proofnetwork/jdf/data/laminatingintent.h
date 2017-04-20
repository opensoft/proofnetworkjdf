#ifndef JDFLAMINATINGINTENT_H
#define JDFLAMINATINGINTENT_H

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentqmlwrapper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class LaminatingIntentPrivate;
class PROOF_NETWORK_JDF_EXPORT LaminatingIntent : public AbstractResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LaminatingIntent)
public:

    LaminatingSurface surface() const;

    void setSurface(LaminatingSurface surface);

    LaminatingIntentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static LaminatingIntentSP create();

    static LaminatingIntentSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    LaminatingIntentLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

signals:
    void surfaceChanged(Proof::Jdf::LaminatingSurface arg);

protected:
    explicit LaminatingIntent();

};

}
}

#endif // JDFLAMINATINGINTENT_H
