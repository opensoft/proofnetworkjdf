#ifndef PROOF_JDF_SPAN_H
#define PROOF_JDF_SPAN_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QDateTime>
#include <QXmlStreamWriter>

namespace Proof {
namespace Jdf {

template <class T, ApiHelper::SpanDataType DATA_TYPE>
class Span;

using TimeSpan = Span<QDateTime, ApiHelper::SpanDataType::TimeSpan>;

template <class T, ApiHelper::SpanDataType DATA_TYPE>
class PROOF_NETWORK_JDF_EXPORT Span
{

public:
    explicit Span() {}

    constexpr ApiHelper::SpanDataType dataType() const
    {
        return DATA_TYPE;
    }

    T actual() const
    {
        return m_actual;
    }
    void setActual(T arg)
    {
        m_actual = arg;
    }

    Span<T, DATA_TYPE> &operator=(const Span<T, DATA_TYPE> &other)
    {
        m_actual = other.actual();
        return *this;
    }

    bool operator==(const Span<T, DATA_TYPE> &other) const
    {
        return m_actual == other.actual();
    }

    bool operator!=(const Span<T, DATA_TYPE> &other) const
    {
        return !(*this == other);
    }

    static Span<T, DATA_TYPE> fromJdf(const QString &name, QXmlStreamReader &jdfReader)
    {
        Span<T, DATA_TYPE> span;
        while (!jdfReader.atEnd() && !jdfReader.hasError()) {
            if (jdfReader.name() == name && jdfReader.isStartElement()) {
                QXmlStreamAttributes attributes = jdfReader.attributes();
                span.setActual(span.readAttribute(attributes.value("Actual")));
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
        jdfWriter.writeAttribute("DataType", ApiHelper::spanDataTypeToString(dataType()));
        if (!actual().isNull())
            writeAttribute(jdfWriter, "Actual", actual());
        jdfWriter.writeEndElement();
    }

private:

    void writeAttribute(QXmlStreamWriter &jdfWriter, const QString &name, const QDateTime &data)
    {
        jdfWriter.writeAttribute(name, data.toString(Qt::ISODate));
    }

    T readAttribute(const QStringRef &attribute);

    T m_actual;

};

template<> inline
QDateTime TimeSpan::readAttribute(const QStringRef &attribute)
{
    return QDateTime::fromString(attribute.toString(), Qt::ISODate);
}

}
}

#endif // PROOF_JDF_SPAN_H
