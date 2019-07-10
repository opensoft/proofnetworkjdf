// clazy:skip

#include "proofnetwork/xjdf/data/amountpool.h"
#include "proofnetwork/xjdf/data/auditcreated.h"
#include "proofnetwork/xjdf/data/auditnotification.h"
#include "proofnetwork/xjdf/data/auditpool.h"
#include "proofnetwork/xjdf/data/boxpackingparams.h"
#include "proofnetwork/xjdf/data/colorintent.h"
#include "proofnetwork/xjdf/data/component.h"
#include "proofnetwork/xjdf/data/cutblock.h"
#include "proofnetwork/xjdf/data/cuttingparams.h"
#include "proofnetwork/xjdf/data/deliveryparams.h"
#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/data/dropitem.h"
#include "proofnetwork/xjdf/data/foldingintent.h"
#include "proofnetwork/xjdf/data/foldingparams.h"
#include "proofnetwork/xjdf/data/laminatingintent.h"
#include "proofnetwork/xjdf/data/media.h"
#include "proofnetwork/xjdf/data/part.h"
#include "proofnetwork/xjdf/data/partamount.h"
#include "proofnetwork/xjdf/data/partwaste.h"
#include "proofnetwork/xjdf/data/product.h"
#include "proofnetwork/xjdf/data/productlist.h"
#include "proofnetwork/xjdf/data/resourceset.h"

#include "gtest/proof/test_global.h"

#include <QFile>
#include <QFileInfo>
#include <QSignalSpy>
#include <QXmlStreamReader>

using namespace Proof;
using namespace Proof::XJdf;
using testing::Test;

class DocumentTest : public Test
{
public:
    DocumentTest() {}

protected:
    void SetUp() override
    {
        xjdfDocUT = Document::fromFile(":/data/proposal.xjdf");
        ASSERT_TRUE(xjdfDocUT);
    }

    void TearDown() override {}

protected:
    DocumentSP xjdfDocUT;
};

TEST_F(DocumentTest, isDirty)
{
    auto document = Document::create();
    ASSERT_FALSE(document->isDirty());

    ASSERT_FALSE(document->createNode<AmountPool>()->isDirty());
    ASSERT_FALSE(document->createNode<AuditCreated>()->isDirty());
    ASSERT_FALSE(document->createNode<AuditNotification>()->isDirty());
    ASSERT_FALSE(document->createNode<AuditPool>()->isDirty());
    ASSERT_FALSE(document->createNode<BoxPackingParams>()->isDirty());
    ASSERT_FALSE(document->createNode<ColorIntent>()->isDirty());
    ASSERT_FALSE(document->createNode<Component>()->isDirty());
    ASSERT_FALSE(document->createNode<CutBlock>(QString())->isDirty());
    ASSERT_FALSE(document->createNode<CuttingParams>()->isDirty());
    ASSERT_FALSE(document->createNode<DeliveryParams>()->isDirty());
    ASSERT_FALSE(document->createNode<DropItem>()->isDirty());
    ASSERT_FALSE(document->createNode<FoldingIntent>()->isDirty());
    ASSERT_FALSE(document->createNode<FoldingParams>()->isDirty());
    ASSERT_FALSE(document->createNode<LaminatingIntent>()->isDirty());
    ASSERT_FALSE(document->createNode<Media>(QString())->isDirty());
    ASSERT_FALSE(document->createNode<Part>()->isDirty());
    ASSERT_FALSE(document->createNode<PartAmount>()->isDirty());
    ASSERT_FALSE(document->createNode<PartWaste>()->isDirty());
    ASSERT_FALSE(document->createNode<Product>(QString())->isDirty());
    ASSERT_FALSE(document->createNode<ProductList>()->isDirty());
    ASSERT_FALSE(document->createNode<ResourceSet>()->isDirty());
}

TEST_F(DocumentTest, misc)
{
    auto dummyDocument = Document::create();

    EXPECT_TRUE(dummyDocument->namespaces().isEmpty());
    dummyDocument->addNamespace({"prefix", "https://www.test.com/test"});
    EXPECT_EQ(1, dummyDocument->namespaces().count());

    xjdfDocUT->toFile("tofile.xml");
    EXPECT_TRUE(QFileInfo("tofile.xml").exists());

    xjdfDocUT->setJobPartId("PART_ID");
    EXPECT_EQ("PART_ID", xjdfDocUT->jobPartId());

    xjdfDocUT->setTypes({ProcessType::Cutting});
    xjdfDocUT->addType(ProcessType::BoxPacking);
    ASSERT_EQ(2, xjdfDocUT->types().count());
    EXPECT_EQ(ProcessType::Cutting, xjdfDocUT->types().first());
    EXPECT_EQ(ProcessType::BoxPacking, xjdfDocUT->types().last());

    ASSERT_TRUE(xjdfDocUT->auditPool());
    auto auditPool = xjdfDocUT->auditPool();
    ASSERT_TRUE(auditPool->created());
    auto created = auditPool->created();
    created->setId("CREATED_ID");
    EXPECT_EQ("CREATED_ID", created->id());
    created->setDeviceId("CREATED_DEVICEID");
    EXPECT_EQ("CREATED_DEVICEID", created->deviceId());

    ASSERT_TRUE(xjdfDocUT->productList());
    auto productList = xjdfDocUT->productList();
    ASSERT_EQ(3, productList->products().size());

    auto product1 = productList->products()[0];
    auto productNew = dummyDocument->createNode<Product>("");
    productNew->updateFrom(product1);
    productNew->setId("newId");

    productList->addProduct(productNew);
    ASSERT_EQ(4, productList->products().size());
    auto productNew2 = productList->products()[3];
    EXPECT_EQ(productNew->id(), productNew2->id());

    auto color = product1->intentsByType<ColorIntent>()[0];
    ASSERT_EQ(2, color->spots().count());
    EXPECT_TRUE(color->spots()[Side::Front]);
    color->addSpot(Side::Back, true);
    EXPECT_TRUE(color->spots()[Side::Front]);
    EXPECT_TRUE(color->spots()[Side::Back]);
    color->addSpot(Side::Front, false);
    EXPECT_FALSE(color->spots()[Side::Front]);
    EXPECT_TRUE(color->spots()[Side::Back]);

    ASSERT_EQ(2, color->coatings().count());
    ASSERT_EQ(1, color->coatings()[Side::Front].count());
    ASSERT_EQ(1, color->coatings()[Side::Back].count());
    color->addCoating(Side::Front, CoatingType::Ink);
    ASSERT_EQ(2, color->coatings()[Side::Front].count());
    EXPECT_EQ(CoatingType::UV, color->coatings()[Side::Front][0]);
    EXPECT_EQ(CoatingType::Ink, color->coatings()[Side::Front][1]);
}

