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

static const QHash<QString, ResourceStatus> RESOURCE_STATUS_STRINGIFIED =
    {{"", ResourceStatus::NoStatus},
     {"Incomplete", ResourceStatus::IncompleteStatus},
     {"Rejected", ResourceStatus::RejectedStatus},
     {"Unavailable", ResourceStatus::UnavailableStatus},
     {"InUse", ResourceStatus::InUseStatus},
     {"Draft", ResourceStatus::DraftStatus},
     {"Complete", ResourceStatus::CompleteStatus},
     {"Available", ResourceStatus::AvailableStatus}};

static const QHash<QString, ResourceClass> RESOURCE_CLASS_STRINGIFIED = {{"", ResourceClass::NoClass},
                                                                         {"Consumable", ResourceClass::ConsumableClass},
                                                                         {"Handling", ResourceClass::HandlingClass},
                                                                         {"Implementation",
                                                                          ResourceClass::ImplementationClass},
                                                                         {"Intent", ResourceClass::IntentClass},
                                                                         {"Parameter", ResourceClass::ParameterClass},
                                                                         {"PlaceHolder", ResourceClass::PlaceHolderClass},
                                                                         {"Quantity", ResourceClass::QuantityClass}};

static const QHash<QString, CoatingType> COATING_STRINGIFIED =
    {{"None", CoatingType::NoCoating},         {"Coated", CoatingType::Coated},
     {"Glossy", CoatingType::GlossyCoating},   {"HighGloss", CoatingType::HighGlossCoating},
     {"InkJet", CoatingType::InkJetCoating},   {"Matte", CoatingType::MatteCoating},
     {"Polymer", CoatingType::PolymerCoating}, {"Silver", CoatingType::SilverCoating},
     {"Satin", CoatingType::SatinCoating},     {"Semigloss", CoatingType::SemiglossCoating}};

static const QHash<QString, CoatingDetail> COATING_DETAIL_STRINGIFIED = {{"", CoatingDetail::NoCoatingDetail},
                                                                         {"Cast", CoatingDetail::CastCoating},
                                                                         {"ProFIT:Full", CoatingDetail::ProfitFullCoating},
                                                                         {"ProFIT:Spot",
                                                                          CoatingDetail::ProfitSpotCoating}};

static const QHash<QString, LaminatingSurface> LAMINATING_SURFACE_STRINGIFIED =
    {{"Front", LaminatingSurface::FrontLaminated},
     {"Back", LaminatingSurface::BackLaminated},
     {"Both", LaminatingSurface::BothLaminated}};

static const QHash<QString, BundleType> BUNDLE_TYPE_STRINGIFIED = {{"BoundSet", BundleType::BoundSetBundle},
                                                                   {"Box", BundleType::BoxBundle},
                                                                   {"Carton", BundleType::CartonBundle},
                                                                   {"CollectedStack", BundleType::CollectedStackBundle},
                                                                   {"CompensatedStack",
                                                                    BundleType::CompensatedStackBundle},
                                                                   {"Pallet", BundleType::PalletBundle},
                                                                   {"Roll", BundleType::RollBundle},
                                                                   {"Sheet", BundleType::SheetBundle},
                                                                   {"Stack", BundleType::StackBundle},
                                                                   {"StrappedStack", BundleType::StrappedStackBundle},
                                                                   {"StrappedCompensatedStack",
                                                                    BundleType::StrappedCompensatedStackBundle},
                                                                   {"WrappedBundle", BundleType::WrappedBundle}};

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

static const QHash<QString, ComponentType> COMPONENT_TYPE_STRINGIFIED = {{"", ComponentType::NotTypedComponent},
                                                                         {"Block", ComponentType::BlockComponent},
                                                                         {"Other", ComponentType::OtherComponent},
                                                                         {"Ribbon", ComponentType::RibbonComponent},
                                                                         {"Sheet", ComponentType::SheetComponent},
                                                                         {"Web", ComponentType::WebComponent},
                                                                         {"FinalProduct",
                                                                          ComponentType::FinalProductComponent},
                                                                         {"PartialProduct",
                                                                          ComponentType::PartialProductComponent},
                                                                         {"Proof", ComponentType::ProofComponent}};

static const QHash<QString, ProductType> PRODUCT_TYPE_STRINGIFIED = {{"", ProductType::NoProduct},
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
                                                                     {"Stack", ProductType::StackProduct}};

static const QHash<QString, ResourcePartType> PART_ID_KEYS_TYPE_STRINGIFIED =
    {{"BinderySignatureName", ResourcePartType::BinderySignatureNamePart},
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
     {"WebSetup", ResourcePartType::WebSetupPart}};

