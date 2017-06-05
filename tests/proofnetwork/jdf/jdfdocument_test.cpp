// clazy:skip
#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/auditpool.h"
#include "proofnetwork/jdf/data/createdaudit.h"
#include "proofnetwork/jdf/data/modifiedaudit.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/bundleitem.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/layout.h"
#include "proofnetwork/jdf/data/laminatingintent.h"
#include "proofnetwork/jdf/data/deliveryintent.h"
#include "proofnetwork/jdf/data/dropintent.h"
#include "proofnetwork/jdf/data/dropitemintent.h"
#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/laminatingintentlink.h"
#include "proofnetwork/jdf/data/componentlink.h"

#include <QXmlStreamReader>
#include <QSignalSpy>
#include <QFile>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class JdfDocumentTest: public Test
{
public:
    JdfDocumentTest()
    {
    }

protected:
    void SetUp() override
    {
        QFile file(":/data/jdfdocument.jdf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        jdfDocUT = JdfDocument::fromJdf(xml);
        ASSERT_TRUE(jdfDocUT);

        QFile file2(":/data/jdfdocument2.jdf");
        ASSERT_TRUE(file2.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml2(&file2);
        jdfDocUT2 = JdfDocument::fromJdf(xml2);
        ASSERT_TRUE(jdfDocUT2);

        QFile file3(":/data/jdfnested.jdf");
        ASSERT_TRUE(file3.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml3(&file3);
        jdfDocUT3 = JdfDocument::fromJdf(xml3);
        ASSERT_TRUE(jdfDocUT3);

        QFile file4(":/data/jdfwithpartitionedcomponents.jdf");
        ASSERT_TRUE(file4.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml4(&file4);
        jdfDocUT4 = JdfDocument::fromJdf(xml4);
        ASSERT_TRUE(jdfDocUT4);

        qmlWrapperUT = jdfDocUT->toQmlWrapper();
    }

    void TearDown() override
    {
        delete qmlWrapperUT;
    }

protected:
    JdfDocumentSP jdfDocUT;
    JdfDocumentSP jdfDocUT2;
    JdfDocumentSP jdfDocUT3;
    JdfDocumentSP jdfDocUT4;
    JdfDocumentQmlWrapper *qmlWrapperUT;
};

TEST_F(JdfDocumentTest, fromJdf)
{
    EXPECT_EQ("JDF_0000", jdfDocUT->id());
    EXPECT_EQ("mixed-flatwork (groups)", jdfDocUT->jobId());
    EXPECT_EQ("ID0001", jdfDocUT->jobPartId());

    AuditPoolSP auditPool = jdfDocUT->auditPool();
    ASSERT_TRUE(auditPool);

    CreatedAuditSP created = auditPool->created();
    ASSERT_TRUE(created);
    EXPECT_EQ("AUD_0000", created->id());
    EXPECT_EQ("K-BC-63", created->templateId());
    EXPECT_EQ("1317311496.73", created->templateVersion());
    EXPECT_EQ("Metrix", created->agentName());
    EXPECT_EQ("2013.0 (1050)", created->agentVersion());
    EXPECT_EQ(QDateTime::fromString(QString("2014-08-26T08:35:28-07:00"), Qt::ISODate), created->timeStamp());

    ModifiedAuditSP modified= auditPool->modified();
    ASSERT_TRUE(modified);
    EXPECT_EQ("AUD_0002", modified->id());
    EXPECT_EQ("Metrix2", modified->agentName());
    EXPECT_EQ("2015.0 (1050)", modified->agentVersion());
    EXPECT_EQ(QDateTime::fromString(QString("2015-08-26T08:35:28-07:00"), Qt::ISODate), modified->timeStamp());

    ASSERT_EQ(2, jdfDocUT->jdfNodes().count());

    JdfNodeSP jdfNode = jdfDocUT->jdfNodes().first();
    ASSERT_TRUE(jdfNode);
    EXPECT_EQ("LAYOUT_0001", jdfNode->id());

    ResourcePoolSP resourcePool = jdfNode->resourcePool();
    ASSERT_TRUE(resourcePool);

    ASSERT_EQ(4, resourcePool->components().count());

    ComponentSP component = resourcePool->components().first();
    ASSERT_TRUE(component);
    EXPECT_EQ("COMP_0000", component->id());
    EXPECT_DOUBLE_EQ(2520.0, component->width());
    EXPECT_DOUBLE_EQ(1656.0, component->height());
    EXPECT_DOUBLE_EQ(0.4896, component->length());
    EXPECT_EQ(1000u, component->amount());

    ComponentSP component2 = resourcePool->components().at(1);
    ASSERT_TRUE(component2);
    EXPECT_EQ("A_OUT", component2->id());
    EXPECT_EQ("PartialProduct", componentTypeToString(component2->componentType()));
    EXPECT_DOUBLE_EQ(432.0, component2->width());
    EXPECT_DOUBLE_EQ(288.0, component2->height());
    EXPECT_DOUBLE_EQ(0.4896, component2->length());

    EXPECT_EQ(15, component2->cutBlocks().count());

    EXPECT_EQ(1, component2->partIdKeys().count());
    EXPECT_EQ(ResourcePartType::BlockNamePart, component2->partIdKeys().first());

    BundleSP bundle = component2->bundle();
    ASSERT_TRUE(bundle);
    EXPECT_EQ(BundleType::BoxBundle, bundle->bundleType());
    EXPECT_EQ(42, bundle->totalAmount());
    ASSERT_TRUE(bundle->bundleItems().count());
    EXPECT_EQ(42, bundle->bundleItems().first()->amount());

    ComponentSP component3 = resourcePool->components().last();
    ASSERT_TRUE(component3);
    BundleSP bundle2 = component3->bundle();
    ASSERT_TRUE(bundle2);
    EXPECT_EQ(BundleType::BoxBundle, bundle2->bundleType());
    EXPECT_EQ(1000, bundle2->totalAmount());
    ASSERT_TRUE(bundle2->bundleItems().count());
    BundleItemSP bundleItem = bundle2->bundleItems().first();
    ASSERT_TRUE(bundleItem);
    EXPECT_EQ(500, bundleItem->amount());
    EXPECT_EQ("B_OUT", bundleItem->component()->id());

    CuttingParamsSP cuttingParams = resourcePool->cuttingParams();
    ASSERT_TRUE(cuttingParams);
    ASSERT_EQ("CPM_0000", cuttingParams->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, cuttingParams->resourceStatus());
    EXPECT_EQ(ResourceClass::ParameterClass, cuttingParams->resourceClass());
    ASSERT_EQ(23, cuttingParams->cutBlocks().count());

    CutBlockSP cutBlock1 = component2->cutBlocks().first();
    CutBlockSP cutBlock2 = cuttingParams->cutBlocks().first();
    for (const CutBlockSP &cutBlock : {cutBlock1, cutBlock2}) {
        ASSERT_TRUE(cutBlock);
        EXPECT_EQ("A-1", cutBlock->blockName());
        EXPECT_DOUBLE_EQ(432, cutBlock->width());
        EXPECT_DOUBLE_EQ(288, cutBlock->height());
        EXPECT_DOUBLE_EQ(54.0000, cutBlock->x());
        EXPECT_DOUBLE_EQ(36.0000, cutBlock->y());
        EXPECT_DOUBLE_EQ(0.0, cutBlock->rotation());
        EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlock->transformationMatrix());
        EXPECT_EQ(BlockType::CutBlock, cutBlock->blockType());
    }

    ASSERT_EQ(4, resourcePool->media().count());
    MediaSP media = resourcePool->media()[2];
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0000", media->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, media->resourceStatus());
    EXPECT_EQ(CoatingType::NoCoating, media->backCoating());
    EXPECT_EQ(CoatingType::HighGlossCoating, media->frontCoating());
    EXPECT_EQ(MediaUnit::SheetMediaUnit, media->mediaUnit());
    EXPECT_EQ(MediaType::PaperMedia, media->mediaType());
    EXPECT_DOUBLE_EQ(2520.0, media->width());
    EXPECT_DOUBLE_EQ(1656.0, media->height());
    EXPECT_DOUBLE_EQ(172.72, media->thickness());

    ASSERT_EQ(2, media->layers().count());

    MediaSP layer = media->layers()[0];
    ASSERT_TRUE(layer);
    EXPECT_EQ("PAP_0000_front", layer->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, layer->resourceStatus());
    EXPECT_EQ(MediaType::SelfAdhesiveMedia, layer->mediaType());
    EXPECT_DOUBLE_EQ(2520.0, layer->width());
    EXPECT_DOUBLE_EQ(1656.0, layer->height());
    EXPECT_DOUBLE_EQ(100.0, layer->thickness());

    layer = media->layers()[1];
    ASSERT_TRUE(layer);
    EXPECT_EQ("PAP_0000_back", layer->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, layer->resourceStatus());
    EXPECT_EQ(MediaType::SelfAdhesiveMedia, layer->mediaType());
    EXPECT_DOUBLE_EQ(2520.0, layer->width());
    EXPECT_DOUBLE_EQ(1656.0, layer->height());
    EXPECT_DOUBLE_EQ(72.72, layer->thickness());

    media = resourcePool->media()[3];
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0001", media->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, media->resourceStatus());
    EXPECT_EQ(MediaType::PlateMedia, media->mediaType());
    EXPECT_DOUBLE_EQ(2620.0, media->width());
    EXPECT_DOUBLE_EQ(1756.0, media->height());

    ASSERT_EQ(1, resourcePool->layouts().count());
    LayoutSP layout = resourcePool->layouts()[0];
    ASSERT_TRUE(layout);
    EXPECT_EQ("Layout1", layout->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, layout->resourceStatus());

    ASSERT_EQ(3, layout->media().count());
    media = layout->media()[0];
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0002", media->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, media->resourceStatus());
    EXPECT_EQ(MediaType::PaperMedia, media->mediaType());
    EXPECT_DOUBLE_EQ(2521.0, media->width());
    EXPECT_DOUBLE_EQ(1657.0, media->height());

    media = layout->media()[1];
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0003", media->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, media->resourceStatus());
    EXPECT_EQ(MediaType::PlateMedia, media->mediaType());
    EXPECT_DOUBLE_EQ(2621.0, media->width());
    EXPECT_DOUBLE_EQ(1757.0, media->height());

    media = layout->media()[2];
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0004", media->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, media->resourceStatus());
    EXPECT_EQ(MediaType::OtherMedia, media->mediaType());
    EXPECT_DOUBLE_EQ(2721.0, media->width());
    EXPECT_DOUBLE_EQ(1857.0, media->height());

    LaminatingIntentSP laminatingIntent = resourcePool->laminatingIntent();
    ASSERT_TRUE(laminatingIntent);

    EXPECT_EQ("LI_0000", laminatingIntent->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, laminatingIntent->resourceStatus());
    EXPECT_EQ(LaminatingSurface::BothLaminated, laminatingIntent->surface());

    DeliveryIntentSP deliveryIntent = resourcePool->deliveryIntent();
    ASSERT_TRUE(deliveryIntent);
    EXPECT_EQ("DI_0000", deliveryIntent->id());

    ASSERT_TRUE(deliveryIntent->dropIntents().count());
    DropIntentSP dropIntent = deliveryIntent->dropIntents().first();
    ASSERT_TRUE(dropIntent);
    EXPECT_EQ(QDateTime::fromString(QString("2014-08-26T08:35:28-07:00"), Qt::ISODate), dropIntent->required().actual());

    DropItemIntentSP dropItemIntent = dropIntent->dropItemIntents().first();
    ASSERT_TRUE(dropItemIntent);
    EXPECT_EQ("A_OUT", dropItemIntent->component()->id());

    JdfNodeSP jdfNode2 = jdfDocUT->jdfNodes().last();
    ASSERT_TRUE(jdfNode2);
    EXPECT_EQ("BoxPacking_B", jdfNode2->id());

    ResourcePoolSP resourcePoolBoxPacking = jdfNode2->resourcePool();
    ASSERT_TRUE(resourcePoolBoxPacking);

    ASSERT_EQ(1, resourcePoolBoxPacking->components().count());

    ComponentSP componentBox = resourcePoolBoxPacking->components().first();
    ASSERT_TRUE(componentBox);
    EXPECT_EQ("Box1ID", componentBox->id());
    EXPECT_EQ(ComponentType::SheetComponent, componentBox->componentType());
    EXPECT_EQ(ProductType::FlatBoxProduct, componentBox->productType());
    EXPECT_EQ("Envelope", componentBox->productTypeDetails());

    ResourceLinkPoolSP resourceLinkPoolBoxPacking = jdfNode2->resourceLinkPool();
    ASSERT_TRUE(resourceLinkPoolBoxPacking);

    ASSERT_EQ(3, resourceLinkPoolBoxPacking->componentLinks().count());
    ComponentLinkSP componentLinkBox = resourceLinkPoolBoxPacking->componentLinks().first();
    ASSERT_TRUE(componentLinkBox);
    EXPECT_EQ("Box1ID", componentLinkBox->rRef());
    EXPECT_EQ(ProcessUsage::UseAsBox, componentLinkBox->processUsage());
}

TEST_F(JdfDocumentTest, fromNestedJdfFirstLevel)
{
    EXPECT_EQ("JDF_0000", jdfDocUT3->id());
    EXPECT_EQ("mixed-flatwork (groups)_2", jdfDocUT3->jobId());
    EXPECT_EQ("ID0001", jdfDocUT3->jobPartId());

    ASSERT_EQ(1, jdfDocUT3->jdfNodes().count());
    JdfNodeSP jdfNode = jdfDocUT3->jdfNodes().first();
    ASSERT_TRUE(jdfNode);

    EXPECT_EQ("ID_Product_0001", jdfNode->id());
    EXPECT_EQ("Product_0001", jdfNode->jobPartId());

    ResourcePoolSP resourcePool = jdfNode->resourcePool();
    ASSERT_TRUE(resourcePool);

    EXPECT_EQ(3, resourcePool->components().count());

    ASSERT_EQ(1, resourcePool->media().count());
    MediaSP media = resourcePool->media().first();
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_1234", media->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, media->resourceStatus());
    EXPECT_EQ(CoatingType::HighGlossCoating, media->frontCoating());
    EXPECT_EQ(CoatingDetail::ProfitFullCoating, media->frontCoatingDetail());
    EXPECT_EQ(CoatingType::NoCoating, media->backCoating());
    EXPECT_EQ(CoatingDetail::NoCoatingDetail, media->backCoatingDetail());
    EXPECT_EQ(MediaUnit::SheetMediaUnit, media->mediaUnit());
    EXPECT_DOUBLE_EQ(2520.0, media->width());
    EXPECT_DOUBLE_EQ(1656.0, media->height());
    EXPECT_DOUBLE_EQ(172.72, media->thickness());

    LaminatingIntentSP laminatingIntent = resourcePool->laminatingIntent();
    ASSERT_TRUE(laminatingIntent);

    EXPECT_EQ("LI_0000", laminatingIntent->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, laminatingIntent->resourceStatus());
    EXPECT_EQ(LaminatingSurface::BothLaminated, laminatingIntent->surface());

    ASSERT_EQ(3, resourcePool->components().count());
    ComponentSP component = resourcePool->components().first();
    ASSERT_TRUE(component);
    EXPECT_EQ("COMP_0000", component->id());
    EXPECT_DOUBLE_EQ(2520.0, component->width());
    EXPECT_DOUBLE_EQ(1656.0, component->height());
    EXPECT_DOUBLE_EQ(0.4896, component->length());
    EXPECT_EQ(1000u, component->amount());

    ComponentSP component2 = resourcePool->components().at(1);
    ASSERT_TRUE(component2);
    EXPECT_EQ("A_OUT", component2->id());
    ASSERT_TRUE(component2->cutBlocks().count());
    CutBlockSP cutBlock = component2->cutBlocks().first();
    ASSERT_TRUE(cutBlock);
    EXPECT_EQ("A-1", cutBlock->blockName());
    EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlock->transformationMatrix());

    ComponentSP componentFold = resourcePool->components().last();
    ASSERT_TRUE(componentFold);
    EXPECT_EQ("A_FOLD", componentFold->id());

    BundleSP bundle = componentFold->bundle();
    ASSERT_TRUE(bundle);
    EXPECT_EQ(BundleType::BoxBundle, bundle->bundleType());
    EXPECT_EQ(42, bundle->totalAmount());
}

TEST_F(JdfDocumentTest, fromNestedJdfCutting)
{
    ASSERT_EQ(1, jdfDocUT3->jdfNodes().count());
    JdfNodeSP jdfNode = jdfDocUT3->jdfNodes().first();
    ASSERT_TRUE(jdfNode);

    ASSERT_EQ(2, jdfNode->jdfNodes().count());
    JdfNodeSP jdfNode2 = jdfNode->jdfNodes().first();
    ASSERT_TRUE(jdfNode2);

    ResourcePoolSP resourcePool2 = jdfNode2->resourcePool();
    ASSERT_TRUE(resourcePool2);

    CuttingParamsSP cuttingParams = resourcePool2->cuttingParams();
    ASSERT_TRUE(cuttingParams);
    ASSERT_EQ("CPM_0000", cuttingParams->id());
    EXPECT_EQ(ResourceStatus::AvailableStatus, cuttingParams->resourceStatus());
    EXPECT_EQ(ResourceClass::ParameterClass, cuttingParams->resourceClass());

    ASSERT_EQ(2, cuttingParams->cutBlocks().count());
    CutBlockSP cutBlock1 = cuttingParams->cutBlocks().at(0);
    EXPECT_EQ("A-1", cutBlock1->blockName());
    EXPECT_DOUBLE_EQ(432, cutBlock1->width());
    EXPECT_DOUBLE_EQ(288, cutBlock1->height());
    EXPECT_DOUBLE_EQ(54.0000, cutBlock1->x());
    EXPECT_DOUBLE_EQ(36.0000, cutBlock1->y());
    EXPECT_DOUBLE_EQ(0.0, cutBlock1->rotation());
    EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlock1->transformationMatrix());
    EXPECT_EQ(BlockType::CutBlock, cutBlock1->blockType());

    CutBlockSP cutBlock2 = cuttingParams->cutBlocks().at(1);
    EXPECT_EQ("A-2", cutBlock2->blockName());
    EXPECT_DOUBLE_EQ(432, cutBlock2->width());
    EXPECT_DOUBLE_EQ(288, cutBlock2->height());
    EXPECT_EQ("1 0 0 1 54.0000 342.0000", cutBlock2->transformationMatrix());
    EXPECT_EQ(BlockType::CutBlock, cutBlock2->blockType());
}

TEST_F(JdfDocumentTest, fromJdfWithPartitionedComponents)
{
    JdfNodeSP jdfNode = jdfDocUT4->jdfNodes().first();
    ASSERT_TRUE(jdfNode);
    EXPECT_EQ("LAYOUT_0001", jdfNode->id());
    ResourcePoolSP resourcePool = jdfNode->resourcePool();
    ASSERT_TRUE(resourcePool);
    ASSERT_EQ(1, resourcePool->components().count());
    ComponentSP component = resourcePool->components().first();
    ASSERT_TRUE(component);

    EXPECT_EQ(1000u, component->amount());

    ASSERT_TRUE(component->parts().count());
    EXPECT_EQ(1, component->parts().first()->parts().count());
    EXPECT_DOUBLE_EQ(2016, component->parts().first()->parts().first()->width());
    EXPECT_DOUBLE_EQ(1440, component->parts().first()->parts().first()->height());
}

TEST_F(JdfDocumentTest, fromNestedJdfFolding)
{
    ASSERT_EQ(1, jdfDocUT3->jdfNodes().count());
    JdfNodeSP jdfNode = jdfDocUT3->jdfNodes().first();
    ASSERT_TRUE(jdfNode);

    ASSERT_EQ(2, jdfNode->jdfNodes().count());
    JdfNodeSP jdfNode2 = jdfNode->jdfNodes().at(1);
    ASSERT_TRUE(jdfNode2);

    ResourcePoolSP resourcePool = jdfNode2->resourcePool();
    ASSERT_TRUE(resourcePool);

    FoldingParamsSP foldingParams = resourcePool->foldingParams();
    EXPECT_EQ("F6-1", foldingParams->foldCatalog());
}

TEST_F(JdfDocumentTest, updateFrom)
{
    QList<QSignalSpy *> spies = spiesForObject(jdfDocUT.data());
    QList<QSignalSpy *> qmlspies = spiesForObject(qmlWrapperUT);

    jdfDocUT->updateFrom(jdfDocUT2);

    for (QSignalSpy *spy: qmlspies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    for (QSignalSpy *spy: spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);
    spies.clear();
    qDeleteAll(qmlspies);
    qmlspies.clear();

    EXPECT_EQ(jdfDocUT->id(), jdfDocUT2->id());
    EXPECT_EQ(jdfDocUT->jobId(), jdfDocUT2->jobId());
    EXPECT_EQ(jdfDocUT->jobPartId(), jdfDocUT2->jobPartId());

    ResourcePoolSP resourcePool = jdfDocUT->resourcePool();
    ASSERT_TRUE(resourcePool);
    ResourcePoolSP resourcePool2 = jdfDocUT2->resourcePool();
    ASSERT_TRUE(resourcePool2);

    ASSERT_FALSE(resourcePool->components().isEmpty());
    ASSERT_FALSE(resourcePool2->components().isEmpty());
    ComponentSP component = resourcePool->components().first();
    ASSERT_TRUE(component);
    ComponentSP component2 = resourcePool2->components().first();
    ASSERT_TRUE(component2);
    EXPECT_EQ(component->id(), component2->id());
    EXPECT_DOUBLE_EQ(component->width(), component2->width());
    EXPECT_DOUBLE_EQ(component->height(), component2->height());
    EXPECT_DOUBLE_EQ(component->length(), component2->length());
    EXPECT_EQ(component->amount(), component2->amount());
    EXPECT_EQ(component->cutBlocks().count(), component2->cutBlocks().count());

    CuttingParamsSP cuttingParams = resourcePool->cuttingParams();
    ASSERT_TRUE(cuttingParams);
    CuttingParamsSP cuttingParams2 = resourcePool2->cuttingParams();
    ASSERT_TRUE(cuttingParams2);
    ASSERT_EQ(cuttingParams->id(), cuttingParams2->id());
    ASSERT_EQ(cuttingParams->resourceStatus(), cuttingParams2->resourceStatus());
    ASSERT_EQ(cuttingParams->resourceClass(), cuttingParams2->resourceClass());
    ASSERT_EQ(cuttingParams->cutBlocks().count(), cuttingParams2->cutBlocks().count());

    CutBlockSP cutBlock = cuttingParams->cutBlocks().at(0);
    ASSERT_TRUE(cutBlock);
    CutBlockSP cutBlock2 = cuttingParams2->cutBlocks().at(0);
    ASSERT_TRUE(cutBlock2);
    EXPECT_EQ(cutBlock->blockName(), cutBlock2->blockName());
    EXPECT_DOUBLE_EQ(cutBlock->width(), cutBlock2->width());
    EXPECT_DOUBLE_EQ(cutBlock->height(), cutBlock2->height());
    EXPECT_DOUBLE_EQ(cutBlock->x(), cutBlock2->x());
    EXPECT_DOUBLE_EQ(cutBlock->y(), cutBlock2->y());
    EXPECT_DOUBLE_EQ(cutBlock->rotation(), cutBlock2->rotation());
    EXPECT_EQ(cutBlock->transformationMatrix(), cutBlock2->transformationMatrix());
    EXPECT_EQ(cutBlock->blockType(), cutBlock2->blockType());

    ASSERT_EQ(1, resourcePool->media().count());
    MediaSP media1 = resourcePool->media().first();
    ASSERT_TRUE(media1);
    ASSERT_EQ(1, resourcePool2->media().count());
    MediaSP media2 = resourcePool2->media().first();
    ASSERT_TRUE(media2);
    EXPECT_EQ(media1->layers().count(), media2->layers().count());
    EXPECT_EQ(media1->id(), media2->id());
    EXPECT_EQ(media1->frontCoating(), media2->frontCoating());
    EXPECT_EQ(media1->frontCoatingDetail(), media2->frontCoatingDetail());
    EXPECT_EQ(media1->backCoating(), media2->backCoating());
    EXPECT_EQ(media1->backCoatingDetail(), media2->backCoatingDetail());
    EXPECT_EQ(media1->mediaUnit(), media2->mediaUnit());
    EXPECT_EQ(media1->mediaType(), media2->mediaType());
    EXPECT_DOUBLE_EQ(media1->width(), media2->width());
    EXPECT_DOUBLE_EQ(media1->height(), media2->height());
    EXPECT_DOUBLE_EQ(media1->thickness(), media2->thickness());

    LaminatingIntentSP laminatingIntent1 = resourcePool->laminatingIntent();
    ASSERT_TRUE(laminatingIntent1);
    LaminatingIntentSP laminatingIntent2 = resourcePool2->laminatingIntent();
    ASSERT_TRUE(laminatingIntent2);
    EXPECT_EQ(laminatingIntent1->id(), laminatingIntent2->id());
    EXPECT_EQ(laminatingIntent1->surface(), laminatingIntent2->surface());

    DeliveryIntentSP deliveryIntent1 = resourcePool->deliveryIntent();
    ASSERT_TRUE(deliveryIntent1);
    DeliveryIntentSP  deliveryIntent2 = resourcePool2->deliveryIntent();
    ASSERT_TRUE(deliveryIntent2);
    EXPECT_EQ(deliveryIntent1->required(), deliveryIntent2->required());
    ASSERT_TRUE(deliveryIntent1->dropIntents().count());
    DropIntentSP dropIntent1 = deliveryIntent1->dropIntents().first();
    ASSERT_TRUE(dropIntent1);
    ASSERT_TRUE(deliveryIntent2->dropIntents().count());
    DropIntentSP dropIntent2 = deliveryIntent2->dropIntents().first();
    ASSERT_TRUE(dropIntent2);

    EXPECT_EQ(dropIntent1->required().actual(), dropIntent2->required().actual());
}

TEST_F(JdfDocumentTest, documentToJdf)
{
    QString jdf = jdfDocUT->toJdf();
    QXmlStreamReader reader(jdf);

    EXPECT_FALSE(reader.atEnd());

    bool hasJdfProductElement = false;
    bool hasJdfNodeCutting = false;
    bool hasJdfNodeBoxPacking = false;
    bool hasResourcePool = false;
    int mediaCount = 0;
    bool hasLayout = false;
    bool hasLaminatingIntent = false;
    bool hasDeliveryIntent = false;
    bool hasRequired = false;
    bool hasComponentOneRef = false;
    bool hasComponentTwoRef = false;
    bool hasComponentBox = false;
    bool hasComponentLinkBox = false;
    bool hasBoxPackingParams = false;
    bool hasBoxPackingParamsLink = false;
    bool hasBundleItemOne = false;
    bool hasBundleItemTwo = false;
    QString currentNodeId;
    QString currentComponentId;
    unsigned int cutBlocksCount = 0;
    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.readNext() == QXmlStreamReader::StartElement) {
            QXmlStreamAttributes attributes = reader.attributes();
            if (reader.name() == "JDF") {
                currentNodeId = attributes.value("ID").toString();
                QString typeNode = attributes.value("Type").toString();
                if (typeNode == "Product") {
                    hasJdfProductElement = true;
                    EXPECT_EQ("1.4", attributes.value("Version").toString());
                    EXPECT_EQ("Waiting", attributes.value("Status").toString());
                    EXPECT_EQ("http://www.CIP4.org/JDFSchema_1_1", reader.namespaceUri().toString());
                    EXPECT_EQ("JDF_0000", currentNodeId);
                    EXPECT_EQ("mixed-flatwork (groups)", attributes.value("JobID").toString());
                    EXPECT_EQ("ID0001", attributes.value("JobPartID").toString());
                } else if (typeNode == "Cutting") {
                    hasJdfNodeCutting = true;
                } else if (typeNode == "BoxPacking") {
                    hasJdfNodeBoxPacking = true;
                }
            }

            if (currentNodeId == "LAYOUT_0001") {
                if (reader.name() == "ResourcePool") {
                    hasResourcePool = true;
                } else if (hasResourcePool && reader.name() == "Component") {
                    if (!attributes.value("ID").toString().isEmpty())
                        currentComponentId = attributes.value("ID").toString();
                    if (attributes.value("ComponentType").toString() == "Sheet") {
                        QStringList dimensionsList = attributes.value("Dimensions").toString().split(" ",QString::SkipEmptyParts);

                        ASSERT_EQ(dimensionsList.count(), 3);
                        double width = dimensionsList.at(0).toDouble();
                        double height = dimensionsList.at(1).toDouble();
                        double length = dimensionsList.at(2).toDouble();
                        EXPECT_DOUBLE_EQ(2520.0000, width);
                        EXPECT_DOUBLE_EQ(1656.0000, height);
                        EXPECT_DOUBLE_EQ(0.4896, length);
                    }
                } else if (reader.name() == "Bundle") {
                    if (currentComponentId == "A_OUT") {
                        EXPECT_EQ(bundleTypeFromString(attributes.value("BundleType").toString()), BundleType::BoxBundle);
                        EXPECT_EQ(attributes.value("TotalAmount").toInt(), 42);
                    } else if (currentComponentId == "B_OUT_BOXED") {
                        EXPECT_EQ(bundleTypeFromString(attributes.value("BundleType").toString()), BundleType::BoxBundle);
                        EXPECT_EQ(attributes.value("TotalAmount").toInt(), 1000);
                    }
                } else if (reader.name() == "BundleItem") {
                    if (currentComponentId == "A_OUT") {
                        hasBundleItemOne = true;
                        EXPECT_EQ(attributes.value("Amount").toInt(), 42);
                    } else if (currentComponentId == "B_OUT_BOXED") {
                        hasBundleItemTwo = true;
                        EXPECT_EQ(attributes.value("Amount").toInt(), 500);
                    }
                } else if (reader.name() == "ComponentRef") {
                    if (!hasComponentOneRef && currentComponentId == "A_OUT") {
                        hasComponentOneRef = true;
                        EXPECT_EQ(attributes.value("rRef").toString(), "ComponentID");
                    } else if (!hasComponentTwoRef && currentComponentId == "B_OUT_BOXED") {
                        hasComponentTwoRef = true;
                        EXPECT_EQ(attributes.value("rRef").toString(), "B_OUT");
                    }
                } else if (hasResourcePool && reader.name() == "Media") {
                    ++mediaCount;
                    QString mediaId = attributes.value("ID").toString();
                    if (mediaId == "PAP_0000") {
                        EXPECT_EQ(attributes.value("FrontCoatings").toString(), "HighGloss");
                        EXPECT_EQ(attributes.value("BackCoatings").toString(), "");
                        EXPECT_EQ(attributes.value("MediaUnit").toString(), "Sheet");
                        EXPECT_EQ(attributes.value("MediaType").toString(), "Paper");
                        QStringList dimensionsList = attributes.value("Dimension").toString().split(" ", QString::SkipEmptyParts);
                        ASSERT_EQ(dimensionsList.count(), 2);
                        double widthMedia = dimensionsList.at(0).toDouble();
                        double heightMedia = dimensionsList.at(1).toDouble();
                        EXPECT_DOUBLE_EQ(widthMedia, 2520.0000);
                        EXPECT_DOUBLE_EQ(heightMedia, 1656.0000);
                        EXPECT_DOUBLE_EQ(attributes.value("Thickness").toDouble(), 172.7200);
                    } else if (mediaId == "PAP_0000_front") {
                        EXPECT_EQ(attributes.value("MediaType").toString(), "SelfAdhesive");
                        QStringList dimensionsList = attributes.value("Dimension").toString().split(" ", QString::SkipEmptyParts);
                        ASSERT_EQ(dimensionsList.count(), 2);
                        double widthMedia = dimensionsList.at(0).toDouble();
                        double heightMedia = dimensionsList.at(1).toDouble();
                        EXPECT_DOUBLE_EQ(widthMedia, 2520.0000);
                        EXPECT_DOUBLE_EQ(heightMedia, 1656.0000);
                        EXPECT_DOUBLE_EQ(attributes.value("Thickness").toDouble(), 100.0);
                    } else if (mediaId == "PAP_0000_back") {
                        EXPECT_EQ(attributes.value("MediaType").toString(), "SelfAdhesive");
                        QStringList dimensionsList = attributes.value("Dimension").toString().split(" ", QString::SkipEmptyParts);
                        ASSERT_EQ(dimensionsList.count(), 2);
                        double widthMedia = dimensionsList.at(0).toDouble();
                        double heightMedia = dimensionsList.at(1).toDouble();
                        EXPECT_DOUBLE_EQ(widthMedia, 2520.0000);
                        EXPECT_DOUBLE_EQ(heightMedia, 1656.0000);
                        EXPECT_DOUBLE_EQ(attributes.value("Thickness").toDouble(), 72.72);
                    } else if (mediaId == "PAP_0001") {
                        EXPECT_EQ(attributes.value("MediaType").toString(), "Plate");
                        QStringList dimensionsList = attributes.value("Dimension").toString().split(" ", QString::SkipEmptyParts);
                        ASSERT_EQ(dimensionsList.count(), 2);
                        double widthMedia = dimensionsList.at(0).toDouble();
                        double heightMedia = dimensionsList.at(1).toDouble();
                        EXPECT_DOUBLE_EQ(widthMedia, 2620.0000);
                        EXPECT_DOUBLE_EQ(heightMedia, 1756.0000);
                    } else if (mediaId == "PAP_0002") {
                        EXPECT_EQ(attributes.value("MediaType").toString(), "Paper");
                        QStringList dimensionsList = attributes.value("Dimension").toString().split(" ", QString::SkipEmptyParts);
                        ASSERT_EQ(dimensionsList.count(), 2);
                        double widthMedia = dimensionsList.at(0).toDouble();
                        double heightMedia = dimensionsList.at(1).toDouble();
                        EXPECT_DOUBLE_EQ(widthMedia, 2521.0000);
                        EXPECT_DOUBLE_EQ(heightMedia, 1657.0000);
                    } else if (mediaId == "PAP_0003") {
                        EXPECT_EQ(attributes.value("MediaType").toString(), "Plate");
                        QStringList dimensionsList = attributes.value("Dimension").toString().split(" ", QString::SkipEmptyParts);
                        ASSERT_EQ(dimensionsList.count(), 2);
                        double widthMedia = dimensionsList.at(0).toDouble();
                        double heightMedia = dimensionsList.at(1).toDouble();
                        EXPECT_DOUBLE_EQ(widthMedia, 2621.0000);
                        EXPECT_DOUBLE_EQ(heightMedia, 1757.0000);
                    } else if (mediaId == "PAP_0004") {
                        EXPECT_EQ(attributes.value("MediaType").toString(), "Other");
                        QStringList dimensionsList = attributes.value("Dimension").toString().split(" ", QString::SkipEmptyParts);
                        ASSERT_EQ(dimensionsList.count(), 2);
                        double widthMedia = dimensionsList.at(0).toDouble();
                        double heightMedia = dimensionsList.at(1).toDouble();
                        EXPECT_DOUBLE_EQ(widthMedia, 2721.0000);
                        EXPECT_DOUBLE_EQ(heightMedia, 1857.0000);
                    } else {
                        EXPECT_TRUE(false);
                    }
                } else if (hasResourcePool && reader.name() == "Layout") {
                    hasLayout = true;
                    EXPECT_EQ("Layout1", attributes.value("ID").toString());
                } else if (hasResourcePool && reader.name() == "LaminatingIntent") {
                    hasLaminatingIntent = true;
                    EXPECT_EQ(attributes.value("ID").toString(), "LI_0000");
                    EXPECT_EQ(attributes.value("Surface").toString(), "Both");
                } else if (hasResourcePool && reader.name() == "DeliveryIntent") {
                    hasDeliveryIntent = true;
                    EXPECT_EQ("DI_0000", attributes.value("ID").toString());
                } else if (hasResourcePool && reader.name() == "Required") {
                    hasRequired = true;
                    EXPECT_EQ(attributes.value("Actual").toString(), "2014-08-26T15:35:28Z");
                } else if (hasResourcePool && reader.name() == "CuttingParams") {
                    EXPECT_EQ(attributes.value("ID").toString(), "CPM_0000");
                    EXPECT_EQ(resourceStatusFromString(attributes.value("Status").toString()),
                              ResourceStatus::AvailableStatus);
                    EXPECT_EQ(resourceClassFromString(attributes.value("Class").toString()),
                              ResourceClass::ParameterClass);
                } else if (hasResourcePool && reader.name() == "CutBlock") {
                    if (!cutBlocksCount++) {
                        EXPECT_EQ(attributes.value("BlockName").toString(), "A-1");
                        EXPECT_EQ(attributes.value("BlockType").toString(), "CutBlock");
                    }
                }
            } else if (currentNodeId == "BoxPacking_B") {
                if (reader.name() == "Component" && attributes.value("ID").toString() == "Box1ID") {
                    hasComponentBox = true;
                    EXPECT_EQ(componentTypeFromString(attributes.value("ComponentType").toString()), ComponentType::SheetComponent);
                    EXPECT_EQ(productTypeFromString(attributes.value("ProductType").toString()), ProductType::FlatBoxProduct);
                    EXPECT_EQ(attributes.value("ProductTypeDetails").toString(), "Envelope");
                } else if (reader.name() == "BoxPackingParams") {
                    hasBoxPackingParams = true;
                } else if (reader.name() == "BoxPackingParamsLink") {
                    hasBoxPackingParamsLink = true;
                } else if (reader.name() == "ComponentLink" && attributes.value("rRef").toString() == "Box1ID") {
                    hasComponentLinkBox = true;
                    EXPECT_EQ(attributes.value("ProcessUsage").toString(), "Box");
                }
            }
        }
    }

    EXPECT_FALSE(reader.hasError()) << reader.errorString().toLatin1().constData();
    EXPECT_TRUE(hasJdfProductElement);
    EXPECT_TRUE(hasJdfNodeCutting);
    EXPECT_TRUE(hasJdfNodeBoxPacking);
    EXPECT_TRUE(hasBoxPackingParams);
    EXPECT_TRUE(hasBoxPackingParamsLink);
    EXPECT_TRUE(hasComponentBox);
    EXPECT_TRUE(hasComponentLinkBox);
    EXPECT_TRUE(hasResourcePool);
    EXPECT_TRUE(hasBundleItemOne);
    EXPECT_TRUE(hasBundleItemTwo);
    EXPECT_EQ(7, mediaCount);
    EXPECT_TRUE(hasLayout);
    EXPECT_TRUE(hasLaminatingIntent);
    EXPECT_TRUE(hasDeliveryIntent);
    EXPECT_TRUE(hasRequired);
    EXPECT_TRUE(hasComponentOneRef);
    EXPECT_TRUE(hasComponentTwoRef);
    EXPECT_EQ(23u, cutBlocksCount);
}

