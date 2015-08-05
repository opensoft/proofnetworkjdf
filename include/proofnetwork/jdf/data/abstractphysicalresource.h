#ifndef PROOF_JDF_ABSTRACTPHYSICALRESOURCE_H
#define PROOF_JDF_ABSTRACTPHYSICALRESOURCE_H

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourcePrivate;
class PROOF_NETWORK_JDF_EXPORT AbstractPhysicalResource : public AbstractResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractPhysicalResource)
public:

    double amount() const;
    double resourceWeight() const;

    void setAmount(double arg);
    void setResourceWeight(double arg);

    static bool fromJdf(const QXmlStreamReader &xmlReader, AbstractPhysicalResourceSP &abstractPhysicalResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void amountChanged(double arg);
    void resourceWeightChanged(double arg);

protected:
    explicit AbstractPhysicalResource() = delete;
    AbstractPhysicalResource(AbstractPhysicalResourcePrivate &dd, QObject *parent = 0);

};

}
}

#endif // PROOF_JDF_ABSTRACTPHYSICALRESOURCE_H
