/* Copyright 2019, OpenSoft Inc.
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
#include "proofnetwork/xjdf/apihelper.h"

#include <QHash>

namespace Proof {
namespace XJdf {

uint qHash(ProcessType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ProductType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(UsageType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(Severity arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(BoxType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(Side arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(CoatingType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

static const QHash<QString, ProcessType> PROCESS_TYPE_STRINGIFIED = {{"", ProcessType::NoProcessType},
                                                                     {"Cutting", ProcessType::Cutting},
                                                                     {"BoxPacking", ProcessType::BoxPacking}};

static const QHash<QString, ProductType> PRODUCT_TYPE_STRINGIFIED =
    {{"", ProductType::NoProductType},    {"BackCover", ProductType::BackCover},
     {"BlankBox", ProductType::BlankBox}, {"BlankSheet", ProductType::BlankSheet},
     {"BlankWeb", ProductType::BlankWeb}, {"Body", ProductType::Body},
     {"Book", ProductType::Book},         {"BookBlock", ProductType::BookBlock},
     {"BookCase", ProductType::BookCase}, {"Box", ProductType::Box},
     {"Brochure", ProductType::Brochure}, {"BusinessCard", ProductType::BusinessCard},
     {"Carton", ProductType::Carton},     {"Cover", ProductType::Cover},
     {"EndSheet", ProductType::EndSheet}, {"FlatBox", ProductType::FlatBox},
     {"FlatWork", ProductType::FlatWork}, {"FrontCover", ProductType::FrontCover},
     {"Insert", ProductType::Insert},     {"Jacket", ProductType::Jacket},
     {"Label", ProductType::Label},       {"Newspaper", ProductType::Newspaper},
     {"Pallet", ProductType::Pallet},     {"Poster", ProductType::Poster},
     {"Stack", ProductType::Stack}};

static const QHash<QString, UsageType> USAGE_TYPE_STRINGIFIED = {{"", UsageType::NoUsageType},
                                                                 {"Input", UsageType::Input},
                                                                 {"Output", UsageType::Output}};

static const QHash<QString, ResourceOrientation> RESOURCE_ORIENTATION_STRINGIFIED =
    {{"Rotate0", ResourceOrientation::Rotate0Orientation},     {"Rotate90", ResourceOrientation::Rotate90Orientation},
     {"Rotate180", ResourceOrientation::Rotate180Orientation}, {"Rotate270", ResourceOrientation::Rotate270Orientation},

     {"Flip0", ResourceOrientation::Flip0Orientation},         {"Flip90", ResourceOrientation::Flip90Orientation},
     {"Flip180", ResourceOrientation::Flip180Orientation},     {"Flip270", ResourceOrientation::Flip270Orientation}};

static const QHash<int, ResourceOrientation> RESOURCE_ROTATE_NUMERICAL = {
    {0, ResourceOrientation::Rotate0Orientation},
    {90, ResourceOrientation::Rotate90Orientation},
    {180, ResourceOrientation::Rotate180Orientation},
    {270, ResourceOrientation::Rotate270Orientation},
};

static const QHash<int, ResourceOrientation> RESOURCE_FLIP_NUMERICAL = {{0, ResourceOrientation::Flip0Orientation},
                                                                        {90, ResourceOrientation::Flip90Orientation},
                                                                        {180, ResourceOrientation::Flip180Orientation},
                                                                        {270, ResourceOrientation::Flip270Orientation}};

static const QHash<QString, Severity> SEVERITY_STRINGIFIED = {{"Event", Severity::Event},
                                                              {"Information", Severity::Information},
                                                              {"Warning", Severity::Warning},
                                                              {"Error", Severity::Error},
                                                              {"Fatal", Severity::Fatal}};

static const QHash<QString, BoxType> BOX_TYPE_STRINGIFIED = {{"", BoxType::NoBoxType},
                                                             {"Box", BoxType::Box},
                                                             {"Carton", BoxType::Carton},
                                                             {"Envelope", BoxType::Envelope},
                                                             {"Tube", BoxType::Tube}};

static const QHash<QString, FoldType>
    FOLD_TYPE_STRINGIFIED{{"", FoldType::NoFoldType},   {"F2-1", FoldType::F2_1},     {"F4-1", FoldType::F4_1},
                          {"F4-2", FoldType::F4_2},     {"F6-1", FoldType::F6_1},     {"F6-2", FoldType::F6_2},
                          {"F6-3", FoldType::F6_3},     {"F6-4", FoldType::F6_4},     {"F6-5", FoldType::F6_5},
                          {"F6-6", FoldType::F6_6},     {"F6-7", FoldType::F6_7},     {"F6-8", FoldType::F6_8},
                          {"F8-1", FoldType::F8_1},     {"F8-2", FoldType::F8_2},     {"F8-3", FoldType::F8_3},
                          {"F8-4", FoldType::F8_4},     {"F8-5", FoldType::F8_5},     {"F8-6", FoldType::F8_6},
                          {"F8-7", FoldType::F8_7},     {"F10-1", FoldType::F10_1},   {"F10-2", FoldType::F10_2},
                          {"F10-3", FoldType::F10_3},   {"F12-1", FoldType::F12_1},   {"F12-2", FoldType::F12_2},
                          {"F12-3", FoldType::F12_3},   {"F12-4", FoldType::F12_4},   {"F12-5", FoldType::F12_5},
                          {"F12-6", FoldType::F12_6},   {"F12-7", FoldType::F12_7},   {"F12-8", FoldType::F12_8},
                          {"F12-9", FoldType::F12_9},   {"F12-10", FoldType::F12_10}, {"F12-11", FoldType::F12_11},
                          {"F12-12", FoldType::F12_12}, {"F12-13", FoldType::F12_13}, {"F12-14", FoldType::F12_14},
                          {"F14-1", FoldType::F14_1},   {"F16-1", FoldType::F16_1},   {"F16-2", FoldType::F16_2},
                          {"F16-3", FoldType::F16_3},   {"F16-4", FoldType::F16_4},   {"F16-5", FoldType::F16_5},
                          {"F16-6", FoldType::F16_6},   {"F16-7", FoldType::F16_7},   {"F16-8", FoldType::F16_8},
                          {"F16-9", FoldType::F16_9},   {"F16-10", FoldType::F16_10}, {"F16-11", FoldType::F16_11},
                          {"F16-12", FoldType::F16_12}, {"F16-13", FoldType::F16_13}, {"F16-14", FoldType::F16_14},
                          {"F18-1", FoldType::F18_1},   {"F18-2", FoldType::F18_2},   {"F18-3", FoldType::F18_3},
                          {"F18-4", FoldType::F18_4},   {"F18-5", FoldType::F18_5},   {"F18-6", FoldType::F18_6},
                          {"F18-7", FoldType::F18_7},   {"F18-8", FoldType::F18_8},   {"F18-9", FoldType::F18_9},
                          {"F20-1", FoldType::F20_1},   {"F20-2", FoldType::F20_2},   {"F24-1", FoldType::F24_1},
                          {"F24-2", FoldType::F24_2},   {"F24-3", FoldType::F24_3},   {"F24-4", FoldType::F24_4},
                          {"F24-5", FoldType::F24_5},   {"F24-6", FoldType::F24_6},   {"F24-7", FoldType::F24_7},
                          {"F24-8", FoldType::F24_8},   {"F24-9", FoldType::F24_9},   {"F24-10", FoldType::F24_10},
                          {"F24-11", FoldType::F24_11}, {"F28-1", FoldType::F28_1},   {"F32-1", FoldType::F32_1},
                          {"F32-2", FoldType::F32_2},   {"F32-3", FoldType::F32_3},   {"F32-4", FoldType::F32_4},
                          {"F32-5", FoldType::F32_5},   {"F32-6", FoldType::F32_6},   {"F32-7", FoldType::F32_7},
                          {"F32-8", FoldType::F32_8},   {"F32-9", FoldType::F32_9},   {"F36-1", FoldType::F36_1},
                          {"F36-2", FoldType::F36_2},   {"F40-1", FoldType::F40_1},   {"F48-1", FoldType::F48_1},
                          {"F48-2", FoldType::F48_2},   {"F64-1", FoldType::F64_1},   {"F64-2", FoldType::F64_2}};

static const QHash<QString, Side> SIDE_STRINGIFIED = {{"Front", Side::Front}, {"Back", Side::Back}};

static const QHash<QString, CoatingType> COATING_TYPE_STRINGIFIED =
    {{"", CoatingType::NoCoatingType},  {"Aqueous", CoatingType::Aqueous},
     {"Gloss", CoatingType::Gloss},     {"Ink", CoatingType::Ink},
     {"InkJet", CoatingType::InkJet},   {"Latex", CoatingType::Latex},
     {"Matte", CoatingType::Matte},     {"Primer", CoatingType::Primer},
     {"Relief", CoatingType::Relief},   {"RubResistant", CoatingType::RubResistant},
     {"Satin", CoatingType::Satin},     {"Silicone", CoatingType::Silicone},
     {"Toner", CoatingType::Toner},     {"UV", CoatingType::UV},
     {"Varnish", CoatingType::Varnish}, {"WaterResistant", CoatingType::WaterResistant}};

ProcessType processTypeFromString(const QString &processType)
{
    return PROCESS_TYPE_STRINGIFIED.value(processType, ProcessType::NoProcessType);
}

QString processTypeToString(ProcessType processType)
{
    return PROCESS_TYPE_STRINGIFIED.key(processType, QString());
}

QString productTypeToString(ProductType productType)
{
    return PRODUCT_TYPE_STRINGIFIED.key(productType, QString());
}

ProductType productTypeFromString(const QString &productType)
{
    return PRODUCT_TYPE_STRINGIFIED.value(productType, ProductType::NoProductType);
}

QString usageTypeToString(UsageType usage)
{
    return USAGE_TYPE_STRINGIFIED.key(usage, QString());
}

UsageType usageTypeFromString(const QString &usage)
{
    return USAGE_TYPE_STRINGIFIED.value(usage, UsageType::NoUsageType);
}

QString resourceOrientationToString(ResourceOrientation resourceOrientation)
{
    return RESOURCE_ORIENTATION_STRINGIFIED.key(resourceOrientation, QString());
}

ResourceOrientation resourceOrientationFromString(const QString &resourceOrientation)
{
    return RESOURCE_ORIENTATION_STRINGIFIED.value(resourceOrientation, ResourceOrientation::Rotate0Orientation);
}

int resourceRotateToInt(ResourceOrientation resourceOrientation)
{
    return RESOURCE_ROTATE_NUMERICAL.key(resourceOrientation, 0);
}

ResourceOrientation resourceRotateFromInt(int resourceRotate)
{
    return RESOURCE_ROTATE_NUMERICAL.value(resourceRotate, ResourceOrientation::Rotate0Orientation);
}

int resourceFlipToInt(ResourceOrientation resourceOrientation)
{
    return RESOURCE_FLIP_NUMERICAL.key(resourceOrientation, 0);
}

ResourceOrientation resourceFlipFromInt(int resourceFlip)
{
    return RESOURCE_FLIP_NUMERICAL.value(resourceFlip, ResourceOrientation::Flip0Orientation);
}

QString severityToString(Severity severity)
{
    return SEVERITY_STRINGIFIED.key(severity, QString());
}

Severity severityFromString(const QString &severity)
{
    return SEVERITY_STRINGIFIED.value(severity, Severity::Information);
}

QString boxTypeToString(BoxType type)
{
    return BOX_TYPE_STRINGIFIED.key(type, QString());
}

BoxType boxTypeFromString(const QString &type)
{
    return BOX_TYPE_STRINGIFIED.value(type, BoxType::NoBoxType);
}

QString foldTypeToString(FoldType type)
{
    return FOLD_TYPE_STRINGIFIED.key(type, QString());
}

FoldType foldTypeFromString(const QString &type)
{
    return FOLD_TYPE_STRINGIFIED.value(type, FoldType::NoFoldType);
}

QString sideTypeToString(Side side)
{
    return SIDE_STRINGIFIED.key(side, QString());
}

Side sideTypeFromString(const QString &side)
{
    return SIDE_STRINGIFIED.value(side, Side::Front);
}

QString coatingTypeToString(CoatingType type)
{
    return COATING_TYPE_STRINGIFIED.key(type, QString());
}

CoatingType coatingTypeFromString(const QString &type)
{
    return COATING_TYPE_STRINGIFIED.value(type, CoatingType::NoCoatingType);
}

} // namespace XJdf
} // namespace Proof
