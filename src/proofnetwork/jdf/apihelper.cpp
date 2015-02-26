#include "apihelper.h"

namespace Proof {
namespace Jdf {

QHash<QString, ApiHelper::Coating> ApiHelper::m_coatingStringified = {
    {"None", ApiHelper::Coating::None},
    {"Glossy", ApiHelper::Coating::Glossy},
    {"Coated", ApiHelper::Coating::Coated},
    {"HighGloss", ApiHelper::Coating::HighGloss},
    {"InkJet", ApiHelper::Coating::InkJet},
    {"Matte", ApiHelper::Coating::Matte},
    {"Polymer", ApiHelper::Coating::Polymer},
    {"Silver", ApiHelper::Coating::Silver},
    {"Satin", ApiHelper::Coating::Satin},
    {"Semigloss", ApiHelper::Coating::Semigloss}
};

QString ApiHelper::coatingToString(ApiHelper::Coating coating)
{
    return m_coatingStringified.key(coating, "");
}

ApiHelper::Coating ApiHelper::coatingFromString(const QString &coating)
{
    return m_coatingStringified.value(coating, Coating::None);
}

}
}
