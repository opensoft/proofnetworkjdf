#include "apihelper.h"

#include <QHash>

namespace Proof {
namespace Jdf {

uint qHash(ApiHelper::ResourceStatus arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::ResourceClass arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::CoatingType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::LaminatingSurface arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::BundleType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::ResourceOrientation arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::ComponentType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::ResourcePartType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::ProcessUsage arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::Usage arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::BlockType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::MediaUnit arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::MediaType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::DeviceFilterDetails arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::DeviceStatus arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::NotificationClass arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}

uint qHash(ApiHelper::SpanDataType arg, uint seed)
{
    return ::qHash(static_cast<int>(arg), seed);
}
}
}

using namespace Proof::Jdf;

static const QHash<QString, ApiHelper::ResourceStatus> RESOURCE_STATUS_STRINGIFIED = {
    {"", ApiHelper::ResourceStatus::NoStatus},
    {"Incomplete", ApiHelper::ResourceStatus::IncompleteStatus},
    {"Rejected", ApiHelper::ResourceStatus::RejectedStatus},
    {"Unavailable", ApiHelper::ResourceStatus::UnavailableStatus},
    {"InUse", ApiHelper::ResourceStatus::InUseStatus},
    {"Draft", ApiHelper::ResourceStatus::DraftStatus},
    {"Complete", ApiHelper::ResourceStatus::CompleteStatus},
    {"Available", ApiHelper::ResourceStatus::AvailableStatus}
};

static const QHash<QString, ApiHelper::ResourceClass> RESOURCE_CLASS_STRINGIFIED = {
    {"", ApiHelper::ResourceClass::NoClass},
    {"Consumable", ApiHelper::ResourceClass::ConsumableClass},
    {"Handling", ApiHelper::ResourceClass::HandlingClass},
    {"Implementation", ApiHelper::ResourceClass::ImplementationClass},
    {"Intent", ApiHelper::ResourceClass::IntentClass},
    {"Parameter", ApiHelper::ResourceClass::ParameterClass},
    {"PlaceHolder", ApiHelper::ResourceClass::PlaceHolderClass},
    {"Quantity", ApiHelper::ResourceClass::QuantityClass}
};

static const QHash<QString, ApiHelper::CoatingType> COATING_STRINGIFIED = {
    {"None", ApiHelper::CoatingType::NoneCoating},
    {"Coated", ApiHelper::CoatingType::Coated},
    {"Glossy", ApiHelper::CoatingType::GlossyCoating},
    {"HighGloss", ApiHelper::CoatingType::HighGlossCoating},
    {"InkJet", ApiHelper::CoatingType::InkJetCoating},
    {"Matte", ApiHelper::CoatingType::MatteCoating},
    {"Polymer", ApiHelper::CoatingType::PolymerCoating},
    {"Silver", ApiHelper::CoatingType::SilverCoating},
    {"Satin", ApiHelper::CoatingType::SatinCoating},
    {"Semigloss", ApiHelper::CoatingType::SemiglossCoating}
};

static const QHash<QString, ApiHelper::LaminatingSurface> LAMINATING_SURFACE_STRINGIFIED = {
    {"Front", ApiHelper::LaminatingSurface::Front},
    {"Back", ApiHelper::LaminatingSurface::Back},
    {"Both", ApiHelper::LaminatingSurface::Both}
};

static const QHash<QString, ApiHelper::BundleType> BUNDLE_TYPE_STRINGIFIED = {
    {"BoundSet", ApiHelper::BundleType::BoundSetBundle},
    {"Box", ApiHelper::BundleType::BoxBundle},
    {"Carton", ApiHelper::BundleType::CartonBundle},
    {"CollectedStack", ApiHelper::BundleType::CollectedStackBundle},
    {"CompensatedStack", ApiHelper::BundleType::CompensatedStackBundle},
    {"Pallet", ApiHelper::BundleType::PalletBundle},
    {"Roll", ApiHelper::BundleType::RollBundle},
    {"Sheet", ApiHelper::BundleType::SheetBundle},
    {"Stack", ApiHelper::BundleType::StackBundle},
    {"StrappedStack", ApiHelper::BundleType::StrappedStackBundle},
    {"StrappedCompensatedStack", ApiHelper::BundleType::StrappedCompensatedStackBundle},
    {"WrappedBundle", ApiHelper::BundleType::WrappedBundle}
};

