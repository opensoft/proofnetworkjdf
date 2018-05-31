#include "medialinkqmlwrapper.h"

#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourcelinkqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class MediaLinkQmlWrapperPrivate : public AbstractPhysicalResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(MediaLinkQmlWrapper)
};

MediaLinkQmlWrapper::MediaLinkQmlWrapper(const MediaLinkSP &media, QObject *parent)
    : AbstractPhysicalResourceLinkQmlWrapper(media, *new MediaLinkQmlWrapperPrivate, parent)
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(MediaLink)

} // namespace Jdf
} // namespace Proof
