#include "layoutqmlwrapper.h"

#include "mediaqmlwrapper.h"

#include "proofnetwork/jdf/data/layout.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class LayoutQmlWrapperPrivate : public AbstractResourceQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(LayoutQmlWrapper)
    void updateMedia();

    QList<MediaQmlWrapper *> media;
    QQmlListProperty<Proof::Jdf::MediaQmlWrapper> qmlMediaList;
    static MediaQmlWrapper *mediaAt(QQmlListProperty<MediaQmlWrapper> *property, int index);
    static int mediaCount(QQmlListProperty<MediaQmlWrapper> *property);
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

LayoutQmlWrapper::LayoutQmlWrapper(const LayoutSP &layout, QObject *parent)
    : AbstractResourceQmlWrapper(layout, *new LayoutQmlWrapperPrivate, parent)
{
    setupEntity();
}

LayoutQmlWrapper::~LayoutQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Layout)

QQmlListProperty<Proof::Jdf::MediaQmlWrapper> LayoutQmlWrapper::media() const
{
    Q_D(const LayoutQmlWrapper);
    return d->qmlMediaList;
}

void LayoutQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    Q_D(LayoutQmlWrapper);
    Q_UNUSED(old)
    LayoutSP layout = d->entity<Layout>();
    Q_ASSERT(layout);

    connect(layout.data(), &Layout::mediaChanged, d->lambdaConnectContext, [d]() { d->updateMedia(); });

    d->updateMedia();

    AbstractResourceQmlWrapper::setupEntity(old);
}

void LayoutQmlWrapperPrivate::updateMedia()
{
    Q_Q(LayoutQmlWrapper);
    LayoutSP layout = entity<Layout>();
    for (MediaQmlWrapper *wrapper : qAsConst(media))
        wrapper->deleteLater();

    media.clear();
    const auto ndeMedia = layout->media();
    for (const MediaSP &md : ndeMedia)
        media << md->toQmlWrapper(q);

    qmlMediaList = QQmlListProperty<Proof::Jdf::MediaQmlWrapper>(q, &media, &LayoutQmlWrapperPrivate::mediaCount,
                                                                 &LayoutQmlWrapperPrivate::mediaAt);
    emit q->mediaChanged(qmlMediaList);
}

MediaQmlWrapper *LayoutQmlWrapperPrivate::mediaAt(QQmlListProperty<MediaQmlWrapper> *property, int index)
{
    return static_cast<QList<MediaQmlWrapper *> *>(property->data)->at(index);
}

int LayoutQmlWrapperPrivate::mediaCount(QQmlListProperty<MediaQmlWrapper> *property)
{
    return static_cast<QList<MediaQmlWrapper *> *>(property->data)->count();
}
