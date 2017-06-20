#ifndef PROOF_JDF_SPAN_H
#define PROOF_JDF_SPAN_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/data/shapedatatype.h"
#include "proofnetwork/jdf/data/rangelistdatatype.h"
#include "proofnetwork/jdf/data/enumerationsdatatype.h"
#include "proofnetwork/jdf/data/stringsdatatype.h"

#include <QDateTime>
#include <QPoint>
#include <QXmlStreamWriter>

namespace Proof {
namespace Jdf {

template <class T, class F, SpanDataType DataType>
class Span;
using DurationSpan = Span<QDateTime, DateTimeRange, SpanDataType::DurationSpan>;
using EnumerationSpan = Span<QString, Enumerations, SpanDataType::EnumerationSpan>;
using IntegerSpan = Span<int, IntegerRangeList, SpanDataType::IntegerSpan>;
using NameSpan = Span<QString, Strings, SpanDataType::NameSpan>;
using NumberSpan = Span<double, DoubleRangeList, SpanDataType::NumberSpan>;
using OptionSpan = Span<bool, Enumerations, SpanDataType::OptionSpan>;
using ShapeSpan = Span<ShapeDataType, ShapeRangeList, SpanDataType::ShapeSpan>;
using StringSpan = Span<QString, Strings, SpanDataType::StringSpan>;
using TimeSpan = Span<QDateTime, DateTimeRange, SpanDataType::TimeSpan>;
using XYPairSpan = Span<QPoint, XYPairRangeList, SpanDataType::XYPairSpan>;

template <class T, class F, SpanDataType DataType>
class PROOF_NETWORK_JDF_EXPORT Span
{
public:
    constexpr SpanDataType dataType() const
    {
        return DataType;
    }

    T actual() const
    {
        return m_actual;
    }

    void setActual(T arg)
    {
        m_actual = arg;
        m_isDirty = true;
    }

    F offerRange() const
    {
        return m_offerRange;
    }

    void setOfferRange(const F &offerRange)
    {
        m_offerRange = offerRange;
        m_isDirty = true;
    }

    T preferred() const
    {
        return m_preferred;
    }

    void setPreferred(const T &preferred)
    {
        m_preferred = preferred;
        m_isDirty = true;
    }

    F range() const
    {
        return m_range;
    }

    void setRange(const F &range)
    {
        m_range = range;
        m_isDirty = true;
    }

    bool isDirty() const
    {
        return m_isDirty;
    }

    bool operator==(const Span<T, F, DataType> &other) const
    {
        return m_actual == other.actual()
                && m_offerRange == other.offerRange()
                && m_preferred == other.preferred()
                && m_range == other.range();
    }

    bool operator!=(const Span<T, F, DataType> &other) const
    {
        return !(*this == other);
    }

    static Span<T, F, DataType> fromJdf(const QString &name, QXmlStreamReader &jdfReader)
    {
        Span<T, F, DataType> span;
        while (!jdfReader.atEnd() && !jdfReader.hasError()) {
            if (jdfReader.name() == name && jdfReader.isStartElement()) {
                QXmlStreamAttributes attributes = jdfReader.attributes();
                span.setActual(span.readAttribute(attributes.value(QStringLiteral("Actual"))));
                span.setOfferRange(F::fromString(attributes.value(QStringLiteral("OfferRange")).toString()));
                span.setPreferred(span.readAttribute(attributes.value(QStringLiteral("Preferred"))));
                span.setRange(F::fromString(attributes.value(QStringLiteral("Range")).toString()));
            } else if (jdfReader.isStartElement()) {
                jdfReader.skipCurrentElement();
            } else if (jdfReader.isEndElement()) {
                break;
            }
            jdfReader.readNext();
        }
        return span;
    }

