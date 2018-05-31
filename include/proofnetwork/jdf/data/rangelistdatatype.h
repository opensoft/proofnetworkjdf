#ifndef PROOF_JDF_RANGELISTDATATYPE_H
#define PROOF_JDF_RANGELISTDATATYPE_H

#include "proofnetwork/jdf/data/rangedatatype.h"

namespace Proof {
namespace Jdf {

template <class T>
class RangeListDataType;
using IntegerRangeList = RangeListDataType<IntegerRange>;
using DoubleRangeList = RangeListDataType<DoubleRange>;
using ShapeRangeList = RangeListDataType<ShapeRange>;
using XYPairRangeList = RangeListDataType<QPoint>;

template <class T>
class RangeListDataType : QList<T>
{
public:
    bool operator==(const RangeListDataType<T> &other) const
    {
        if (this->count() != other.count())
            return false;

        for (int i = 0; i < this->count(); ++i) {
            if (this->at(i) != other.at(i))
                return false;
        }
        return true;
    }

    bool operator!=(const RangeListDataType<T> &other) const { return !(*this == other); }

    static RangeListDataType<T> fromString(const QString &attribute)
    {
        QString preparedAttribute = attribute;
        while (preparedAttribute.contains(QStringLiteral(" ~")))
            preparedAttribute = preparedAttribute.replace(QStringLiteral(" ~"), QStringLiteral("~"));

        while (preparedAttribute.contains(QStringLiteral("~ ")))
            preparedAttribute = preparedAttribute.replace(QStringLiteral("~ "), QStringLiteral("~"));

        RangeListDataType<T> rangeListDataType;
        QStringList dataList = preparedAttribute.split(QStringLiteral(" "), QString::SplitBehavior::SkipEmptyParts);
        for (const auto &range : dataList)
            rangeListDataType.append(T::fromString(range));

        return rangeListDataType;
    }

    QString toString() const
    {
        QStringList list;
        for (int i = 0; i < this->count(); ++i)
            list.append(this->at(i).toString());

        return list.join(QStringLiteral(" "));
    }
};

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_RANGELISTDATATYPE_H
