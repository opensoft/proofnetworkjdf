#ifndef JDFMEDIAQMLWRAPPER_H
#define JDFMEDIAQMLWRAPPER_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class Media;

class MediaQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT MediaQmlWrapper : public AbstractPhysicalResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(double thickness READ thickness NOTIFY thicknessChanged)
    Q_PROPERTY(double height READ height NOTIFY heightChanged)
    Q_PROPERTY(double width READ width NOTIFY widthChanged)
    Q_PROPERTY(Proof::Jdf::CoatingType frontCoating READ frontCoating NOTIFY frontCoatingChanged)
    Q_PROPERTY(Proof::Jdf::CoatingDetail frontCoatingDetail READ frontCoatingDetail NOTIFY frontCoatingDetailChanged)
    Q_PROPERTY(Proof::Jdf::CoatingType backCoating READ backCoating NOTIFY backCoatingChanged)
    Q_PROPERTY(Proof::Jdf::CoatingDetail backCoatingDetail READ backCoatingDetail NOTIFY backCoatingDetailChanged)
    Q_PROPERTY(Proof::Jdf::MediaUnit mediaUnit READ mediaUnit NOTIFY mediaUnitChanged)
    Q_PROPERTY(Proof::Jdf::MediaType mediaType READ mediaType NOTIFY mediaTypeChanged)
    Q_DECLARE_PRIVATE(MediaQmlWrapper)
public:
    explicit MediaQmlWrapper(const MediaSP &media, QObject *parent = nullptr);
    ~MediaQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(Media)

    double thickness() const;
    double height() const;
    double width() const;
    CoatingType frontCoating() const;
    CoatingDetail frontCoatingDetail() const;
    CoatingType backCoating() const;
    CoatingDetail backCoatingDetail() const;
    MediaUnit mediaUnit() const;
    MediaType mediaType() const;

signals:
    void thicknessChanged(double thickness);
    void heightChanged(double height);
    void widthChanged(double width);
    void frontCoatingChanged(Proof::Jdf::CoatingType frontCoating);
    void frontCoatingDetailChanged(Proof::Jdf::CoatingDetail frontCoating);
    void backCoatingChanged(Proof::Jdf::CoatingType backCoating);
    void backCoatingDetailChanged(Proof::Jdf::CoatingDetail backCoating);
    void mediaUnitChanged(Proof::Jdf::MediaUnit mediaUnit);
    void mediaTypeChanged(Proof::Jdf::MediaType mediaType);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFMEDIAQMLWRAPPER_H
