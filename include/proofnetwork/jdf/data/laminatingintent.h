#ifndef JDFLAMINATINGINTENT_H
#define JDFLAMINATINGINTENT_H

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
//TODO : impl
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

    ApiHelper::LaminatingSurface surface() const;

    void setSurface(ApiHelper::LaminatingSurface surface);

    void updateFrom(const NetworkDataEntitySP &other) override;
    LaminatingIntentQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static LaminatingIntentSP create();

    static LaminatingIntentSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);
    static LaminatingIntentSP defaultObject();

signals:
    void surfaceChanged(ApiHelper::LaminatingSurface arg);

protected:
    explicit LaminatingIntent();

};

}
}

#endif // JDFLAMINATINGINTENT_H
