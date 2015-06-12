#include "medialinkqmlwrapper.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class MediaLinkQmlWrapperPrivate : public AbstractResourceLinkQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(MediaLinkQmlWrapper)
};

MediaLinkQmlWrapper::MediaLinkQmlWrapper(const MediaLinkSP &media, QObject *parent) :
    AbstractResourceLinkQmlWrapper(media, *new MediaLinkQmlWrapperPrivate, parent)
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(MediaLink)

}
}
