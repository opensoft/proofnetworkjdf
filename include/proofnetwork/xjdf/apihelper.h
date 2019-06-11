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
#ifndef XJDFAPIHELPER_H
#define XJDFAPIHELPER_H

#include "proofcore/proofobject.h"

#include "proofnetwork/xjdf/proofnetworkxjdf_global.h"

#include <QHash>

namespace Proof {
namespace XJdf {
PROOF_NETWORK_XJDF_EXPORT Q_NAMESPACE;

enum class ProcessType
{
    NoProcessType,
    Cutting,
    BoxPacking
};

enum class ProductType
{
    NoProductType,
    BackCover,
    BlankBox, // Cut, Unfolded box, input for folder-gluer
    BlankSheet, // A sheet with connected blanks after a die cutting
    BlankWeb, // A web with connected blanks after a die cutting.
    Body, //Generic content inside of a cover.
    Book,
    BookBlock,
    BookCase,
    Box, // Convenience packaging that is not envisioned to be protection for shipping.
    Brochure,
    BusinessCard,
    Carton, // Protection packaging for shipping.
    Cover,
    EndSheet, // Endsheet for hard cover books.
    FlatBox, // A folded and glued blank (not opened). Output from a box folder-gluer.
    FlatWork, // Non-bound, non-folded Products or Products that only have packaging folds.
    FrontCover,
    Insert,
    Jacket, //Hard cover case jacket.
    Label,
    Newspaper, //A newspaper-product
    Pallet, //Loaded pallet of Boxes, Cartons or Component Resources
    Poster,
    Stack //Stacked Component.
};

enum class UsageType
{
    NoUsageType,
    Input,
    Output
};

enum class ResourceOrientation
{
    Rotate0Orientation, // 0 degrees
    Rotate90Orientation, // 90
    Rotate180Orientation, // 180
    Rotate270Orientation, // 270

