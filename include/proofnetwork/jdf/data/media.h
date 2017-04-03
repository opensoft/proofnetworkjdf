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
    CoatingType frontCoating() const;
    CoatingType backCoating() const;
    MediaUnit mediaUnit() const;
    MediaType mediaType() const;
    double height() const;
    double width() const;

    void setThickness(double microns);
    void setFrontCoating(CoatingType coating);
    void setBackCoating(CoatingType coating);
    void setMediaUnit(MediaUnit mediaUnit);
    void setMediaType(MediaType mediaType);
    void setHeight(double arg);
    void setWidth(double arg);

    MediaQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static MediaSP create();

    static MediaSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    MediaLinkSP toLink(Usage usage = Usage::InputUsage) const;

signals:
    void thicknessChanged(double arg);
    void heightChanged(double arg);
    void widthChanged(double arg);
    void frontCoatingChanged(Proof::Jdf::CoatingType arg);
    void backCoatingChanged(Proof::Jdf::CoatingType arg);
    void mediaUnitChanged(Proof::Jdf::MediaUnit arg);
    void mediaTypeChanged(Proof::Jdf::MediaType arg);

protected:
    explicit Media();

};

}
}

#endif // JDFMEDIA_H
