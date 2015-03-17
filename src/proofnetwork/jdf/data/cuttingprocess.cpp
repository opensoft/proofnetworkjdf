#include "cuttingprocess.h"

#include "component.h"
#include "cuttingparams.h"
#include "media.h"
#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class CuttingProcessPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(CuttingProcess)

    QString id;
    double pressSheetWidth;
    double pressSheetHeight;
    quint32 amount;
    ComponentSP component = Component::defaultObject();
    CuttingParamsSP cuttingParams = CuttingParams::defaultObject();
    MediaSP media = Media::defaultObject();

};

ObjectsCache<QString, CuttingProcess> &cuttingProcessCache()
{
    return WeakObjectsCache<QString, CuttingProcess>::instance();
}

}
}

using namespace Proof::Jdf;

CuttingProcess::CuttingProcess()
    : NetworkDataEntity(*new CuttingProcessPrivate)
{
}

ComponentSP CuttingProcess::component() const
{
    Q_D(const CuttingProcess);
    return d->component;
}

CuttingParamsSP CuttingProcess::cuttingParams() const
{
    Q_D(const CuttingProcess);
    return d->cuttingParams;
}

MediaSP CuttingProcess::media() const
{
    Q_D(const CuttingProcess);
    return d->media;
}

void CuttingProcess::updateFrom(const NetworkDataEntitySP &other)
{
    CuttingProcessSP castedOther = qSharedPointerCast<CuttingProcess>(other);
    setComponent(castedOther->component());
    setCuttingParams(castedOther->cuttingParams());
    setMedia(castedOther->media());

    NetworkDataEntity::updateFrom(other);
}

CuttingProcessQmlWrapper *CuttingProcess::toQmlWrapper(QObject *parent) const
{
    Q_D(const CuttingProcess);
    CuttingProcessSP castedSelf = qSharedPointerCast<CuttingProcess>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new CuttingProcessQmlWrapper(castedSelf, parent);
}

CuttingProcessSP CuttingProcess::create()
{
    CuttingProcessSP result(new CuttingProcess());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

CuttingProcessSP CuttingProcess::fromJdf(QXmlStreamReader &xmlReader)
{
    CuttingProcessSP cutProcess = create();
    cutProcess->setFetched(true);

    if (xmlReader.name() == "ResourcePool") {
        uint elementsCounter = 1;

        while (!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if (token == QXmlStreamReader::StartElement) {
                ++elementsCounter;
                if (xmlReader.name() == "Media")
                    cutProcess->setMedia(Media::fromJdf(xmlReader));
                if (xmlReader.name() == "Component")
                    cutProcess->setComponent(Component::fromJdf(xmlReader));
                if (xmlReader.name() == "CuttingParams") {
                    cutProcess->setCuttingParams(CuttingParams::fromJdf(xmlReader));
                }
            }
            if (token == QXmlStreamReader::EndElement) {
                --elementsCounter;
                if (elementsCounter == 0)
                    break;
            }
        }
    }

    return cutProcess;
}

void CuttingProcess::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(CuttingProcess);

    jdfWriter.writeStartElement("ResourcePool");

    if (d->component)
        d->component->toJdf(jdfWriter);
    if (d->media)
        d->media->toJdf(jdfWriter);
    if (d->cuttingParams)
        d->cuttingParams->toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

CuttingProcessSP CuttingProcess::defaultObject()
{
    static CuttingProcessSP entity = create();
    return entity;
}

void CuttingProcess::setComponent(const ComponentSP &arg)
{
    Q_D(CuttingProcess);
    if (d->component != arg) {
        d->component = arg;
        emit componentChanged(d->component);
    }
}

void CuttingProcess::setCuttingParams(const CuttingParamsSP &arg)
{
    Q_D(CuttingProcess);
    if (d->cuttingParams != arg) {
        d->cuttingParams = arg;
        emit cuttingParamsChanged(d->cuttingParams);
    }
}

void CuttingProcess::setMedia(const MediaSP &media)
{
    Q_D(CuttingProcess);
    if (media == nullptr)
        setMedia(Media::defaultObject());
    else if (d->media != media) {
        d->media = media;
        emit mediaChanged(d->media);
    }
}
