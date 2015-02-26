#ifndef JDFMEDIA_H
#define JDFMEDIA_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class MediaPrivate;
class PROOF_NETWORK_JDF_EXPORT Media : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Media)
public:
    QString id() const;
    double thickness() const;
    ApiHelper::Coating frontCoating() const;
    ApiHelper::Coating backCoating() const;
    double height() const;
    double width() const;

    void setId(const QString &arg);
    void setThickness(double microns);
    void setFrontCoating(ApiHelper::Coating coating);
    void setBackCoating(ApiHelper::Coating coating);
    void setHeight(double arg);
    void setWidth(double arg);

    void updateFrom(const NetworkDataEntitySP &other) override;
    MediaQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static MediaSP create();

    static MediaSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);
    static MediaSP defaultObject();

signals:
    void idChanged(const QString &arg);
    void thicknessChanged(double arg);
    void heightChanged(double arg);
    void widthChanged(double arg);
    void frontCoatingChanged(ApiHelper::Coating arg);
    void backCoatingChanged(ApiHelper::Coating arg);

protected:
    explicit Media();

};

}
}

#endif // JDFMEDIA_H
