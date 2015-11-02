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

    enum class DeviceFilterDetails {
        // Provide only DeviceID and DeviceStatus.
        NoneDeviceFilterDetails,
        // Provide all available Device information except for Device Ele­ments.
        BriefDeviceFilterDetails,
        // ModuleStatus Elements are to be provided without module specific status details
        // and without module specific employee information.
        ModulesDeviceFilterDetails,
        // Provide maximum available Device information excluding Device capability descriptions.
        // Includes Device Elements which repre­sent details of the Device.
        DetailsDeviceFilterDetails,
        // Provide maximum available Device information includ­ing limited Device capability descriptions.
        // Includes Device Elements which represent details of the Device
        // and Device/DeviceCap/FeaturePool Subelements which represent named features of the Device.
        NamedFeatureDeviceFilterDetails,
        // Provide Device/DeviceCap Subelements which represent details of the capabilities of the Device.
        CapabilityDeviceFilterDetails,
        // Provide maximum available Device information including Device capability descriptions.
        // Includes Device Elements which represent details of the Device.
        FullDeviceFilterDetails
    };

    enum class DeviceStatus {
        UnknownDeviceStatus, // No Device is known or the Device cannot provide a DeviceStatus.
        IdleDeviceStatus, // No Job is being processed and the Device is accepting new Jobs.
        DownDeviceStatus, // No Job is being processed and the Device currently cannot execute a Job.
                          // The Device might be broken, switched off, etc.
        SetupDeviceStatus, // The Device is currently being set up.
                           // This state is allowed to occur also during the execution of a Job.
        RunningDeviceStatus, // The Device is currently executing a Job.
        CleanupDeviceStatus, // The Device is currently being cleaned.
                             // This state is allowed to occur also during the execution of a Job.
        StoppedDeviceStatus // The Device has been stopped, probably temporarily.
                            // This status indicates some kind of break, including a pause, maintenance or a breakdown,
                            // as long as execution has not been aborted.
    };

    enum class DeviceCondition {
        OkDeviceCondition, // The Device is in working condition.
        NeedsAttentionDeviceCondition, // The Device is still in working condition but requires attention.
        FailureDeviceCondition, // The Device is not in working condition.
        OffLineDeviceCondition  // The Device is off line and its condition is unknown.
    };

    enum class NotificationClass {
        // Indicates that a pure event due to certain operation-related activity has occurred,
        // (e.g., Machine events, operator activities, etc.).
        // This Class is used for the transfer of conventional event Messages.
        // In case of Class = "Event", further event informa­tion is to be provided by the Type Attribute
        // and NotificationDetails Element.
        EventNotificationClass,
        // Any information about a Process which cannot be expressed by the other Classes (e.g., the beginning of execu­tion).
        // No user interaction is needed.
        InformationNotificationClass,
        // Indicates that a minor error has occurred, and an auto­matic fix was applied. Execution continues.
        // The Node’s Status is unchanged. This appears in situations such as A4-Letter sub­stitutions when toner is low or when unknown extensions are encountered in a REQUIRED Resource
        WarningNotificationClass,
        // Indicates that an error has occurred that requires user inter­action.
        // Execution cannot continue until the problem has been fixed. The Node’s Status is Stopped.
        // This value appears in situations such as when Resources are missing, when major incompatibilities are detected,
        // or when the toner is empty.
        ErrorNotificationClass,
        // Indicates that a fatal error led to abortion of the Process. The Node’s Status is Aborted.
        // This value is seen with most protocol errors or when major Device malfunction has occurred.
        FatalNotificationClass
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
    static int resourceRotateToInt(ResourceOrientation resourceOrientation);
    static ResourceOrientation resourceRotateFromInt(int resourceRotate, bool *ok = nullptr);
    static int resourceFlipToInt(ResourceOrientation resourceOrientation);
    static ResourceOrientation resourceFlipFromInt(int resourceFlip, bool *ok = nullptr);

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

    static QString deviceFilterDetailsToString(DeviceFilterDetails details);
    static DeviceFilterDetails deviceFilterDetailsFromString(const QString &details, bool *ok = nullptr);

    static QString deviceStatusToString(DeviceStatus status);
    static DeviceStatus deviceStatusFromString(const QString &status, bool *ok = nullptr);

    static QString deviceConditionToString(DeviceCondition condition);
    static DeviceCondition deviceConditionFromString(const QString &condition, bool *ok = nullptr);

    static QString notificationClassToString(NotificationClass notification);
    static NotificationClass notificationClassFromString(const QString &notification, bool *ok = nullptr);
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
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::DeviceFilterDetails arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::DeviceStatus arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::DeviceCondition arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ApiHelper::NotificationClass arg, uint seed = 0);

}
}

#endif // PROOF_JDF_APIHELPER_H
