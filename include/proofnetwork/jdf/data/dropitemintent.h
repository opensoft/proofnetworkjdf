#ifndef JDFDROPITEMINTENT_H
#define JDFDROPITEMINTENT_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/dropitemintentqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QDateTime>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class DropItemIntentPrivate;
class PROOF_NETWORK_JDF_EXPORT DropItemIntent : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DropItemIntent)
public:
    ComponentSP component() const;

    void setComponent(const ComponentSP &arg);

    DropItemIntentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DropItemIntentSP create();

    static DropItemIntentSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void componentChanged(const Proof::Jdf::ComponentSP &component);

protected:
    explicit DropItemIntent();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFDROPITEMINTENT_H
