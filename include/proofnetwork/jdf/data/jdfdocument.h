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
    JdfDocumentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static JdfDocumentSP create();

    static JdfDocumentSP fromJdf(QXmlStreamReader &xmlReader, const QString &forceJobId = QString(),
                                 const QStringList &alternativeIdAttributes = QStringList(), bool sanitize = false);
    QString toJdf();

protected:
    explicit JdfDocument();
};

} // namespace Jdf
} // namespace Proof

#endif // JDFDOCUMENT_H
