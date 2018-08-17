#include "proofcore/proofglobal.h"

#include "proofnetwork/jdf/data/abstractaudit.h"
#include "proofnetwork/jdf/data/abstractphysicalresource.h"
#include "proofnetwork/jdf/data/abstractphysicalresourcelink.h"
#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/auditpool.h"
#include "proofnetwork/jdf/data/boxpackingparams.h"
#include "proofnetwork/jdf/data/boxpackingparamslink.h"
#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/createdaudit.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"
#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/deliveryintentlink.h"
#include "proofnetwork/jdf/data/devicefilter.h"
#include "proofnetwork/jdf/data/deviceinfo.h"
#include "proofnetwork/jdf/data/dropintent.h"
#include "proofnetwork/jdf/data/dropitemintent.h"
#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/foldingparamslink.h"
#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/jmfdocument.h"
#include "proofnetwork/jdf/data/knowndevicesquery.h"
#include "proofnetwork/jdf/data/knowndevicesresponse.h"
#include "proofnetwork/jdf/data/laminatingintent.h"
#include "proofnetwork/jdf/data/laminatingintentlink.h"
#include "proofnetwork/jdf/data/layout.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/message.h"
#include "proofnetwork/jdf/data/message_p.h"
#include "proofnetwork/jdf/data/modifiedaudit.h"
#include "proofnetwork/jdf/data/notification.h"
#include "proofnetwork/jdf/data/query.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/response.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"

Q_LOGGING_CATEGORY(proofNetworkJdfDataLog, "proof.network.jdf.data")

