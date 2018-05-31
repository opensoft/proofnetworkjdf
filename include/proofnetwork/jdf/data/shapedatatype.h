#ifndef PROOF_JDF_SHAPEDATATYPE_H
#define PROOF_JDF_SHAPEDATATYPE_H

#include <QString>

class ShapeDataType
{
public:
    ShapeDataType(float width, float height, float depth) : m_width(width), m_height(height), m_depth(depth) {}

    float width() const { return m_width; }

    float height() const { return m_height; }

    float depth() const { return m_depth; }

    static ShapeDataType fromString(const QString &string)
    {
        QStringList shapeDataTypeList = string.split(QStringLiteral(" "));
        if (shapeDataTypeList.count() == 3)
            return {shapeDataTypeList.at(0).toFloat(), shapeDataTypeList.at(1).toFloat(),
                    shapeDataTypeList.at(2).toFloat()};
        return ShapeDataType(0.0, 0.0, 0.0);
    }

    QString toString() const { return QStringLiteral("%1 %2 %3").arg(m_width, m_height, m_depth); }

private:
    float m_width = 0.0;
    float m_height = 0.0;
    float m_depth = 0.0;
};

#endif // PROOF_JDF_SHAPEDATATYPE_H