TEST_F(DocumentTest, toXJdf)
{
    QByteArray xml;
    QXmlStreamWriter writer(&xml);
    xjdfDocUT->toXJdf(writer);

    ASSERT_FALSE(xml.isEmpty());
    QXmlStreamReader reader(xml);
    auto xjdfDocNew = Document::fromXJdf(reader);

    EXPECT_EQ("PRESSSHEET_ID", xjdfDocNew->jobId());
    EXPECT_EQ(ProcessType::Cutting, xjdfDocNew->types()[0]);
    EXPECT_EQ(ProcessType::Folding, xjdfDocNew->types()[1]);
    EXPECT_EQ(ProcessType::BoxPacking, xjdfDocNew->types()[2]);

    ASSERT_EQ(2, xjdfDocNew->namespaces().count());
    EXPECT_EQ("profit", xjdfDocNew->namespaces()[1].prefix());
    EXPECT_EQ("https://www.opensoftdev.com/profit", xjdfDocNew->namespaces()[1].namespaceUri());

    ASSERT_TRUE(xjdfDocNew->auditPool());
    auto auditPool = xjdfDocNew->auditPool();
    ASSERT_TRUE(auditPool->created());
    auto created = auditPool->created();
    EXPECT_EQ("3BC-1PC", created->templateId());
    EXPECT_EQ("0.42", created->templateVersion());
    EXPECT_EQ("Sh-Job-Manager-Service", created->agentName());
    EXPECT_EQ("0.18.10.9", created->agentVersion());
    EXPECT_EQ(QDateTime::fromString("2018-01-29T16:00:20+00:00", Qt::ISODate), created->timestamp());

    ASSERT_FALSE(auditPool->notifications().isEmpty());
    auto notification = auditPool->notifications()[0];
    EXPECT_EQ("Cutting-Station", notification->agentName());
    EXPECT_EQ("0.18.9.23", notification->agentVersion());
    EXPECT_EQ(QDateTime::fromString("2018-02-05T16:00:20+00:00", Qt::ISODate), notification->timestamp());
    EXPECT_EQ(Severity::Event, notification->severityClass());

    ASSERT_TRUE(xjdfDocNew->productList());
    auto productList = xjdfDocNew->productList();
    ASSERT_EQ(3, productList->products().size());
    auto product1 = productList->products()[0];

    EXPECT_EQ("ProductInfo_1", product1->id());
    EXPECT_EQ("ORDER_ITEM_ID", product1->externalId());
    EXPECT_TRUE(product1->isRoot());
    EXPECT_EQ(30, product1->amount());
    EXPECT_EQ(ProductType::BusinessCard, product1->type());
    ASSERT_EQ(1, product1->intents().size());

    ASSERT_EQ(1, product1->intentsByType<ColorIntent>().size());
    ASSERT_FALSE(product1->intentsByType<FoldingIntent>().size());

    auto product3 = productList->products()[2];
    ASSERT_EQ(3, product3->intents().size());
    ASSERT_EQ(1, product3->intentsByType<ColorIntent>().size());
    ASSERT_EQ(1, product3->intentsByType<FoldingIntent>().size());
    ASSERT_EQ(1, product3->intentsByType<LaminatingIntent>().size());

    auto color = product1->intentsByType<ColorIntent>()[0];
    ASSERT_EQ(2, color->spots().count());
    EXPECT_TRUE(color->spots()[Side::Front]);
    ASSERT_EQ(2, color->coatings().count());
    ASSERT_EQ(1, color->coatings()[Side::Front].count());
    ASSERT_EQ(1, color->coatings()[Side::Back].count());
    EXPECT_EQ(CoatingType::UV, color->coatings()[Side::Front][0]);
    EXPECT_EQ(CoatingType::UV, color->coatings()[Side::Back][0]);

    auto folding = product3->intentsByType<FoldingIntent>()[0];
    EXPECT_EQ(FoldType::F4_2, folding->foldCatalog());

    auto laminating = product3->intentsByType<LaminatingIntent>()[0];
    EXPECT_EQ(Side::Front, laminating->surface());

    ASSERT_EQ(8, xjdfDocNew->resourceSets().count());

    auto resourceSet1 = xjdfDocNew->resourceSets()[0];
    EXPECT_EQ("DeliveryParams", resourceSet1->name());
    ASSERT_EQ(3, resourceSet1->resourcesByType<DeliveryParams>().count());
    auto deliveryParams = resourceSet1->resourcesByType<DeliveryParams>()[0];
    EXPECT_EQ(QDateTime::fromString("2018-02-28T16:00:20+00:00", Qt::ISODate), deliveryParams->required());
    ASSERT_EQ(1, deliveryParams->items().count());
    EXPECT_EQ(30, deliveryParams->items()[0]->amount());
    EXPECT_EQ("ProductInfo_1", deliveryParams->items()[0]->product()->id());

    auto resourceSet2 = xjdfDocNew->resourceSets()[1];
    EXPECT_EQ("Media", resourceSet2->name());
    ASSERT_EQ(1, resourceSet2->resourcesByType<Media>().count());
    auto media = resourceSet2->resourcesByType<Media>()[0];
    EXPECT_DOUBLE_EQ(1500.0, media->width());
    EXPECT_DOUBLE_EQ(1000.0, media->height());
    EXPECT_DOUBLE_EQ(1560.0, media->thickness());
    EXPECT_EQ(MediaType::Paper, media->type());
    EXPECT_EQ(MediaUnit::Sheet, media->unit());

    ASSERT_EQ(3, media->layers().count());
    auto frontLayer = media->layers().first();
    EXPECT_EQ(MediaType::Paper, frontLayer->type());
    auto insertLayer = media->layers().at(1);
    EXPECT_EQ(MediaType::MountingTape, insertLayer->type());
    auto backLayer = media->layers().first();
    EXPECT_EQ(MediaType::Paper, backLayer->type());

    auto resourceSet3 = xjdfDocNew->resourceSets()[2];
    EXPECT_EQ("Component", resourceSet3->name());
    ASSERT_EQ(1, resourceSet3->resourcesByType<Component>().count());
    auto component1 = resourceSet3->resourcesByType<Component>()[0];
    EXPECT_EQ(ResourceOrientation::Rotate90Orientation, component1->orientation());
    ASSERT_EQ(1, component1->amountPool()->parts().count());
    EXPECT_EQ(30, component1->amountPool()->parts()[0]->amount());
    EXPECT_EQ("Media_1", component1->mediaRef()->id());

    auto resourceSet4 = xjdfDocNew->resourceSets()[3];
    EXPECT_EQ("CuttingParams", resourceSet4->name());
    ASSERT_EQ(1, resourceSet4->resourcesByType<CuttingParams>().count());
    auto cuttingParams = resourceSet4->resourcesByType<CuttingParams>()[0];
    ASSERT_EQ(4, cuttingParams->cutBlocks().count());
    auto cutBlock = cuttingParams->cutBlocks()[0];
    EXPECT_EQ("Block_1", cutBlock->blockName());
    EXPECT_DOUBLE_EQ(1.0, cutBlock->x());
    EXPECT_DOUBLE_EQ(1.1, cutBlock->y());
    EXPECT_DOUBLE_EQ(400.0, cutBlock->width());
    EXPECT_DOUBLE_EQ(300.0, cutBlock->height());

    auto resourceSet5 = xjdfDocNew->resourceSets()[4];
    EXPECT_EQ("Component", resourceSet5->name());
    ASSERT_EQ(3, resourceSet5->resourcesByType<Component>().count());
    ASSERT_EQ(2, resourceSet5->combinedProcessIndexes().count());
    auto component2 = resourceSet5->resourcesByType<Component>()[1];
    EXPECT_DOUBLE_EQ(400.0, component2->width());
    EXPECT_DOUBLE_EQ(300.0, component2->height());
    EXPECT_DOUBLE_EQ(10.0, component2->thickness());
    ASSERT_EQ(2, component2->parts().count());
    EXPECT_EQ("Block_2", component2->parts()[0]->blockName());
    EXPECT_EQ("ProductInfo_2", component2->parts()[0]->productPart());

    auto resourceSet6 = xjdfDocNew->resourceSets()[5];
    EXPECT_EQ("BoxPackingParams", resourceSet6->name());
    ASSERT_EQ(3, resourceSet6->resourcesByType<BoxPackingParams>().count());
    auto boxPackingParams = resourceSet6->resourcesByType<BoxPackingParams>()[2];
    EXPECT_EQ(BoxType::Carton, boxPackingParams->boxType());
    EXPECT_EQ("Easter Bunny Box", boxPackingParams->boxTypeDetails());

    auto resourceSet7 = xjdfDocNew->resourceSets()[6];
    EXPECT_EQ("Component", resourceSet7->name());
    ASSERT_TRUE(resourceSet7->resources().count());
    ASSERT_EQ(1, resourceSet7->combinedProcessIndexes().count());
    EXPECT_EQ(1, resourceSet7->combinedProcessIndexes()[0]);
    EXPECT_EQ(UsageType::Output, resourceSet7->usage());

    auto component3 = resourceSet7->resourcesByType<Component>().first();
    ASSERT_TRUE(component3);
    ASSERT_EQ(1, component3->amountPool()->parts().count());
    auto partAmount = component3->amountPool()->parts().first();
    EXPECT_EQ(30, partAmount->amount());
    ASSERT_EQ(1, partAmount->parts().count());
    EXPECT_EQ("ProductInfo_3", partAmount->parts().first()->productPart());
    ASSERT_EQ(1, partAmount->partsWaste().count());
    EXPECT_EQ(10, partAmount->partsWaste().first()->waste());
    EXPECT_EQ(WasteDetails::Overrun, partAmount->partsWaste().first()->wasteDetails());

    auto resourceSet8 = xjdfDocNew->resourceSets()[7];
    EXPECT_EQ("FoldingParams", resourceSet8->name());
    ASSERT_EQ(3, resourceSet8->resourcesByType<FoldingParams>().count());
    auto foldingParams = resourceSet8->resourcesByType<FoldingParams>()[2];
    EXPECT_EQ("F6-1", foldingParams->foldCatalog());
    EXPECT_EQ("Test folding", foldingParams->foldingDetails());
}

