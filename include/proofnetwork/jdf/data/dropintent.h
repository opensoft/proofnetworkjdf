#ifndef JDFDROPINTENT_H
#define JDFDROPINTENT_H

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

#include "proofnetwork/jdf/data/span.h"
#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"

#include <QXmlStreamReader>
#include <QDateTime>

namespace Proof {
namespace Jdf {

class DropIntentPrivate;
class PROOF_NETWORK_JDF_EXPORT DropIntent : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DropIntent)
public:

    TimeSpan required() const;
    QList<DropItemIntentSP> dropItemIntents() const;

    void setRequired(const TimeSpan &arg);
    void setDropItemIntents(const QList<DropItemIntentSP> &arg);
    void addDropItemIntent(const DropItemIntentSP &arg);

    DropIntentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DropIntentSP create();

    static DropIntentSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void requiredChanged(const TimeSpan &required);
    void dropItemIntentsChanged();

protected:
    explicit DropIntent();

};

}
}

#endif // JDFDROPINTENT_H
