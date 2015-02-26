#include "apihelper.h"

namespace Proof {
namespace Jdf {

QHash<Coating, QString> ApiHelper::m_coatingStringified = {
    {ApiHelper::Coating::None, "None"},
    {ApiHelper::Coating::Glossy, "Glossy"},
    {ApiHelper::Coating::Coated, "Coated"},
    {ApiHelper::Coating::HighGloss, "HighGloss"},
    {ApiHelper::Coating::InkJet, "InkJet"},
    {ApiHelper::Coating::Matte, "Matte"},
    {ApiHelper::Coating::Polymer, "Polymer"},
    {ApiHelper::Coating::Silver, "Silver"},
    {ApiHelper::Coating::Satin, "Satin"},
    {ApiHelper::Coating::Semigloss, "Semigloss"}
};

QString ApiHelper::coatingToString(ApiHelper::Coating coating)
{
    return m_coatingStringified.value(coating, "");
}

ApiHelper::Coating ApiHelper::coatingFromString(const QString &coating)
{
    return m_coatingStringified.key(coating, Coating::None);
}

} // namespace Jdf
} // namespace Proof
