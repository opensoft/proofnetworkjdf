#include "layout.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/media.h"

namespace Proof {
namespace Jdf {

class LayoutPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(Layout)

    LayoutPrivate() : AbstractResourcePrivate(ResourceClass::ParameterClass) { registerChildren(media); }

    QVector<MediaSP> media;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof;
using namespace Proof::Jdf;

Layout::Layout() : AbstractResource(*new LayoutPrivate)
{}

QVector<MediaSP> Layout::media() const
{
    Q_D_CONST(Layout);
    return d->media;
}

void Layout::setMedia(const QVector<MediaSP> &arg)
{
    Q_D(Layout);
    bool emitNeeded = arg.count() != d->media.count();
    for (int i = 0; i < arg.count() && !emitNeeded; ++i)
        emitNeeded = arg[i]->id() != d->media[i]->id();
    if (emitNeeded) {
        d->media = arg;
        emit mediaChanged();
    }
}

void Layout::addMedia(const MediaSP &arg)
{
    Q_D(Layout);
    if (!arg)
        return;
    d->media << arg;
    emit mediaChanged();
}

LayoutQmlWrapper *Layout::toQmlWrapper(QObject *parent) const
{
    LayoutSP castedSelf = castedSelfPtr<Layout>();
    Q_ASSERT(castedSelf);
    return new LayoutQmlWrapper(castedSelf, parent);
}

LayoutSP Layout::create()
{
    LayoutSP result(new Layout());
    initSelfWeakPtr(result);
    return result;
}

LayoutSP Layout::fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize)
{
    LayoutSP layout = create();

    QVector<MediaSP> mediaList;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Layout" && xmlReader.isStartElement() && !layout->isFetched()) {
            layout->setFetched(true);
            AbstractResourceSP castedComponent = qSharedPointerCast<AbstractResource>(layout);
            AbstractResource::fromJdf(xmlReader, castedComponent);
        } else if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Media") {
                MediaSP media = Media::fromJdf(xmlReader, jobId, sanitize);
                if (!media) {
                    qCWarning(proofNetworkJdfDataLog) << "Layout not created. Media is invalid.";
                    return LayoutSP();
                }
                mediaList << media;
            } else {
                xmlReader.skipCurrentElement();
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    layout->setMedia(mediaList);

    return layout;
}

void Layout::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Layout);
    jdfWriter.writeStartElement(QStringLiteral("Layout"));
    AbstractResource::toJdf(jdfWriter);

    for (const MediaSP &media : qAsConst(d->media)) {
        if (isValidAndDirty(media))
            media->toJdf(jdfWriter);
    }

    jdfWriter.writeEndElement();
}

void Layout::updateSelf(const NetworkDataEntitySP &other)
{
    LayoutSP castedOther = qSharedPointerCast<Layout>(other);
    setMedia(castedOther->media());

    AbstractResource::updateSelf(other);
}
