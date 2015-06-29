#include "laminatingintent.h"

#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentqmlwrapper.h"
#include "proofnetwork/jdf/data/laminatingintentlink.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentPrivate : AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(LaminatingIntent)

    LaminatingIntentPrivate() : AbstractResourcePrivate(ApiHelper::ResourceClass::IntentClass) {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    ApiHelper::LaminatingSurface surface = ApiHelper::LaminatingSurface::None;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ApiHelper::LaminatingSurface LaminatingIntent::surface() const
{
    Q_D(const LaminatingIntent);
    return d->surface;
}

void LaminatingIntent::setSurface(ApiHelper::LaminatingSurface surface)
{
    Q_D(LaminatingIntent);
    if (d->surface != surface) {
        d->surface = surface;
        emit surfaceChanged(surface);
    }
}

LaminatingIntentQmlWrapper *LaminatingIntent::toQmlWrapper(QObject *parent) const
{
    Q_D(const LaminatingIntent);
    LaminatingIntentSP castedSelf = qSharedPointerCast<LaminatingIntent>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new LaminatingIntentQmlWrapper(castedSelf, parent);
}

LaminatingIntentSP LaminatingIntent::create()
{
    LaminatingIntentSP result(new LaminatingIntent());
    initSelfWeakPtr(result);
    return result;
}

LaminatingIntentSP LaminatingIntent::fromJdf(QXmlStreamReader &xmlReader)
{
    LaminatingIntentSP laminatingIntent = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "LaminatingIntent" && xmlReader.isStartElement() && !laminatingIntent->isFetched()) {
            laminatingIntent->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            laminatingIntent->setSurface(ApiHelper::laminatingSurfaceFromString(attributes.value("Surface").toString()));
            AbstractResourceSP castedLaminatingIntent = qSharedPointerCast<AbstractResource>(laminatingIntent);
            AbstractResource::fromJdf(xmlReader, castedLaminatingIntent);

        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return laminatingIntent;
}

void LaminatingIntent::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(LaminatingIntent);

    jdfWriter.writeStartElement("LaminatingIntent");
    jdfWriter.writeAttribute("Surface", ApiHelper::laminatingSurfaceToString(d->surface));
    AbstractResource::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

LaminatingIntentLinkSP LaminatingIntent::toLink(ApiHelper::Usage usage) const
{
    LaminatingIntentLinkSP link = LaminatingIntentLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

LaminatingIntent::LaminatingIntent()
    : AbstractResource(*new LaminatingIntentPrivate)
{
}

void LaminatingIntentPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(LaminatingIntent);
    LaminatingIntentSP castedOther = qSharedPointerCast<LaminatingIntent>(other);
    q->setSurface(castedOther->surface());

    AbstractResourcePrivate::updateFrom(other);
}