static const QHash<QString, ApiHelper::ResourceOrientation> RESOURCE_ORIENTATION_STRINGIFIED = {
    {"Rotate0", ApiHelper::ResourceOrientation::Rotate0Orientation},
    {"Rotate90", ApiHelper::ResourceOrientation::Rotate90Orientation},
    {"Rotate180", ApiHelper::ResourceOrientation::Rotate180Orientation},
    {"Rotate270", ApiHelper::ResourceOrientation::Rotate270Orientation},

    {"Flip0", ApiHelper::ResourceOrientation::Flip0Orientation},
    {"Flip90", ApiHelper::ResourceOrientation::Flip90Orientation},
    {"Flip180", ApiHelper::ResourceOrientation::Flip180Orientation},
    {"Flip270", ApiHelper::ResourceOrientation::Flip270Orientation}
};

static const QHash<int, ApiHelper::ResourceOrientation> RESOURCE_ROTATE_NUMERICAL = {
    {0, ApiHelper::ResourceOrientation::Rotate0Orientation},
    {90, ApiHelper::ResourceOrientation::Rotate90Orientation},
    {180, ApiHelper::ResourceOrientation::Rotate180Orientation},
    {270, ApiHelper::ResourceOrientation::Rotate270Orientation},
};
static const QHash<int, ApiHelper::ResourceOrientation> RESOURCE_FLIP_NUMERICAL = {
    {0, ApiHelper::ResourceOrientation::Flip0Orientation},
    {90, ApiHelper::ResourceOrientation::Flip90Orientation},
    {180, ApiHelper::ResourceOrientation::Flip180Orientation},
    {270, ApiHelper::ResourceOrientation::Flip270Orientation}
};

static const QHash<QString, ApiHelper::ComponentType> COMPONENT_TYPE_STRINGIFIED = {
    {"", ApiHelper::ComponentType::NotTypedComponent},
    {"Block", ApiHelper::ComponentType::BlockComponent},
    {"Other", ApiHelper::ComponentType::OtherComponent},
    {"Ribbon", ApiHelper::ComponentType::RibbonComponent},
    {"Sheet", ApiHelper::ComponentType::SheetComponent},
    {"Web", ApiHelper::ComponentType::WebComponent},
    {"FinalProduct", ApiHelper::ComponentType::FinalProductComponent},
    {"PartialProduct", ApiHelper::ComponentType::PartialProductComponent},
    {"Proof", ApiHelper::ComponentType::ProofComponent}
};

