#include "query.h"

#include "query_p.h"

namespace Proof {
namespace Jdf {

Query::Query(QueryPrivate &dd, QObject *parent)
    : Message(dd, parent)
{
}

void QueryPrivate::specificMessageFromJmf(QXmlStreamReader &xmlReader)
{
    xmlReader.skipCurrentElement();
}

QString QueryPrivate::tagName() const
{
    return "Query";
}

void QueryPrivate::specificMessageToJmf(QXmlStreamWriter &) const
{
}

} // namespace Jdf
} // namespace Proof
