#ifndef PROOF_JDF_QUERY_P_H
#define PROOF_JDF_QUERY_P_H

#include "proofnetwork/jdf/data/message_p.h"

namespace Proof {
namespace Jdf {

class QueryPrivate : public MessagePrivate
{
    Q_DECLARE_PUBLIC(Query)

protected:
    void specificMessageFromJmf(QXmlStreamReader &xmlReader) override;
    QString tagName() const override;
    void specificMessageToJmf(QXmlStreamWriter &xmlWriter) const override;
};

}
}

#endif // PROOF_JDF_QUERY_P_H

