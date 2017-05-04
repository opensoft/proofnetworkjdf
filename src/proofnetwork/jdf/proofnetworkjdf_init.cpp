#include "data/abstractresource.h"
#include "data/abstractphysicalresource.h"
#include "data/cutblock.h"
#include "data/cuttingparams.h"
#include "data/foldingparams.h"
#include "data/boxpackingparams.h"
#include "data/resourcepool.h"
#include "data/media.h"
#include "data/layout.h"
#include "data/laminatingintent.h"
#include "data/deliveryintent.h"
#include "data/dropintent.h"
#include "data/dropitemintent.h"
#include "data/component.h"
#include "data/bundle.h"
#include "data/jdfdocument.h"
#include "data/jmfdocument.h"
#include "data/message.h"
#include "data/message_p.h"
#include "data/query.h"
#include "data/response.h"
#include "data/knowndevicesquery.h"
#include "data/devicefilter.h"
#include "data/knowndevicesresponse.h"
#include "data/deviceinfo.h"
#include "data/notification.h"

#include "data/abstractresourcelink.h"
#include "data/abstractphysicalresourcelink.h"
#include "data/cuttingparamslink.h"
#include "data/foldingparamslink.h"
#include "data/boxpackingparamslink.h"
#include "data/medialink.h"
#include "data/laminatingintentlink.h"
#include "data/deliveryintentlink.h"
#include "data/componentlink.h"
#include "data/resourcelinkpool.h"

#include "proofnetworkjdf_global.h"
#include "proofcore/proofglobal.h"

Q_LOGGING_CATEGORY(proofNetworkJdfDataLog, "proof.network.jdf.data")

PROOF_LIBRARY_INITIALIZER(libraryInit)
{
    //clang-format off
    qRegisterMetaType<Proof::Jdf::AbstractResourceQmlWrapper *>("Proof::Jdf::AbstractResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractPhysicalResourceQmlWrapper *>("Proof::Jdf::AbstractPhysicalResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractResourceLinkQmlWrapper *>("Proof::Jdf::AbstractResourceLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractPhysicalResourceLinkQmlWrapper *>("Proof::Jdf::AbstractPhysicalResourceLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ResourcePoolQmlWrapper *>("Proof::Jdf::ResourcePoolQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CuttingParamsQmlWrapper *>("Proof::Jdf::CuttingParamsQmlWrapper *");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>>("QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>>("QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper>>("QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::ComponentQmlWrapper>>("QQmlListProperty<Proof::Jdf::ComponentQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::MediaQmlWrapper>>("QQmlListProperty<Proof::Jdf::MediaQmlWrapper>");
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
    qRegisterMetaType<QList<Proof::Jdf::MessageSP>>("QList<Proof::Jdf::MessageSP>");
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
    qRegisterMetaType<QList<Proof::Jdf::DeviceInfoSP>>("QList<Proof::Jdf::DeviceInfoSP>");
    qRegisterMetaType<Proof::Jdf::DeviceInfoWP>("Proof::Jdf::DeviceInfoWP");
    qRegisterMetaType<Proof::Jdf::NotificationSP>("Proof::Jdf::NotificationSP");
    qRegisterMetaType<Proof::Jdf::NotificationWP>("Proof::Jdf::NotificationWP");
    //clang-format on
}
