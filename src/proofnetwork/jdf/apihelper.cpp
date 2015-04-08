#include "apihelper.h"

using namespace Proof::Jdf;

QHash<QString, ApiHelper::ResourceStatus> ApiHelper::m_resourceStatusStringified = {
    {"Incomplete", ApiHelper::IncompleteStatus},
    {"Rejected", ApiHelper::RejectedStatus},
    {"Unavailable", ApiHelper::UnavailableStatus},
    {"InUse", ApiHelper::InUseStatus},
    {"Draft", ApiHelper::DraftStatus},
    {"Complete", ApiHelper::CompleteStatus},
    {"Available", ApiHelper::AvailableStatus}
};

QHash<QString, ApiHelper::ResourceClass> ApiHelper::m_resourceClassStringified = {
    {"Consumable", ApiHelper::ConsumableClass},
    {"Handling", ApiHelper::HandlingClass},
    {"Implementation", ApiHelper::ImplementationClass},
    {"Intent", ApiHelper::IntentClass},
    {"Parameter", ApiHelper::ParameterClass},
    {"PlaceHolder", ApiHelper::PlaceHolderClass},
    {"Quantity", ApiHelper::QuantityClass}
};

QHash<QString, ApiHelper::CoatingType> ApiHelper::m_coatingStringified = {
    {"None", ApiHelper::NoneCoating},
    {"Coated", ApiHelper::Coated},
    {"Glossy", ApiHelper::GlossyCoating},
    {"HighGloss", ApiHelper::HighGlossCoating},
    {"InkJet", ApiHelper::InkJetCoating},
    {"Matte", ApiHelper::MatteCoating},
    {"Polymer", ApiHelper::PolymerCoating},
    {"Silver", ApiHelper::SilverCoating},
    {"Satin", ApiHelper::SatinCoating},
    {"Semigloss", ApiHelper::SemiglossCoating}
};

QHash<QString, ApiHelper::BundleType> ApiHelper::m_bundleTypeStringified = {
    {"BoundSet", ApiHelper::BoundSetBundle},
    {"Box", ApiHelper::BoxBundle},
    {"Carton", ApiHelper::CartonBundle},
    {"CollectedStack", ApiHelper::CollectedStackBundle},
    {"CompensatedStack", ApiHelper::CompensatedStackBundle},
    {"Pallet", ApiHelper::PalletBundle},
    {"Roll", ApiHelper::RollBundle},
    {"Sheet", ApiHelper::SheetBundle},
    {"Stack", ApiHelper::StackBundle},
    {"StrappedStack", ApiHelper::StrappedStackBundle},
    {"StrappedCompensatedStack", ApiHelper::StrappedCompensatedStackBundle},
    {"WrappedBundle", ApiHelper::WrappedBundle}
};

QHash<QString, ApiHelper::ComponentType> ApiHelper::m_componentTypeStringified = {
    {"Block", ApiHelper::BlockComponent},
    {"Other", ApiHelper::OtherComponent},
    {"Ribbon", ApiHelper::RibbonComponent},
    {"Sheet", ApiHelper::SheetComponent},
    {"Web", ApiHelper::WebComponent},
    {"FinalProduct", ApiHelper::FinalProductComponent},
    {"PartialProduct", ApiHelper::PartialProductComponent},
    {"Proof", ApiHelper::ProofComponent}
};

QHash<QString, ApiHelper::PartIdKeysType> ApiHelper::m_partIdKeysTypeStringified = {
    {"BlockName", ApiHelper::BlockNameKey},
    {"BundleItemIndex", ApiHelper::BundleItemIndexKey},
    {"CellIndex", ApiHelper::CellIndexKey}
};

QHash<QString, ApiHelper::ProcessUsage> ApiHelper::m_processUsageStringified = {
    {"Accepted", ApiHelper::AcceptedProcess},
    {"Application", ApiHelper::ApplicationProcess},
    {"BackEndSheet", ApiHelper::BackEndSheetProcess},
    {"Book", ApiHelper::BookProcess},
    {"BookBlock", ApiHelper::BookBlockProcess},
    {"Box", ApiHelper::BoxProcess},
    {"Case", ApiHelper::CaseProcess},
    {"Child", ApiHelper::ChildProcess},
    {"Cover", ApiHelper::CoverProcess},
    {"CoverBoard", ApiHelper::CoverBoardProcess},
    {"CoverMaterial", ApiHelper::CoverMaterialProcess},
    {"Cylinder", ApiHelper::CylinderProcess},
    {"Document", ApiHelper::DocumentProcess},
    {"FrontEndSheet", ApiHelper::FrontEndSheetProcess},
    {"Good", ApiHelper::GoodProcess},
    {"Input", ApiHelper::InputProcess},
    {"Jacket", ApiHelper::JacketProcess},
    {"Label", ApiHelper::LabelProcess},
    {"Marks", ApiHelper::MarksProcess},
    {"Mother", ApiHelper::MotherProcess},
    {"Plate", ApiHelper::PlateProcess},
    {"Proof", ApiHelper::ProofProcess},
    {"Rejected", ApiHelper::RejectedProcess},
    {"RingBinder", ApiHelper::RingBinderProcess},
    {"SpineBoard", ApiHelper::SpineBoardProcess},
    {"Surface", ApiHelper::SurfaceProcess},
    {"Tie", ApiHelper::TieProcess},
    {"Underlay", ApiHelper::UnderlayProcess},
    {"Waste", ApiHelper::WasteProcess}
};

