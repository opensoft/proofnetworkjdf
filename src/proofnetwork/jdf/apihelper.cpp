#include "apihelper.h"

namespace Proof {
namespace Jdf {

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
