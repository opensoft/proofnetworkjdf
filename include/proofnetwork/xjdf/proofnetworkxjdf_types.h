/* Copyright 2019, OpenSoft Inc.
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
#ifndef PROOFNETWORKXJDF_TYPES_H
#define PROOFNETWORKXJDF_TYPES_H

#include "proofnetwork/proofnetwork_types.h"

#include <QSharedPointer>
#include <QWeakPointer>

namespace Proof {
namespace XJdf {

class AbstractNode;
using AbstractNodeSP = QSharedPointer<AbstractNode>;
using AbstractNodeWP = QWeakPointer<AbstractNode>;

class GrayBox;
using GrayBoxSP = QSharedPointer<GrayBox>;
using GrayBoxWP = QWeakPointer<GrayBox>;

class Document;
using DocumentSP = QSharedPointer<Document>;
using DocumentWP = QWeakPointer<Document>;

class AuditPool;
using AuditPoolSP = QSharedPointer<AuditPool>;
using AuditPoolWP = QWeakPointer<AuditPool>;

class AuditItemBase;
using AuditItemBaseSP = QSharedPointer<AuditItemBase>;
using AuditItemBaseWP = QWeakPointer<AuditItemBase>;

class AuditCreated;
using AuditCreatedSP = QSharedPointer<AuditCreated>;
using AuditCreatedWP = QWeakPointer<AuditCreated>;

class AuditNotification;
using AuditNotificationSP = QSharedPointer<AuditNotification>;
using AuditNotificationWP = QWeakPointer<AuditNotification>;

class ProductList;
using ProductListSP = QSharedPointer<ProductList>;
using ProductListWP = QWeakPointer<ProductList>;

class Product;
using ProductSP = QSharedPointer<Product>;
using ProductWP = QWeakPointer<Product>;

class ResourceSet;
using ResourceSetSP = QSharedPointer<ResourceSet>;
using ResourceSetWP = QWeakPointer<ResourceSet>;

class Resource;
using ResourceSP = QSharedPointer<Resource>;
using ResourceWP = QWeakPointer<Resource>;

class Component;
using ComponentSP = QSharedPointer<Component>;
using ComponentWP = QWeakPointer<Component>;

class BoxPackingParams;
using BoxPackingParamsSP = QSharedPointer<BoxPackingParams>;
using BoxPackingParamsWP = QWeakPointer<BoxPackingParams>;

class CuttingParams;
using CuttingParamsSP = QSharedPointer<CuttingParams>;
using CuttingParamsWP = QWeakPointer<CuttingParams>;

class DeliveryParams;
using DeliveryParamsSP = QSharedPointer<DeliveryParams>;
using DeliveryParamsWP = QWeakPointer<DeliveryParams>;

class Part;
using PartSP = QSharedPointer<Part>;
using PartWP = QWeakPointer<Part>;

class PartAmount;
using PartAmountSP = QSharedPointer<PartAmount>;
using PartAmountWP = QWeakPointer<PartAmount>;

class AmountPool;
using AmountPoolSP = QSharedPointer<AmountPool>;
using AmountPoolWP = QWeakPointer<AmountPool>;

class Intent;
using IntentSP = QSharedPointer<Intent>;
using IntentWP = QWeakPointer<Intent>;

class ColorIntent;
using ColorIntentSP = QSharedPointer<ColorIntent>;
using ColorIntentWP = QWeakPointer<ColorIntent>;

class FoldingIntent;
using FoldingIntentSP = QSharedPointer<FoldingIntent>;
using FoldingIntentWP = QWeakPointer<FoldingIntent>;

class Media;
using MediaSP = QSharedPointer<Media>;
using MediaWP = QWeakPointer<Media>;

class CutBlock;
using CutBlockSP = QSharedPointer<CutBlock>;
using CutBlockWP = QWeakPointer<CutBlock>;

class DropItem;
using DropItemSP = QSharedPointer<DropItem>;
using DropItemWP = QWeakPointer<DropItem>;

} // namespace XJdf
} // namespace Proof

#endif // PROOFNETWORKXJDF_TYPES_H
