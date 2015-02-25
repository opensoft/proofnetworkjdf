#ifndef JDFMEDIA_H
#define JDFMEDIA_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class MediaPrivate;
class PROOF_NETWORK_JDF_EXPORT Media : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Media)
    Q_ENUMS(Coating)
public:
    enum class Coating
    {
        None, // No coating.
        Coated, // A coating of a system-specified type. New in JDF 1.2
        Glossy,
        HighGloss,
        InkJet, // A coating intended for use with inkjet technology.
                // Deprecation note: use PrintingTechnology = "InkJet" New in JDF 1.2 Deprecated in JDF 1.4
        Matte,
        Polymer, // Coating for a photo polymer process New in JDF 1.3
        Silver, // Coating for a silver halide process New in JDF 1.3
        Satin,
        Semigloss
    };

    QString id() const;
    double thickness() const;
    Coating frontCoating() const;
    Coating backCoating() const;
    double height() const;
    double width() const;

    void setId(const QString &arg);
    void setThickness(double microns);
    void setFrontCoating(Coating coating);
    void setBackCoating(Coating coating);
    void setHeight(double arg);
    void setWidth(double arg);

    void updateFrom(const NetworkDataEntitySP &other) override;
    NetworkDataEntityQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static MediaSP create();

    static MediaSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);
    static MediaSP defaultObject();

signals:
    void idChanged(const QString &arg);
    void thicknessChanged(double arg);
    void heightChanged(double arg);
    void widthChanged(double arg);
    void frontCoatingChanged(Media::Coating arg);
    void backCoatingChanged(Media::Coating arg);

protected:
    explicit Media();

};

}
}

#endif // JDFMEDIA_H