TEST_F(JdfDocumentTest, orientationTest)
{
    ASSERT_EQ(2, jdfDocUT->jdfNodes().count());
    JdfNodeSP jdfNode = jdfDocUT->jdfNodes().first();
    ASSERT_TRUE(jdfNode);

    ASSERT_EQ(4, jdfNode->resourcePool()->components().count());
    Proof::Jdf::ComponentSP sheet;
    for (const auto &component : jdfNode->resourcePool()->components()) {
        if (component->componentType() == Proof::Jdf::ComponentType::SheetComponent) {
            sheet = component;
            break;
        }
    }
    ASSERT_TRUE(sheet);

    Proof::Jdf::ComponentLinkSP sheetLink;
    for (const auto &component : jdfNode->resourceLinkPool()->componentLinks()) {
        if (component->rRef() == sheet->id()) {
            sheetLink = component;
            break;
        }
    }
    ASSERT_TRUE(sheetLink);

    EXPECT_EQ(Proof::Jdf::ResourceOrientation::Rotate0Orientation, sheetLink->orientation());

    sheetLink->setOrientation(Proof::Jdf::ResourceOrientation::Rotate180Orientation);
    EXPECT_EQ(Proof::Jdf::ResourceOrientation::Rotate180Orientation, sheetLink->orientation());

    QString jdf = jdfDocUT->toJdf();

    EXPECT_TRUE(jdf.contains("Orientation=\"Rotate180\""));
}

