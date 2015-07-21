#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/laminatingintent.h"
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

        QFile file2(":/data/jdfdocument2.jdf");
        ASSERT_TRUE(file2.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml2(&file2);
        jdfDocUT2 = JdfDocument::fromJdf(xml2);

        QFile file3(":/data/jdfnested.jdf");
        ASSERT_TRUE(file3.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml3(&file3);
        jdfDocUT3 = JdfDocument::fromJdf(xml3);

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
    JdfDocumentQmlWrapper *qmlWrapperUT;
};

TEST_F(JdfDocumentTest, fromJdf)
{
    EXPECT_EQ("JDF_0000", jdfDocUT->id());
    EXPECT_EQ("mixed-flatwork (groups)", jdfDocUT->jobId());
    EXPECT_EQ("ID0001", jdfDocUT->jobPartId());

    ASSERT_EQ(1, jdfDocUT->jdfNodes().count());

    JdfNodeSP jdfNode = jdfDocUT->jdfNodes().first();
    ASSERT_TRUE(jdfNode);
    EXPECT_EQ("LAYOUT_0001", jdfNode->id());

    ResourcePoolSP resourcePool = jdfNode->resourcePool();
    ASSERT_TRUE(resourcePool);

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
    EXPECT_EQ(15, component2->cutBlocks().count());

    BundleSP bundle = component2->bundle();
    ASSERT_TRUE(bundle);
    EXPECT_EQ(ApiHelper::BundleType::BoxBundle, bundle->bundleType());
    EXPECT_EQ(42, bundle->totalAmount());

    CuttingParamsSP cuttingParams = resourcePool->cuttingParams();
    ASSERT_TRUE(cuttingParams);
    ASSERT_EQ("CPM_0000", cuttingParams->id());
    EXPECT_EQ(ApiHelper::ResourceStatus::AvailableStatus, cuttingParams->resourceStatus());
    EXPECT_EQ(ApiHelper::ResourceClass::ParameterClass, cuttingParams->resourceClass());
    ASSERT_EQ(23, cuttingParams->cutBlocks().count());

    CutBlockSP cutBlock1 = component2->cutBlocks().first();
    CutBlockSP cutBlock2 = cuttingParams->cutBlocks().first();
    for (const CutBlockSP &cutBlock : {cutBlock1, cutBlock2}) {
        ASSERT_TRUE(cutBlock);
        EXPECT_EQ("A-1", cutBlock->blockName());
        EXPECT_DOUBLE_EQ(432, cutBlock->width());
        EXPECT_DOUBLE_EQ(288, cutBlock->height());
        EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlock->transformationMatrix());
        EXPECT_EQ(ApiHelper::BlockType::CutBlockType, cutBlock->blockType());
    }

    MediaSP media = resourcePool->media();
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0000", media->id());
    EXPECT_EQ(ApiHelper::ResourceStatus::AvailableStatus, media->resourceStatus());
    EXPECT_EQ(ApiHelper::CoatingType::NoneCoating, media->backCoating());
    EXPECT_EQ(ApiHelper::CoatingType::HighGlossCoating, media->frontCoating());
    EXPECT_EQ(ApiHelper::MediaUnit::SheetMediaUnit, media->mediaUnit());
    EXPECT_DOUBLE_EQ(2520.0, media->width());
    EXPECT_DOUBLE_EQ(1656.0, media->height());
    EXPECT_DOUBLE_EQ(172.72, media->thickness());

    LaminatingIntentSP laminatingIntent = resourcePool->laminatingIntent();
    ASSERT_TRUE(laminatingIntent);

    EXPECT_EQ("LI_0000", laminatingIntent->id());
    EXPECT_EQ(ApiHelper::ResourceStatus::AvailableStatus, laminatingIntent->resourceStatus());
    EXPECT_EQ(ApiHelper::LaminatingSurface::Both, laminatingIntent->surface());
}