static const QHash<QString, ApiHelper::ResourcePartType> PART_ID_KEYS_TYPE_STRINGIFIED = {
    {"BinderySignatureName", ApiHelper::ResourcePartType::BinderySignatureNamePart},
    {"BinderySignaturePaginationIndex", ApiHelper::ResourcePartType::BinderySignaturePaginationIndexPart},
    {"BlockName", ApiHelper::ResourcePartType::BlockNamePart},
    {"BundleItemIndex", ApiHelper::ResourcePartType::BundleItemIndexPart},
    {"CellIndex", ApiHelper::ResourcePartType::CellIndexPart},
    {"Condition", ApiHelper::ResourcePartType::ConditionPart},
    {"DeliveryUnit0", ApiHelper::ResourcePartType::DeliveryUnit0Part},
    {"DeliveryUnit1", ApiHelper::ResourcePartType::DeliveryUnit1Part},
    {"DeliveryUnit2", ApiHelper::ResourcePartType::DeliveryUnit2Part},
    {"DeliveryUnit3", ApiHelper::ResourcePartType::DeliveryUnit3Part},
    {"DeliveryUnit4", ApiHelper::ResourcePartType::DeliveryUnit4Part},
    {"DeliveryUnit5", ApiHelper::ResourcePartType::DeliveryUnit5Part},
    {"DeliveryUnit6", ApiHelper::ResourcePartType::DeliveryUnit6Part},
    {"DeliveryUnit7", ApiHelper::ResourcePartType::DeliveryUnit7Part},
    {"DeliveryUnit8", ApiHelper::ResourcePartType::DeliveryUnit8Part},
    {"DeliveryUnit9", ApiHelper::ResourcePartType::DeliveryUnit9Part},
    {"DocCopies", ApiHelper::ResourcePartType::DocCopiesPart},
    {"DocIndex", ApiHelper::ResourcePartType::DocIndexPart},
    {"DocRunIndex", ApiHelper::ResourcePartType::DocRunIndexPart},
    {"DocSheetIndex", ApiHelper::ResourcePartType::DocSheetIndexPart},
    {"DocTags", ApiHelper::ResourcePartType::DocTagsPart},
    {"Edition", ApiHelper::ResourcePartType::EditionPart},
    {"EditionVersion", ApiHelper::ResourcePartType::EditionVersionPart},
    {"FountainNumber", ApiHelper::ResourcePartType::FountainNumberPart},
    {"ItemNames", ApiHelper::ResourcePartType::ItemNamesPart},
    {"LayerIDs", ApiHelper::ResourcePartType::LayerIdsPart},
    {"Location", ApiHelper::ResourcePartType::LocationPart},
    {"Metadata0", ApiHelper::ResourcePartType::Metadata0Part},
    {"Metadata1", ApiHelper::ResourcePartType::Metadata1Part},
    {"Metadata2", ApiHelper::ResourcePartType::Metadata2Part},
    {"Metadata3", ApiHelper::ResourcePartType::Metadata3Part},
    {"Metadata4", ApiHelper::ResourcePartType::Metadata4Part},
    {"Metadata5", ApiHelper::ResourcePartType::Metadata5Part},
    {"Metadata6", ApiHelper::ResourcePartType::Metadata6Part},
    {"Metadata7", ApiHelper::ResourcePartType::Metadata7Part},
    {"Metadata8", ApiHelper::ResourcePartType::Metadata8Part},
    {"Metadata9", ApiHelper::ResourcePartType::Metadata9Part},
    {"Option", ApiHelper::ResourcePartType::OptionPart},
    {"PageNumber", ApiHelper::ResourcePartType::PageNumberPart},
    {"PageTags", ApiHelper::ResourcePartType::PageTagsPart},
    {"PartVersion", ApiHelper::ResourcePartType::PartVersionPart},
    {"PlateLayout", ApiHelper::ResourcePartType::PlateLayoutPart},
    {"PreflightRule", ApiHelper::ResourcePartType::PreflightRulePart},
    {"PreviewType", ApiHelper::ResourcePartType::PreviewTypePart},
    {"RibbonName", ApiHelper::ResourcePartType::RibbonNamePart},
    {"Run", ApiHelper::ResourcePartType::RunPart},
    {"RunIndex", ApiHelper::ResourcePartType::RunIndexPart},
    {"RunPage", ApiHelper::ResourcePartType::RunPagePart},
    {"RunPageRange", ApiHelper::ResourcePartType::RunPageRangePart},
    {"RunSet", ApiHelper::ResourcePartType::RunSetPart},
    {"RunTags", ApiHelper::ResourcePartType::RunTagsPart},
    {"SectionIndex", ApiHelper::ResourcePartType::SectionIndexPart},
    {"Separation", ApiHelper::ResourcePartType::SeparationPart},
    {"SetDocIndex", ApiHelper::ResourcePartType::SetDocIndexPart},
    {"SetIndex", ApiHelper::ResourcePartType::SetIndexPart},
    {"SetRunIndex", ApiHelper::ResourcePartType::SetRunIndexPart},
    {"SetSheetIndex", ApiHelper::ResourcePartType::SetSheetIndexPart},
    {"SetTags", ApiHelper::ResourcePartType::SetTagsPart},
    {"SheetIndex", ApiHelper::ResourcePartType::SheetIndexPart},
    {"SheetName", ApiHelper::ResourcePartType::SheetNamePart},
    {"Side", ApiHelper::ResourcePartType::SidePart},
    {"SignatureName", ApiHelper::ResourcePartType::SignatureNamePart},
    {"StationName", ApiHelper::ResourcePartType::StationNamePart},
    {"SubRun", ApiHelper::ResourcePartType::SubRunPart},
    {"TileID", ApiHelper::ResourcePartType::TileIdPart},
    {"WebName", ApiHelper::ResourcePartType::WebNamePart},
    {"WebProduct", ApiHelper::ResourcePartType::WebProductPart},
    {"WebSetup", ApiHelper::ResourcePartType::WebSetupPart}
};