TEST_F(JdfDocumentTest, toLink)
{
    ASSERT_EQ(2, jdfDocUT->jdfNodes().count());
    JdfNodeSP jdfNode = jdfDocUT->jdfNodes().first();
    ASSERT_TRUE(jdfNode);

    ASSERT_EQ(4, jdfNode->resourcePool()->components().count());
    Proof::Jdf::ComponentSP component = jdfNode->resourcePool()->components().at(0);
    ASSERT_TRUE(component);

    Proof::Jdf::ComponentLinkSP componentLink = component->toLink(LinkUsage::OutputLink);
    ASSERT_TRUE(componentLink);
    EXPECT_EQ(component->id(), componentLink->rRef());
    EXPECT_EQ(LinkUsage::OutputLink, componentLink->usage());

    ASSERT_EQ(4, jdfNode->resourcePool()->media().count());
    Proof::Jdf::MediaSP media = jdfNode->resourcePool()->media()[2];
    ASSERT_TRUE(media);

    Proof::Jdf::MediaLinkSP mediaLink = media->toLink(LinkUsage::OutputLink);
    ASSERT_TRUE(mediaLink);
    EXPECT_EQ(media->id(), mediaLink->rRef());
    EXPECT_EQ(LinkUsage::OutputLink, mediaLink->usage());

    Proof::Jdf::LaminatingIntentSP laminatingIntent = jdfNode->resourcePool()->laminatingIntent();
    ASSERT_TRUE(laminatingIntent);

    Proof::Jdf::LaminatingIntentLinkSP laminatingIntentLink = laminatingIntent->toLink(LinkUsage::OutputLink);
    ASSERT_TRUE(laminatingIntentLink);
    EXPECT_EQ(laminatingIntent->id(), laminatingIntentLink->rRef());
    EXPECT_EQ(LinkUsage::OutputLink, laminatingIntentLink->usage());

}

