#ifndef JDFJDFDOCUMENT_H
#define JDFJDFDOCUMENT_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfdocumentqmlwrapper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class JdfDocumentPrivate;
class PROOF_NETWORK_JDF_EXPORT JdfDocument : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(JdfDocument)
public:

    QString id() const;
    QString jobId() const;
    ResourcePoolSP resourcePool() const;

    void setId(const QString &arg);
    void setJobId(const QString &arg);
    void setResourcePool(const ResourcePoolSP &arg);

    void updateFrom(const NetworkDataEntitySP &other) override;
    JdfDocumentQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static JdfDocumentSP create();

    static JdfDocumentSP fromJdf(QXmlStreamReader &xmlReader);
    QString toJdf();
    static JdfDocumentSP defaultObject();

signals:
    void idChanged(const QString &arg);
    void jobIdChanged(const QString &arg);
    void resourcePoolChanged(Proof::Jdf::ResourcePoolSP arg);

protected:
    explicit JdfDocument();

};

}
}

#endif // JDFJDFDOCUMENT_H