static const QHash<QString, LinkUsage> LINK_USAGE_STRINGIFIED = {{"Input", LinkUsage::InputLink},
                                                                 {"Output", LinkUsage::OutputLink}};

static const QHash<QString, ProcessUsage> PROCESS_USAGE_STRINGIFIED = {{"", ProcessUsage::UseAsDefault},
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
                                                                       {"Waste", ProcessUsage::UseAsWaste}};

static const QHash<QString, BlockType> BLOCK_TYPE_STRINGIFIED = {{"CutBlock", BlockType::CutBlock},
                                                                 {"SaveBlock", BlockType::SaveBlock},
                                                                 {"TempBlock", BlockType::TempBlock},
                                                                 {"MarkBlock", BlockType::MarkBlock}};

static const QHash<QString, MediaUnit> MEDIA_UNIT_STRINGIFIED = {{"Continuous", MediaUnit::ContinuousMediaUnit},
                                                                 {"Roll", MediaUnit::RollMediaUnit},
                                                                 {"Sheet", MediaUnit::SheetMediaUnit}};

static const QHash<QString, MediaType> MEDIA_TYPE_STRINGIFIED = {{"CorrugatedBoard", MediaType::CorrugatedBoardMedia},
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
                                                                 {"Vinyl", MediaType::VinylMedia}};

static const QHash<QString, DeviceFilterDetails> DEVICE_FILTER_DETAILS_STRINGIFIED =
    {{"None", DeviceFilterDetails::NoneDeviceFilterDetails},
     {"Brief", DeviceFilterDetails::BriefDeviceFilterDetails},
     {"Module", DeviceFilterDetails::ModulesDeviceFilterDetails},
     {"Details", DeviceFilterDetails::DetailsDeviceFilterDetails},
     {"NamedFeature", DeviceFilterDetails::NamedFeatureDeviceFilterDetails},
     {"Capability", DeviceFilterDetails::CapabilityDeviceFilterDetails},
     {"Full", DeviceFilterDetails::FullDeviceFilterDetails}};

static const QHash<QString, DeviceStatus> DEVICE_STATUS_STRINGIFIED = {{"Unknown", DeviceStatus::UnknownDeviceStatus},
                                                                       {"Idle", DeviceStatus::IdleDeviceStatus},
                                                                       {"Down", DeviceStatus::DownDeviceStatus},
                                                                       {"Setup", DeviceStatus::SetupDeviceStatus},
                                                                       {"Running", DeviceStatus::RunningDeviceStatus},
                                                                       {"Cleanup", DeviceStatus::CleanupDeviceStatus},
                                                                       {"Stopped", DeviceStatus::StoppedDeviceStatus}};

static const QHash<QString, DeviceCondition> DEVICE_CONDITION_STRINGIFIED =
    {{"OK", DeviceCondition::OkDeviceCondition},
     {"NeedsAttention", DeviceCondition::NeedsAttentionDeviceCondition},
     {"Failure", DeviceCondition::FailureDeviceCondition},
     {"OffLine", DeviceCondition::OffLineDeviceCondition}};

static const QHash<QString, NotificationClass> NOTIFICATION_CLASS_STRINGIFIED =
    {{"Event", NotificationClass::EventNotificationClass},
     {"Information", NotificationClass::InformationNotificationClass},
     {"Warning", NotificationClass::WarningNotificationClass},
     {"Error", NotificationClass::ErrorNotificationClass},
     {"Fatal", NotificationClass::FatalNotificationClass}};

static const QHash<QString, SpanDataType> SPAN_DATA_TYPE_STRINGIFIED =
    {{"DurationSpan", SpanDataType::DurationSpan}, {"EnumerationSpan", SpanDataType::EnumerationSpan},
     {"IntegerSpan", SpanDataType::IntegerSpan},   {"NameSpan", SpanDataType::NameSpan},
     {"NumberSpan", SpanDataType::NumberSpan},     {"OptionSpan", SpanDataType::OptionSpan},
     {"ShapeSpan", SpanDataType::ShapeSpan},       {"StringSpan", SpanDataType::StringSpan},
     {"TimeSpan", SpanDataType::TimeSpan},         {"XYPairSpan", SpanDataType::XYPairSpan}};

QString resourceStatusToString(ResourceStatus status)
{
    return RESOURCE_STATUS_STRINGIFIED.key(status, QString());
}

ResourceStatus resourceStatusFromString(const QString &status, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_STATUS_STRINGIFIED.contains(status);
    return RESOURCE_STATUS_STRINGIFIED.value(status, ResourceStatus::NoStatus);
}

QString resourceClassToString(ResourceClass resourceClass)
{
    return RESOURCE_CLASS_STRINGIFIED.key(resourceClass, QString());
}

