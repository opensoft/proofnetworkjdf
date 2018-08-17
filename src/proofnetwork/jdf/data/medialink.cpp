#include "proofnetwork/jdf/data/medialink.h"

#include "proofnetwork/jdf/data/abstractphysicalresourcelink_p.h"

namespace Proof {
namespace Jdf {

class MediaLinkPrivate : public AbstractPhysicalResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(MediaLink)
};

MediaLinkQmlWrapper *MediaLink::toQmlWrapper(QObject *parent) const
{
    MediaLinkSP castedSelf = castedSelfPtr<MediaLink>();
    Q_ASSERT(castedSelf);
    return new MediaLinkQmlWrapper(castedSelf, parent);
}

MediaLinkSP MediaLink::create()
{
    MediaLinkSP result(new MediaLink());
    initSelfWeakPtr(result);
    return result;
}

MediaLinkSP MediaLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    MediaLinkSP media = create();
    AbstractPhysicalResourceLink::fromJdf(xmlReader, media);
    return media;
}

void MediaLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement(jdfNodeName());
    AbstractPhysicalResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

MediaLink::MediaLink() : AbstractPhysicalResourceLink(*new MediaLinkPrivate)
{}

} // namespace Jdf
} // namespace Proof