TEST_F(JdfDocumentTest, fromNestedJdfFirstLevel)
{
    EXPECT_EQ("JDF_0000", jdfDocUT3->id());
    EXPECT_EQ("mixed-flatwork (groups)", jdfDocUT3->jobId());
    EXPECT_EQ("ID0001", jdfDocUT3->jobPartId());

    ASSERT_EQ(1, jdfDocUT3->jdfNodes().count());
    JdfNodeSP jdfNode = jdfDocUT3->jdfNodes().first();
    ASSERT_TRUE(jdfNode);

    EXPECT_EQ("ID_Product_0001", jdfNode->id());
    EXPECT_EQ("Product_0001", jdfNode->jobPartId());

    ResourcePoolSP resourcePool = jdfNode->resourcePool();
    ASSERT_TRUE(resourcePool);

    EXPECT_EQ(3, resourcePool->components().count());

    MediaSP media = resourcePool->media();
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_1234", media->id());
    EXPECT_EQ(ApiHelper::ResourceStatus::AvailableStatus, media->resourceStatus());
    EXPECT_EQ(ApiHelper::CoatingType::NoneCoating, media->backCoating());
    EXPECT_EQ(ApiHelper::CoatingType::HighGlossCoating, media->frontCoating());
    EXPECT_EQ(ApiHelper::MediaUnit::SheetMediaUnit, media->mediaUnit());
    EXPECT_DOUBLE_EQ(2520.0, media->width());
    EXPECT_DOUBLE_EQ(1656.0, media->height());
    EXPECT_DOUBLE_EQ(172.72, media->thickness());

    LaminatingIntentSP laminatingIntent = resourcePool->laminatingIntent();
    ASSERT_TRUE(laminatingIntent);

    EXPECT_EQ("LI_0000", laminatingIntent->id());
    EXPECT_EQ(ApiHelper::ResourceStatus::AvailableStatus, laminatingIntent->resourceStatus());
    EXPECT_EQ(ApiHelper::LaminatingSurface::Both, laminatingIntent->surface());

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

    BundleSP bundle = componentFold->bundle();
    ASSERT_TRUE(bundle);
    EXPECT_EQ(ApiHelper::BundleType::BoxBundle, bundle->bundleType());
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
    EXPECT_EQ(ApiHelper::ResourceStatus::AvailableStatus, cuttingParams->resourceStatus());
    EXPECT_EQ(ApiHelper::ResourceClass::ParameterClass, cuttingParams->resourceClass());

    ASSERT_EQ(2, cuttingParams->cutBlocks().count());
    CutBlockSP cutBlock1 = cuttingParams->cutBlocks().at(0);
    EXPECT_EQ("A-1", cutBlock1->blockName());
    EXPECT_DOUBLE_EQ(432, cutBlock1->width());
    EXPECT_DOUBLE_EQ(288, cutBlock1->height());
    EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlock1->transformationMatrix());
    EXPECT_EQ(ApiHelper::BlockType::CutBlockType, cutBlock1->blockType());

    CutBlockSP cutBlock2 = cuttingParams->cutBlocks().at(1);
    EXPECT_EQ("A-2", cutBlock2->blockName());
    EXPECT_DOUBLE_EQ(432, cutBlock2->width());
    EXPECT_DOUBLE_EQ(288, cutBlock2->height());
    EXPECT_EQ("1 0 0 1 54.0000 342.0000", cutBlock2->transformationMatrix());
    EXPECT_EQ(ApiHelper::BlockType::CutBlockType, cutBlock2->blockType());
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
    EXPECT_EQ(cutBlock->transformationMatrix(), cutBlock2->transformationMatrix());
    EXPECT_EQ(cutBlock->blockType(), cutBlock2->blockType());

    MediaSP media1 = resourcePool->media();
    ASSERT_TRUE(media1);
    MediaSP media2 = resourcePool2->media();
    ASSERT_TRUE(media2);
    EXPECT_EQ(media1->id(), media2->id());
    EXPECT_EQ(media1->backCoating(), media2->backCoating());
    EXPECT_EQ(media1->frontCoating(), media2->frontCoating());
    EXPECT_EQ(media1->mediaUnit(), media2->mediaUnit());
    EXPECT_DOUBLE_EQ(media1->width(), media2->width());
    EXPECT_DOUBLE_EQ(media1->height(), media2->height());
    EXPECT_DOUBLE_EQ(media1->thickness(), media2->thickness());

    LaminatingIntentSP laminatingIntent1 = resourcePool->laminatingIntent();
    ASSERT_TRUE(laminatingIntent1);
    LaminatingIntentSP laminatingIntent2 = resourcePool2->laminatingIntent();
    ASSERT_TRUE(laminatingIntent2);
    EXPECT_EQ(laminatingIntent1->id(), laminatingIntent2->id());
    EXPECT_EQ(laminatingIntent1->surface(), laminatingIntent2->surface());
}

