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
#include "proofnetwork/jdf/apihelper.h"

#include <QHash>

namespace Proof {
namespace Jdf {

uint qHash(ResourceStatus arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ResourceClass arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(CoatingType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(LaminatingSurface arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(BundleType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ResourceOrientation arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ComponentType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ProductType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ResourcePartType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(LinkUsage arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ProcessUsage arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(BlockType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(MediaUnit arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(MediaType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(DeviceFilterDetails arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(DeviceStatus arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(NotificationClass arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(SpanDataType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

template <typename T>
using StringDict = QHash<QString, T>;
template <typename T>
using IntDict = QHash<int, T>;

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<ResourceStatus>, RESOURCE_STATUS_STRINGIFIED,
                          ({{"", ResourceStatus::NoStatus},
                            {"Incomplete", ResourceStatus::IncompleteStatus},
                            {"Rejected", ResourceStatus::RejectedStatus},
                            {"Unavailable", ResourceStatus::UnavailableStatus},
                            {"InUse", ResourceStatus::InUseStatus},
                            {"Draft", ResourceStatus::DraftStatus},
                            {"Complete", ResourceStatus::CompleteStatus},
                            {"Available", ResourceStatus::AvailableStatus}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<ResourceClass>, RESOURCE_CLASS_STRINGIFIED,
                          ({{"", ResourceClass::NoClass},
                            {"Consumable", ResourceClass::ConsumableClass},
                            {"Handling", ResourceClass::HandlingClass},
                            {"Implementation", ResourceClass::ImplementationClass},
                            {"Intent", ResourceClass::IntentClass},
                            {"Parameter", ResourceClass::ParameterClass},
                            {"PlaceHolder", ResourceClass::PlaceHolderClass},
                            {"Quantity", ResourceClass::QuantityClass}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<CoatingType>, COATING_STRINGIFIED,
                          ({{"None", CoatingType::NoCoating},
                            {"Coated", CoatingType::Coated},
                            {"Glossy", CoatingType::GlossyCoating},
                            {"HighGloss", CoatingType::HighGlossCoating},
                            {"InkJet", CoatingType::InkJetCoating},
                            {"Matte", CoatingType::MatteCoating},
                            {"Polymer", CoatingType::PolymerCoating},
                            {"Silver", CoatingType::SilverCoating},
                            {"Satin", CoatingType::SatinCoating},
                            {"Semigloss", CoatingType::SemiglossCoating}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<CoatingDetail>, COATING_DETAIL_STRINGIFIED,
                          ({{"", CoatingDetail::NoCoatingDetail},
                            {"Cast", CoatingDetail::CastCoating},
                            {"ProFIT:Full", CoatingDetail::ProfitFullCoating},
                            {"ProFIT:Spot", CoatingDetail::ProfitSpotCoating}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<LaminatingSurface>, LAMINATING_SURFACE_STRINGIFIED,
                          ({{"Front", LaminatingSurface::FrontLaminated},
                            {"Back", LaminatingSurface::BackLaminated},
                            {"Both", LaminatingSurface::BothLaminated}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<BundleType>, BUNDLE_TYPE_STRINGIFIED,
                          ({{"BoundSet", BundleType::BoundSetBundle},
                            {"Box", BundleType::BoxBundle},
                            {"Carton", BundleType::CartonBundle},
                            {"CollectedStack", BundleType::CollectedStackBundle},
                            {"CompensatedStack", BundleType::CompensatedStackBundle},
                            {"Pallet", BundleType::PalletBundle},
                            {"Roll", BundleType::RollBundle},
                            {"Sheet", BundleType::SheetBundle},
                            {"Stack", BundleType::StackBundle},
                            {"StrappedStack", BundleType::StrappedStackBundle},
                            {"StrappedCompensatedStack", BundleType::StrappedCompensatedStackBundle},
                            {"WrappedBundle", BundleType::WrappedBundle}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<ResourceOrientation>, RESOURCE_ORIENTATION_STRINGIFIED,
                          ({{"Rotate0", ResourceOrientation::Rotate0Orientation},
                            {"Rotate90", ResourceOrientation::Rotate90Orientation},
                            {"Rotate180", ResourceOrientation::Rotate180Orientation},
                            {"Rotate270", ResourceOrientation::Rotate270Orientation},

                            {"Flip0", ResourceOrientation::Flip0Orientation},
                            {"Flip90", ResourceOrientation::Flip90Orientation},
                            {"Flip180", ResourceOrientation::Flip180Orientation},
                            {"Flip270", ResourceOrientation::Flip270Orientation}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(IntDict<ResourceOrientation>, RESOURCE_ROTATE_NUMERICAL,
                          ({
                              {0, ResourceOrientation::Rotate0Orientation},
                              {90, ResourceOrientation::Rotate90Orientation},
                              {180, ResourceOrientation::Rotate180Orientation},
                              {270, ResourceOrientation::Rotate270Orientation},
                          }))
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(IntDict<ResourceOrientation>, RESOURCE_FLIP_NUMERICAL,
                          ({{0, ResourceOrientation::Flip0Orientation},
                            {90, ResourceOrientation::Flip90Orientation},
                            {180, ResourceOrientation::Flip180Orientation},
                            {270, ResourceOrientation::Flip270Orientation}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<ComponentType>, COMPONENT_TYPE_STRINGIFIED,
                          ({{"", ComponentType::NotTypedComponent},
                            {"Block", ComponentType::BlockComponent},
                            {"Other", ComponentType::OtherComponent},
                            {"Ribbon", ComponentType::RibbonComponent},
                            {"Sheet", ComponentType::SheetComponent},
                            {"Web", ComponentType::WebComponent},
                            {"FinalProduct", ComponentType::FinalProductComponent},
                            {"PartialProduct", ComponentType::PartialProductComponent},
                            {"Proof", ComponentType::ProofComponent}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<ProductType>, PRODUCT_TYPE_STRINGIFIED,
                          ({{"", ProductType::NoProduct},
                            {"BackCover", ProductType::BackCoverProduct},
                            {"BlankBox", ProductType::BlankBoxProduct},
                            {"BlankSheet", ProductType::BlankSheetProduct},
                            {"BlankWeb", ProductType::BlankWebProduct},
                            {"Body", ProductType::BodyProduct},
                            {"Book", ProductType::BookProduct},
                            {"BookBlock", ProductType::BookBlockProduct},
                            {"BookCase", ProductType::BookCaseProduct},
                            {"Box", ProductType::BoxProduct},
                            {"Brochure", ProductType::BrochureProduct},
                            {"BusinessCard", ProductType::BusinessCardProduct},
                            {"Carton", ProductType::CartonProduct},
                            {"Cover", ProductType::CoverProduct},
                            {"EndSheet", ProductType::EndSheetProduct},
                            {"FlatBox", ProductType::FlatBoxProduct},
                            {"FlatWork", ProductType::FlatWorkProduct},
                            {"FrontCover", ProductType::FrontCoverProduct},
                            {"Insert", ProductType::InsertProduct},
                            {"Jacket", ProductType::JacketProduct},
                            {"Label", ProductType::LabelProduct},
                            {"Newspaper", ProductType::NewspaperProduct},
                            {"Pallet", ProductType::PalletProduct},
                            {"Poster", ProductType::PosterProduct},
                            {"Stack", ProductType::StackProduct}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<ResourcePartType>, PART_ID_KEYS_TYPE_STRINGIFIED,
                          ({{"BinderySignatureName", ResourcePartType::BinderySignatureNamePart},
                            {"BinderySignaturePaginationIndex", ResourcePartType::BinderySignaturePaginationIndexPart},
                            {"BlockName", ResourcePartType::BlockNamePart},
                            {"BundleItemIndex", ResourcePartType::BundleItemIndexPart},
                            {"CellIndex", ResourcePartType::CellIndexPart},
                            {"Condition", ResourcePartType::ConditionPart},
                            {"DeliveryUnit0", ResourcePartType::DeliveryUnit0Part},
                            {"DeliveryUnit1", ResourcePartType::DeliveryUnit1Part},
                            {"DeliveryUnit2", ResourcePartType::DeliveryUnit2Part},
                            {"DeliveryUnit3", ResourcePartType::DeliveryUnit3Part},
                            {"DeliveryUnit4", ResourcePartType::DeliveryUnit4Part},
                            {"DeliveryUnit5", ResourcePartType::DeliveryUnit5Part},
                            {"DeliveryUnit6", ResourcePartType::DeliveryUnit6Part},
                            {"DeliveryUnit7", ResourcePartType::DeliveryUnit7Part},
                            {"DeliveryUnit8", ResourcePartType::DeliveryUnit8Part},
                            {"DeliveryUnit9", ResourcePartType::DeliveryUnit9Part},
                            {"DocCopies", ResourcePartType::DocCopiesPart},
                            {"DocIndex", ResourcePartType::DocIndexPart},
                            {"DocRunIndex", ResourcePartType::DocRunIndexPart},
                            {"DocSheetIndex", ResourcePartType::DocSheetIndexPart},
                            {"DocTags", ResourcePartType::DocTagsPart},
                            {"Edition", ResourcePartType::EditionPart},
                            {"EditionVersion", ResourcePartType::EditionVersionPart},
                            {"FountainNumber", ResourcePartType::FountainNumberPart},
                            {"ItemNames", ResourcePartType::ItemNamesPart},
                            {"LayerIDs", ResourcePartType::LayerIdsPart},
                            {"Location", ResourcePartType::LocationPart},
                            {"Metadata0", ResourcePartType::Metadata0Part},
                            {"Metadata1", ResourcePartType::Metadata1Part},
                            {"Metadata2", ResourcePartType::Metadata2Part},
                            {"Metadata3", ResourcePartType::Metadata3Part},
                            {"Metadata4", ResourcePartType::Metadata4Part},
                            {"Metadata5", ResourcePartType::Metadata5Part},
                            {"Metadata6", ResourcePartType::Metadata6Part},
                            {"Metadata7", ResourcePartType::Metadata7Part},
                            {"Metadata8", ResourcePartType::Metadata8Part},
                            {"Metadata9", ResourcePartType::Metadata9Part},
                            {"Option", ResourcePartType::OptionPart},
                            {"PageNumber", ResourcePartType::PageNumberPart},
                            {"PageTags", ResourcePartType::PageTagsPart},
                            {"PartVersion", ResourcePartType::PartVersionPart},
                            {"PlateLayout", ResourcePartType::PlateLayoutPart},
                            {"PreflightRule", ResourcePartType::PreflightRulePart},
                            {"PreviewType", ResourcePartType::PreviewTypePart},
                            {"RibbonName", ResourcePartType::RibbonNamePart},
                            {"Run", ResourcePartType::RunPart},
                            {"RunIndex", ResourcePartType::RunIndexPart},
                            {"RunPage", ResourcePartType::RunPagePart},
                            {"RunPageRange", ResourcePartType::RunPageRangePart},
                            {"RunSet", ResourcePartType::RunSetPart},
                            {"RunTags", ResourcePartType::RunTagsPart},
                            {"SectionIndex", ResourcePartType::SectionIndexPart},
                            {"Separation", ResourcePartType::SeparationPart},
                            {"SetDocIndex", ResourcePartType::SetDocIndexPart},
                            {"SetIndex", ResourcePartType::SetIndexPart},
                            {"SetRunIndex", ResourcePartType::SetRunIndexPart},
                            {"SetSheetIndex", ResourcePartType::SetSheetIndexPart},
                            {"SetTags", ResourcePartType::SetTagsPart},
                            {"SheetIndex", ResourcePartType::SheetIndexPart},
                            {"SheetName", ResourcePartType::SheetNamePart},
                            {"Side", ResourcePartType::SidePart},
                            {"SignatureName", ResourcePartType::SignatureNamePart},
                            {"StationName", ResourcePartType::StationNamePart},
                            {"SubRun", ResourcePartType::SubRunPart},
                            {"TileID", ResourcePartType::TileIdPart},
                            {"WebName", ResourcePartType::WebNamePart},
                            {"WebProduct", ResourcePartType::WebProductPart},
                            {"WebSetup", ResourcePartType::WebSetupPart}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<LinkUsage>, LINK_USAGE_STRINGIFIED,
                          ({{"Input", LinkUsage::InputLink}, {"Output", LinkUsage::OutputLink}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<ProcessUsage>, PROCESS_USAGE_STRINGIFIED,
                          ({{"", ProcessUsage::UseAsDefault},
                            {"Accepted", ProcessUsage::UseAsAccepted},
                            {"Application", ProcessUsage::UseAsApplication},
                            {"BackEndSheet", ProcessUsage::UseAsBackEndSheet},
                            {"Book", ProcessUsage::UseAsBook},
                            {"BookBlock", ProcessUsage::UseAsBookBlock},
                            {"Box", ProcessUsage::UseAsBox},
                            {"Case", ProcessUsage::UseAsCase},
                            {"Child", ProcessUsage::UseAsChild},
                            {"Cover", ProcessUsage::UseAsCover},
                            {"CoverBoard", ProcessUsage::UseAsCoverBoard},
                            {"CoverMaterial", ProcessUsage::UseAsCoverMaterial},
                            {"Cylinder", ProcessUsage::UseAsCylinder},
                            {"Document", ProcessUsage::UseAsDocument},
                            {"FrontEndSheet", ProcessUsage::UseAsFrontEndSheet},
                            {"Good", ProcessUsage::UseAsGood},
                            {"Input", ProcessUsage::UseAsInput},
                            {"Jacket", ProcessUsage::UseAsJacket},
                            {"Label", ProcessUsage::UseAsLabel},
                            {"Marks", ProcessUsage::UseAsMarks},
                            {"Mother", ProcessUsage::UseAsMother},
                            {"Plate", ProcessUsage::UseAsPlate},
                            {"Proof", ProcessUsage::UseAsProof},
                            {"Rejected", ProcessUsage::UseAsRejected},
                            {"RingBinder", ProcessUsage::UseAsRingBinder},
                            {"SpineBoard", ProcessUsage::UseAsSpineBoard},
                            {"Surface", ProcessUsage::UseAsSurface},
                            {"Tie", ProcessUsage::UseAsTie},
                            {"Underlay", ProcessUsage::UseAsUnderlay},
                            {"Waste", ProcessUsage::UseAsWaste}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<BlockType>, BLOCK_TYPE_STRINGIFIED,
                          ({{"CutBlock", BlockType::CutBlock},
                            {"SaveBlock", BlockType::SaveBlock},
                            {"TempBlock", BlockType::TempBlock},
                            {"MarkBlock", BlockType::MarkBlock}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<MediaUnit>, MEDIA_UNIT_STRINGIFIED,
                          ({{"Continuous", MediaUnit::ContinuousMediaUnit},
                            {"Roll", MediaUnit::RollMediaUnit},
                            {"Sheet", MediaUnit::SheetMediaUnit}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<MediaType>, MEDIA_TYPE_STRINGIFIED,
                          ({{"CorrugatedBoard", MediaType::CorrugatedBoardMedia},
                            {"Disc", MediaType::DiscMedia},
                            {"EndBoard", MediaType::EndBoardMedia},
                            {"EmbossingFoil", MediaType::EmbossingFoilMedia},
                            {"Film", MediaType::FilmMedia},
                            {"Foil", MediaType::FoilMedia},
                            {"GravureCylinder", MediaType::GravureCylinderMedia},
                            {"ImagingCylinder", MediaType::ImagingCylinderMedia},
                            {"LaminatingFoil", MediaType::LaminatingFoilMedia},
                            {"MountingTape", MediaType::MountingTapeMedia},
                            {"Paper", MediaType::PaperMedia},
                            {"Plate", MediaType::PlateMedia},
                            {"Screen", MediaType::ScreenMedia},
                            {"SelfAdhesive", MediaType::SelfAdhesiveMedia},
                            {"Sleeve", MediaType::SleeveMedia},
                            {"ShrinkFoil", MediaType::ShrinkFoilMedia},
                            {"Textile", MediaType::TextileMedia},
                            {"Other", MediaType::OtherMedia},
                            {"Vinyl", MediaType::VinylMedia}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<DeviceFilterDetails>, DEVICE_FILTER_DETAILS_STRINGIFIED,
                          ({{"None", DeviceFilterDetails::NoneDeviceFilterDetails},
                            {"Brief", DeviceFilterDetails::BriefDeviceFilterDetails},
                            {"Module", DeviceFilterDetails::ModulesDeviceFilterDetails},
                            {"Details", DeviceFilterDetails::DetailsDeviceFilterDetails},
                            {"NamedFeature", DeviceFilterDetails::NamedFeatureDeviceFilterDetails},
                            {"Capability", DeviceFilterDetails::CapabilityDeviceFilterDetails},
                            {"Full", DeviceFilterDetails::FullDeviceFilterDetails}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<DeviceStatus>, DEVICE_STATUS_STRINGIFIED,
                          ({{"Unknown", DeviceStatus::UnknownDeviceStatus},
                            {"Idle", DeviceStatus::IdleDeviceStatus},
                            {"Down", DeviceStatus::DownDeviceStatus},
                            {"Setup", DeviceStatus::SetupDeviceStatus},
                            {"Running", DeviceStatus::RunningDeviceStatus},
                            {"Cleanup", DeviceStatus::CleanupDeviceStatus},
                            {"Stopped", DeviceStatus::StoppedDeviceStatus}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<DeviceCondition>, DEVICE_CONDITION_STRINGIFIED,
                          ({{"OK", DeviceCondition::OkDeviceCondition},
                            {"NeedsAttention", DeviceCondition::NeedsAttentionDeviceCondition},
                            {"Failure", DeviceCondition::FailureDeviceCondition},
                            {"OffLine", DeviceCondition::OffLineDeviceCondition}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<NotificationClass>, NOTIFICATION_CLASS_STRINGIFIED,
                          ({{"Event", NotificationClass::EventNotificationClass},
                            {"Information", NotificationClass::InformationNotificationClass},
                            {"Warning", NotificationClass::WarningNotificationClass},
                            {"Error", NotificationClass::ErrorNotificationClass},
                            {"Fatal", NotificationClass::FatalNotificationClass}}))

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
Q_GLOBAL_STATIC_WITH_ARGS(StringDict<SpanDataType>, SPAN_DATA_TYPE_STRINGIFIED,
                          ({{"DurationSpan", SpanDataType::DurationSpan},
                            {"EnumerationSpan", SpanDataType::EnumerationSpan},
                            {"IntegerSpan", SpanDataType::IntegerSpan},
                            {"NameSpan", SpanDataType::NameSpan},
                            {"NumberSpan", SpanDataType::NumberSpan},
                            {"OptionSpan", SpanDataType::OptionSpan},
                            {"ShapeSpan", SpanDataType::ShapeSpan},
                            {"StringSpan", SpanDataType::StringSpan},
                            {"TimeSpan", SpanDataType::TimeSpan},
                            {"XYPairSpan", SpanDataType::XYPairSpan}}))

QString resourceStatusToString(ResourceStatus status)
{
    return RESOURCE_STATUS_STRINGIFIED->key(status, QString());
}

ResourceStatus resourceStatusFromString(const QString &status)
{
    return RESOURCE_STATUS_STRINGIFIED->value(status, ResourceStatus::NoStatus);
}

QString resourceClassToString(ResourceClass resourceClass)
{
    return RESOURCE_CLASS_STRINGIFIED->key(resourceClass, QString());
}

ResourceClass resourceClassFromString(const QString &resourceClass)
{
    return RESOURCE_CLASS_STRINGIFIED->value(resourceClass, ResourceClass::NoClass);
}

QString coatingToString(CoatingType coating)
{
    return COATING_STRINGIFIED->key(coating, QString());
}

CoatingType coatingFromString(const QString &coating)
{
    return COATING_STRINGIFIED->value(coating, CoatingType::NoCoating);
}

QString coatingDetailToString(CoatingDetail coatingDetail)
{
    return COATING_DETAIL_STRINGIFIED->key(coatingDetail, QString());
}

CoatingDetail coatingDetailFromString(const QString &coatingDetail)
{
    return COATING_DETAIL_STRINGIFIED->value(coatingDetail, CoatingDetail::NoCoatingDetail);
}

QString laminatingSurfaceToString(LaminatingSurface surface)
{
    return LAMINATING_SURFACE_STRINGIFIED->key(surface, QString());
}

LaminatingSurface laminatingSurfaceFromString(const QString &surface)
{
    return LAMINATING_SURFACE_STRINGIFIED->value(surface, LaminatingSurface::NoneLaminated);
}

QString bundleTypeToString(BundleType bundleType)
{
    return BUNDLE_TYPE_STRINGIFIED->key(bundleType, QString());
}

BundleType bundleTypeFromString(const QString &bundleType)
{
    return BUNDLE_TYPE_STRINGIFIED->value(bundleType, BundleType::BoxBundle);
}

QString resourceOrientationToString(ResourceOrientation resourceOrientation)
{
    return RESOURCE_ORIENTATION_STRINGIFIED->key(resourceOrientation, QString());
}

ResourceOrientation resourceOrientationFromString(const QString &resourceOrientation)
{
    return RESOURCE_ORIENTATION_STRINGIFIED->value(resourceOrientation, ResourceOrientation::Rotate0Orientation);
}

int resourceRotateToInt(ResourceOrientation resourceOrientation)
{
    return RESOURCE_ROTATE_NUMERICAL->key(resourceOrientation, 0);
}

ResourceOrientation resourceRotateFromInt(int resourceRotate)
{
    return RESOURCE_ROTATE_NUMERICAL->value(resourceRotate, ResourceOrientation::Rotate0Orientation);
}

int resourceFlipToInt(ResourceOrientation resourceOrientation)
{
    return RESOURCE_FLIP_NUMERICAL->key(resourceOrientation, 0);
}

ResourceOrientation resourceFlipFromInt(int resourceFlip)
{
    return RESOURCE_FLIP_NUMERICAL->value(resourceFlip, ResourceOrientation::Flip0Orientation);
}

QString componentTypeToString(ComponentType componentType)
{
    return COMPONENT_TYPE_STRINGIFIED->key(componentType, QString());
}

ComponentType componentTypeFromString(const QString &componentType)
{
    return COMPONENT_TYPE_STRINGIFIED->value(componentType, ComponentType::NotTypedComponent);
}

QString productTypeToString(ProductType productType)
{
    return PRODUCT_TYPE_STRINGIFIED->key(productType, QString());
}

ProductType productTypeFromString(const QString &productType)
{
    return PRODUCT_TYPE_STRINGIFIED->value(productType, ProductType::NoProduct);
}

QString resourcePartTypeToString(ResourcePartType resourcePartType)
{
    return PART_ID_KEYS_TYPE_STRINGIFIED->key(resourcePartType, QString());
}

ResourcePartType resourcePartTypeFromString(const QString &resourcePartType)
{
    return PART_ID_KEYS_TYPE_STRINGIFIED->value(resourcePartType, ResourcePartType::UnknownPart);
}

QString linkUsageToString(LinkUsage usage)
{
    return LINK_USAGE_STRINGIFIED->key(usage, QString());
}

LinkUsage linkUsageFromString(const QString &usage)
{
    return LINK_USAGE_STRINGIFIED->value(usage, LinkUsage::InputLink);
}

QString processUsageToString(ProcessUsage processUsage)
{
    return PROCESS_USAGE_STRINGIFIED->key(processUsage, QString());
}

ProcessUsage processUsageFromString(const QString &processUsage)
{
    return PROCESS_USAGE_STRINGIFIED->value(processUsage, ProcessUsage::UseAsDefault);
}

QString blockTypeToString(BlockType blockType)
{
    return BLOCK_TYPE_STRINGIFIED->key(blockType, QString());
}

BlockType blockTypeFromString(const QString &blockType)
{
    return BLOCK_TYPE_STRINGIFIED->value(blockType, BlockType::CutBlock);
}

QString mediaUnitToString(MediaUnit mediaUnit)
{
    return MEDIA_UNIT_STRINGIFIED->key(mediaUnit, QString());
}

MediaUnit mediaUnitFromString(const QString &mediaUnit)
{
    return MEDIA_UNIT_STRINGIFIED->value(mediaUnit, MediaUnit::SheetMediaUnit);
}

QString mediaTypeToString(MediaType mediaType)
{
    return MEDIA_TYPE_STRINGIFIED->key(mediaType, QString());
}

MediaType mediaTypeFromString(const QString &mediaType)
{
    return MEDIA_TYPE_STRINGIFIED->value(mediaType, MediaType::OtherMedia);
}

QString deviceFilterDetailsToString(DeviceFilterDetails details)
{
    return DEVICE_FILTER_DETAILS_STRINGIFIED->key(details, QString());
}

DeviceFilterDetails deviceFilterDetailsFromString(const QString &details)
{
    return DEVICE_FILTER_DETAILS_STRINGIFIED->value(details, DeviceFilterDetails::NoneDeviceFilterDetails);
}

QString deviceStatusToString(DeviceStatus status)
{
    return DEVICE_STATUS_STRINGIFIED->key(status, QString());
}

DeviceStatus deviceStatusFromString(const QString &status)
{
    return DEVICE_STATUS_STRINGIFIED->value(status, DeviceStatus::UnknownDeviceStatus);
}

QString deviceConditionToString(DeviceCondition condition)
{
    return DEVICE_CONDITION_STRINGIFIED->key(condition, QString());
}

DeviceCondition deviceConditionFromString(const QString &condition)
{
    return DEVICE_CONDITION_STRINGIFIED->value(condition, DeviceCondition::OkDeviceCondition);
}

QString notificationClassToString(NotificationClass notification)
{
    return NOTIFICATION_CLASS_STRINGIFIED->key(notification, QString());
}

NotificationClass notificationClassFromString(const QString &notification)
{
    return NOTIFICATION_CLASS_STRINGIFIED->value(notification, NotificationClass::EventNotificationClass);
}

QString spanDataTypeToString(SpanDataType dataType)
{
    return SPAN_DATA_TYPE_STRINGIFIED->key(dataType, QString());
}

SpanDataType spanDataTypeFromString(const QString &dataType)
{
    return SPAN_DATA_TYPE_STRINGIFIED->value(dataType, SpanDataType::DurationSpan);
}

} // namespace Jdf
} // namespace Proof