ResourceClass resourceClassFromString(const QString &resourceClass, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_CLASS_STRINGIFIED.contains(resourceClass);
    return RESOURCE_CLASS_STRINGIFIED.value(resourceClass, ResourceClass::NoClass);
}

QString coatingToString(CoatingType coating)
{
    return COATING_STRINGIFIED.key(coating, QString());
}

CoatingType coatingFromString(const QString &coating, bool *ok)
{
    if (ok != nullptr)
        *ok = COATING_STRINGIFIED.contains(coating);
    return COATING_STRINGIFIED.value(coating, CoatingType::NoCoating);
}

QString coatingDetailToString(CoatingDetail coatingDetail)
{
    return COATING_DETAIL_STRINGIFIED.key(coatingDetail, QString());
}

CoatingDetail coatingDetailFromString(const QString &coatingDetail, bool *ok)
{
    if (ok != nullptr)
        *ok = COATING_DETAIL_STRINGIFIED.contains(coatingDetail);
    return COATING_DETAIL_STRINGIFIED.value(coatingDetail, CoatingDetail::NoCoatingDetail);
}

QString laminatingSurfaceToString(LaminatingSurface surface)
{
    return LAMINATING_SURFACE_STRINGIFIED.key(surface, QString());
}

LaminatingSurface laminatingSurfaceFromString(const QString &surface, bool *ok)
{
    if (ok != nullptr)
        *ok = LAMINATING_SURFACE_STRINGIFIED.contains(surface);
    return LAMINATING_SURFACE_STRINGIFIED.value(surface, LaminatingSurface::NoneLaminated);
}

QString bundleTypeToString(BundleType bundleType)
{
    return BUNDLE_TYPE_STRINGIFIED.key(bundleType, QString());
}

BundleType bundleTypeFromString(const QString &bundleType, bool *ok)
{
    if (ok != nullptr)
        *ok = BUNDLE_TYPE_STRINGIFIED.contains(bundleType);
    return BUNDLE_TYPE_STRINGIFIED.value(bundleType, BundleType::BoxBundle);
}

QString resourceOrientationToString(ResourceOrientation resourceOrientation)
{
    return RESOURCE_ORIENTATION_STRINGIFIED.key(resourceOrientation, QString());
}

ResourceOrientation resourceOrientationFromString(const QString &resourceOrientation, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_ORIENTATION_STRINGIFIED.contains(resourceOrientation);
    return RESOURCE_ORIENTATION_STRINGIFIED.value(resourceOrientation, ResourceOrientation::Rotate0Orientation);
}

int resourceRotateToInt(ResourceOrientation resourceOrientation)
{
    return RESOURCE_ROTATE_NUMERICAL.key(resourceOrientation, 0);
}

ResourceOrientation resourceRotateFromInt(int resourceRotate, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_ROTATE_NUMERICAL.contains(resourceRotate);
    return RESOURCE_ROTATE_NUMERICAL.value(resourceRotate, ResourceOrientation::Rotate0Orientation);
}

int resourceFlipToInt(ResourceOrientation resourceOrientation)
{
    return RESOURCE_FLIP_NUMERICAL.key(resourceOrientation, 0);
}

ResourceOrientation resourceFlipFromInt(int resourceFlip, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_FLIP_NUMERICAL.contains(resourceFlip);
    return RESOURCE_FLIP_NUMERICAL.value(resourceFlip, ResourceOrientation::Flip0Orientation);
}

QString componentTypeToString(ComponentType componentType)
{
    return COMPONENT_TYPE_STRINGIFIED.key(componentType, QString());
}

ComponentType componentTypeFromString(const QString &componentType, bool *ok)
{
    if (ok != nullptr)
        *ok = COMPONENT_TYPE_STRINGIFIED.contains(componentType);
    return COMPONENT_TYPE_STRINGIFIED.value(componentType, ComponentType::NotTypedComponent);
}

QString productTypeToString(ProductType productType)
{
    return PRODUCT_TYPE_STRINGIFIED.key(productType, QString());
}

ProductType productTypeFromString(const QString &productType, bool *ok)
{
    if (ok != nullptr)
        *ok = PRODUCT_TYPE_STRINGIFIED.contains(productType);
    return PRODUCT_TYPE_STRINGIFIED.value(productType, ProductType::NoProduct);
}

QString resourcePartTypeToString(ResourcePartType resourcePartType)
{
    return PART_ID_KEYS_TYPE_STRINGIFIED.key(resourcePartType, QString());
}

ResourcePartType resourcePartTypeFromString(const QString &resourcePartType, bool *ok)
{
    if (ok != nullptr)
        *ok = PART_ID_KEYS_TYPE_STRINGIFIED.contains(resourcePartType);
    return PART_ID_KEYS_TYPE_STRINGIFIED.value(resourcePartType, ResourcePartType::BlockNamePart);
}