    Flip0Orientation, // 0 degrees
    Flip90Orientation, // 90
    Flip180Orientation, // 180
    Flip270Orientation // 270
};

enum class Severity
{
    // Indicates that a pure event due to certain operation-related activity has occurred,
    // (e.g., Machine events, operator activities, etc.).
    // This Class is used for the transfer of conventional event Messages.
    // In case of Class = "Event", further event informa­tion is to be provided by the Type Attribute
    // and NotificationDetails Element.
    Event,
    // Any information about a Process which cannot be expressed by the other Classes (e.g., the beginning of execu­tion).
    // No user interaction is needed.
    Information,
    // Indicates that a minor error has occurred, and an auto­matic fix was applied. Execution continues.
    // The Node’s Status is unchanged. This appears in situations such as A4-Letter sub­stitutions when toner is low or when unknown extensions are encountered in a REQUIRED Resource
    Warning,
    // Indicates that an error has occurred that requires user inter­action.
    // Execution cannot continue until the problem has been fixed. The Node’s Status is Stopped.
    // This value appears in situations such as when Resources are missing, when major incompatibilities are detected,
    // or when the toner is empty.
    Error,
    // Indicates that a fatal error led to abortion of the Process. The Node’s Status is Aborted.
    // This value is seen with most protocol errors or when major Device malfunction has occurred.
    Fatal
};

enum class BoxType
{
    NoBoxType,
    Box,
    Carton,
    Envelope,
    Tube
};

enum class FoldType
{
    NoFoldType,
    F2_1,
    F4_1,
    F4_2,
    F6_1,
    F6_2,
    F6_3,
    F6_4,
    F6_5,
    F6_6,
    F6_7,
    F6_8,
    F8_1,
    F8_2,
    F8_3,
    F8_4,
    F8_5,
    F8_6,
    F8_7,
    F10_1,
    F10_2,
    F10_3,
    F12_1,
    F12_2,
    F12_3,
    F12_4,
    F12_5,
    F12_6,
    F12_7,
    F12_8,
    F12_9,
    F12_10,
    F12_11,
    F12_12,
    F12_13,
    F12_14,
    F14_1,
    F16_1,
    F16_2,
    F16_3,
    F16_4,
    F16_5,
    F16_6,
    F16_7,
    F16_8,
    F16_9,
    F16_10,
    F16_11,
    F16_12,
    F16_13,
    F16_14,
    F18_1,
    F18_2,
    F18_3,
    F18_4,
    F18_5,
    F18_6,
    F18_7,
    F18_8,
    F18_9,
    F20_1,
    F20_2,
    F24_1,
    F24_2,
    F24_3,
    F24_4,
    F24_5,
    F24_6,
    F24_7,
    F24_8,
    F24_9,
    F24_10,
    F24_11,
    F28_1,
    F32_1,
    F32_2,
    F32_3,
    F32_4,
    F32_5,
    F32_6,
    F32_7,
    F32_8,
    F32_9,
    F36_1,
    F36_2,
    F40_1,
    F48_1,
    F48_2,
    F64_1,
    F64_2
};

enum class Side
{
    Front,
    Back
};

enum class CoatingType
{
    NoCoatingType,
    Aqueous,
    Gloss,
    Ink,
    InkJet,
    Latex,
    Matte,
    Primer,
    Relief,
    RubResistant,
    Satin,
    Silicone,
    Toner,
    UV,
    Varnish,
    WaterResistant
};

enum class MediaUnit
{
    NoMediaUnit,
    Continuous,
    Roll,
    Sheet
};

enum class MediaType
{
    NoMediaType,
    Blanket,
    CorrugatedBoard,
    Disc,
    EmbossingFoil,
    Film,
    Foil,
    GravureCylinder,
    ImagingCylinder,
    LaminatingFoil,
    MountingTape,
    Other,
    Paper,
    Plate,
    Screen,
    SelfAdhesive,
    ShrinkFoil,
    Sleeve
};

Q_ENUM_NS(ProcessType)
Q_ENUM_NS(ProductType)
Q_ENUM_NS(UsageType)
Q_ENUM_NS(ResourceOrientation)
Q_ENUM_NS(Severity)
Q_ENUM_NS(BoxType)
Q_ENUM_NS(FoldType)
Q_ENUM_NS(Side)
Q_ENUM_NS(CoatingType)
Q_ENUM_NS(MediaUnit)
Q_ENUM_NS(MediaType)

PROOF_NETWORK_XJDF_EXPORT QString processTypeToString(ProcessType processType);
PROOF_NETWORK_XJDF_EXPORT ProcessType processTypeFromString(const QString &processType);

PROOF_NETWORK_XJDF_EXPORT QString productTypeToString(ProductType productType);
PROOF_NETWORK_XJDF_EXPORT ProductType productTypeFromString(const QString &productType);

PROOF_NETWORK_XJDF_EXPORT QString usageTypeToString(UsageType usage);
PROOF_NETWORK_XJDF_EXPORT UsageType usageTypeFromString(const QString &usage);

PROOF_NETWORK_XJDF_EXPORT QString resourceOrientationToString(ResourceOrientation resourceOrientation);
PROOF_NETWORK_XJDF_EXPORT ResourceOrientation resourceOrientationFromString(const QString &resourceOrientation);
PROOF_NETWORK_XJDF_EXPORT int resourceRotateToInt(ResourceOrientation resourceOrientation);
PROOF_NETWORK_XJDF_EXPORT ResourceOrientation resourceRotateFromInt(int resourceRotate);
PROOF_NETWORK_XJDF_EXPORT int resourceFlipToInt(ResourceOrientation resourceOrientation);
PROOF_NETWORK_XJDF_EXPORT ResourceOrientation resourceFlipFromInt(int resourceFlip);

PROOF_NETWORK_XJDF_EXPORT QString severityToString(Severity severity);
PROOF_NETWORK_XJDF_EXPORT Severity severityFromString(const QString &severity);

PROOF_NETWORK_XJDF_EXPORT QString boxTypeToString(BoxType type);
PROOF_NETWORK_XJDF_EXPORT BoxType boxTypeFromString(const QString &type);

PROOF_NETWORK_XJDF_EXPORT QString foldTypeToString(FoldType type);
PROOF_NETWORK_XJDF_EXPORT FoldType foldTypeFromString(const QString &type);

PROOF_NETWORK_XJDF_EXPORT QString sideTypeToString(Side side);
PROOF_NETWORK_XJDF_EXPORT Side sideTypeFromString(const QString &side);

PROOF_NETWORK_XJDF_EXPORT QString coatingTypeToString(CoatingType type);
PROOF_NETWORK_XJDF_EXPORT CoatingType coatingTypeFromString(const QString &type);

PROOF_NETWORK_XJDF_EXPORT QString mediaUnitToString(MediaUnit unit);
PROOF_NETWORK_XJDF_EXPORT MediaUnit mediaUnitFromString(const QString &unit);

PROOF_NETWORK_XJDF_EXPORT QString mediaTypeToString(MediaType type);
PROOF_NETWORK_XJDF_EXPORT MediaType mediaTypeFromString(const QString &type);

PROOF_NETWORK_XJDF_EXPORT uint qHash(ProcessType arg, uint seed = 0);
PROOF_NETWORK_XJDF_EXPORT uint qHash(ProductType arg, uint seed = 0);
PROOF_NETWORK_XJDF_EXPORT uint qHash(UsageType arg, uint seed = 0);
PROOF_NETWORK_XJDF_EXPORT uint qHash(Severity arg, uint seed = 0);
PROOF_NETWORK_XJDF_EXPORT uint qHash(BoxType arg, uint seed = 0);
PROOF_NETWORK_XJDF_EXPORT uint qHash(FoldType arg, uint seed = 0);
PROOF_NETWORK_XJDF_EXPORT uint qHash(Side arg, uint seed = 0);
PROOF_NETWORK_XJDF_EXPORT uint qHash(CoatingType arg, uint seed = 0);
PROOF_NETWORK_XJDF_EXPORT uint qHash(MediaType arg, uint seed = 0);

} // namespace XJdf
} // namespace Proof

#endif // PROOF_XJDF_APIHELPER_H
