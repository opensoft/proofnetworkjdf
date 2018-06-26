#ifndef MEDIALINK_H
#define MEDIALINK_H

#include "proofnetwork/jdf/data/abstractphysicalresourcelink.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/qmlwrappers/medialinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class MediaLinkPrivate;
class PROOF_NETWORK_JDF_EXPORT MediaLink : public AbstractPhysicalResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(MediaLink)
public:
    MediaLinkQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static MediaLinkSP create();

    static MediaLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;

protected:
    MediaLink();
};

} // namespace Jdf
} // namespace Proof

#endif // MEDIALINK_H