TEST_F(JdfDocumentTest, documentToJdf)
{
    QString jdf = jdfDocUT->toJdf();
    QXmlStreamReader reader(jdf);

    EXPECT_FALSE(reader.atEnd());

    bool hasJdfProductElement = false;
    bool hasResourcePool = false;
    bool hasMedia = false;
    bool hasLaminatingIntent = false;
    QString id;
    QString jobId;
    QString jobPartId;
    QString version;
    QString status;
    QString defaultNamespace;
    QString cutProcessId;
    unsigned int cutBlocksCount = 0;
    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == "JDF") {
                QXmlStreamAttributes attributes = reader.attributes();
                if (attributes.value("Type").toString() == "Product") {
                    hasJdfProductElement = true;
                    id = attributes.value("ID").toString();
                    jobId = attributes.value("JobID").toString();
                    jobPartId = attributes.value("JobPartID").toString();
                    status = attributes.value("Status").toString();
                    version = attributes.value("Version").toString();
                    defaultNamespace = reader.namespaceUri().toString();
                }
            } else if (reader.name() == "ResourcePool") {
                hasResourcePool = true;
            } else if (hasResourcePool && reader.name() == "Component") {
                QXmlStreamAttributes attributes = reader.attributes();
                if (attributes.value("ComponentType").toString() == "Sheet") {
                    cutProcessId = attributes.value("ID").toString();
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
                QXmlStreamAttributes attributes = reader.attributes();
                EXPECT_EQ(ApiHelper::bundleTypeFromString(attributes.value("BundleType").toString()),
                          ApiHelper::BundleType::BoxBundle);
                EXPECT_EQ(attributes.value("TotalAmount").toInt(), 42);
            } else if (hasResourcePool && reader.name() == "Media") {
                hasMedia = true;
                QXmlStreamAttributes attributes = reader.attributes();
                EXPECT_EQ(attributes.value("ID").toString(), "PAP_0000");
                EXPECT_EQ(attributes.value("FrontCoatings").toString(), "HighGloss");
                EXPECT_EQ(attributes.value("BackCoatings").toString(), "None");
                EXPECT_EQ(attributes.value("MediaUnit").toString(), "Sheet");
                QStringList dimensionsList = attributes.value("Dimension").toString().split(" ",QString::SkipEmptyParts);

                ASSERT_EQ(dimensionsList.count(),2);
                double widthMedia = dimensionsList.at(0).toDouble();
                double heightMedia = dimensionsList.at(1).toDouble();
                EXPECT_DOUBLE_EQ(widthMedia, 2520.0000);
                EXPECT_DOUBLE_EQ(heightMedia, 1656.0000);
                EXPECT_DOUBLE_EQ(attributes.value("Thickness").toDouble(), 172.7200);
            } else if (hasResourcePool && reader.name() == "LaminatingIntent") {
                hasLaminatingIntent = true;
                QXmlStreamAttributes attributes = reader.attributes();
                EXPECT_EQ(attributes.value("ID").toString(), "LI_0000");
                EXPECT_EQ(attributes.value("Surface").toString(), "Both");
            } else if (hasResourcePool && reader.name() == "CuttingParams") {
                QXmlStreamAttributes attributes = reader.attributes();
                EXPECT_EQ(attributes.value("ID").toString(), "CPM_0000");
                EXPECT_EQ(ApiHelper::resourceStatusFromString(attributes.value("Status").toString()),
                          ApiHelper::ResourceStatus::AvailableStatus);
                EXPECT_EQ(ApiHelper::resourceClassFromString(attributes.value("Class").toString()),
                          ApiHelper::ResourceClass::ParameterClass);
            } else if (hasResourcePool && reader.name() == "CutBlock") {
                if (!cutBlocksCount++) {
                    QXmlStreamAttributes attributes = reader.attributes();
                    EXPECT_EQ(attributes.value("BlockName").toString(), "A-1");
                    EXPECT_EQ(attributes.value("BlockType").toString(), "CutBlock");
                }
            }
        }
    }

    EXPECT_FALSE(reader.hasError());
    EXPECT_TRUE(hasJdfProductElement);
    EXPECT_EQ("1.4", version);
    EXPECT_EQ("Waiting", status);
    EXPECT_EQ("http://www.CIP4.org/JDFSchema_1_1", defaultNamespace);
    EXPECT_EQ("JDF_0000", id);
    EXPECT_EQ("mixed-flatwork (groups)", jobId);
    EXPECT_EQ("ID0001", jobPartId);
    EXPECT_TRUE(hasResourcePool);
    EXPECT_EQ("COMP_0000", cutProcessId);
    EXPECT_TRUE(hasMedia);
    EXPECT_TRUE(hasLaminatingIntent);
    EXPECT_EQ(23u, cutBlocksCount);
}

