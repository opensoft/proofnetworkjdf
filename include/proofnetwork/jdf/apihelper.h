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
    Q_ENUMS(CoatingType)
    Q_ENUMS(BundleType)
    Q_ENUMS(ComponentType)
    Q_ENUMS(ResourceOrientation)
    Q_ENUMS(ResourcePartType)
    Q_ENUMS(ProcessUsage)
    Q_ENUMS(Usage)
    Q_ENUMS(BlockType)
    Q_ENUMS(LaminatingSurface)
    Q_ENUMS(MediaUnit)
public:
    ApiHelper() = delete;

    enum class ResourceStatus {
        NoStatus,
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

    enum class ResourceClass {
        NoClass,
        ConsumableClass,
        HandlingClass,
        ImplementationClass,
        IntentClass,
        ParameterClass,
        PlaceHolderClass,
        QuantityClass
    };

    enum class CoatingType {
        NoneCoating, // No coating.
        Coated, // A coating of a system-specified type. New in JDF 1.2
        GlossyCoating,
        HighGlossCoating,
        InkJetCoating, // A coating intended for use with inkjet technology.
        // Deprecation note: use PrintingTechnology = "InkJet". New in JDF 1.2. Deprecated in JDF 1.4
        MatteCoating,
        PolymerCoating, // Coating for a photo polymer process. New in JDF 1.3
        SilverCoating, // Coating for a silver halide process. New in JDF 1.3
        SatinCoating,
        SemiglossCoating
    };

    enum class LaminatingSurface {
        Front,
        Back,
        Both,
        None
    };

    enum class BundleType {
        BoundSetBundle, // Stack of components that are bound together.
        BoxBundle,
        CartonBundle,
        CollectedStackBundle, // Components collected on a saddle, result of Collecting Process
        CompensatedStackBundle, // Loose stack of compensated components
        PalletBundle,
        RollBundle, // Rolled components on a print Roll.
        SheetBundle, // Multiple individual items printed onto one Sheet.
        StackBundle, // Loose stack of equally stacked components.
        StrappedStackBundle, // Strapped stack of equally stacked components.
        StrappedCompensatedStackBundle, // Strapped stack of compensated components.
        WrappedBundle
    };

    enum class ResourceOrientation {
        Rotate0Orientation, // 0 degrees
        Rotate90Orientation, // 90
        Rotate180Orientation, // 180
        Rotate270Orientation, // 270

        Flip0Orientation, // 0 degrees
        Flip90Orientation, // 90
        Flip180Orientation, // 180
        Flip270Orientation // 270
    };

    enum class ComponentType {
        NotTypedComponent, //No ComponentType attribute set for this component
        BlockComponent, // Folded or stacked product, (e.g., book block).
        OtherComponent, // The Component describes a sample that has not been produced in this Job.
        RibbonComponent, // The Component is a ribbon on a Web Press.
        SheetComponent, // Single layer (Sheet) of paper.
        WebComponent, // The Component is a Web on a Web Press.
        FinalProductComponent, // The Component is the final product that was ordered by the customer.
        PartialProductComponent, // The Component is an intermediate product that will be input to a following Process.
        ProofComponent // The Component is a proof., e.g., a press proof or output from a digital press.
    };

    enum class ResourcePartType {
        BinderySignatureNamePart,
        BinderySignaturePaginationIndexPart,
        BlockNamePart,
        BundleItemIndexPart,
        CellIndexPart,
        ConditionPart,
        DeliveryUnit0Part,
        DeliveryUnit1Part,
        DeliveryUnit2Part,
        DeliveryUnit3Part,
        DeliveryUnit4Part,
        DeliveryUnit5Part,
        DeliveryUnit6Part,
        DeliveryUnit7Part,
        DeliveryUnit8Part,
        DeliveryUnit9Part,
        DocCopiesPart,
        DocIndexPart,
        DocRunIndexPart,
        DocSheetIndexPart,
        DocTagsPart,
        EditionPart,
        EditionVersionPart,
        FountainNumberPart,
        ItemNamesPart,
        LayerIdsPart,
        LocationPart,
        Metadata0Part,
        Metadata1Part,
        Metadata2Part,
        Metadata3Part,
        Metadata4Part,
        Metadata5Part,
        Metadata6Part,
        Metadata7Part,
        Metadata8Part,
        Metadata9Part,
        OptionPart,
        PageNumberPart,
        PageTagsPart,
        PartVersionPart,
        PlateLayoutPart,
        PreflightRulePart,
        PreviewTypePart,
        RibbonNamePart,
        RunPart,
        RunIndexPart,
        RunPagePart,
        RunPageRangePart,
        RunSetPart,
        RunTagsPart,
        SectionIndexPart,
        SeparationPart,
        SetDocIndexPart,
        SetIndexPart,
        SetRunIndexPart,
        SetSheetIndexPart,
        SetTagsPart,
        SheetIndexPart,
        SheetNamePart,
        SidePart,
        SignatureNamePart,
        StationNamePart,
        SubRunPart,
        TileIdPart,
        WebNamePart,
        WebProductPart,
        WebSetupPart
    };

    enum class ProcessUsage {
        AcceptedProcess, // Used for Resource in an Output Resource of Approval l
        ApplicationProcess, // Used for Component in an Input Resource of BoxFolding
        BackEndSheetProcess, // Used for Component in an Input Resource of EndSheetGluing
        BookProcess, // Used for Component in an Input Resource of Jacketing
        BookBlockProcess, // Used for Component in an Input Resource of ChannelBinding , EndSheetGluing and RingBinding
        BoxProcess, // Used for Component in an Input Resource of BoxPacking
        CaseProcess, // Used for Component in an Input Resource of CasingIn
        ChildProcess, // Used for Component in an Input Resource of Inserting
        CoverProcess, // Used for Component in an Input Resource of ChannelBinding and CoverApplication
        CoverBoardProcess, // Used for Media in an Input Resource of CaseMaking
        CoverMaterialProcess, // Used for Component and Media in an Input Resource of CaseMaking
        CylinderProcess, // Used for ExposedMedia in an Input Resource of ConventionalPrinting
        DocumentProcess, // Used for RunList in an Input Resource of Imposition , LayoutPreparation and Stripping and used for RunList in an Output Resource of Stripping
        FrontEndSheetProcess, // Used for Component in an Input Resource of EndSheetGluing
        GoodProcess, // Used for Component in an Output Resource of ConventionalPrinting and DigitalPrinting
        InputProcess, // Used for Component in an Input Resource of ConventionalPrinting and DigitalPrinting
        JacketProcess, // Used for Component in an Input Resource of Jacketing
        LabelProcess, // Used for Component in an Input Resource of Labeling
        MarksProcess, // Used for RunList in an Input Resource of Imposition , LayoutPreparation and Tiling , and used for RunList in an Output Resource of LayoutPreparation and Stripping
        MotherProcess, // Used for Component in an Input Resource of Inserting
        PlateProcess, // Used for ExposedMedia in an Input Resource of ConventionalPrinting
        ProofProcess, // Used for Component in an Input Resource of ConventionalPrinting and DigitalPrinting , and used for ExposedMedia in an Input Resource of ConventionalPrinting
        RejectedProcess, // Used for Resource in an Output Resource of Approval
        RingBinderProcess, // Used for Component in an Input Resource of RingBinding
        SpineBoardProcess, // Used for Media in an Input Resource of CaseMaking
        SurfaceProcess, // Used for RunList in an Input Resource of Tiling
        TieProcess, // Used for Media in an Input Resource of BoxPacking
        UnderlayProcess, // Used for Media in an Input Resource of BoxPacking
        WasteProcess, // Used for Component in an Output Resource of ConventionalPrinting and DigitalPrinting
    };

    enum class Usage {
        InputUsage,
        OutputUsage
    };

    enum class BlockType {
        CutBlockType, //Block to be cut.
        SaveBlockType, //Protected block, cut only via outer contour.
        TempBlockType, //Auxiliary block that is not taken into account during cutting.
        MarkBlockType //Contains no elements, only marks.
    };

    enum class MediaUnit {
        ContinuousMediaUnit, // Continuously connected Sheets which can be fan folded
        RollMediaUnit,
        SheetMediaUnit // Individual cut Sheets.
    };

    static QString resourceStatusToString(ResourceStatus status);
    static ResourceStatus resourceStatusFromString(const QString &status, bool *ok = nullptr);

    static QString resourceClassToString(ResourceClass resourceClass);
    static ResourceClass resourceClassFromString(const QString &resourceClass, bool *ok = nullptr);

    static QString coatingToString(CoatingType coating);
    static CoatingType coatingFromString(const QString &coating, bool *ok = nullptr);

    static QString laminatingSurfaceToString(LaminatingSurface surface);
    static LaminatingSurface laminatingSurfaceFromString(const QString &surface, bool *ok = nullptr);

    static QString bundleTypeToString(BundleType bundleType);
    static BundleType bundleTypeFromString(const QString &bundleType, bool *ok = nullptr);

    static QString resourceOrientationToString(ResourceOrientation resourceOrientation);
    static ResourceOrientation resourceOrientationFromString(const QString &resourceOrientation, bool *ok = nullptr);

    static QString componentTypeToString(ComponentType componentType);
    static ComponentType componentTypeFromString(const QString &componentType, bool *ok = nullptr);

    static QString resourcePartTypeToString(ResourcePartType resourcePartType);
    static ResourcePartType resourcePartTypeFromString(const QString &resourcePartType, bool *ok = nullptr);

    static QString processUsageToString(ProcessUsage processUsage);
    static ProcessUsage processUsageFromString(const QString &processUsage, bool *ok = nullptr);

    static QString usageToString(Usage usage);
    static Usage usageFromString(const QString &usage, bool *ok = nullptr);

    static QString blockTypeToString(BlockType blockType);
    static BlockType blockTypeFromString(const QString &blockType, bool *ok = nullptr);

    static QString mediaUnitToString(MediaUnit mediaUnit);
    static MediaUnit mediaUnitFromString(const QString &mediaUnit, bool *ok = nullptr);
};

PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::ResourceStatus arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::ResourceClass arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::CoatingType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::LaminatingSurface arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::BundleType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::ResourceOrientation arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::ComponentType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::ResourcePartType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::ProcessUsage arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::Usage arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::BlockType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::MediaUnit arg, uint seed = 0);

}
}

#endif // PROOF_JDF_APIHELPER_H
