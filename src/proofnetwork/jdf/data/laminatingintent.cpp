#include "laminatingintent.h"

#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentqmlwrapper.h"
#include "proofnetwork/jdf/data/abstractresource_p.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentPrivate : AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(LaminatingIntent)

    ApiHelper::LaminatingSurface surface = ApiHelper::LaminatingSurface::Front;
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

void LaminatingIntent::updateFrom(const NetworkDataEntitySP &other)
{
    LaminatingIntentSP castedOther = qSharedPointerCast<LaminatingIntent>(other);
    setId(castedOther->id());
    setSurface(castedOther->surface());
    NetworkDataEntity::updateFrom(other);
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
    result->d_func()->weakSelf = result.toWeakRef();
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
    if (d->surface == Proof::Jdf::ApiHelper::LaminatingSurface::None)
        return;

    jdfWriter.writeStartElement("LaminatingIntent");
    jdfWriter.writeAttribute("Surface", ApiHelper::laminatingSurfaceToString(d->surface));
    AbstractResource::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

LaminatingIntentSP LaminatingIntent::defaultObject()
{
    static LaminatingIntentSP entity = create();
    return entity;
}

LaminatingIntent::LaminatingIntent()
    : AbstractResource(*new LaminatingIntentPrivate)
{
    setResourceClass(ApiHelper::IntentClass);
}

