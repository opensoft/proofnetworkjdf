#ifndef PROOF_JDF_RANGEDATATYPE_H
#define PROOF_JDF_RANGEDATATYPE_H

#include "proofnetwork/jdf/data/shapedatatype.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QDateTime>

namespace Proof {
namespace Jdf {

template <class T>
class RangeDataType;
using IntegerRange = RangeDataType<int>;
using DoubleRange = RangeDataType<double>;
using ShapeRange = RangeDataType<ShapeDataType>;
using DateTimeRange = RangeDataType<QDateTime>;

template <class T>
class RangeDataType
{
public:
    RangeDataType() {}
    RangeDataType(T start, T stop) : m_start(start), m_stop(stop) {}

    T start() const { return m_start; }

    T stop() const { return m_stop; }

    void setStart(const T &start) { m_start = start; }

    void setStop(const T &stop) { m_stop = stop; }

    bool operator==(const RangeDataType<T> &other) const
    {
        return this->start() == other.start() && this->stop() == other.stop();
    }

    bool operator!=(const RangeDataType<T> &other) const { return !(*this == other); }

    static RangeDataType<T> fromString(const QString &attribute)
    {
        RangeDataType<T> rangeDataType;
        QStringList dataList = attribute.split(QStringLiteral("~"));
        QString start;
        QString stop;
        if (dataList.count() == 1) {
            start = dataList.at(0).trimmed();
            stop = start;
        } else if (dataList.count() == 2) {
            start = dataList.at(0).trimmed();
            stop = dataList.at(1).trimmed();
            if (start.isEmpty())
                start = stop;
            else if (stop.isEmpty())
                stop = start;
        }

        if (!start.isEmpty()) {
            rangeDataType.setStart(rangeDataType.dataFromString(start));
            rangeDataType.setStop(rangeDataType.dataFromString(stop));
        }
        return rangeDataType;
    }

    QString toString() const { return dataToString(m_start, m_stop); }

private:
    T dataFromString(const QString &string);

    QString dataToString(const QDateTime &start, const QDateTime &stop) const
    {
        return dataToString(start.toUTC().toString(Qt::ISODate), stop.toUTC().toString(Qt::ISODate));
    }

    QString dataToString(int start, int stop) const
    {
        return dataToString(QString::number(start), QString::number(stop));
    }

    QString dataToString(const QString &start, const QString &stop) const
    {
        if (start.isEmpty() || stop.isEmpty())
            return QString();
        if (start == stop)
            return QStringLiteral("%1").arg(start);
        return QStringLiteral("%1 ~ %2").arg(start, stop);
    }

    QString dataToString(double start, double stop) const
    {
        return dataToString(QString::number(start), QString::number(stop));
    }

    QString dataToString(ShapeDataType start, ShapeDataType stop) const
    {
        return dataToString(start.toString(), stop.toString());
    }

    T m_start;
    T m_stop;
};

template <>
inline QDateTime DateTimeRange::dataFromString(const QString &string)
{
    return QDateTime::fromString(string, Qt::ISODate);
}

template <>
inline int IntegerRange::dataFromString(const QString &string)
{
    return string.toInt();
}

template <>
inline double DoubleRange::dataFromString(const QString &string)
{
    return string.toDouble();
}

template <>
inline ShapeDataType ShapeRange::dataFromString(const QString &string)
{
    return ShapeDataType::fromString(string);
}

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_RANGEDATATYPE_H
