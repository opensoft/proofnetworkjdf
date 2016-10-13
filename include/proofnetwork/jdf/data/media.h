#ifndef JDFMEDIA_H
#define JDFMEDIA_H

#include "proofnetwork/jdf/data/abstractphysicalresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class MediaPrivate;
class PROOF_NETWORK_JDF_EXPORT Media : public AbstractPhysicalResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Media)
public:
    double thickness() const;
    ApiHelper::CoatingType frontCoating() const;
    ApiHelper::CoatingType backCoating() const;
    ApiHelper::MediaUnit mediaUnit() const;
    ApiHelper::MediaType mediaType() const;
    double height() const;
    double width() const;

    void setThickness(double microns);
    void setFrontCoating(ApiHelper::CoatingType coating);
    void setBackCoating(ApiHelper::CoatingType coating);
    void setMediaUnit(ApiHelper::MediaUnit mediaUnit);
    void setMediaType(ApiHelper::MediaType mediaType);
    void setHeight(double arg);
    void setWidth(double arg);

    MediaQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static MediaSP create();

    static MediaSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    MediaLinkSP toLink(ApiHelper::Usage usage = ApiHelper::Usage::InputUsage) const;

signals:
    void thicknessChanged(double arg);
    void heightChanged(double arg);
    void widthChanged(double arg);
    void frontCoatingChanged(Proof::Jdf::ApiHelper::CoatingType arg);
    void backCoatingChanged(Proof::Jdf::ApiHelper::CoatingType arg);
    void mediaUnitChanged(Proof::Jdf::ApiHelper::MediaUnit arg);
    void mediaTypeChanged(Proof::Jdf::ApiHelper::MediaType arg);

protected:
    explicit Media();

};

}
}

#endif // JDFMEDIA_H
