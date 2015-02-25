#include "gtest/test_global.h"

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
        QFile file(":/data/cuttingprocess.jdf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        cutProcessUT = CuttingProcess::fromJdf(xml);

        QFile file2(":/data/cuttingprocess2.jdf");
        ASSERT_TRUE(file2.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml2(&file2);
        cutProcessUT2 = CuttingProcess::fromJdf(xml2);

        qmlWrapperUT = cutProcessUT->toQmlWrapper();

        jdfDocument = cutProcessUT->toJdf();
    }

    void TearDown() override
    {
        delete qmlWrapperUT;
    }

protected:
    CuttingProcessSP cutProcessUT;
    CuttingProcessSP cutProcessUT2;
    CuttingProcessQmlWrapper *qmlWrapperUT;
    QString jdfDocument;
};

TEST_F(CuttingProcessTest, fromJdf)
{
    EXPECT_EQ("COMP_0000", cutProcessUT->id());
    EXPECT_DOUBLE_EQ(2520, cutProcessUT->pressSheetWidth());
    EXPECT_DOUBLE_EQ(1656, cutProcessUT->pressSheetHeight());

    ASSERT_EQ(23, cutProcessUT->cutBlocks().count());

    CutBlockSP cutBlock = cutProcessUT->cutBlocks().at(0);
    ASSERT_TRUE(cutBlock);

    EXPECT_EQ("A-1_BLK", cutBlock->id());
    ASSERT_TRUE(cutBlock->available());
    EXPECT_EQ("A-1", cutBlock->blockName());
    EXPECT_DOUBLE_EQ(432, cutBlock->width());
    EXPECT_DOUBLE_EQ(288, cutBlock->height());
    EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlock->transformationMatrix());

    MediaSP media = cutProcessUT->media();
    ASSERT_TRUE(media);

    EXPECT_EQ("PAP_0000", media->id());
    EXPECT_EQ(Media::Coating::None, media->backCoating());
    EXPECT_EQ(Media::Coating::HighGloss, media->frontCoating());
    EXPECT_DOUBLE_EQ(2520.0, media->width());
    EXPECT_DOUBLE_EQ(1656.0, media->height());
    EXPECT_DOUBLE_EQ(172.72, media->thickness());
}

TEST_F(CuttingProcessTest, updateFrom)
{
    QList<QSignalSpy *> spies = spiesForObject(cutProcessUT.data());
    QList<QSignalSpy *> qmlspies = spiesForObject(qmlWrapperUT);

    cutProcessUT->updateFrom(cutProcessUT2);

    for (QSignalSpy *spy: qmlspies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    for (QSignalSpy *spy: spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);
    spies.clear();
    qDeleteAll(qmlspies);
    qmlspies.clear();

    EXPECT_EQ(cutProcessUT->id(), cutProcessUT2->id());
    EXPECT_DOUBLE_EQ(cutProcessUT->pressSheetWidth(), cutProcessUT2->pressSheetWidth());
    EXPECT_DOUBLE_EQ(cutProcessUT->pressSheetHeight(), cutProcessUT2->pressSheetHeight());

    ASSERT_EQ(cutProcessUT->cutBlocks().count(), cutProcessUT2->cutBlocks().count());

    CutBlockSP cutBlock = cutProcessUT->cutBlocks().at(0);
    ASSERT_TRUE(cutBlock);
    CutBlockSP cutBlock2 = cutProcessUT2->cutBlocks().at(0);
    ASSERT_TRUE(cutBlock2);

    EXPECT_EQ(cutBlock->id(), cutBlock2->id());
    ASSERT_TRUE(cutBlock->available() == cutBlock2->available());
    EXPECT_EQ(cutBlock->blockName(), cutBlock2->blockName());
    EXPECT_DOUBLE_EQ(cutBlock->width(), cutBlock2->width());
    EXPECT_DOUBLE_EQ(cutBlock->height(), cutBlock2->height());
    EXPECT_EQ(cutBlock->transformationMatrix(), cutBlock2->transformationMatrix());

    MediaSP media1 = cutProcessUT->media();
    ASSERT_TRUE(media1);
    MediaSP media2 = cutProcessUT2->media();
    ASSERT_TRUE(media2);
    EXPECT_EQ(media1->id(), media2->id());
    EXPECT_EQ(media1->backCoating(), media2->backCoating());
    EXPECT_EQ(media1->frontCoating(), media2->frontCoating());
    EXPECT_DOUBLE_EQ(media1->width(), media2->width());
    EXPECT_DOUBLE_EQ(media1->height(), media2->height());
    EXPECT_DOUBLE_EQ(media1->thickness(), media2->thickness());
}
