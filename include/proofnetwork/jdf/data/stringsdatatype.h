#ifndef PROOF_JDF_STRINGSDATATYPE_H
#define PROOF_JDF_STRINGSDATATYPE_H

#include <QStringList>

namespace Proof {
namespace Jdf {

class Strings : public QStringList
{
public:
    Strings(const QStringList &list = QStringList()) : QStringList(list) {}

    static Strings fromString(const QString &attribute)
    {
        return attribute.split(QStringLiteral(" "), QString::SplitBehavior::SkipEmptyParts);
    }

    QString toString() const { return join(QStringLiteral(" ")); }
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_STRINGSDATATYPE_H
