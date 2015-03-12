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
    Q_ENUMS(ResourceStatus)
    Q_ENUMS(ResourceClass)
    Q_ENUMS(Coating)
    Q_ENUMS(BundleType)
public:
    ApiHelper() = delete;

    enum ResourceStatus {
        IncompleteStatus, // Indicates that the Resource does not exist, and the metadata is not yet valid.
        RejectedStatus, // Indicates that the Resource has been rejected by an Approval Process. The metadata is valid. New in JDF 1.2
        UnavailableStatus, // Indicates that the Resource is not ready to be used or that the Resource in the real world
                     //represented by the Physical Resource in JDF is not available for processing. The metadata is valid.
        InUseStatus, // Indicates that the Resource exists, but is in use by another Process. Also used for active pipes
        DraftStatus, // Indicates that the Resource exists in a state that is suffi­cient for setting up the next Process but not for production.
        CompleteStatus, // Indicates that the Resource is completely specified and the parameters are valid for usage.
                 //A Physical Resource with Status = "Complete" is not yet available for produc­tion,
                 //although it is sufficiently specified for a Process that refer­ences it through a ResourceRef from a Parameter Resource to commence execution.
        AvailableStatus // Indicates that the whole Resource is available for usage.
    };

    enum ResourceClass {
        ConsumableClass,
        HandlingClass,
        ImplementationClass,
        IntentClass,
        ParameterClass,
        PlaceHolderClass,
        QuantityClass
    };

    enum Coating {
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

    enum BundleType {
        BoundSet, // Stack of components that are bound together.
        Box,
        Carton,
        CollectedStack, // Components collected on a saddle, result of Collecting Process
        CompensatedStack, // Loose stack of compensated components
        Pallet,
        Roll, // Rolled components on a print Roll.
        Sheet, // Multiple individual items printed onto one Sheet.
        Stack, // Loose stack of equally stacked components.
        StrappedStack, // Strapped stack of equally stacked components.
        StrappedCompensatedStack, // Strapped stack of compensated components.
        WrappedBundle
    };

    static QString resourceStatusToString(ResourceStatus status);
    static ResourceStatus resourceStatusFromString(const QString &status);

    static QString resourceClassToString(ResourceClass resourceClass);
    static ResourceClass resourceClassFromString(const QString &resourceClass);

    static QString coatingToString(Coating coating);
    static Coating coatingFromString(const QString &coating);

    static QString bundleTypeToString(BundleType bundleType);
    static BundleType bundleTypeFromString(const QString &bundleType);

private:
    static QHash<QString, ResourceStatus> m_resourceStatusStringified;
    static QHash<QString, ResourceClass> m_resourceClassStringified;
    static QHash<QString, Coating> m_coatingStringified;
    static QHash<QString, BundleType> m_bundleTypeStringified;
};

}
}

#endif // PROOF_JDF_APIHELPER_H
