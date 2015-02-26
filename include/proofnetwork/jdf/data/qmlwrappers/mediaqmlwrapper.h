#ifndef JDFMEDIAQMLWRAPPER_H
#define JDFMEDIAQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class Media;

class MediaQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT MediaQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(double thickness READ thickness NOTIFY thicknessChanged)
    Q_PROPERTY(double height READ height NOTIFY heightChanged)
    Q_PROPERTY(double width READ width NOTIFY widthChanged)
    Q_PROPERTY(Proof::Jdf::ApiHelper::Coating frontCoating READ frontCoating NOTIFY frontCoatingChanged)
    Q_PROPERTY(Proof::Jdf::ApiHelper::Coating backCoating READ backCoating NOTIFY backCoatingChanged)
    Q_DECLARE_PRIVATE(MediaQmlWrapper)
public:
    explicit MediaQmlWrapper(const MediaSP &media, QObject *parent = 0);
    ~MediaQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(Media)

    QString id() const;
    double thickness() const;
    double height() const;
    double width() const;
    ApiHelper::Coating frontCoating() const;
    ApiHelper::Coating backCoating() const;

signals:
    void idChanged(const QString &arg);
    void thicknessChanged(double arg);
    void heightChanged(double arg);
    void widthChanged(double arg);
    void frontCoatingChanged(Proof::Jdf::ApiHelper::Coating arg);
    void backCoatingChanged(Proof::Jdf::ApiHelper::Coating arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;

};

}
}

#endif // JDFMEDIAQMLWRAPPER_H
