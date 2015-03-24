#include "apihelper.h"

namespace Proof {
namespace Jdf {

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

QHash<QString, ApiHelper::Coating> ApiHelper::m_coatingStringified = {
    {"None", ApiHelper::None},
    {"Glossy", ApiHelper::Glossy},
    {"Coated", ApiHelper::Coated},
    {"HighGloss", ApiHelper::HighGloss},
    {"InkJet", ApiHelper::InkJet},
    {"Matte", ApiHelper::Matte},
    {"Polymer", ApiHelper::Polymer},
    {"Silver", ApiHelper::Silver},
    {"Satin", ApiHelper::Satin},
    {"Semigloss", ApiHelper::Semigloss}
};

QHash<QString, ApiHelper::BundleType> ApiHelper::m_bundleTypeStringified = {
    {"BoundSet", ApiHelper::BoundSet},
    {"Box", ApiHelper::Box},
    {"Carton", ApiHelper::Carton},
    {"CollectedStack", ApiHelper::CollectedStack},
    {"CompensatedStack", ApiHelper::CompensatedStack},
    {"Pallet", ApiHelper::Pallet},
    {"Roll", ApiHelper::Roll},
    {"Sheet", ApiHelper::Sheet},
    {"Stack", ApiHelper::Stack},
    {"StrappedStack", ApiHelper::StrappedStack},
    {"StrappedCompensatedStack", ApiHelper::StrappedCompensatedStack},
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

QHash<QString, ApiHelper::PartIDKeysType> ApiHelper::m_partIdKeysTypeStringified = {
    {"BlockName", ApiHelper::BlockName},
    {"BundleItemIndex", ApiHelper::BundleItemIndex},
    {"CellIndex", ApiHelper::CellIndex}
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

QString ApiHelper::coatingToString(ApiHelper::Coating coating)
{
    return m_coatingStringified.key(coating, "");
}

ApiHelper::Coating ApiHelper::coatingFromString(const QString &coating)
{
    return m_coatingStringified.value(coating, Coating::None);
}

QString ApiHelper::bundleTypeToString(ApiHelper::BundleType bundleType)
{
    return m_bundleTypeStringified.key(bundleType, "");
}

ApiHelper::BundleType ApiHelper::bundleTypeFromString(const QString &bundleType)
{
    return m_bundleTypeStringified.value(bundleType, BundleType::Box);
}

QString ApiHelper::componentTypeToString(ApiHelper::ComponentType componentType)
{
    return m_componentTypeStringified.key(componentType, "");
}

ApiHelper::ComponentType ApiHelper::componentTypeFromString(const QString &componentType)
{
    return m_componentTypeStringified.value(componentType, ComponentType::SheetComponent);
}

QString ApiHelper::partIdKeysTypeToString(ApiHelper::PartIDKeysType partIdKeysType)
{
    return m_partIdKeysTypeStringified.key(partIdKeysType, "");
}

ApiHelper::PartIDKeysType ApiHelper::partIdKeysTypeFromString(const QString &partIdKeysType)
{
    return m_partIdKeysTypeStringified.value(partIdKeysType, PartIDKeysType::BlockName);
}

}
}