static const QHash<QString, ApiHelper::ProcessUsage> PROCESS_USAGE_STRINGIFIED = {
    {"Accepted", ApiHelper::ProcessUsage::AcceptedProcess},
    {"Application", ApiHelper::ProcessUsage::ApplicationProcess},
    {"BackEndSheet", ApiHelper::ProcessUsage::BackEndSheetProcess},
    {"Book", ApiHelper::ProcessUsage::BookProcess},
    {"BookBlock", ApiHelper::ProcessUsage::BookBlockProcess},
    {"Box", ApiHelper::ProcessUsage::BoxProcess},
    {"Case", ApiHelper::ProcessUsage::CaseProcess},
    {"Child", ApiHelper::ProcessUsage::ChildProcess},
    {"Cover", ApiHelper::ProcessUsage::CoverProcess},
    {"CoverBoard", ApiHelper::ProcessUsage::CoverBoardProcess},
    {"CoverMaterial", ApiHelper::ProcessUsage::CoverMaterialProcess},
    {"Cylinder", ApiHelper::ProcessUsage::CylinderProcess},
    {"Document", ApiHelper::ProcessUsage::DocumentProcess},
    {"FrontEndSheet", ApiHelper::ProcessUsage::FrontEndSheetProcess},
    {"Good", ApiHelper::ProcessUsage::GoodProcess},
    {"Input", ApiHelper::ProcessUsage::InputProcess},
    {"Jacket", ApiHelper::ProcessUsage::JacketProcess},
    {"Label", ApiHelper::ProcessUsage::LabelProcess},
    {"Marks", ApiHelper::ProcessUsage::MarksProcess},
    {"Mother", ApiHelper::ProcessUsage::MotherProcess},
    {"Plate", ApiHelper::ProcessUsage::PlateProcess},
    {"Proof", ApiHelper::ProcessUsage::ProofProcess},
    {"Rejected", ApiHelper::ProcessUsage::RejectedProcess},
    {"RingBinder", ApiHelper::ProcessUsage::RingBinderProcess},
    {"SpineBoard", ApiHelper::ProcessUsage::SpineBoardProcess},
    {"Surface", ApiHelper::ProcessUsage::SurfaceProcess},
    {"Tie", ApiHelper::ProcessUsage::TieProcess},
    {"Underlay", ApiHelper::ProcessUsage::UnderlayProcess},
    {"Waste", ApiHelper::ProcessUsage::WasteProcess}
};

static const QHash<QString, ApiHelper::Usage> USAGE_STRINGIFIED = {
    {"Input", ApiHelper::Usage::InputUsage},
    {"Output", ApiHelper::Usage::OutputUsage}
};

static const QHash<QString, ApiHelper::BlockType> BLOCK_TYPE_STRINGIFIED = {
    {"CutBlock", ApiHelper::BlockType::CutBlockType},
    {"SaveBlock", ApiHelper::BlockType::SaveBlockType},
    {"TempBlock", ApiHelper::BlockType::TempBlockType},
    {"MarkBlock", ApiHelper::BlockType::MarkBlockType}
};

