#ifndef PROOF_JDF_LAYOUTQMLWRAPPER_H
#define PROOF_JDF_LAYOUTQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourceqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QtQml/QQmlListProperty>

namespace Proof {
namespace Jdf {
class MediaQmlWrapper;

class LayoutQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT LayoutQmlWrapper : public AbstractResourceQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Proof::Jdf::MediaQmlWrapper> media READ media NOTIFY mediaChanged)

    Q_DECLARE_PRIVATE(LayoutQmlWrapper)
public:
    explicit LayoutQmlWrapper(const LayoutSP &layout, QObject *parent = 0);
    ~LayoutQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(Layout)

    QQmlListProperty<Proof::Jdf::MediaQmlWrapper> media() const;

signals:
    void mediaChanged(const QQmlListProperty<Proof::Jdf::MediaQmlWrapper> &media);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_LAYOUTQMLWRAPPER_H
