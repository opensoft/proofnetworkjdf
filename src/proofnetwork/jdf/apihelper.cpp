#include "apihelper.h"

#include <QHash>

using namespace Proof::Jdf;

static const QHash<QString, ApiHelper::ResourceStatus> RESOURCE_STATUS_STRINGIFIED = {
    {"Incomplete", ApiHelper::ResourceStatus::IncompleteStatus},
    {"Rejected", ApiHelper::ResourceStatus::RejectedStatus},
    {"Unavailable", ApiHelper::ResourceStatus::UnavailableStatus},
    {"InUse", ApiHelper::ResourceStatus::InUseStatus},
    {"Draft", ApiHelper::ResourceStatus::DraftStatus},
    {"Complete", ApiHelper::ResourceStatus::CompleteStatus},
    {"Available", ApiHelper::ResourceStatus::AvailableStatus}
};

static const QHash<QString, ApiHelper::ResourceClass> RESOURCE_CLASS_STRINGIFIED = {
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

static const QHash<QString, ApiHelper::ComponentType> COMPONENT_TYPE_STRINGIFIED = {
    {"Block", ApiHelper::ComponentType::BlockComponent},
    {"Other", ApiHelper::ComponentType::OtherComponent},
    {"Ribbon", ApiHelper::ComponentType::RibbonComponent},
    {"Sheet", ApiHelper::ComponentType::SheetComponent},
    {"Web", ApiHelper::ComponentType::WebComponent},
    {"FinalProduct", ApiHelper::ComponentType::FinalProductComponent},
    {"PartialProduct", ApiHelper::ComponentType::PartialProductComponent},
    {"Proof", ApiHelper::ComponentType::ProofComponent}
};

static const QHash<QString, ApiHelper::PartIdKeysType> PART_ID_KEYS_TYPE_STRINGIFIED = {
    {"BlockName", ApiHelper::PartIdKeysType::BlockNameKey},
    {"BundleItemIndex", ApiHelper::PartIdKeysType::BundleItemIndexKey},
    {"CellIndex", ApiHelper::PartIdKeysType::CellIndexKey}
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

QString ApiHelper::resourceStatusToString(ApiHelper::ResourceStatus status)
{
    return RESOURCE_STATUS_STRINGIFIED.key(status, "");
}

ApiHelper::ResourceStatus ApiHelper::resourceStatusFromString(const QString &status, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_STATUS_STRINGIFIED.contains(status);
    return RESOURCE_STATUS_STRINGIFIED.value(status, ResourceStatus::IncompleteStatus);
}

QString ApiHelper::resourceClassToString(ApiHelper::ResourceClass resourceClass)
{
    return RESOURCE_CLASS_STRINGIFIED.key(resourceClass, "");
}

ApiHelper::ResourceClass ApiHelper::resourceClassFromString(const QString &resourceClass, bool *ok)
{
    if (ok != nullptr)
        *ok = RESOURCE_CLASS_STRINGIFIED.contains(resourceClass);
    return RESOURCE_CLASS_STRINGIFIED.value(resourceClass, ResourceClass::ConsumableClass);
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

QString ApiHelper::componentTypeToString(ApiHelper::ComponentType componentType)
{
    return COMPONENT_TYPE_STRINGIFIED.key(componentType, "");
}

ApiHelper::ComponentType ApiHelper::componentTypeFromString(const QString &componentType, bool *ok)
{
    if (ok != nullptr)
        *ok = COMPONENT_TYPE_STRINGIFIED.contains(componentType);
    return COMPONENT_TYPE_STRINGIFIED.value(componentType, ComponentType::SheetComponent);
}

QString ApiHelper::partIdKeysTypeToString(ApiHelper::PartIdKeysType partIdKeysType)
{
    return PART_ID_KEYS_TYPE_STRINGIFIED.key(partIdKeysType, "");
}

ApiHelper::PartIdKeysType ApiHelper::partIdKeysTypeFromString(const QString &partIdKeysType, bool *ok)
{
    if (ok != nullptr)
        *ok = PART_ID_KEYS_TYPE_STRINGIFIED.contains(partIdKeysType);
    return PART_ID_KEYS_TYPE_STRINGIFIED.value(partIdKeysType, PartIdKeysType::BlockNameKey);
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

uint qHash(ApiHelper::PartIdKeysType arg, uint seed)
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