QHash<QString, ApiHelper::Usage> ApiHelper::m_usageStringified = {
    {"Input", ApiHelper::InputUsage},
    {"Output", ApiHelper::OutputUsage}
};

QHash<QString, ApiHelper::BlockType> ApiHelper::m_blockTypeStringified = {
    {"CutBlock", ApiHelper::CutBlockType},
    {"SaveBlock", ApiHelper::SaveBlockType},
    {"TempBlock", ApiHelper::TempBlockType},
    {"MarkBlock", ApiHelper::MarkBlockType}
};

QString ApiHelper::resourceStatusToString(ApiHelper::ResourceStatus status)
{
    return m_resourceStatusStringified.key(status, "");
}

ApiHelper::ResourceStatus ApiHelper::resourceStatusFromString(const QString &status)
{
    return m_resourceStatusStringified.value(status, ResourceStatus::IncompleteStatus);
}

QString ApiHelper::resourceClassToString(ApiHelper::ResourceClass resourceClass)
{
    return m_resourceClassStringified.key(resourceClass, "");
}

ApiHelper::ResourceClass ApiHelper::resourceClassFromString(const QString &resourceClass)
{
    return m_resourceClassStringified.value(resourceClass, ResourceClass::ConsumableClass);
}

QString ApiHelper::coatingToString(ApiHelper::CoatingType coating)
{
    return m_coatingStringified.key(coating, "");
}

ApiHelper::CoatingType ApiHelper::coatingFromString(const QString &coating)
{
    return m_coatingStringified.value(coating, CoatingType::NoneCoating);
}

QString ApiHelper::bundleTypeToString(ApiHelper::BundleType bundleType)
{
    return m_bundleTypeStringified.key(bundleType, "");
}

ApiHelper::BundleType ApiHelper::bundleTypeFromString(const QString &bundleType)
{
    return m_bundleTypeStringified.value(bundleType, BundleType::BoxBundle);
}

QString ApiHelper::componentTypeToString(ApiHelper::ComponentType componentType)
{
    return m_componentTypeStringified.key(componentType, "");
}

ApiHelper::ComponentType ApiHelper::componentTypeFromString(const QString &componentType)
{
    return m_componentTypeStringified.value(componentType, ComponentType::SheetComponent);
}

QString ApiHelper::partIdKeysTypeToString(ApiHelper::PartIdKeysType partIdKeysType)
{
    return m_partIdKeysTypeStringified.key(partIdKeysType, "");
}

ApiHelper::PartIdKeysType ApiHelper::partIdKeysTypeFromString(const QString &partIdKeysType)
{
    return m_partIdKeysTypeStringified.value(partIdKeysType, PartIdKeysType::BlockNameKey);
}

QString ApiHelper::processUsageToString(ApiHelper::ProcessUsage processUsage)
{
    return m_processUsageStringified.key(processUsage, "");
}

ApiHelper::ProcessUsage ApiHelper::processUsageFromString(const QString &processUsage)
{
    return m_processUsageStringified.value(processUsage, ProcessUsage::InputProcess);
}

QString ApiHelper::usageToString(ApiHelper::Usage usage)
{
    return m_usageStringified.key(usage, "");
}

ApiHelper::Usage ApiHelper::usageFromString(const QString &usage)
{
    return m_usageStringified.value(usage, Usage::InputUsage);
}

QString ApiHelper::blockTypeToString(ApiHelper::BlockType blockType)
{
    return m_blockTypeStringified.key(blockType, "");
}

ApiHelper::BlockType ApiHelper::blockTypeFromString(const QString &blockType)
{
    return m_blockTypeStringified.value(blockType, BlockType::CutBlockType);
}

