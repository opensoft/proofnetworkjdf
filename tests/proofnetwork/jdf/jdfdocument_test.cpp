#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/resourcepool.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/media.h"

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

        qmlWrapperUT = jdfDocUT->toQmlWrapper();
    }

    void TearDown() override
    {
        delete qmlWrapperUT;
    }

protected:
    JdfDocumentSP jdfDocUT;
    JdfDocumentSP jdfDocUT2;
    JdfDocumentQmlWrapper *qmlWrapperUT;
};

TEST_F(JdfDocumentTest, fromJdf)
{
    EXPECT_EQ("JDF_0000", jdfDocUT->id());
    EXPECT_EQ("mixed-flatwork (groups)", jdfDocUT->jobId());
    EXPECT_EQ("ID0001", jdfDocUT->jobPartId());

    ResourcePoolSP resourcePool = jdfDocUT->resourcePool();
    ASSERT_TRUE(resourcePool);

    EXPECT_EQ(3, resourcePool->components().count());

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
    ASSERT_EQ(ApiHelper::Box, bundle->bundleType());
    ASSERT_EQ(42, bundle->totalAmount());

    CuttingParamsSP cuttingParams = resourcePool->cuttingParams();
    ASSERT_TRUE(cuttingParams);
    ASSERT_EQ("CPM_0000", cuttingParams->id());
    EXPECT_EQ(ApiHelper::AvailableStatus, cuttingParams->status());
    EXPECT_EQ(ApiHelper::ParameterClass, cuttingParams->resourceClass());
    ASSERT_EQ(23, cuttingParams->cutBlocks().count());

    CutBlockSP cutBlock1 = component2->cutBlocks().first();
    CutBlockSP cutBlock2 = cuttingParams->cutBlocks().first();
    for (const CutBlockSP &cutBlock : {cutBlock1, cutBlock2}) {
        ASSERT_TRUE(cutBlock);
        EXPECT_EQ("A-1", cutBlock->blockName());
        EXPECT_DOUBLE_EQ(432, cutBlock->width());
        EXPECT_DOUBLE_EQ(288, cutBlock->height());
        EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlock->transformationMatrix());
        EXPECT_EQ(ApiHelper::CutBlockType, cutBlock->blockType());
    }

    MediaSP media = resourcePool->media();
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0000", media->id());
    EXPECT_EQ(ApiHelper::AvailableStatus, media->status());
    EXPECT_EQ(ApiHelper::NoneCoating, media->backCoating());
    EXPECT_EQ(ApiHelper::HighGloss, media->frontCoating());
    EXPECT_DOUBLE_EQ(2520.0, media->width());
    EXPECT_DOUBLE_EQ(1656.0, media->height());
    EXPECT_DOUBLE_EQ(172.72, media->thickness());
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
    ASSERT_EQ(cuttingParams->status(), cuttingParams2->status());
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
    EXPECT_DOUBLE_EQ(media1->width(), media2->width());
    EXPECT_DOUBLE_EQ(media1->height(), media2->height());
    EXPECT_DOUBLE_EQ(media1->thickness(), media2->thickness());
}

TEST_F(JdfDocumentTest, documentToJdf)
{
    QString jdf = jdfDocUT->toJdf();

    QXmlStreamReader reader(jdf);

    EXPECT_FALSE(reader.atEnd());

    bool hasJdfProductElement = false;
    bool hasResourcePool = false;
    bool hasMedia = false;
    QString id;
    QString jobId;
    QString jobPartId;
    QString version;
    QString status;
    QString defaultNamespace;
    QString cutProcessId;
    double height = .0;
    double width = .0;
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
                    if (dimensionsList.count() >= 2) {
                        width = dimensionsList.at(0).toDouble();
                        height = dimensionsList.at(1).toDouble();
                    }
                }
            } else if (reader.name() == "Bundle") {
                QXmlStreamAttributes attributes = reader.attributes();
                EXPECT_EQ(ApiHelper::bundleTypeFromString(attributes.value("BundleType").toString()), ApiHelper::Box);
                EXPECT_EQ(attributes.value("TotalAmount").toInt(), 42);
            } else if (hasResourcePool && reader.name() == "Media") {
                hasMedia = true;
            } else if (hasResourcePool && reader.name() == "CuttingParams") {
                QXmlStreamAttributes attributes = reader.attributes();
                EXPECT_EQ(attributes.value("ID").toString(), "CPM_0000");
                EXPECT_EQ(ApiHelper::resourceStatusFromString(attributes.value("Status").toString()), ApiHelper::AvailableStatus);
                EXPECT_EQ(ApiHelper::resourceClassFromString(attributes.value("Class").toString()), ApiHelper::ParameterClass);
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
    EXPECT_DOUBLE_EQ(2520., width);
    EXPECT_DOUBLE_EQ(1656., height);
    EXPECT_TRUE(hasMedia);
    EXPECT_EQ(23u, cutBlocksCount);
}