static const QHash<QString, ApiHelper::MediaUnit> MEDIA_UNIT_STRINGIFIED = {
    {"Continuous", ApiHelper::MediaUnit::ContinuousMediaUnit},
    {"Roll", ApiHelper::MediaUnit::RollMediaUnit},
    {"Sheet", ApiHelper::MediaUnit::SheetMediaUnit}
};

static const QHash<QString, ApiHelper::MediaType> MEDIA_TYPE_STRINGIFIED = {
    {"CorrugatedBoard", ApiHelper::MediaType::CorrugatedBoardMedia},
    {"Disc", ApiHelper::MediaType::DiscMedia},
    {"EndBoard", ApiHelper::MediaType::EndBoardMedia},
    {"EmbossingFoil", ApiHelper::MediaType::EmbossingFoilMedia},
    {"Film", ApiHelper::MediaType::FilmMedia},
    {"Foil", ApiHelper::MediaType::FoilMedia},
    {"GravureCylinder", ApiHelper::MediaType::GravureCylinderMedia},
    {"ImagingCylinder", ApiHelper::MediaType::ImagingCylinderMedia},
    {"LaminatingFoil", ApiHelper::MediaType::LaminatingFoilMedia},
    {"MountingTape", ApiHelper::MediaType::MountingTapeMedia},
    {"Paper", ApiHelper::MediaType::PaperMedia},
    {"Plate", ApiHelper::MediaType::PlateMedia},
    {"Screen", ApiHelper::MediaType::ScreenMedia},
    {"SelfAdhesive", ApiHelper::MediaType::SelfAdhesiveMedia},
    {"Sleeve", ApiHelper::MediaType::SleeveMedia},
    {"ShrinkFoil", ApiHelper::MediaType::ShrinkFoilMedia},
    {"Textile", ApiHelper::MediaType::TextileMedia},
    {"Other", ApiHelper::MediaType::OtherMedia}
};

static const QHash<QString, ApiHelper::DeviceFilterDetails> DEVICE_FILTER_DETAILS_STRINGIFIED = {
    {"None", ApiHelper::DeviceFilterDetails::NoneDeviceFilterDetails},
    {"Brief", ApiHelper::DeviceFilterDetails::BriefDeviceFilterDetails},
    {"Module", ApiHelper::DeviceFilterDetails::ModulesDeviceFilterDetails},
    {"Details", ApiHelper::DeviceFilterDetails::DetailsDeviceFilterDetails},
    {"NamedFeature", ApiHelper::DeviceFilterDetails::NamedFeatureDeviceFilterDetails},
    {"Capability", ApiHelper::DeviceFilterDetails::CapabilityDeviceFilterDetails},
    {"Full", ApiHelper::DeviceFilterDetails::FullDeviceFilterDetails}
};

static const QHash<QString, ApiHelper::DeviceStatus> DEVICE_STATUS_STRINGIFIED = {
    {"Unknown", ApiHelper::DeviceStatus::UnknownDeviceStatus},
    {"Idle", ApiHelper::DeviceStatus::IdleDeviceStatus},
    {"Down", ApiHelper::DeviceStatus::DownDeviceStatus},
    {"Setup", ApiHelper::DeviceStatus::SetupDeviceStatus},
    {"Running", ApiHelper::DeviceStatus::RunningDeviceStatus},
    {"Cleanup", ApiHelper::DeviceStatus::CleanupDeviceStatus},
    {"Stopped", ApiHelper::DeviceStatus::StoppedDeviceStatus}
};

static const QHash<QString, ApiHelper::DeviceCondition> DEVICE_CONDITION_STRINGIFIED = {
    {"OK", ApiHelper::DeviceCondition::OkDeviceCondition},
    {"NeedsAttention", ApiHelper::DeviceCondition::NeedsAttentionDeviceCondition},
    {"Failure", ApiHelper::DeviceCondition::FailureDeviceCondition},
    {"OffLine", ApiHelper::DeviceCondition::OffLineDeviceCondition}
};