TEST_F(DocumentTest, updateFrom)
{
    auto dummyDocument = Document::create();
    auto xjdfDocUT2 = Document::fromFile(":/data/proposal2.xjdf");
    auto xjdfDocUT3 = Document::create();
    ASSERT_TRUE(xjdfDocUT2);
    xjdfDocUT3->updateFrom(xjdfDocUT2);

    EXPECT_EQ(xjdfDocUT2->namespaces()[1], xjdfDocUT3->namespaces()[1]);

    EXPECT_EQ(xjdfDocUT2->jobId(), xjdfDocUT3->jobId());
    ASSERT_EQ(2, xjdfDocUT3->types().count());
    ASSERT_EQ(xjdfDocUT2->types().count(), xjdfDocUT3->types().count());
    EXPECT_EQ(xjdfDocUT2->types()[0], xjdfDocUT3->types()[0]);
    EXPECT_EQ(xjdfDocUT2->types()[1], xjdfDocUT3->types()[1]);

    auto auditPool = xjdfDocUT2->auditPool();
    auto auditPool2 = dummyDocument->createNode<AuditPool>();
    auditPool2->updateFrom(auditPool);
    auto created = auditPool->created();
    auto created2 = auditPool2->created();
    EXPECT_EQ(created2->templateId(), created->templateId());
    EXPECT_EQ(created2->templateVersion(), created->templateVersion());
    EXPECT_EQ(created2->agentName(), created->agentName());
    EXPECT_EQ(created2->agentVersion(), created->agentVersion());
    EXPECT_EQ(created2->timestamp(), created->timestamp());
    auto notification = auditPool->notifications()[0];
    auto notification2 = auditPool2->notifications()[0];
    EXPECT_EQ(notification2->agentName(), notification->agentName());
    EXPECT_EQ(notification2->agentVersion(), notification->agentVersion());
    EXPECT_EQ(notification2->timestamp(), notification->timestamp());
    EXPECT_EQ(notification2->severityClass(), notification->severityClass());

    created2 = dummyDocument->createNode<AuditCreated>();
    created2->updateFrom(created);
    EXPECT_EQ(created2->templateId(), created->templateId());
    EXPECT_EQ(created2->templateVersion(), created->templateVersion());
    EXPECT_EQ(created2->agentName(), created->agentName());
    EXPECT_EQ(created2->agentVersion(), created->agentVersion());
    EXPECT_EQ(created2->timestamp(), created->timestamp());

    notification2 = dummyDocument->createNode<AuditNotification>();
    notification2->updateFrom(notification);
    EXPECT_EQ(notification2->agentName(), notification->agentName());
    EXPECT_EQ(notification2->agentVersion(), notification->agentVersion());
    EXPECT_EQ(notification2->timestamp(), notification->timestamp());
    EXPECT_EQ(notification2->severityClass(), notification->severityClass());

    auto productList = xjdfDocUT2->productList();
    auto productList2 = xjdfDocUT3->productList();

    ASSERT_FALSE(productList->products().isEmpty());
    ASSERT_FALSE(productList2->products().isEmpty());
    auto product1 = productList->products()[0];
    auto product21 = productList2->products()[0];

    EXPECT_EQ(product21->id(), product1->id());
    EXPECT_EQ(product21->externalId(), product1->externalId());
    EXPECT_EQ(product21->isRoot(), product1->isRoot());
    EXPECT_EQ(product21->amount(), product1->amount());

    productList2 = dummyDocument->createNode<ProductList>();
    productList2->updateFrom(productList);

    product21 = productList2->products()[0];

    EXPECT_EQ(product21->id(), product1->id());
    EXPECT_EQ(product21->externalId(), product1->externalId());
    EXPECT_EQ(product21->isRoot(), product1->isRoot());
    EXPECT_EQ(product21->amount(), product1->amount());
    EXPECT_EQ(product21->type(), product1->type());
    EXPECT_EQ(product21->type(), product1->type());

    auto color = product1->intentsByType<ColorIntent>()[0];
    auto color2 = product21->intentsByType<ColorIntent>()[0];
    EXPECT_EQ(color2->spots()[Side::Front], color->spots()[Side::Front]);
    EXPECT_EQ(color2->coatings()[Side::Front][0], color->coatings()[Side::Front][0]);
    EXPECT_EQ(color2->coatings()[Side::Back][0], color->coatings()[Side::Back][0]);

    product21 = dummyDocument->createNode<Product>("0");
    product21->updateFrom(product1);

    EXPECT_EQ(product21->id(), product1->id());
    EXPECT_EQ(product21->externalId(), product1->externalId());
    EXPECT_EQ(product21->isRoot(), product1->isRoot());
    EXPECT_EQ(product21->amount(), product1->amount());
    EXPECT_EQ(product21->type(), product1->type());

    auto product3 = productList->products()[2];
    auto product23 = productList2->products()[2];

    color2 = dummyDocument->createNode<ColorIntent>();
    color2->updateFrom(color);
    EXPECT_EQ(color2->spots()[Side::Front], color->spots()[Side::Front]);
    EXPECT_EQ(color2->coatings()[Side::Front][0], color->coatings()[Side::Front][0]);
    EXPECT_EQ(color2->coatings()[Side::Back][0], color->coatings()[Side::Back][0]);

    auto folding = product3->intentsByType<FoldingIntent>()[0];
    auto folding2 = product23->intentsByType<FoldingIntent>()[0];
    EXPECT_EQ(folding2->foldCatalog(), folding->foldCatalog());

    product23 = dummyDocument->createNode<Product>("0");
    product23->updateFrom(product3);

    folding2 = product23->intentsByType<FoldingIntent>()[0];
    EXPECT_EQ(folding2->foldCatalog(), folding->foldCatalog());

    folding2 = dummyDocument->createNode<FoldingIntent>();
    folding2->updateFrom(folding);

    EXPECT_EQ(folding2->foldCatalog(), folding->foldCatalog());

    auto laminating = product3->intentsByType<LaminatingIntent>()[0];
    auto laminating2 = product23->intentsByType<LaminatingIntent>()[0];
    EXPECT_EQ(laminating2->surface(), laminating->surface());

    product23 = dummyDocument->createNode<Product>("0");
    product23->updateFrom(product3);

    laminating2 = product23->intentsByType<LaminatingIntent>()[0];
    EXPECT_EQ(laminating2->surface(), laminating->surface());

    laminating2 = dummyDocument->createNode<LaminatingIntent>();
    laminating2->updateFrom(laminating);

    EXPECT_EQ(laminating2->surface(), laminating->surface());

    auto resourceSet1 = xjdfDocUT3->resourceSets()[0];
    auto resourceSet21 = xjdfDocUT2->resourceSets()[0];
    EXPECT_EQ(resourceSet21->name(), resourceSet1->name());
    auto deliveryParams = resourceSet1->resourcesByType<DeliveryParams>()[0];
    auto deliveryParams2 = resourceSet21->resourcesByType<DeliveryParams>()[0];
    EXPECT_EQ(deliveryParams2->required(), deliveryParams->required());
    EXPECT_EQ(deliveryParams2->items()[0]->amount(), deliveryParams->items()[0]->amount());
    EXPECT_EQ(deliveryParams2->items()[0]->product()->id(), deliveryParams->items()[0]->product()->id());

    resourceSet21 = dummyDocument->createNode<ResourceSet>();
    resourceSet21->updateFrom(resourceSet1);

    EXPECT_EQ(resourceSet21->name(), resourceSet1->name());
    deliveryParams2 = resourceSet21->resourcesByType<DeliveryParams>()[0];
    EXPECT_EQ(deliveryParams2->required(), deliveryParams->required());
    EXPECT_EQ(deliveryParams2->items()[0]->amount(), deliveryParams->items()[0]->amount());
    EXPECT_EQ(deliveryParams2->items()[0]->product()->id(), deliveryParams->items()[0]->product()->id());

    deliveryParams2 = dummyDocument->createNode<DeliveryParams>();
    deliveryParams2->updateFrom(deliveryParams);
    EXPECT_EQ(deliveryParams2->required(), deliveryParams->required());
    EXPECT_EQ(deliveryParams2->items()[0]->amount(), deliveryParams->items()[0]->amount());
    EXPECT_EQ(deliveryParams2->items()[0]->product()->id(), deliveryParams->items()[0]->product()->id());

    auto resourceSet2 = xjdfDocUT2->resourceSets()[1];
    auto resourceSet22 = xjdfDocUT2->resourceSets()[1];
    EXPECT_EQ(resourceSet22->name(), resourceSet2->name());
    auto media = resourceSet2->resourcesByType<Media>()[0];
    auto media2 = resourceSet22->resourcesByType<Media>()[0];
    EXPECT_DOUBLE_EQ(media2->width(), media->width());
    EXPECT_DOUBLE_EQ(media2->height(), media->height());
    EXPECT_DOUBLE_EQ(media2->thickness(), media->thickness());

    media2 = dummyDocument->createNode<Media>();
    media2->updateFrom(media);
    EXPECT_DOUBLE_EQ(media2->width(), media->width());
    EXPECT_DOUBLE_EQ(media2->height(), media->height());
    EXPECT_DOUBLE_EQ(media2->thickness(), media->thickness());
    EXPECT_EQ(media2->type(), media->type());

    auto resourceSet3 = xjdfDocUT3->resourceSets()[2];
    auto resourceSet23 = xjdfDocUT2->resourceSets()[2];
    EXPECT_EQ(resourceSet23->name(), resourceSet3->name());
    auto component1 = resourceSet3->resourcesByType<Component>()[0];
    auto component21 = resourceSet23->resourcesByType<Component>()[0];
    EXPECT_EQ(component21->orientation(), component1->orientation());
    EXPECT_EQ(component21->amountPool()->parts()[0]->amount(), component1->amountPool()->parts()[0]->amount());
    EXPECT_EQ(component21->mediaRef()->id(), component1->mediaRef()->id());

    auto amountPool = component1->amountPool();
    auto amountPool2 = dummyDocument->createNode<AmountPool>();
    amountPool2->updateFrom(amountPool);
    EXPECT_EQ(amountPool->parts()[0]->amount(), amountPool2->parts()[0]->amount());

    auto partAmount = amountPool->parts()[0];
    auto partAmount2 = dummyDocument->createNode<PartAmount>();
    partAmount2->updateFrom(partAmount);
    EXPECT_EQ(partAmount->amount(), partAmount2->amount());

    component21 = dummyDocument->createNode<Component>();
    component21->updateFrom(component1);
    EXPECT_EQ(component21->orientation(), component1->orientation());
    EXPECT_EQ(component21->amountPool()->parts()[0]->amount(), component1->amountPool()->parts()[0]->amount());
    EXPECT_EQ(component21->mediaRef()->id(), component1->mediaRef()->id());

    auto resourceSet4 = xjdfDocUT3->resourceSets()[3];
    auto resourceSet24 = xjdfDocUT2->resourceSets()[3];
    EXPECT_EQ(resourceSet24->name(), resourceSet4->name());
    auto cuttingParams = resourceSet4->resourcesByType<CuttingParams>()[0];
    auto cuttingParams2 = resourceSet24->resourcesByType<CuttingParams>()[0];
    auto cutBlock = cuttingParams->cutBlocks()[0];
    auto cutBlock2 = cuttingParams2->cutBlocks()[0];
    EXPECT_EQ(cutBlock2->blockName(), cutBlock->blockName());

    cuttingParams2 = dummyDocument->createNode<CuttingParams>();
    cuttingParams2->updateFrom(cuttingParams);
    cutBlock2 = cuttingParams2->cutBlocks()[0];
    EXPECT_EQ(cutBlock2->blockName(), cutBlock->blockName());
    EXPECT_DOUBLE_EQ(cutBlock2->x(), cutBlock->x());
    EXPECT_DOUBLE_EQ(cutBlock2->y(), cutBlock->y());
    EXPECT_DOUBLE_EQ(cutBlock2->width(), cutBlock->width());
    EXPECT_DOUBLE_EQ(cutBlock2->height(), cutBlock->height());

    cutBlock2 = dummyDocument->createNode<CutBlock>();
    cutBlock2->updateFrom(cutBlock);
    EXPECT_EQ(cutBlock2->blockName(), cutBlock->blockName());
    EXPECT_DOUBLE_EQ(cutBlock2->x(), cutBlock->x());
    EXPECT_DOUBLE_EQ(cutBlock2->y(), cutBlock->y());
    EXPECT_DOUBLE_EQ(cutBlock2->width(), cutBlock->width());
    EXPECT_DOUBLE_EQ(cutBlock2->height(), cutBlock->height());

    auto resourceSet5 = xjdfDocUT3->resourceSets()[4];
    auto resourceSet25 = xjdfDocUT2->resourceSets()[4];
    EXPECT_EQ(resourceSet25->name(), resourceSet5->name());
    auto component2 = resourceSet5->resourcesByType<Component>()[1];
    auto component22 = resourceSet5->resourcesByType<Component>()[1];
    EXPECT_DOUBLE_EQ(component22->width(), component2->width());
    EXPECT_DOUBLE_EQ(component22->height(), component2->height());
    EXPECT_DOUBLE_EQ(component22->thickness(), component2->thickness());
    EXPECT_EQ(component22->parts()[0]->blockName(), component2->parts()[0]->blockName());
    EXPECT_EQ(component22->parts()[0]->productPart(), component2->parts()[0]->productPart());

    component22 = dummyDocument->createNode<Component>();
    component22->updateFrom(component2);
    EXPECT_DOUBLE_EQ(component22->width(), component2->width());
    EXPECT_DOUBLE_EQ(component22->height(), component2->height());
    EXPECT_DOUBLE_EQ(component22->thickness(), component2->thickness());
    EXPECT_EQ(component22->parts()[0]->blockName(), component2->parts()[0]->blockName());
    EXPECT_EQ(component22->parts()[0]->productPart(), component2->parts()[0]->productPart());

    auto resourceSet6 = xjdfDocUT3->resourceSets()[5];
    auto resourceSet26 = xjdfDocUT2->resourceSets()[5];
    EXPECT_EQ(resourceSet26->name(), resourceSet6->name());
    auto boxPackingParams = resourceSet6->resourcesByType<BoxPackingParams>()[2];
    auto boxPackingParams2 = resourceSet26->resourcesByType<BoxPackingParams>()[2];
    EXPECT_EQ(boxPackingParams2->boxType(), boxPackingParams->boxType());
    EXPECT_EQ(boxPackingParams2->boxTypeDetails(), boxPackingParams->boxTypeDetails());

    boxPackingParams2 = dummyDocument->createNode<BoxPackingParams>();
    boxPackingParams2->updateFrom(boxPackingParams);
    EXPECT_EQ(boxPackingParams2->boxType(), boxPackingParams->boxType());
    EXPECT_EQ(boxPackingParams2->boxTypeDetails(), boxPackingParams->boxTypeDetails());

    auto resourceSet7 = xjdfDocUT3->resourceSets()[6];
    auto resourceSet27 = xjdfDocUT2->resourceSets()[6];
    EXPECT_EQ(resourceSet27->name(), resourceSet7->name());
    EXPECT_EQ(resourceSet27->combinedProcessIndexes()[0], resourceSet7->combinedProcessIndexes()[0]);
    EXPECT_EQ(resourceSet27->usage(), resourceSet7->usage());

    resourceSet27 = dummyDocument->createNode<ResourceSet>();
    resourceSet27->updateFrom(resourceSet7);
    EXPECT_EQ(resourceSet27->combinedProcessIndexes()[0], resourceSet7->combinedProcessIndexes()[0]);
    EXPECT_EQ(resourceSet27->usage(), resourceSet7->usage());
}

