#include "apihelper.h"

namespace Proof {
namespace Jdf {

QString ApiHelper::coatingToString(ApiHelper::Coating coating)
{
    switch (coating) {
    case Coating::None: return QStringLiteral("None");
    case Coating::Coated: return QStringLiteral("Coated");
    case Coating::Glossy: return QStringLiteral("Glossy");
    case Coating::HighGloss: return QStringLiteral("HighGloss");
    case Coating::InkJet: return QStringLiteral("InkJet");
    case Coating::Matte: return QStringLiteral("Matte");
    case Coating::Polymer: return QStringLiteral("Polymer");
    case Coating::Silver: return QStringLiteral("Silver");
    case Coating::Satin: return QStringLiteral("Satin");
    case Coating::Semigloss: return QStringLiteral("Semigloss");
    default: return QString(); // make compiler happy
    }
}

ApiHelper::Coating ApiHelper::coatingFromString(const QString &coating)
{
    if (coating == QStringLiteral("None"))
        return Coating::None;
    else if (coating == QStringLiteral("Coated"))
        return Coating::Coated;
    else if (coating == QStringLiteral("Glossy"))
        return Coating::Glossy;
    else if (coating == QStringLiteral("HighGloss"))
        return Coating::HighGloss;
    else if (coating == QStringLiteral("InkJet"))
        return Coating::InkJet;
    else if (coating == QStringLiteral("Matte"))
        return Coating::Matte;
    else if (coating == QStringLiteral("Polymer"))
        return Coating::Polymer;
    else if (coating == QStringLiteral("Silver"))
        return Coating::Silver;
    else if (coating == QStringLiteral("Satin"))
        return Coating::Satin;
    else if (coating == QStringLiteral("Semigloss"))
        return Coating::Semigloss;
    else // make compiler happy
        return Coating::None;
}

} // namespace Jdf
} // namespace Proof