    void toJdf(const QString &name, QXmlStreamWriter &jdfWriter)
    {
        jdfWriter.writeStartElement(name);
        jdfWriter.writeAttribute(QStringLiteral("DataType"), spanDataTypeToString(dataType()));
        writeAttribute(jdfWriter, QStringLiteral("Actual"), actual());
        writeAttribute(jdfWriter, QStringLiteral("OfferRange"), m_offerRange.toString());
        writeAttribute(jdfWriter, QStringLiteral("Preferred"), preferred());
        writeAttribute(jdfWriter, QStringLiteral("Range"), m_range.toString());
        jdfWriter.writeEndElement();
    }

private:

    void writeAttribute(QXmlStreamWriter &jdfWriter, const QString &name, int data)
    {
        if (data != 0)
            jdfWriter.writeAttribute(name, QString::number(data));
    }

    void writeAttribute(QXmlStreamWriter &jdfWriter, const QString &name, double data)
    {
        if (!qFuzzyIsNull(data))
            jdfWriter.writeAttribute(name, QString::number(data));
    }

    void writeAttribute(QXmlStreamWriter &jdfWriter, const QString &name, bool data)
    {
        jdfWriter.writeAttribute(name, data ? "true" : "false");
    }

    void writeAttribute(QXmlStreamWriter &jdfWriter, const QString &name, const ShapeDataType &data)
    {
        if (!qFuzzyIsNull(data.height()) && !qFuzzyIsNull(data.width()) && !qFuzzyIsNull(data.depth()))
            jdfWriter.writeAttribute(name, data.toString());
    }

    void writeAttribute(QXmlStreamWriter &jdfWriter, const QString &name, const QString &data)
    {
        if (!data.isEmpty())
            jdfWriter.writeAttribute(name, data);
    }

    void writeAttribute(QXmlStreamWriter &jdfWriter, const QString &name, const QDateTime &data)
    {
        if (!data.isNull())
            jdfWriter.writeAttribute(name, data.toUTC().toString(Qt::ISODate));
    }

    void writeAttribute(QXmlStreamWriter &jdfWriter, const QString &name, const QPoint &data)
    {
        if (data.isNull())
            jdfWriter.writeAttribute(name, QStringLiteral("%1 %2").arg(data.x(), data.y()));
    }

    T readAttribute(const QStringRef &attribute);

    T m_actual;
    F m_offerRange;
    T m_preferred;
    F m_range;

    bool m_isDirty = false;

};

template<> inline
QDateTime DurationSpan::readAttribute(const QStringRef &attribute)
{
    return QDateTime::fromString(attribute.toString(), Qt::ISODate);
}

template<> inline
QString EnumerationSpan::readAttribute(const QStringRef &attribute)
{
    return attribute.toString();
}

template<> inline
int IntegerSpan::readAttribute(const QStringRef &attribute)
{
    return attribute.toInt();
}

template<> inline
QString NameSpan::readAttribute(const QStringRef &attribute)
{
    return attribute.toString();
}

template<> inline
double NumberSpan::readAttribute(const QStringRef &attribute)
{
    return attribute.toDouble();
}

template<> inline
bool OptionSpan::readAttribute(const QStringRef &attribute)
{
    return attribute.toString() == "true";
}

template<> inline
ShapeDataType ShapeSpan::readAttribute(const QStringRef &attribute)
{
    return ShapeDataType::fromString(attribute.toString());
}

template<> inline
QString StringSpan::readAttribute(const QStringRef &attribute)
{
    return attribute.toString();
}

template<> inline
QDateTime TimeSpan::readAttribute(const QStringRef &attribute)
{
    return QDateTime::fromString(attribute.toString(), Qt::ISODate);
}

template<> inline
QPoint XYPairSpan::readAttribute(const QStringRef &attribute)
{
    QStringList attributeList = attribute.toString().split(QStringLiteral(" "));
    if (attributeList.count() == 2)
        return {attributeList.at(0).toInt(), attributeList.at(1).toInt()};
    return QPoint();
}

}
}

#endif // PROOF_JDF_SPAN_H