TEST_F(DocumentTest, fromXJdf)
{
    EXPECT_EQ("PRESSSHEET_ID", xjdfDocUT->jobId());
    EXPECT_EQ(ProcessType::Cutting, xjdfDocUT->types()[0]);
    EXPECT_EQ(ProcessType::Folding, xjdfDocUT->types()[1]);
    EXPECT_EQ(ProcessType::BoxPacking, xjdfDocUT->types()[2]);

    //Default ns here too
    ASSERT_EQ(2, xjdfDocUT->namespaces().count());
    EXPECT_EQ("profit", xjdfDocUT->namespaces()[1].prefix());
    EXPECT_EQ("https://www.opensoftdev.com/profit", xjdfDocUT->namespaces()[1].namespaceUri());

    ASSERT_TRUE(xjdfDocUT->auditPool());
    auto auditPool = xjdfDocUT->auditPool();
    ASSERT_TRUE(auditPool->created());
    auto created = auditPool->created();
    EXPECT_EQ("3BC-1PC", created->templateId());
    EXPECT_EQ("0.42", created->templateVersion());
    EXPECT_EQ("Sh-Job-Manager-Service", created->agentName());
    EXPECT_EQ("0.18.10.9", created->agentVersion());
    EXPECT_EQ(QDateTime::fromString("2018-01-29T16:00:20+00:00", Qt::ISODate), created->timestamp());

    ASSERT_FALSE(auditPool->notifications().isEmpty());
    auto notification = auditPool->notifications()[0];
    EXPECT_EQ("Cutting-Station", notification->agentName());
    EXPECT_EQ("0.18.9.23", notification->agentVersion());
    EXPECT_EQ(QDateTime::fromString("2018-02-05T16:00:20+00:00", Qt::ISODate), notification->timestamp());
    EXPECT_EQ(Severity::Event, notification->severityClass());

    ASSERT_TRUE(xjdfDocUT->productList());
    auto productList = xjdfDocUT->productList();
    ASSERT_EQ(3, productList->products().size());
    auto product1 = productList->products()[0];

    EXPECT_EQ("ProductInfo_1", product1->id());
    EXPECT_EQ("ORDER_ITEM_ID", product1->externalId());
    EXPECT_TRUE(product1->isRoot());
    EXPECT_EQ(30, product1->amount());
    EXPECT_EQ(ProductType::BusinessCard, product1->type());
    ASSERT_EQ(1, product1->intents().size());

    ASSERT_EQ(1, product1->intentsByType<ColorIntent>().size());
    ASSERT_FALSE(product1->intentsByType<FoldingIntent>().size());

    auto product3 = productList->products()[2];
    ASSERT_EQ(3, product3->intents().size());
    ASSERT_EQ(1, product3->intentsByType<ColorIntent>().size());
    ASSERT_EQ(1, product3->intentsByType<FoldingIntent>().size());
    ASSERT_EQ(1, product3->intentsByType<LaminatingIntent>().size());

    auto color = product1->intentsByType<ColorIntent>()[0];
    ASSERT_EQ(2, color->spots().count());
    EXPECT_TRUE(color->spots()[Side::Front]);
    ASSERT_EQ(2, color->coatings().count());
    ASSERT_EQ(1, color->coatings()[Side::Front].count());
    ASSERT_EQ(1, color->coatings()[Side::Back].count());
    EXPECT_EQ(CoatingType::UV, color->coatings()[Side::Front][0]);
    EXPECT_EQ(CoatingType::UV, color->coatings()[Side::Back][0]);

    auto folding = product3->intentsByType<FoldingIntent>()[0];
    EXPECT_EQ(FoldType::F4_2, folding->foldCatalog());

    auto laminating = product3->intentsByType<LaminatingIntent>()[0];
    EXPECT_EQ(Side::Front, laminating->surface());

    ASSERT_EQ(8, xjdfDocUT->resourceSets().count());

    auto resourceSet1 = xjdfDocUT->resourceSets()[0];
    EXPECT_EQ("DeliveryParams", resourceSet1->name());
    ASSERT_EQ(3, resourceSet1->resourcesByType<DeliveryParams>().count());
    auto deliveryParams = resourceSet1->resourcesByType<DeliveryParams>()[0];
    EXPECT_EQ(QDateTime::fromString("2018-02-28T16:00:20+00:00", Qt::ISODate), deliveryParams->required());
    ASSERT_EQ(1, deliveryParams->items().count());
    EXPECT_EQ(30, deliveryParams->items()[0]->amount());
    EXPECT_EQ("ProductInfo_1", deliveryParams->items()[0]->product()->id());

    auto resourceSet2 = xjdfDocUT->resourceSets()[1];
    EXPECT_EQ("Media", resourceSet2->name());
    ASSERT_EQ(1, resourceSet2->resourcesByType<Media>().count());
    auto media = resourceSet2->resourcesByType<Media>()[0];
    EXPECT_DOUBLE_EQ(1500.0, media->width());
    EXPECT_DOUBLE_EQ(1000.0, media->height());
    EXPECT_DOUBLE_EQ(1560.0, media->thickness());
    EXPECT_EQ(MediaType::Paper, media->type());
    EXPECT_EQ(MediaUnit::Sheet, media->unit());

    ASSERT_EQ(3, media->layers().count());
    auto frontLayer = media->layers().first();
    EXPECT_EQ(MediaType::Paper, frontLayer->type());
    auto insertLayer = media->layers().at(1);
    EXPECT_EQ(MediaType::MountingTape, insertLayer->type());
    auto backLayer = media->layers().first();
    EXPECT_EQ(MediaType::Paper, backLayer->type());

    auto resourceSet3 = xjdfDocUT->resourceSets()[2];
    EXPECT_EQ("Component", resourceSet3->name());
    ASSERT_EQ(1, resourceSet3->resourcesByType<Component>().count());
    auto component1 = resourceSet3->resourcesByType<Component>()[0];
    EXPECT_EQ(ResourceOrientation::Rotate90Orientation, component1->orientation());
    ASSERT_EQ(1, component1->amountPool()->parts().count());
    EXPECT_EQ(30, component1->amountPool()->parts()[0]->amount());
    EXPECT_EQ("Media_1", component1->mediaRef()->id());

    auto resourceSet4 = xjdfDocUT->resourceSets()[3];
    EXPECT_EQ("CuttingParams", resourceSet4->name());
    ASSERT_EQ(1, resourceSet4->resourcesByType<CuttingParams>().count());
    auto cuttingParams = resourceSet4->resourcesByType<CuttingParams>()[0];
    ASSERT_EQ(4, cuttingParams->cutBlocks().count());
    auto cutBlock = cuttingParams->cutBlocks()[0];
    EXPECT_EQ("Block_1", cutBlock->blockName());
    EXPECT_DOUBLE_EQ(1.0, cutBlock->x());
    EXPECT_DOUBLE_EQ(1.1, cutBlock->y());
    EXPECT_DOUBLE_EQ(400.0, cutBlock->width());
    EXPECT_DOUBLE_EQ(300.0, cutBlock->height());

    auto resourceSet5 = xjdfDocUT->resourceSets()[4];
    EXPECT_EQ("Component", resourceSet5->name());
    ASSERT_EQ(3, resourceSet5->resourcesByType<Component>().count());
    ASSERT_EQ(2, resourceSet5->combinedProcessIndexes().count());
    auto component2 = resourceSet5->resourcesByType<Component>()[1];
    EXPECT_DOUBLE_EQ(400.0, component2->width());
    EXPECT_DOUBLE_EQ(300.0, component2->height());
    EXPECT_DOUBLE_EQ(10.0, component2->thickness());
    ASSERT_EQ(2, component2->parts().count());
    EXPECT_EQ("Block_2", component2->parts()[0]->blockName());
    EXPECT_EQ("ProductInfo_2", component2->parts()[0]->productPart());

    auto resourceSet6 = xjdfDocUT->resourceSets()[5];
    EXPECT_EQ("BoxPackingParams", resourceSet6->name());
    ASSERT_EQ(3, resourceSet6->resourcesByType<BoxPackingParams>().count());
    auto boxPackingParams = resourceSet6->resourcesByType<BoxPackingParams>()[2];
    EXPECT_EQ(BoxType::Carton, boxPackingParams->boxType());
    EXPECT_EQ("Easter Bunny Box", boxPackingParams->boxTypeDetails());

    auto resourceSet7 = xjdfDocUT->resourceSets()[6];
    EXPECT_EQ("Component", resourceSet7->name());
    ASSERT_EQ(1, resourceSet7->resources().count());
    ASSERT_EQ(1, resourceSet7->combinedProcessIndexes().count());
    EXPECT_EQ(1, resourceSet7->combinedProcessIndexes()[0]);
    EXPECT_EQ(UsageType::Output, resourceSet7->usage());

    auto component3 = resourceSet7->resourcesByType<Component>().first();
    ASSERT_TRUE(component3);
    ASSERT_EQ(1, component3->amountPool()->parts().count());
    auto partAmount = component3->amountPool()->parts().first();
    EXPECT_EQ(30, partAmount->amount());
    ASSERT_EQ(1, partAmount->parts().count());
    EXPECT_EQ("ProductInfo_3", partAmount->parts().first()->productPart());
    ASSERT_EQ(1, partAmount->partsWaste().count());
    EXPECT_EQ(10, partAmount->partsWaste().first()->waste());
    EXPECT_EQ(WasteDetails::Overrun, partAmount->partsWaste().first()->wasteDetails());

    auto resourceSet8 = xjdfDocUT->resourceSets()[7];
    EXPECT_EQ("FoldingParams", resourceSet8->name());
    ASSERT_EQ(3, resourceSet8->resourcesByType<FoldingParams>().count());
    auto foldingParams = resourceSet8->resourcesByType<FoldingParams>()[2];
    EXPECT_EQ("F6-1", foldingParams->foldCatalog());
    EXPECT_EQ("Test folding", foldingParams->foldingDetails());
}

TEST_F(DocumentTest, findResources)
{
    auto components = xjdfDocUT->findResources<Component>(
        [](const auto &component) { return component->mediaRef()->id() == "Media_1"; });
    EXPECT_EQ(1, components.count());

    auto cuttingParamsList = xjdfDocUT->findResources<CuttingParams>();
    EXPECT_EQ(1, cuttingParamsList.count());

    auto deliveryParamsList = xjdfDocUT->findResources<DeliveryParams>();
    EXPECT_EQ(4, deliveryParamsList.count());
}