static const QHash<QString, ApiHelper::NotificationClass> NOTIFICATION_CLASS_STRINGIFIED = {
    {"Event", ApiHelper::NotificationClass::EventNotificationClass},
    {"Information", ApiHelper::NotificationClass::InformationNotificationClass},
    {"Warning", ApiHelper::NotificationClass::WarningNotificationClass},
    {"Error", ApiHelper::NotificationClass::ErrorNotificationClass},
    {"Fatal", ApiHelper::NotificationClass::FatalNotificationClass}
};

static const QHash<QString, ApiHelper::SpanDataType> SPAN_DATA_TYPE_STRINGIFIED = {
    {"DurationSpan", ApiHelper::SpanDataType::DurationSpan},
    {"EnumerationSpan", ApiHelper::SpanDataType::EnumerationSpan},
    {"IntegerSpan", ApiHelper::SpanDataType::IntegerSpan},
    {"NameSpan", ApiHelper::SpanDataType::NameSpan},
    {"NumberSpan", ApiHelper::SpanDataType::NumberSpan},
    {"OptionSpan", ApiHelper::SpanDataType::OptionSpan},
    {"ShapeSpan", ApiHelper::SpanDataType::ShapeSpan},
    {"StringSpan", ApiHelper::SpanDataType::StringSpan},
    {"TimeSpan", ApiHelper::SpanDataType::TimeSpan},
    {"XYPairSpan", ApiHelper::SpanDataType::XYPairSpan}
};

QString ApiHelper::resourceStatusToString(ApiHelper::ResourceStatus status)
{
    return RESOURCE_STATUS_STRINGIFIED.key(status, "");
}

ApiHelper::ResourceStatus ApiHelper::resourceStatusFromString(const QString &status, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_STATUS_STRINGIFIED.contains(status);
    return RESOURCE_STATUS_STRINGIFIED.value(status, ResourceStatus::NoStatus);
}

QString ApiHelper::resourceClassToString(ApiHelper::ResourceClass resourceClass)
{
    return RESOURCE_CLASS_STRINGIFIED.key(resourceClass, "");
}

ApiHelper::ResourceClass ApiHelper::resourceClassFromString(const QString &resourceClass, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_CLASS_STRINGIFIED.contains(resourceClass);
    return RESOURCE_CLASS_STRINGIFIED.value(resourceClass, ResourceClass::NoClass);
}

QString ApiHelper::coatingToString(ApiHelper::CoatingType coating)
{
    return COATING_STRINGIFIED.key(coating, "");
}

ApiHelper::CoatingType ApiHelper::coatingFromString(const QString &coating, bool *ok)
{
    if (ok != nullptr)
        *ok = COATING_STRINGIFIED.contains(coating);
    return COATING_STRINGIFIED.value(coating, CoatingType::NoneCoating);
}

QString ApiHelper::laminatingSurfaceToString(ApiHelper::LaminatingSurface surface)
{
    return LAMINATING_SURFACE_STRINGIFIED.key(surface, "");
}

ApiHelper::LaminatingSurface ApiHelper::laminatingSurfaceFromString(const QString &surface, bool *ok)
{
    if (ok != nullptr)
        *ok = LAMINATING_SURFACE_STRINGIFIED.contains(surface);
    return LAMINATING_SURFACE_STRINGIFIED.value(surface, LaminatingSurface::None);
}

QString ApiHelper::bundleTypeToString(ApiHelper::BundleType bundleType)
{
    return BUNDLE_TYPE_STRINGIFIED.key(bundleType, "");
}

ApiHelper::BundleType ApiHelper::bundleTypeFromString(const QString &bundleType, bool *ok)
{
    if (ok != nullptr)
        *ok = BUNDLE_TYPE_STRINGIFIED.contains(bundleType);
    return BUNDLE_TYPE_STRINGIFIED.value(bundleType, BundleType::BoxBundle);
}

