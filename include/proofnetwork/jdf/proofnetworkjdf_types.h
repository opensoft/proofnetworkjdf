#ifndef PROOFNETWORKJDF_TYPES_H
#define PROOFNETWORKJDF_TYPES_H

#include "proofnetwork/proofnetwork_types.h"

#include <QSharedPointer>
#include <QWeakPointer>

namespace Proof {
namespace Jdf {

class AbstractResource;
using AbstractResourceSP = QSharedPointer<AbstractResource>;
using AbstractResourceWP = QWeakPointer<AbstractResource>;

class AbstractPhysicalResource;
using AbstractPhysicalResourceSP = QSharedPointer<AbstractPhysicalResource>;
using AbstractPhysicalResourceWP = QWeakPointer<AbstractPhysicalResource>;

class JdfNode;
using JdfNodeSP = QSharedPointer<JdfNode>;
using JdfNodeWP = QWeakPointer<JdfNode>;

class JdfDocument;
using JdfDocumentSP = QSharedPointer<JdfDocument>;
using JdfDocumentWP = QWeakPointer<JdfDocument>;

class JmfDocument;
using JmfDocumentSP = QSharedPointer<JmfDocument>;
using JmfDocumentWP = QWeakPointer<JmfDocument>;

class ResourcePool;
using ResourcePoolSP = QSharedPointer<ResourcePool>;
using ResourcePoolWP = QWeakPointer<ResourcePool>;

class CuttingParams;
using CuttingParamsSP = QSharedPointer<CuttingParams>;
using CuttingParamsWP = QWeakPointer<CuttingParams>;

class CutBlock;
using CutBlockSP = QSharedPointer<CutBlock>;
using CutBlockWP = QWeakPointer<CutBlock>;

class Media;
using MediaSP = QSharedPointer<Media>;
using MediaWP = QWeakPointer<Media>;

class Layout;
using LayoutSP = QSharedPointer<Layout>;
using LayoutWP = QWeakPointer<Layout>;

class LaminatingIntent;
using LaminatingIntentSP = QSharedPointer<LaminatingIntent>;
using LaminatingIntentWP = QWeakPointer<LaminatingIntent>;

class DeliveryIntent;
using DeliveryIntentSP = QSharedPointer<DeliveryIntent>;
using DeliveryIntentWP = QWeakPointer<DeliveryIntent>;

class DropIntent;
using DropIntentSP = QSharedPointer<DropIntent>;
using DropIntentWP = QWeakPointer<DropIntent>;

class DropItemIntent;
using DropItemIntentSP = QSharedPointer<DropItemIntent>;
using DropItemIntentWP = QWeakPointer<DropItemIntent>;

class Component;
using ComponentSP = QSharedPointer<Component>;
using ComponentWP = QWeakPointer<Component>;

class Bundle;
using BundleSP = QSharedPointer<Bundle>;
using BundleWP = QWeakPointer<Bundle>;

class BundleItem;
using BundleItemSP = QSharedPointer<BundleItem>;
using BundleItemWP = QWeakPointer<BundleItem>;

class AbstractResourceLink;
using AbstractResourceLinkSP = QSharedPointer<AbstractResourceLink>;
using AbstractResourceLinkWP = QWeakPointer<AbstractResourceLink>;

class AbstractPhysicalResourceLink;
using AbstractPhysicalResourceLinkSP = QSharedPointer<AbstractPhysicalResourceLink>;
using AbstractPhysicalResourceLinkWP = QWeakPointer<AbstractPhysicalResourceLink>;

class FoldingParams;
using FoldingParamsSP = QSharedPointer<FoldingParams>;
using FoldingParamsWP = QSharedPointer<FoldingParams>;

class CuttingParamsLink;
using CuttingParamsLinkSP = QSharedPointer<CuttingParamsLink>;
using CuttingParamsLinkWP = QWeakPointer<CuttingParamsLink>;

class MediaLink;
using MediaLinkSP = QSharedPointer<MediaLink>;
using MediaLinkWP = QWeakPointer<MediaLink>;

class LaminatingIntentLink;
using LaminatingIntentLinkSP = QSharedPointer<LaminatingIntentLink>;
using LaminatingIntentLinkWP = QWeakPointer<LaminatingIntentLink>;

class DeliveryIntentLink;
using DeliveryIntentLinkSP = QSharedPointer<DeliveryIntentLink>;
using DeliveryIntentLinkWP = QWeakPointer<DeliveryIntentLink>;

class ComponentLink;
using ComponentLinkSP = QSharedPointer<ComponentLink>;
using ComponentLinkWP = QWeakPointer<ComponentLink>;

class FoldingParamsLink;
using FoldingParamsLinkSP = QSharedPointer<FoldingParamsLink>;
using FoldingParamsLinkWP = QWeakPointer<FoldingParamsLink>;

class ResourceLinkPool;
using ResourceLinkPoolSP = QSharedPointer<ResourceLinkPool>;
using ResourceLinkPoolWP = QWeakPointer<ResourceLinkPool>;

class Message;
using MessageSP = QSharedPointer<Message>;
using MessageWP = QWeakPointer<Message>;

class Query;
using QuerySP = QSharedPointer<Query>;
using QueryWP = QWeakPointer<Query>;

class Response;
using ResponseSP = QSharedPointer<Response>;
using ResponseWP = QWeakPointer<Response>;

class KnownDevicesQuery;
using KnownDevicesQuerySP = QSharedPointer<KnownDevicesQuery>;
using KnownDevicesQueryWP = QWeakPointer<KnownDevicesQuery>;

class KnownDevicesResponse;
using KnownDevicesResponseSP = QSharedPointer<KnownDevicesResponse>;
using KnownDevicesResponseWP = QWeakPointer<KnownDevicesResponse>;

class DeviceFilter;
using DeviceFilterSP = QSharedPointer<DeviceFilter>;
using DeviceFilterWP = QWeakPointer<DeviceFilter>;

class DeviceInfo;
using DeviceInfoSP = QSharedPointer<DeviceInfo>;
using DeviceInfoWP = QWeakPointer<DeviceInfo>;

class Notification;
using NotificationSP = QSharedPointer<Notification>;
using NotificationWP = QWeakPointer<Notification>;

}
}

#endif // PROOFNETWORKJDF_TYPES_H
