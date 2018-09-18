/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
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

class AbstractAudit;
using AbstractAuditSP = QSharedPointer<AbstractAudit>;
using AbstractAuditWP = QWeakPointer<AbstractAudit>;

class JdfNode;
using JdfNodeSP = QSharedPointer<JdfNode>;
using JdfNodeWP = QWeakPointer<JdfNode>;

class JdfDocument;
using JdfDocumentSP = QSharedPointer<JdfDocument>;
using JdfDocumentWP = QWeakPointer<JdfDocument>;

class JmfDocument;
using JmfDocumentSP = QSharedPointer<JmfDocument>;
using JmfDocumentWP = QWeakPointer<JmfDocument>;

class AuditPool;
using AuditPoolSP = QSharedPointer<AuditPool>;
using AuditPoolWP = QWeakPointer<AuditPool>;

class CreatedAudit;
using CreatedAuditSP = QSharedPointer<CreatedAudit>;
using CreatedAuditWP = QWeakPointer<CreatedAudit>;

class ModifiedAudit;
using ModifiedAuditSP = QSharedPointer<ModifiedAudit>;
using ModifiedAuditWP = QWeakPointer<ModifiedAudit>;

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

class BoxPackingParams;
using BoxPackingParamsSP = QSharedPointer<BoxPackingParams>;
using BoxPackingParamsWP = QSharedPointer<BoxPackingParams>;

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

class BoxPackingParamsLink;
using BoxPackingParamsLinkSP = QSharedPointer<BoxPackingParamsLink>;
using BoxPackingParamsLinkWP = QWeakPointer<BoxPackingParamsLink>;

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

} // namespace Jdf
} // namespace Proof

#endif // PROOFNETWORKJDF_TYPES_H
