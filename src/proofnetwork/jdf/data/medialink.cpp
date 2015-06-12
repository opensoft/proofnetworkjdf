#include "medialink.h"
#include "proofnetwork/jdf/data/abstractresourcelink_p.h"

namespace Proof {
namespace Jdf {

class MediaLinkPrivate : public AbstractResourceLinkPrivate
{
    Q_DECLARE_PUBLIC(MediaLink)
};

MediaLinkQmlWrapper *MediaLink::toQmlWrapper(QObject *parent) const
{
    Q_D(const MediaLink);
    MediaLinkSP castedSelf = qSharedPointerCast<MediaLink>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new MediaLinkQmlWrapper(castedSelf, parent);

}

MediaLinkSP MediaLink::create()
{
    MediaLinkSP result(new MediaLink());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

MediaLinkSP MediaLink::fromJdf(const QXmlStreamReader &xmlReader)
{
    MediaLinkSP media = create();
    AbstractResourceLink::fromJdf(xmlReader, media);
    return media;
}

void MediaLink::toJdf(QXmlStreamWriter &jdfWriter)
{
    jdfWriter.writeStartElement("MediaLink");
    AbstractResourceLink::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

MediaLink::MediaLink(QObject *parent) :
    AbstractResourceLink(*new MediaLinkPrivate, parent)
{
}

}
}
