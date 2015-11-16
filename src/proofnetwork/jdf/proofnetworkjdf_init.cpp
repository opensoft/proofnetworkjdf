#include "data/abstractresource.h"
#include "data/abstractphysicalresource.h"
#include "data/cutblock.h"
#include "data/cuttingparams.h"
#include "data/foldingparams.h"
#include "data/resourcepool.h"
#include "data/media.h"
#include "data/laminatingintent.h"
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
#include "data/medialink.h"
#include "data/laminatingintentlink.h"
#include "data/componentlink.h"
#include "data/resourcelinkpool.h"

#include "proofnetworkjdf_global.h"

Q_LOGGING_CATEGORY(proofNetworkJdfDataLog, "proof.network.jdf.data")

__attribute__((constructor))
static void libraryInit()
{
    qRegisterMetaType<Proof::Jdf::AbstractResourceQmlWrapper *>("Proof::Jdf::AbstractResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractPhysicalResourceQmlWrapper *>("Proof::Jdf::AbstractPhysicalResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractResourceLinkQmlWrapper *>("Proof::Jdf::AbstractResourceLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractPhysicalResourceLinkQmlWrapper *>("Proof::Jdf::AbstractPhysicalResourceLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ResourcePoolQmlWrapper *>("Proof::Jdf::ResourcePoolQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CuttingParamsQmlWrapper *>("Proof::Jdf::CuttingParamsQmlWrapper *");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>>("QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>>("QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper>>("QQmlListProperty<Proof::Jdf::ComponentLinkQmlWrapper>");
    qRegisterMetaType<Proof::Jdf::MediaQmlWrapper *>("Proof::Jdf::MediaQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentQmlWrapper *>("Proof::Jdf::LaminatingIntentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentQmlWrapper *>("Proof::Jdf::ComponentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::FoldingParamsQmlWrapper *>("Proof::Jdf::FoldingParamsQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfNodeQmlWrapper *>("Proof::Jdf::JdfNodeQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfDocumentQmlWrapper *>("Proof::Jdf::JdfDocumentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ResourceLinkPoolQmlWrapper *>("Proof::Jdf::ResourceLinkPoolQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkQmlWrapper *>("Proof::Jdf::CuttingParamsLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::MediaLinkQmlWrapper *>("Proof::Jdf::MediaLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkQmlWrapper *>("Proof::Jdf::LaminatingIntentLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentLinkQmlWrapper *>("Proof::Jdf::ComponentLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkQmlWrapper *>("Proof::Jdf::FoldingParamsLinkQmlWrapper *");
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
    qRegisterMetaType<Proof::Jdf::CutBlockSP>("Proof::Jdf::CutBlockSP");
    qRegisterMetaType<Proof::Jdf::CutBlockWP>("Proof::Jdf::CutBlockWP");
    qRegisterMetaType<Proof::Jdf::MediaSP>("Proof::Jdf::MediaSP");
    qRegisterMetaType<Proof::Jdf::MediaWP>("Proof::Jdf::MediaWP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentSP>("Proof::Jdf::LaminatingIntentSP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentWP>("Proof::Jdf::LaminatingIntentWP");
    qRegisterMetaType<Proof::Jdf::ComponentSP>("Proof::Jdf::ComponentSP");
    qRegisterMetaType<Proof::Jdf::ComponentWP>("Proof::Jdf::ComponentWP");
    qRegisterMetaType<Proof::Jdf::BundleSP>("Proof::Jdf::BundleSP");
    qRegisterMetaType<Proof::Jdf::BundleWP>("Proof::Jdf::BundleWP");

    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkSP>("Proof::Jdf::CuttingParamsLinkSP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkWP>("Proof::Jdf::CuttingParamsLinkWP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkSP>("Proof::Jdf::FoldingParamsLinkSP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkWP>("Proof::Jdf::FoldingParamsLinkWP");
    qRegisterMetaType<Proof::Jdf::MediaLinkSP>("Proof::Jdf::MediaLinkSP");
    qRegisterMetaType<Proof::Jdf::MediaLinkWP>("Proof::Jdf::MediaLinkWP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkSP>("Proof::Jdf::LaminatingIntentLinkSP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkWP>("Proof::Jdf::LaminatingIntentLinkWP");
    qRegisterMetaType<Proof::Jdf::ComponentLinkSP>("Proof::Jdf::ComponentLinkSP");
    qRegisterMetaType<Proof::Jdf::ComponentLinkWP>("Proof::Jdf::ComponentLinkWP");
    qRegisterMetaType<Proof::Jdf::ResourceLinkPoolSP>("Proof::Jdf::ResourceLinkPoolSP");
    qRegisterMetaType<Proof::Jdf::ResourceLinkPoolWP>("Proof::Jdf::ResourceLinkPoolWP");

    qRegisterMetaType<Proof::Jdf::ApiHelper::ResourceStatus>("Proof::Jdf::ApiHelper::ResourceStatus");
    qRegisterMetaType<Proof::Jdf::ApiHelper::ResourceClass>("Proof::Jdf::ApiHelper::ResourceClass");
    qRegisterMetaType<Proof::Jdf::ApiHelper::ResourceOrientation>("Proof::Jdf::ApiHelper::ResourceOrientation");
    qRegisterMetaType<Proof::Jdf::ApiHelper::CoatingType>("Proof::Jdf::ApiHelper::CoatingType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::MediaUnit>("Proof::Jdf::ApiHelper::MediaUnit");
    qRegisterMetaType<Proof::Jdf::ApiHelper::LaminatingSurface>("Proof::Jdf::ApiHelper::LaminatingSurface");
    qRegisterMetaType<Proof::Jdf::ApiHelper::BundleType>("Proof::Jdf::ApiHelper::BundleType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::ComponentType>("Proof::Jdf::ApiHelper::ComponentType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::ResourcePartType>("Proof::Jdf::ApiHelper::PartIdKeysType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::ProcessUsage>("Proof::Jdf::ApiHelper::ProcessUsage");
    qRegisterMetaType<Proof::Jdf::ApiHelper::Usage>("Proof::Jdf::ApiHelper::Usage");
    qRegisterMetaType<Proof::Jdf::ApiHelper::BlockType>("Proof::Jdf::ApiHelper::BlockType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::DeviceFilterDetails>("Proof::Jdf::ApiHelper::DeviceFilterDetails");
    qRegisterMetaType<Proof::Jdf::ApiHelper::DeviceStatus>("Proof::Jdf::ApiHelper::DeviceStatus");
    qRegisterMetaType<Proof::Jdf::ApiHelper::DeviceCondition>("Proof::Jdf::ApiHelper::DeviceCondition");
    qRegisterMetaType<Proof::Jdf::ApiHelper::NotificationClass>("Proof::Jdf::ApiHelper::NotificationClass");

    qRegisterMetaType<Proof::Jdf::MessageSP>("Proof::Jdf::MessageSP");
    qRegisterMetaType<Proof::Jdf::MessageWP>("Proof::Jdf::MessageWP");
    qRegisterMetaType<Proof::Jdf::QuerySP>("Proof::Jdf::QuerySP");
    qRegisterMetaType<Proof::Jdf::QueryWP>("Proof::Jdf::QueryWP");
    qRegisterMetaType<Proof::Jdf::ResponseSP>("Proof::Jdf::ResponseSP");
    qRegisterMetaType<Proof::Jdf::ResponseWP>("Proof::Jdf::ResponseWP");
    qRegisterMetaType<Proof::Jdf::KnownDevicesQuerySP>("Proof::Jdf::KnownDevicesSP");
    qRegisterMetaType<Proof::Jdf::KnownDevicesQueryWP>("Proof::Jdf::KnownDevicesWP");
    Proof::Jdf::registerJmfMessage<Proof::Jdf::KnownDevicesQuery>("Query", "KnownDevices");
    qRegisterMetaType<Proof::Jdf::DeviceFilterSP>("Proof::Jdf::DeviceFilterSP");
    qRegisterMetaType<Proof::Jdf::DeviceFilterWP>("Proof::Jdf::DeviceFilterWP");
    qRegisterMetaType<Proof::Jdf::KnownDevicesResponseSP>("Proof::Jdf::KnownDevicesResponseSP");
    qRegisterMetaType<Proof::Jdf::KnownDevicesResponseWP>("Proof::Jdf::KnownDevicesResponseWP");
    Proof::Jdf::registerJmfMessage<Proof::Jdf::KnownDevicesResponse>("Response", "KnownDevices");
    qRegisterMetaType<Proof::Jdf::DeviceInfoSP>("Proof::Jdf::DeviceInfoSP");
    qRegisterMetaType<QList<Proof::Jdf::DeviceInfoSP>>("QList<Proof::Jdf::DeviceInfoSP>");
    qRegisterMetaType<Proof::Jdf::DeviceInfoWP>("Proof::Jdf::DeviceInfoWP");
    qRegisterMetaType<Proof::Jdf::NotificationSP>("Proof::Jdf::NotificationSP");
    qRegisterMetaType<Proof::Jdf::NotificationWP>("Proof::Jdf::NotificationWP");
}
