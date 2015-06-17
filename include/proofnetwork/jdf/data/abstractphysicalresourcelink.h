#ifndef ABSTRACTPHYSICALRESOURCELINK_H
#define ABSTRACTPHYSICALRESOURCELINK_H

#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class AbstractPhysicalResourceLinkPrivate;
class AbstractPhysicalResourceLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractPhysicalResourceLink)
public:
    ApiHelper::Orientation orientation() const;
    void setOrientation(ApiHelper::Orientation arg);

    static void fromJdf(const QXmlStreamReader &xmlReader, const AbstractPhysicalResourceLinkSP &abstractResource);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);
signals:
    void orientationChanged(ApiHelper::Orientation orientation);
protected:
    explicit AbstractPhysicalResourceLink() = delete;
    AbstractPhysicalResourceLink(AbstractPhysicalResourceLinkPrivate &dd, QObject *parent = nullptr);
};

}
}

#endif // ABSTRACTPHYSICALRESOURCELINK_H
