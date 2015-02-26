#ifndef JDFAPIHELPER_H
#define JDFAPIHELPER_H

#include "proofcore/proofobject.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QHash>

namespace Proof {
namespace Jdf {

class PROOF_NETWORK_JDF_EXPORT ApiHelper : public ProofObject
{
    Q_OBJECT
    Q_ENUMS(Coating)
public:
    ApiHelper() = delete;

    enum class Coating : int
    {
        None, // No coating.
        Coated, // A coating of a system-specified type. New in JDF 1.2
        Glossy,
        HighGloss,
        InkJet, // A coating intended for use with inkjet technology.
                // Deprecation note: use PrintingTechnology = "InkJet". New in JDF 1.2. Deprecated in JDF 1.4
        Matte,
        Polymer, // Coating for a photo polymer process. New in JDF 1.3
        Silver, // Coating for a silver halide process. New in JDF 1.3
        Satin,
        Semigloss
    };

    static QString coatingToString(Coating coating);

    static Coating coatingFromString(const QString &coating);

private:
    static QHash<QString, Coating> m_coatingStringified;
};

}
}

#endif // PROOF_JDF_APIHELPER_H
