#ifndef JDFDOCUMENT_H
#define JDFDOCUMENT_H

#include "proofnetwork/jdf/data/jdfnode.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfdocumentqmlwrapper.h"

namespace Proof {
namespace Jdf {

class JdfDocumentPrivate;
class PROOF_NETWORK_JDF_EXPORT JdfDocument : public JdfNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(JdfDocument)
public:
    QString id() const;
    QString jobId() const;
    QString jobPartId() const;
    ResourcePoolSP resourcePool() const;
    ResourceLinkPoolSP resourceLinkPool() const;

    void setId(const QString &arg);
    void setJobId(const QString &arg);
    void setJobPartId(const QString &arg);
    void setResourcePool(const ResourcePoolSP &arg);
    void setResourceLinkPool(const ResourceLinkPoolSP &arg);

    JdfDocumentQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static JdfDocumentSP create();

    static JdfDocumentSP fromJdf(QXmlStreamReader &xmlReader);
    QString toJdf();

signals:
    void idChanged(const QString &id);
    void jobIdChanged(const QString &jobId);
    void jobPartIdChanged(const QString &jobPartId);
    void resourcePoolChanged(Proof::Jdf::ResourcePoolSP resourcePool);
    void resourceLinkPoolChanged(Proof::Jdf::ResourceLinkPoolSP resourceLinkPool);
protected:
    explicit JdfDocument();
};

}
}

#endif // JDFDOCUMENT_H
