/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
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
class RangeListDataType : QVector<T>
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
