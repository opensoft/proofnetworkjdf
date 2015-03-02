#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/cuttingprocess.h"
#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/jdf/data/media.h"

#include <QXmlStreamReader>
#include <QSignalSpy>
#include <QFile>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class CuttingProcessTest: public Test
{
public:
    CuttingProcessTest()
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

TEST_F(CuttingProcessTest, fromJdf)
{
    EXPECT_EQ("JDF_0000", jdfDocUT->id());
    EXPECT_EQ("mixed-flatwork (groups)", jdfDocUT->jobId());

    CuttingProcessSP cutProcess = jdfDocUT->cuttingProcess();
    ASSERT_TRUE(cutProcess);

    EXPECT_EQ("COMP_0000", cutProcess->id());
    EXPECT_DOUBLE_EQ(2520, cutProcess->pressSheetWidth());
    EXPECT_DOUBLE_EQ(1656, cutProcess->pressSheetHeight());
    EXPECT_EQ(1000, cutProcess->amount());

    ASSERT_EQ(23, cutProcess->cutBlocks().count());

    CutBlockSP cutBlock = cutProcess->cutBlocks().at(0);
    ASSERT_TRUE(cutBlock);

    EXPECT_EQ("A-1_BLK", cutBlock->id());
    ASSERT_TRUE(cutBlock->available());
    EXPECT_EQ("A-1", cutBlock->blockName());
    EXPECT_DOUBLE_EQ(432, cutBlock->width());
    EXPECT_DOUBLE_EQ(288, cutBlock->height());
    EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlock->transformationMatrix());

    MediaSP media = cutProcess->media();
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0000", media->id());
    EXPECT_EQ(ApiHelper::None, media->backCoating());
    EXPECT_EQ(ApiHelper::HighGloss, media->frontCoating());
    EXPECT_DOUBLE_EQ(2520.0, media->width());
    EXPECT_DOUBLE_EQ(1656.0, media->height());
    EXPECT_DOUBLE_EQ(172.72, media->thickness());
}

TEST_F(CuttingProcessTest, updateFrom)
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

    CuttingProcessSP cutProcess = jdfDocUT->cuttingProcess();
    ASSERT_TRUE(cutProcess);
    CuttingProcessSP cutProcess2 = jdfDocUT2->cuttingProcess();
    ASSERT_TRUE(cutProcess2);

    EXPECT_EQ(cutProcess->id(), cutProcess2->id());
    EXPECT_DOUBLE_EQ(cutProcess->pressSheetWidth(), cutProcess2->pressSheetWidth());
    EXPECT_DOUBLE_EQ(cutProcess->pressSheetHeight(), cutProcess2->pressSheetHeight());
    EXPECT_EQ(cutProcess->amount(), cutProcess2->amount());

    ASSERT_EQ(cutProcess->cutBlocks().count(), cutProcess2->cutBlocks().count());

    CutBlockSP cutBlock = cutProcess->cutBlocks().at(0);
    ASSERT_TRUE(cutBlock);
    CutBlockSP cutBlock2 = cutProcess2->cutBlocks().at(0);
    ASSERT_TRUE(cutBlock2);

    EXPECT_EQ(cutBlock->id(), cutBlock2->id());
    ASSERT_TRUE(cutBlock->available() == cutBlock2->available());
    EXPECT_EQ(cutBlock->blockName(), cutBlock2->blockName());
    EXPECT_DOUBLE_EQ(cutBlock->width(), cutBlock2->width());
    EXPECT_DOUBLE_EQ(cutBlock->height(), cutBlock2->height());
    EXPECT_EQ(cutBlock->transformationMatrix(), cutBlock2->transformationMatrix());

    MediaSP media1 = cutProcess->media();
    ASSERT_TRUE(media1);
    MediaSP media2 = cutProcess2->media();
    ASSERT_TRUE(media2);
    EXPECT_EQ(media1->id(), media2->id());
    EXPECT_EQ(media1->backCoating(), media2->backCoating());
    EXPECT_EQ(media1->frontCoating(), media2->frontCoating());
    EXPECT_DOUBLE_EQ(media1->width(), media2->width());
    EXPECT_DOUBLE_EQ(media1->height(), media2->height());
    EXPECT_DOUBLE_EQ(media1->thickness(), media2->thickness());
}

TEST_F(CuttingProcessTest, documentToJdf)
{
    QString jdf = jdfDocUT->toJdf();
    QXmlStreamReader reader(jdf);

    EXPECT_FALSE(reader.atEnd());

    bool hasJdfProductElement = false;
    bool hasResourcePool = false;
    bool hasMedia = false;
    QString id;
    QString jobId;
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
            } else if (hasResourcePool && reader.name() == "Media") {
                hasMedia = true;
            } else if (hasResourcePool && reader.name() == "CutBlock") {
                ++cutBlocksCount;
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
    EXPECT_TRUE(hasResourcePool);
    EXPECT_EQ("COMP_0000", cutProcessId);
    EXPECT_DOUBLE_EQ(2520., width);
    EXPECT_DOUBLE_EQ(1656., height);
    EXPECT_TRUE(hasMedia);
    EXPECT_EQ(23, cutBlocksCount);
}
