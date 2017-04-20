#ifndef JDFAPIHELPER_H
#define JDFAPIHELPER_H

#include "proofcore/proofobject.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

#include <QHash>

namespace Proof {
namespace Jdf {
PROOF_NETWORK_JDF_EXPORT Q_NAMESPACE

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
    NoCoating, // No coating.
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

enum class CoatingDetail {
    NoCoatingDetail, // No coating detail specified.
    CastCoating,
    ProfitFullCoating,
    ProfitSpotCoating
};

enum class LaminatingSurface {
    FrontLaminated,
    BackLaminated,
    BothLaminated,
    NoneLaminated
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

enum class ProductType {
    NoProduct,
    BackCoverProduct,
    BlankBoxProduct, // Cut, Unfolded box, input for folder-gluer
    BlankSheetProduct, // A sheet with connected blanks after a die cutting
    BlankWebProduct, // A web with connected blanks after a die cutting.
    BodyProduct, //Generic content inside of a cover.
    BookProduct,
    BookBlockProduct,
    BookCaseProduct,
    BoxProduct, // Convenience packaging that is not envisioned to be protection for shipping.
    BrochureProduct,
    BusinessCardProduct,
    CartonProduct, // Protection packaging for shipping.
    CoverProduct,
    EndSheetProduct, // Endsheet for hard cover books.
    FlatBoxProduct, // A folded and glued blank (not opened). Output from a box folder-gluer.
    FlatWorkProduct, // Non-bound, non-folded Products or Products that only have packaging folds.
    FrontCoverProduct,
    InsertProduct,
    JacketProduct, //Hard cover case jacket.
    LabelProduct,
    NewspaperProduct, //A newspaper-product
    PalletProduct, //Loaded pallet of Boxes, Cartons or Component Resources
    PosterProduct,
    StackProduct //Stacked Component.
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

enum class LinkUsage {
    InputLink,
    OutputLink
};

enum class ProcessUsage {
    UseAsDefault,
    UseAsAccepted, //Used for Resource in an Output Resource of Approvall
    UseAsApplication, //Used for Component in an Input Resource of BoxFolding
    UseAsBackEndSheet, //Used for Component in an Input Resource of EndSheetGluing
    UseAsBook, //Used for Component in an Input Resource of Jacketing
    UseAsBookBlock, //Used for Component in an Input Resource of ChannelBinding, EndSheetGluing and RingBinding
    UseAsBox, //Used for Component in an Input Resource of BoxPacking
    UseAsCase, //Used for Component in an Input Resource of CasingIn
    UseAsChild, //Used for Component in an Input Resource of Inserting
    UseAsCover, //Used for Component in an Input Resource of ChannelBinding and CoverApplication
    UseAsCoverBoard, //Used for Media in an Input Resource of CaseMaking
    UseAsCoverMaterial, //Used for Component and Media in an Input Resource of CaseMaking
    UseAsCylinder, //Used for ExposedMedia in an Input Resource of ConventionalPrinting
    UseAsDocument, //Used for RunList in an Input Resource of Imposition, LayoutPreparation and Stripping and used for RunList in an Output Resource of Stripping
    UseAsFrontEndSheet, //Used for Component in an Input Resource of EndSheetGluing
    UseAsGood, //Used for Component in an Output Resource of ConventionalPrinting and DigitalPrinting
    UseAsInput, //Used for Component in an Input Resource of ConventionalPrinting and DigitalPrinting
    UseAsJacket, //Used for Component in an Input Resource of Jacketing
    UseAsLabel, //Used for Component in an Input Resource of Labeling
    UseAsMarks, //Used for RunList in an Input Resource of Imposition, LayoutPreparation and Tiling, and used for RunList in an Output Resource of LayoutPreparation and Stripping
    UseAsMother, //Used for Component in an Input Resource of Inserting
    UseAsPlate, //Used for ExposedMedia in an Input Resource of ConventionalPrinting
    UseAsProof, //Used for Component in an Input Resource of ConventionalPrinting and DigitalPrinting, and used for ExposedMedia in an Input Resource of ConventionalPrinting
    UseAsRejected, //Used for Resource in an Output Resource of Approval
    UseAsRingBinder, //Used for Component in an Input Resource of RingBinding
    UseAsSpineBoard, //Used for Media in an Input Resource of CaseMaking
    UseAsSurface, //Used for RunList in an Input Resource of Tiling
    UseAsTie, //Used for Media in an Input Resource of BoxPacking
    UseAsUnderlay, //Used for Media in an Input Resource of BoxPacking
    UseAsWaste //Used for Component in an Output Resource of ConventionalPrinting and DigitalPrinting
};

enum class BlockType {
    CutBlock, //Block to be cut.
    SaveBlock, //Protected block, cut only via outer contour.
    TempBlock, //Auxiliary block that is not taken into account during cutting.
    MarkBlock //Contains no elements, only marks.
};

enum class MediaUnit {
    ContinuousMediaUnit, // Continuously connected Sheets which can be fan folded
    RollMediaUnit,
    SheetMediaUnit // Individual cut Sheets.
};

enum class MediaType {
    CorrugatedBoardMedia,
    DiscMedia,
    EndBoardMedia,
    EmbossingFoilMedia,
    FilmMedia,
    FoilMedia,
    GravureCylinderMedia,
    ImagingCylinderMedia,
    LaminatingFoilMedia,
    MountingTapeMedia,
    PaperMedia,
    PlateMedia,
    ScreenMedia,
    SelfAdhesiveMedia,
    SleeveMedia,
    ShrinkFoilMedia,
    TextileMedia,
    OtherMedia
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

enum class SpanDataType {
    DurationSpan,
    EnumerationSpan,
    IntegerSpan,
    NameSpan,
    NumberSpan,
    OptionSpan,
    ShapeSpan,
    StringSpan,
    TimeSpan,
    XYPairSpan
};

Q_ENUM_NS(ResourceStatus)
Q_ENUM_NS(ResourceClass)
Q_ENUM_NS(CoatingType)
Q_ENUM_NS(CoatingDetail)
Q_ENUM_NS(BundleType)
Q_ENUM_NS(ComponentType)
Q_ENUM_NS(ProductType)
Q_ENUM_NS(ResourceOrientation)
Q_ENUM_NS(ResourcePartType)
Q_ENUM_NS(LinkUsage)
Q_ENUM_NS(ProcessUsage)
Q_ENUM_NS(BlockType)
Q_ENUM_NS(LaminatingSurface)
Q_ENUM_NS(MediaUnit)
Q_ENUM_NS(MediaType)

PROOF_NETWORK_JDF_EXPORT QString resourceStatusToString(ResourceStatus status);
PROOF_NETWORK_JDF_EXPORT ResourceStatus resourceStatusFromString(const QString &status, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString resourceClassToString(ResourceClass resourceClass);
PROOF_NETWORK_JDF_EXPORT ResourceClass resourceClassFromString(const QString &resourceClass, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString coatingToString(CoatingType coating);
PROOF_NETWORK_JDF_EXPORT CoatingType coatingFromString(const QString &coating, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString coatingDetailToString(CoatingDetail coatingDetail);
PROOF_NETWORK_JDF_EXPORT CoatingDetail coatingDetailFromString(const QString &coatingDetail, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString laminatingSurfaceToString(LaminatingSurface surface);
PROOF_NETWORK_JDF_EXPORT LaminatingSurface laminatingSurfaceFromString(const QString &surface, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString bundleTypeToString(BundleType bundleType);
PROOF_NETWORK_JDF_EXPORT BundleType bundleTypeFromString(const QString &bundleType, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString resourceOrientationToString(ResourceOrientation resourceOrientation);
PROOF_NETWORK_JDF_EXPORT ResourceOrientation resourceOrientationFromString(const QString &resourceOrientation, bool *ok = nullptr);
PROOF_NETWORK_JDF_EXPORT int resourceRotateToInt(ResourceOrientation resourceOrientation);
PROOF_NETWORK_JDF_EXPORT ResourceOrientation resourceRotateFromInt(int resourceRotate, bool *ok = nullptr);
PROOF_NETWORK_JDF_EXPORT int resourceFlipToInt(ResourceOrientation resourceOrientation);
PROOF_NETWORK_JDF_EXPORT ResourceOrientation resourceFlipFromInt(int resourceFlip, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString componentTypeToString(ComponentType componentType);
PROOF_NETWORK_JDF_EXPORT ComponentType componentTypeFromString(const QString &componentType, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString productTypeToString(ProductType productType);
PROOF_NETWORK_JDF_EXPORT ProductType productTypeFromString(const QString &productType, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString resourcePartTypeToString(ResourcePartType resourcePartType);
PROOF_NETWORK_JDF_EXPORT ResourcePartType resourcePartTypeFromString(const QString &resourcePartType, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString linkUsageToString(LinkUsage usage);
PROOF_NETWORK_JDF_EXPORT LinkUsage linkUsageFromString(const QString &usage, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString processUsageToString(ProcessUsage processusage);
PROOF_NETWORK_JDF_EXPORT ProcessUsage processUsageFromString(const QString &processUsage, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString blockTypeToString(BlockType blockType);
PROOF_NETWORK_JDF_EXPORT BlockType blockTypeFromString(const QString &blockType, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString mediaUnitToString(MediaUnit mediaUnit);
PROOF_NETWORK_JDF_EXPORT MediaUnit mediaUnitFromString(const QString &mediaUnit, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString mediaTypeToString(MediaType mediaType);
PROOF_NETWORK_JDF_EXPORT MediaType mediaTypeFromString(const QString &mediaType, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString deviceFilterDetailsToString(DeviceFilterDetails details);
PROOF_NETWORK_JDF_EXPORT DeviceFilterDetails deviceFilterDetailsFromString(const QString &details, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString deviceStatusToString(DeviceStatus status);
PROOF_NETWORK_JDF_EXPORT DeviceStatus deviceStatusFromString(const QString &status, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString deviceConditionToString(DeviceCondition condition);
PROOF_NETWORK_JDF_EXPORT DeviceCondition deviceConditionFromString(const QString &condition, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString notificationClassToString(NotificationClass notification);
PROOF_NETWORK_JDF_EXPORT NotificationClass notificationClassFromString(const QString &notification, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT QString spanDataTypeToString(SpanDataType dataType);
PROOF_NETWORK_JDF_EXPORT SpanDataType spanDataTypeFromString(const QString &dataType, bool *ok = nullptr);

PROOF_NETWORK_JDF_EXPORT uint qHash(ResourceStatus arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ResourceClass arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(CoatingType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(LaminatingSurface arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(BundleType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ResourceOrientation arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ComponentType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ProductType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ResourcePartType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(LinkUsage arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(ProcessUsage arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(BlockType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(MediaUnit arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(MediaType arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(DeviceFilterDetails arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(DeviceStatus arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(DeviceCondition arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(NotificationClass arg, uint seed = 0);
PROOF_NETWORK_JDF_EXPORT uint qHash(SpanDataType arg, uint seed = 0);

}
}

#endif // PROOF_JDF_APIHELPER_H