TEST_F(JdfDocumentTest, orientationTest)
{
    ASSERT_EQ(1, jdfDocUT->jdfNodes().count());
    JdfNodeSP jdfNode = jdfDocUT->jdfNodes().first();
    ASSERT_TRUE(jdfNode);

    ASSERT_EQ(3, jdfNode->resourcePool()->components().count());
    Proof::Jdf::ComponentSP sheet;
    for (const auto &component : jdfNode->resourcePool()->components()) {
        if (component->componentType() == Proof::Jdf::ApiHelper::ComponentType::SheetComponent) {
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

    EXPECT_EQ(Proof::Jdf::ApiHelper::ResourceOrientation::Rotate0Orientation, sheetLink->orientation());

    sheetLink->setOrientation(Proof::Jdf::ApiHelper::ResourceOrientation::Rotate180Orientation);
    EXPECT_EQ(Proof::Jdf::ApiHelper::ResourceOrientation::Rotate180Orientation, sheetLink->orientation());

    QString jdf = jdfDocUT->toJdf();

    EXPECT_TRUE(jdf.contains("Orientation=\"Rotate180\""));
}

TEST_F(JdfDocumentTest, toLink)
{
    ASSERT_EQ(1, jdfDocUT->jdfNodes().count());
    JdfNodeSP jdfNode = jdfDocUT->jdfNodes().first();
    ASSERT_TRUE(jdfNode);

    ASSERT_EQ(3, jdfNode->resourcePool()->components().count());
    Proof::Jdf::ComponentSP component = jdfNode->resourcePool()->components().at(0);
    ASSERT_TRUE(component);

    Proof::Jdf::ComponentLinkSP componentLink = component->toLink(ApiHelper::Usage::OutputUsage);
    ASSERT_TRUE(componentLink);
    EXPECT_EQ(component->id(), componentLink->rRef());
    EXPECT_EQ(ApiHelper::Usage::OutputUsage, componentLink->usage());

    Proof::Jdf::MediaSP media = jdfNode->resourcePool()->media();
    ASSERT_TRUE(media);

    Proof::Jdf::MediaLinkSP mediaLink = media->toLink(ApiHelper::Usage::OutputUsage);
    ASSERT_TRUE(mediaLink);
    EXPECT_EQ(media->id(), mediaLink->rRef());
    EXPECT_EQ(ApiHelper::Usage::OutputUsage, mediaLink->usage());

    Proof::Jdf::LaminatingIntentSP laminatingIntent = jdfNode->resourcePool()->laminatingIntent();
    ASSERT_TRUE(laminatingIntent);

    Proof::Jdf::LaminatingIntentLinkSP laminatingIntentLink = laminatingIntent->toLink(ApiHelper::Usage::OutputUsage);
    ASSERT_TRUE(laminatingIntentLink);
    EXPECT_EQ(laminatingIntent->id(), laminatingIntentLink->rRef());
    EXPECT_EQ(ApiHelper::Usage::OutputUsage, laminatingIntentLink->usage());

}
