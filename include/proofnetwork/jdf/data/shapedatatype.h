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