QString ApiHelper::resourceOrientationToString(ApiHelper::ResourceOrientation resourceOrientation)
{
    return RESOURCE_ORIENTATION_STRINGIFIED.key(resourceOrientation, "");
}

ApiHelper::ResourceOrientation ApiHelper::resourceOrientationFromString(const QString &resourceOrientation, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_ORIENTATION_STRINGIFIED.contains(resourceOrientation);
    return RESOURCE_ORIENTATION_STRINGIFIED.value(resourceOrientation, ResourceOrientation::Rotate0Orientation);
}

int ApiHelper::resourceRotateToInt(ApiHelper::ResourceOrientation resourceOrientation)
{
    return RESOURCE_ROTATE_NUMERICAL.key(resourceOrientation, 0);
}

ApiHelper::ResourceOrientation ApiHelper::resourceRotateFromInt(int resourceRotate, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_ROTATE_NUMERICAL.contains(resourceRotate);
    return RESOURCE_ROTATE_NUMERICAL.value(resourceRotate, ResourceOrientation::Rotate0Orientation);
}

int ApiHelper::resourceFlipToInt(ApiHelper::ResourceOrientation resourceOrientation)
{
    return RESOURCE_FLIP_NUMERICAL.key(resourceOrientation, 0);
}

ApiHelper::ResourceOrientation ApiHelper::resourceFlipFromInt(int resourceFlip, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_FLIP_NUMERICAL.contains(resourceFlip);
    return RESOURCE_FLIP_NUMERICAL.value(resourceFlip, ResourceOrientation::Flip0Orientation);
}

QString ApiHelper::componentTypeToString(ApiHelper::ComponentType componentType)
{
    return COMPONENT_TYPE_STRINGIFIED.key(componentType, "");
}

ApiHelper::ComponentType ApiHelper::componentTypeFromString(const QString &componentType, bool *ok)
{
    if (ok != nullptr)
        *ok = COMPONENT_TYPE_STRINGIFIED.contains(componentType);
    return COMPONENT_TYPE_STRINGIFIED.value(componentType, ComponentType::NotTypedComponent);
}

QString ApiHelper::resourcePartTypeToString(ApiHelper::ResourcePartType resourcePartType)
{
    return PART_ID_KEYS_TYPE_STRINGIFIED.key(resourcePartType, "");
}

ApiHelper::ResourcePartType ApiHelper::resourcePartTypeFromString(const QString &resourcePartType, bool *ok)
{
    if (ok != nullptr)
        *ok = PART_ID_KEYS_TYPE_STRINGIFIED.contains(resourcePartType);
    return PART_ID_KEYS_TYPE_STRINGIFIED.value(resourcePartType, ResourcePartType::BlockNamePart);
}

QString ApiHelper::processUsageToString(ApiHelper::ProcessUsage processUsage)
{
    return PROCESS_USAGE_STRINGIFIED.key(processUsage, "");
}

ApiHelper::ProcessUsage ApiHelper::processUsageFromString(const QString &processUsage, bool *ok)
{
    if (ok != nullptr)
        *ok = PROCESS_USAGE_STRINGIFIED.contains(processUsage);
    return PROCESS_USAGE_STRINGIFIED.value(processUsage, ProcessUsage::InputProcess);
}

QString ApiHelper::usageToString(ApiHelper::Usage usage)
{
    return USAGE_STRINGIFIED.key(usage, "");
}

ApiHelper::Usage ApiHelper::usageFromString(const QString &usage, bool *ok)
{
    if (ok != nullptr)
        *ok = USAGE_STRINGIFIED.contains(usage);
    return USAGE_STRINGIFIED.value(usage, Usage::InputUsage);
}

QString ApiHelper::blockTypeToString(ApiHelper::BlockType blockType)
{
    return BLOCK_TYPE_STRINGIFIED.key(blockType, "");
}