//TODO: cover these methods better
TEST_F(JdfDocumentTest, findNode)
{
    Proof::Jdf::JdfNodeSP node = jdfDocUT->findNode([](const Proof::Jdf::JdfNodeSP &node){return node->type() == "Cutting";});
    ASSERT_TRUE(node);
    EXPECT_EQ("LAYOUT_0001", node->id());
    EXPECT_EQ("Cutting", node->type());
}

TEST_F(JdfDocumentTest, findComponent)
{
    Proof::Jdf::ComponentSP component = jdfDocUT->findComponent([](const Proof::Jdf::ComponentSP &component){return component->id() == "COMP_0000";});
    ASSERT_TRUE(component);
    EXPECT_EQ("COMP_0000", component->id());
    component = jdfDocUT2->findComponent([](const Proof::Jdf::ComponentSP &component){return component->id() == "061106-00002_1_Comp00001";});
    ASSERT_TRUE(component);
    EXPECT_EQ("061106-00002_1_Comp00001", component->id());
}

TEST_F(JdfDocumentTest, findComponentLink)
{
    Proof::Jdf::ComponentLinkSP link = jdfDocUT->findComponentLink([](const Proof::Jdf::ComponentLinkSP &link){return link->rRef() == "COMP_0000";});
    EXPECT_EQ("COMP_0000", link->rRef());
    EXPECT_EQ(Proof::Jdf::LinkUsage::InputLink, link->usage());
}

TEST_F(JdfDocumentTest, findMedia)
{
    Proof::Jdf::MediaSP media = jdfDocUT->findMedia([](const Proof::Jdf::MediaSP &media){return media->mediaType() == Proof::Jdf::MediaType::PaperMedia;});
    EXPECT_EQ("PAP_0000", media->id());
    EXPECT_EQ(Proof::Jdf::MediaType::PaperMedia, media->mediaType());
}

TEST_F(JdfDocumentTest, findLayout)
{
    Proof::Jdf::LayoutSP layout = jdfDocUT->findLayout([](const Proof::Jdf::LayoutSP &layout){return layout->id() == "Layout1";});
    EXPECT_EQ("Layout1", layout->id());
    EXPECT_EQ(3, layout->media().count());
}
