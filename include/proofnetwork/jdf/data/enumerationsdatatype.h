#ifndef PROOF_JDF_ENUMERATIONSDATATYPE_H
#define PROOF_JDF_ENUMERATIONSDATATYPE_H

#include <QStringList>

namespace Proof {
namespace Jdf {

class Enumerations : public QStringList
{
public:
    Enumerations(const QStringList &list = QStringList()) : QStringList(list) {}

    static Enumerations fromString(const QString &attribute)
    {
        QStringList newEnumList;
        QStringList enumList = attribute.split(QStringLiteral(" "), QString::SplitBehavior::SkipEmptyParts);
        for (const auto &data : enumList) {
            QString trimmedData(data.trimmed());
            if (!trimmedData.isEmpty())
                newEnumList.append(trimmedData);
        }

        return newEnumList;
    }

    QString toString() const { return join(" "); }
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_ENUMERATIONSDATATYPE_H
