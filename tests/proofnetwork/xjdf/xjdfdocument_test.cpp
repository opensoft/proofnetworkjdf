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
#include "proofnetwork/xjdf/data/dropitem.h"
#include "proofnetwork/xjdf/data/foldingintent.h"
#include "proofnetwork/xjdf/data/media.h"
#include "proofnetwork/xjdf/data/part.h"
#include "proofnetwork/xjdf/data/partamount.h"
#include "proofnetwork/xjdf/data/product.h"
#include "proofnetwork/xjdf/data/productlist.h"
#include "proofnetwork/xjdf/data/resourceset.h"
#include "proofnetwork/xjdf/data/xjdfdocument.h"

#include "gtest/proof/test_global.h"

#include <QFile>
#include <QSignalSpy>
#include <QXmlStreamReader>

using namespace Proof;
using namespace Proof::XJdf;
using testing::Test;

class XJdfDocumentTest : public Test
{
public:
    XJdfDocumentTest() {}

protected:
    void SetUp() override
    {
        xjdfDocUT = XJdfDocument::fromFile(":/data/proposal.xjdf");
        ASSERT_TRUE(xjdfDocUT);
    }

    void TearDown() override {}

protected:
    XJdfDocumentSP xjdfDocUT;
};

TEST_F(XJdfDocumentTest, toXJdf)
{
    QByteArray xml;
    QXmlStreamWriter writer(&xml);
    xjdfDocUT->toXJdf(writer);

    ASSERT_FALSE(xml.isEmpty());
    QXmlStreamReader reader(xml);
    auto xjdfDocNew = XJdfDocument::fromXJdf(reader);
}

TEST_F(XJdfDocumentTest, fromXJdf)
{
    EXPECT_EQ("PRESSSHEET_ID", xjdfDocUT->jobId());
    EXPECT_EQ(ProcessType::Cutting, xjdfDocUT->types()[0]);
    EXPECT_EQ(ProcessType::BoxPacking, xjdfDocUT->types()[1]);

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
    ASSERT_EQ(2, product3->intents().size());
    ASSERT_EQ(1, product3->intentsByType<ColorIntent>().size());
    ASSERT_EQ(1, product3->intentsByType<FoldingIntent>().size());

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

    ASSERT_EQ(7, xjdfDocUT->resourceSets().count());

    auto resourceSet1 = xjdfDocUT->resourceSets()[0];
    EXPECT_EQ("DeliveryParams", resourceSet1->name());
    ASSERT_EQ(3, resourceSet1->resourcesByType<DeliveryParams>().count());
    auto deliveryParams = resourceSet1->resourcesByType<DeliveryParams>()[0];
    EXPECT_EQ(QDateTime::fromString("2018-02-28T16:00:20+00:00", Qt::ISODate), deliveryParams->required());
    ASSERT_EQ(1, deliveryParams->items().count());
    EXPECT_EQ(30, deliveryParams->items()[0]->amount());
    //TODO check prodref

    auto resourceSet2 = xjdfDocUT->resourceSets()[1];
    EXPECT_EQ("Media", resourceSet2->name());
    ASSERT_EQ(1, resourceSet2->resourcesByType<Media>().count());
    auto media = resourceSet2->resourcesByType<Media>()[0];
    EXPECT_DOUBLE_EQ(1500.0, media->width());
    EXPECT_DOUBLE_EQ(1000.0, media->height());
    EXPECT_DOUBLE_EQ(1560.0, media->thickness());

    auto resourceSet3 = xjdfDocUT->resourceSets()[2];
    EXPECT_EQ("Component", resourceSet3->name());
    ASSERT_EQ(1, resourceSet3->resourcesByType<Component>().count());
    auto component1 = resourceSet3->resourcesByType<Component>()[0];
    EXPECT_EQ(ResourceOrientation::Rotate90Orientation, component1->orientation());
    ASSERT_EQ(1, component1->amountPool()->parts().count());
    EXPECT_EQ(30, component1->amountPool()->parts()[0]->amount());
    //TODO Check mediaref

    auto resourceSet4 = xjdfDocUT->resourceSets()[3];
    EXPECT_EQ("CuttingParams", resourceSet4->name());
    ASSERT_EQ(1, resourceSet4->resourcesByType<CuttingParams>().count());
    auto cuttingParams = resourceSet4->resourcesByType<CuttingParams>()[0];
    ASSERT_EQ(4, cuttingParams->cutBlocks().count());
    auto cutBlock = cuttingParams->cutBlocks()[0];
    EXPECT_EQ("Block_1", cutBlock->blockName());

    auto resourceSet5 = xjdfDocUT->resourceSets()[4];
    EXPECT_EQ("Component", resourceSet5->name());
    ASSERT_EQ(3, resourceSet5->resourcesByType<Component>().count());
    ASSERT_EQ(2, resourceSet5->combinedProcessIndexes().count());
    auto component2 = resourceSet5->resourcesByType<Component>()[1];
    EXPECT_DOUBLE_EQ(400.0, component2->width());
    EXPECT_DOUBLE_EQ(300.0, component2->height());
    EXPECT_DOUBLE_EQ(10.0, component2->thickness());
    ASSERT_EQ(2, component2->parts().count());
    //TODO check parts

    auto resourceSet6 = xjdfDocUT->resourceSets()[5];
    EXPECT_EQ("BoxPackingParams", resourceSet6->name());
    ASSERT_EQ(3, resourceSet6->resourcesByType<BoxPackingParams>().count());
    auto boxPackingParams = resourceSet6->resourcesByType<BoxPackingParams>()[2];
    EXPECT_EQ(BoxType::Carton, boxPackingParams->boxType());
    EXPECT_EQ("Easter Bunny Box", boxPackingParams->boxTypeDetails());

    auto resourceSet7 = xjdfDocUT->resourceSets()[6];
    EXPECT_EQ("Component", resourceSet7->name());
    ASSERT_FALSE(resourceSet7->resources().count());
    ASSERT_EQ(1, resourceSet7->combinedProcessIndexes().count());
    EXPECT_EQ(1, resourceSet7->combinedProcessIndexes()[0]);
    EXPECT_EQ(UsageType::Output, resourceSet7->usage());
}