ApiHelper::BlockType ApiHelper::blockTypeFromString(const QString &blockType, bool *ok)
{
    if (ok != nullptr)
        *ok = BLOCK_TYPE_STRINGIFIED.contains(blockType);
    return BLOCK_TYPE_STRINGIFIED.value(blockType, BlockType::CutBlockType);
}

QString ApiHelper::mediaUnitToString(ApiHelper::MediaUnit mediaUnit)
{
    return MEDIA_UNIT_STRINGIFIED.key(mediaUnit, "");
}

ApiHelper::MediaUnit ApiHelper::mediaUnitFromString(const QString &mediaUnit, bool *ok)
{
    if (ok != nullptr)
        *ok = MEDIA_UNIT_STRINGIFIED.contains(mediaUnit);
    return MEDIA_UNIT_STRINGIFIED.value(mediaUnit, MediaUnit::SheetMediaUnit);
}

QString ApiHelper::mediaTypeToString(ApiHelper::MediaType mediaType)
{
    return MEDIA_TYPE_STRINGIFIED.key(mediaType, "");
}

ApiHelper::MediaType ApiHelper::mediaTypeFromString(const QString &mediaType, bool *ok)
{
    if (ok != nullptr)
        *ok = MEDIA_TYPE_STRINGIFIED.contains(mediaType);
    return MEDIA_TYPE_STRINGIFIED.value(mediaType, MediaType::OtherMedia);
}

QString ApiHelper::deviceFilterDetailsToString(ApiHelper::DeviceFilterDetails details)
{
    return DEVICE_FILTER_DETAILS_STRINGIFIED.key(details, "");
}

ApiHelper::DeviceFilterDetails ApiHelper::deviceFilterDetailsFromString(const QString &details, bool *ok)
{
    if (ok != nullptr)
        *ok = DEVICE_FILTER_DETAILS_STRINGIFIED.contains(details);
    return DEVICE_FILTER_DETAILS_STRINGIFIED.value(details, DeviceFilterDetails::NoneDeviceFilterDetails);
}

QString ApiHelper::deviceStatusToString(DeviceStatus status)
{
    return DEVICE_STATUS_STRINGIFIED.key(status, "");
}

ApiHelper::DeviceStatus ApiHelper::deviceStatusFromString(const QString &status, bool *ok)
{
    if (ok != nullptr)
        *ok = DEVICE_STATUS_STRINGIFIED.contains(status);
    return DEVICE_STATUS_STRINGIFIED.value(status, DeviceStatus::UnknownDeviceStatus);
}

QString ApiHelper::deviceConditionToString(DeviceCondition condition)
{
    return DEVICE_CONDITION_STRINGIFIED.key(condition, "");
}

ApiHelper::DeviceCondition ApiHelper::deviceConditionFromString(const QString &condition, bool *ok)
{
    if (ok != nullptr)
        *ok = DEVICE_CONDITION_STRINGIFIED.contains(condition);
    return DEVICE_CONDITION_STRINGIFIED.value(condition, DeviceCondition::OkDeviceCondition);
}

QString ApiHelper::notificationClassToString(NotificationClass notification)
{
    return NOTIFICATION_CLASS_STRINGIFIED.key(notification, "");
}

ApiHelper::NotificationClass ApiHelper::notificationClassFromString(const QString &notification, bool *ok)
{
    if (ok != nullptr)
        *ok = NOTIFICATION_CLASS_STRINGIFIED.contains(notification);
    return NOTIFICATION_CLASS_STRINGIFIED.value(notification, NotificationClass::EventNotificationClass);
}

QString ApiHelper::spanDataTypeToString(ApiHelper::SpanDataType dataType)
{
    return SPAN_DATA_TYPE_STRINGIFIED.key(dataType, "");
}

ApiHelper::SpanDataType ApiHelper::spanDataTypeFromString(const QString &dataType, bool *ok)
{
    if (ok != nullptr)
        *ok = SPAN_DATA_TYPE_STRINGIFIED.contains(dataType);
    return SPAN_DATA_TYPE_STRINGIFIED.value(dataType, SpanDataType::DurationSpan);
}
