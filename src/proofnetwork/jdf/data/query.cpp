#include "query.h"

#include "query_p.h"

namespace Proof {
namespace Jdf {

Query::Query(QueryPrivate &dd) : Message(dd)
{}

void QueryPrivate::specificMessageFromJmf(QXmlStreamReader &xmlReader)
{
    xmlReader.skipCurrentElement();
}

QString QueryPrivate::tagName() const
{
    return QStringLiteral("Query");
}

void QueryPrivate::specificMessageToJmf(QXmlStreamWriter &) const
{}

} // namespace Jdf
} // namespace Proof