PROOF_LIBRARY_INITIALIZER(libraryInit)
{
    // clang-format off
    qRegisterMetaType<Proof::Jdf::AbstractResourceQmlWrapper *>("Proof::Jdf::AbstractResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractPhysicalResourceQmlWrapper *>("Proof::Jdf::AbstractPhysicalResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractResourceLinkQmlWrapper *>("Proof::Jdf::AbstractResourceLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractPhysicalResourceLinkQmlWrapper *>("Proof::Jdf::AbstractPhysicalResourceLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractAuditQmlWrapper *>("Proof::Jdf::AbstractAuditQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ResourcePoolQmlWrapper *>("Proof::Jdf::ResourcePoolQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AuditPoolQmlWrapper *>("Proof::Jdf::AuditPoolQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CreatedAuditQmlWrapper *>("Proof::Jdf::CreatedAuditQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ModifiedAuditQmlWrapper *>("Proof::Jdf::ModifiedAuditQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CuttingParamsQmlWrapper *>("Proof::Jdf::CuttingParamsQmlWrapper *");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>>("QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>>("QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper>>("QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::ComponentQmlWrapper>>("QQmlListProperty<Proof::Jdf::ComponentQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::MediaQmlWrapper>>("QQmlListProperty<Proof::Jdf::MediaQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::MediaLinkQmlWrapper>>("QQmlListProperty<Proof::Jdf::MediaLinkQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::LayoutQmlWrapper>>("QQmlListProperty<Proof::Jdf::LayoutQmlWrapper>");
    qRegisterMetaType<Proof::Jdf::MediaQmlWrapper *>("Proof::Jdf::MediaQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::LayoutQmlWrapper *>("Proof::Jdf::LayoutQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentQmlWrapper *>("Proof::Jdf::LaminatingIntentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::DeliveryIntentQmlWrapper *>("Proof::Jdf::DeliveryIntentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::DropIntentQmlWrapper *>("Proof::Jdf::DropIntentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::DropItemIntentQmlWrapper *>("Proof::Jdf::DropItemIntentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentQmlWrapper *>("Proof::Jdf::ComponentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::FoldingParamsQmlWrapper *>("Proof::Jdf::FoldingParamsQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::BoxPackingParamsQmlWrapper *>("Proof::Jdf::BoxPackingParamsQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfNodeQmlWrapper *>("Proof::Jdf::JdfNodeQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfDocumentQmlWrapper *>("Proof::Jdf::JdfDocumentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ResourceLinkPoolQmlWrapper *>("Proof::Jdf::ResourceLinkPoolQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkQmlWrapper *>("Proof::Jdf::CuttingParamsLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::MediaLinkQmlWrapper *>("Proof::Jdf::MediaLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkQmlWrapper *>("Proof::Jdf::LaminatingIntentLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::DeliveryIntentLinkQmlWrapper *>("Proof::Jdf::DeliveryIntentLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentLinkQmlWrapper *>("Proof::Jdf::ComponentLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkQmlWrapper *>("Proof::Jdf::FoldingParamsLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::BoxPackingParamsLinkQmlWrapper *>("Proof::Jdf::BoxPackingParamsLinkQmlWrapper *");

    qRegisterMetaType<Proof::Jdf::JdfDocument *>("Proof::Jdf::JdfDocument *");

    qRegisterMetaType<Proof::Jdf::JdfNodeSP>("Proof::Jdf::JdfNodeSP");
    qRegisterMetaType<Proof::Jdf::JdfNodeWP>("Proof::Jdf::JdfNodeWP");
    qRegisterMetaType<Proof::Jdf::JdfDocumentSP>("Proof::Jdf::JdfDocumentSP");
    qRegisterMetaType<Proof::Jdf::JdfDocumentWP>("Proof::Jdf::JdfDocumentWP");
    qRegisterMetaType<Proof::Jdf::JmfDocumentSP>("Proof::Jdf::JmfDocumentSP");
    qRegisterMetaType<Proof::Jdf::JmfDocumentWP>("Proof::Jdf::JmfDocumentWP");
    qRegisterMetaType<Proof::Jdf::ResourcePoolSP>("Proof::Jdf::ResourcePoolSP");
    qRegisterMetaType<Proof::Jdf::ResourcePoolWP>("Proof::Jdf::ResourcePoolWP");
    qRegisterMetaType<Proof::Jdf::AuditPoolSP>("Proof::Jdf::AuditPoolSP");
    qRegisterMetaType<Proof::Jdf::AuditPoolWP>("Proof::Jdf::AuditPoolWP");
    qRegisterMetaType<Proof::Jdf::CreatedAuditSP>("Proof::Jdf::CreatedAuditSP");
    qRegisterMetaType<Proof::Jdf::CreatedAuditWP>("Proof::Jdf::CreatedAuditWP");
    qRegisterMetaType<Proof::Jdf::ModifiedAuditSP>("Proof::Jdf::ModifiedAuditSP");
    qRegisterMetaType<Proof::Jdf::ModifiedAuditWP>("Proof::Jdf::ModifiedAuditWP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsSP>("Proof::Jdf::CuttingParamsSP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsWP>("Proof::Jdf::CuttingParamsWP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsSP>("Proof::Jdf::FoldingParamsSP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsWP>("Proof::Jdf::FoldingParamsWP");
    qRegisterMetaType<Proof::Jdf::BoxPackingParamsSP>("Proof::Jdf::BoxPackingParamsSP");
    qRegisterMetaType<Proof::Jdf::BoxPackingParamsWP>("Proof::Jdf::BoxPackingParamsWP");
    qRegisterMetaType<Proof::Jdf::CutBlockSP>("Proof::Jdf::CutBlockSP");
    qRegisterMetaType<Proof::Jdf::CutBlockWP>("Proof::Jdf::CutBlockWP");
    qRegisterMetaType<Proof::Jdf::MediaSP>("Proof::Jdf::MediaSP");
    qRegisterMetaType<Proof::Jdf::MediaWP>("Proof::Jdf::MediaWP");
    qRegisterMetaType<Proof::Jdf::LayoutSP>("Proof::Jdf::LayoutSP");
    qRegisterMetaType<Proof::Jdf::LayoutWP>("Proof::Jdf::LayoutWP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentSP>("Proof::Jdf::LaminatingIntentSP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentWP>("Proof::Jdf::LaminatingIntentWP");
    qRegisterMetaType<Proof::Jdf::DeliveryIntentSP>("Proof::Jdf::DeliveryIntentSP");
    qRegisterMetaType<Proof::Jdf::DeliveryIntentWP>("Proof::Jdf::DeliveryIntentWP");
    qRegisterMetaType<Proof::Jdf::DropIntentSP>("Proof::Jdf::DropIntentSP");
    qRegisterMetaType<Proof::Jdf::DropIntentWP>("Proof::Jdf::DropIntentWP");
    qRegisterMetaType<Proof::Jdf::DropItemIntentSP>("Proof::Jdf::DropItemIntentSP");
    qRegisterMetaType<Proof::Jdf::DropItemIntentWP>("Proof::Jdf::DropItemIntentWP");
    qRegisterMetaType<Proof::Jdf::ComponentSP>("Proof::Jdf::ComponentSP");
    qRegisterMetaType<Proof::Jdf::ComponentWP>("Proof::Jdf::ComponentWP");
    qRegisterMetaType<Proof::Jdf::BundleSP>("Proof::Jdf::BundleSP");
    qRegisterMetaType<Proof::Jdf::BundleWP>("Proof::Jdf::BundleWP");

    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkSP>("Proof::Jdf::CuttingParamsLinkSP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkWP>("Proof::Jdf::CuttingParamsLinkWP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkSP>("Proof::Jdf::FoldingParamsLinkSP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkWP>("Proof::Jdf::FoldingParamsLinkWP");
    qRegisterMetaType<Proof::Jdf::BoxPackingParamsLinkSP>("Proof::Jdf::BoxPackingParamsLinkSP");
    qRegisterMetaType<Proof::Jdf::BoxPackingParamsLinkWP>("Proof::Jdf::BoxPackingParamsLinkWP");
    qRegisterMetaType<Proof::Jdf::MediaLinkSP>("Proof::Jdf::MediaLinkSP");
    qRegisterMetaType<Proof::Jdf::MediaLinkWP>("Proof::Jdf::MediaLinkWP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkSP>("Proof::Jdf::LaminatingIntentLinkSP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkWP>("Proof::Jdf::LaminatingIntentLinkWP");
    qRegisterMetaType<Proof::Jdf::DeliveryIntentLinkSP>("Proof::Jdf::DeliveryIntentLinkSP");
    qRegisterMetaType<Proof::Jdf::DeliveryIntentLinkWP>("Proof::Jdf::DeliveryIntentLinkWP");
    qRegisterMetaType<Proof::Jdf::ComponentLinkSP>("Proof::Jdf::ComponentLinkSP");
    qRegisterMetaType<Proof::Jdf::ComponentLinkWP>("Proof::Jdf::ComponentLinkWP");
    qRegisterMetaType<Proof::Jdf::ResourceLinkPoolSP>("Proof::Jdf::ResourceLinkPoolSP");
    qRegisterMetaType<Proof::Jdf::ResourceLinkPoolWP>("Proof::Jdf::ResourceLinkPoolWP");

    qRegisterMetaType<Proof::Jdf::ResourceStatus>("Proof::Jdf::ResourceStatus");
    qRegisterMetaType<Proof::Jdf::ResourceClass>("Proof::Jdf::ResourceClass");
    qRegisterMetaType<Proof::Jdf::ResourceOrientation>("Proof::Jdf::ResourceOrientation");
    qRegisterMetaType<Proof::Jdf::CoatingType>("Proof::Jdf::CoatingType");
    qRegisterMetaType<Proof::Jdf::MediaUnit>("Proof::Jdf::MediaUnit");
    qRegisterMetaType<Proof::Jdf::MediaType>("Proof::Jdf::MediaType");
    qRegisterMetaType<Proof::Jdf::LaminatingSurface>("Proof::Jdf::LaminatingSurface");
    qRegisterMetaType<Proof::Jdf::BundleType>("Proof::Jdf::BundleType");
    qRegisterMetaType<Proof::Jdf::ComponentType>("Proof::Jdf::ComponentType");
    qRegisterMetaType<Proof::Jdf::ResourcePartType>("Proof::Jdf::PartIdKeysType");
    qRegisterMetaType<Proof::Jdf::LinkUsage>("Proof::Jdf::Usage");
    qRegisterMetaType<Proof::Jdf::BlockType>("Proof::Jdf::BlockType");
    qRegisterMetaType<Proof::Jdf::DeviceFilterDetails>("Proof::Jdf::DeviceFilterDetails");
    qRegisterMetaType<Proof::Jdf::DeviceStatus>("Proof::Jdf::DeviceStatus");
    qRegisterMetaType<Proof::Jdf::DeviceCondition>("Proof::Jdf::DeviceCondition");
    qRegisterMetaType<Proof::Jdf::NotificationClass>("Proof::Jdf::NotificationClass");

    qRegisterMetaType<Proof::Jdf::MessageSP>("Proof::Jdf::MessageSP");
    qRegisterMetaType<Proof::Jdf::MessageWP>("Proof::Jdf::MessageWP");
    qRegisterMetaType<QVector<Proof::Jdf::MessageSP>>("QVector<Proof::Jdf::MessageSP>");
    qRegisterMetaType<Proof::Jdf::QuerySP>("Proof::Jdf::QuerySP");
    qRegisterMetaType<Proof::Jdf::QueryWP>("Proof::Jdf::QueryWP");
    qRegisterMetaType<Proof::Jdf::ResponseSP>("Proof::Jdf::ResponseSP");
    qRegisterMetaType<Proof::Jdf::ResponseWP>("Proof::Jdf::ResponseWP");
    qRegisterMetaType<Proof::Jdf::KnownDevicesQuerySP>("Proof::Jdf::KnownDevicesSP");
    qRegisterMetaType<Proof::Jdf::KnownDevicesQueryWP>("Proof::Jdf::KnownDevicesWP");
    Proof::Jdf::registerJmfMessage<Proof::Jdf::KnownDevicesQuery>(QStringLiteral("Query"), QStringLiteral("KnownDevices"));
    qRegisterMetaType<Proof::Jdf::DeviceFilterSP>("Proof::Jdf::DeviceFilterSP");
    qRegisterMetaType<Proof::Jdf::DeviceFilterWP>("Proof::Jdf::DeviceFilterWP");
    qRegisterMetaType<Proof::Jdf::KnownDevicesResponseSP>("Proof::Jdf::KnownDevicesResponseSP");
    qRegisterMetaType<Proof::Jdf::KnownDevicesResponseWP>("Proof::Jdf::KnownDevicesResponseWP");
    Proof::Jdf::registerJmfMessage<Proof::Jdf::KnownDevicesResponse>(QStringLiteral("Response"), QStringLiteral("KnownDevices"));
    qRegisterMetaType<Proof::Jdf::DeviceInfoSP>("Proof::Jdf::DeviceInfoSP");
    qRegisterMetaType<QVector<Proof::Jdf::DeviceInfoSP>>("QVector<Proof::Jdf::DeviceInfoSP>");
    qRegisterMetaType<Proof::Jdf::DeviceInfoWP>("Proof::Jdf::DeviceInfoWP");
    qRegisterMetaType<Proof::Jdf::NotificationSP>("Proof::Jdf::NotificationSP");
    qRegisterMetaType<Proof::Jdf::NotificationWP>("Proof::Jdf::NotificationWP");

    // clang-format on
}
