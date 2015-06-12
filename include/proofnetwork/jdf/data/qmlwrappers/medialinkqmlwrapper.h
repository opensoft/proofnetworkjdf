#ifndef MEDIALINKQMLWRAPPER_H
#define MEDIALINKQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

namespace Proof {
namespace Jdf {

class MediaLinkQmlWrapperPrivate;
class MediaLinkQmlWrapper : public AbstractResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(MediaLinkQmlWrapper)
public:
    explicit MediaLinkQmlWrapper(const MediaLinkSP &media, QObject *parent = 0);
    PROOF_NDE_WRAPPER_TOOLS(MediaLink)
};

}
}
#endif // MEDIALINKQMLWRAPPER_H