QString linkUsageToString(LinkUsage usage)
{
    return LINK_USAGE_STRINGIFIED.key(usage, QString());
}

LinkUsage linkUsageFromString(const QString &usage, bool *ok)
{
    if (ok != nullptr)
        *ok = LINK_USAGE_STRINGIFIED.contains(usage);
    return LINK_USAGE_STRINGIFIED.value(usage, LinkUsage::InputLink);
}

QString processUsageToString(ProcessUsage processUsage)
{
    return PROCESS_USAGE_STRINGIFIED.key(processUsage, QString());
}

ProcessUsage processUsageFromString(const QString &processUsage, bool *ok)
{
    if (ok != nullptr)
        *ok = PROCESS_USAGE_STRINGIFIED.contains(processUsage);
    return PROCESS_USAGE_STRINGIFIED.value(processUsage, ProcessUsage::UseAsDefault);
}

QString blockTypeToString(BlockType blockType)
{
    return BLOCK_TYPE_STRINGIFIED.key(blockType, QString());
}

BlockType blockTypeFromString(const QString &blockType, bool *ok)
{
    if (ok != nullptr)
        *ok = BLOCK_TYPE_STRINGIFIED.contains(blockType);
    return BLOCK_TYPE_STRINGIFIED.value(blockType, BlockType::CutBlock);
}

QString mediaUnitToString(MediaUnit mediaUnit)
{
    return MEDIA_UNIT_STRINGIFIED.key(mediaUnit, QString());
}

MediaUnit mediaUnitFromString(const QString &mediaUnit, bool *ok)
{
    if (ok != nullptr)
        *ok = MEDIA_UNIT_STRINGIFIED.contains(mediaUnit);
    return MEDIA_UNIT_STRINGIFIED.value(mediaUnit, MediaUnit::SheetMediaUnit);
}

QString mediaTypeToString(MediaType mediaType)
{
    return MEDIA_TYPE_STRINGIFIED.key(mediaType, QString());
}

MediaType mediaTypeFromString(const QString &mediaType, bool *ok)
{
    if (ok != nullptr)
        *ok = MEDIA_TYPE_STRINGIFIED.contains(mediaType);
    return MEDIA_TYPE_STRINGIFIED.value(mediaType, MediaType::OtherMedia);
}

QString deviceFilterDetailsToString(DeviceFilterDetails details)
{
    return DEVICE_FILTER_DETAILS_STRINGIFIED.key(details, QString());
}

DeviceFilterDetails deviceFilterDetailsFromString(const QString &details, bool *ok)
{
    if (ok != nullptr)
        *ok = DEVICE_FILTER_DETAILS_STRINGIFIED.contains(details);
    return DEVICE_FILTER_DETAILS_STRINGIFIED.value(details, DeviceFilterDetails::NoneDeviceFilterDetails);
}

QString deviceStatusToString(DeviceStatus status)
{
    return DEVICE_STATUS_STRINGIFIED.key(status, QString());
}

DeviceStatus deviceStatusFromString(const QString &status, bool *ok)
{
    if (ok != nullptr)
        *ok = DEVICE_STATUS_STRINGIFIED.contains(status);
    return DEVICE_STATUS_STRINGIFIED.value(status, DeviceStatus::UnknownDeviceStatus);
}

QString deviceConditionToString(DeviceCondition condition)
{
    return DEVICE_CONDITION_STRINGIFIED.key(condition, QString());
}

DeviceCondition deviceConditionFromString(const QString &condition, bool *ok)
{
    if (ok != nullptr)
        *ok = DEVICE_CONDITION_STRINGIFIED.contains(condition);
    return DEVICE_CONDITION_STRINGIFIED.value(condition, DeviceCondition::OkDeviceCondition);
}

QString notificationClassToString(NotificationClass notification)
{
    return NOTIFICATION_CLASS_STRINGIFIED.key(notification, QString());
}

NotificationClass notificationClassFromString(const QString &notification, bool *ok)
{
    if (ok != nullptr)
        *ok = NOTIFICATION_CLASS_STRINGIFIED.contains(notification);
    return NOTIFICATION_CLASS_STRINGIFIED.value(notification, NotificationClass::EventNotificationClass);
}

QString spanDataTypeToString(SpanDataType dataType)
{
    return SPAN_DATA_TYPE_STRINGIFIED.key(dataType, QString());
}

SpanDataType spanDataTypeFromString(const QString &dataType, bool *ok)
{
    if (ok != nullptr)
        *ok = SPAN_DATA_TYPE_STRINGIFIED.contains(dataType);
    return SPAN_DATA_TYPE_STRINGIFIED.value(dataType, SpanDataType::DurationSpan);
}

} // namespace Jdf
} // namespace Proof
