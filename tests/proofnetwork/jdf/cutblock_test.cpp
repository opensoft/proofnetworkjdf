// clazy:skip

#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/cutblock.h"

#include <QXmlStreamReader>
#include <QSignalSpy>
#include <QFile>
#include <QDebug>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class CutBlockTest: public Test
{
public:
    CutBlockTest()
    {
    }

protected:
    void SetUp() override
    {
        QFile file(":/data/cutblock.jdf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        cutBlockUT = CutBlock::fromJdf(xml, "id1");
        ASSERT_TRUE(cutBlockUT);

        QFile file2(":/data/cutblock2.jdf");
        ASSERT_TRUE(file2.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml2(&file2);
        cutBlockUT2 = CutBlock::fromJdf(xml2, "id2");
        ASSERT_TRUE(cutBlockUT2);

        qmlWrapperUT = cutBlockUT->toQmlWrapper();
        ASSERT_TRUE(qmlWrapperUT);
    }

    void TearDown() override
    {
        delete qmlWrapperUT;
    }

protected:
    CutBlockSP cutBlockUT;
    CutBlockSP cutBlockUT2;
    CutBlockQmlWrapper *qmlWrapperUT;
};

TEST_F(CutBlockTest, fromJdf)
{
    EXPECT_EQ("A-1", cutBlockUT->blockName());
    EXPECT_DOUBLE_EQ(432, cutBlockUT->width());
    EXPECT_DOUBLE_EQ(288, cutBlockUT->height());
    EXPECT_DOUBLE_EQ(54.0000, cutBlockUT->x());
    EXPECT_DOUBLE_EQ(36.0000, cutBlockUT->y());
    EXPECT_DOUBLE_EQ(0.0, cutBlockUT->rotation());
    EXPECT_EQ("1 0 0 1 54.0000 36.0000", cutBlockUT->transformationMatrix());
    EXPECT_EQ(BlockType::CutBlock, cutBlockUT->blockType());
}

TEST_F(CutBlockTest, updateFrom)
{
    QList<QSignalSpy *> spies = spiesForObject(cutBlockUT.data());
    QList<QSignalSpy *> qmlspies = spiesForObject(qmlWrapperUT);

    cutBlockUT->updateFrom(cutBlockUT2);

    for (QSignalSpy *spy: qmlspies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    for (QSignalSpy *spy: spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);
    spies.clear();
    qDeleteAll(qmlspies);
    qmlspies.clear();

    EXPECT_EQ(cutBlockUT->blockName(), cutBlockUT2->blockName());
    EXPECT_DOUBLE_EQ(cutBlockUT->width(), cutBlockUT2->width());
    EXPECT_DOUBLE_EQ(cutBlockUT->height(), cutBlockUT2->height());
    EXPECT_DOUBLE_EQ(cutBlockUT->x(), cutBlockUT2->x());
    EXPECT_DOUBLE_EQ(cutBlockUT->y(), cutBlockUT2->y());
    EXPECT_DOUBLE_EQ(cutBlockUT->rotation(), cutBlockUT2->rotation());
    EXPECT_EQ(cutBlockUT->transformationMatrix(), cutBlockUT2->transformationMatrix());
    EXPECT_EQ(cutBlockUT->blockType(), cutBlockUT2->blockType());
}

TEST_F(CutBlockTest, cutBlockToJdf)
{
    QString jdf;
    QXmlStreamWriter xmlWriter(&jdf);
    cutBlockUT->toJdf(xmlWriter);
    xmlWriter.writeEndDocument();

    QXmlStreamReader xmlReader(jdf);
    EXPECT_FALSE(xmlReader.atEnd());

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "CutBlock" && xmlReader.isStartElement()) {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            EXPECT_EQ(attributes.value("BlockName").toString(), "A-1");
            EXPECT_EQ(attributes.value("BlockSize").toString(), "432.0000 288.0000");
            EXPECT_EQ(attributes.value("BlockTrf").toString(), "1 0 0 1 54.0000 36.0000");
            EXPECT_EQ(attributes.value("BlockType").toString(), "CutBlock");
            break;
        } else {
            xmlReader.readNext();
        }
    }
}
