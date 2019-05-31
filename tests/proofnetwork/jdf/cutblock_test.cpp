// clazy:skip

#include "proofnetwork/jdf/data/cutblock.h"

#include "gtest/proof/test_global.h"

#include <QDebug>
#include <QFile>
#include <QSignalSpy>
#include <QXmlStreamReader>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class CutBlockTest : public Test
{
public:
    CutBlockTest() {}

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

    void TearDown() override { delete qmlWrapperUT; }

protected:
    CutBlockSP cutBlockUT;
    CutBlockSP cutBlockUT2;
    CutBlockQmlWrapper *qmlWrapperUT;
};

TEST_F(CutBlockTest, qmlWrapperProperties)
{
    QStringList invalidProperties = findWrongChangedSignalsInQmlWrapper(qmlWrapperUT);
    EXPECT_EQ(0, invalidProperties.count()) << invalidProperties.join("\n").toLatin1().constData();
}

TEST_F(CutBlockTest, fromJdf)
{
    EXPECT_EQ("A-1", cutBlockUT->blockName());
    EXPECT_DOUBLE_EQ(432, cutBlockUT->width());
    EXPECT_DOUBLE_EQ(288, cutBlockUT->height());
    EXPECT_EQ(QTransform(1.0, 0.0, 0.0, 1.0, 54.0, 36.0), cutBlockUT->transformationMatrix());
    EXPECT_EQ(BlockType::CutBlock, cutBlockUT->blockType());
}

TEST_F(CutBlockTest, updateFrom)
{
    QVector<QSignalSpy *> spies = spiesForObject(cutBlockUT.data(), {"xChanged(double)", "yChanged(double)"});
    QVector<QSignalSpy *> qmlspies = spiesForObject(qmlWrapperUT, {"xChanged(double)", "yChanged(double)"});

    cutBlockUT->updateFrom(cutBlockUT2);

    for (QSignalSpy *spy : qmlspies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    for (QSignalSpy *spy : spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);
    spies.clear();
    qDeleteAll(qmlspies);
    qmlspies.clear();

    EXPECT_EQ(cutBlockUT->blockName(), cutBlockUT2->blockName());
    EXPECT_DOUBLE_EQ(cutBlockUT->width(), cutBlockUT2->width());
    EXPECT_DOUBLE_EQ(cutBlockUT->height(), cutBlockUT2->height());
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
            EXPECT_EQ("A-1", attributes.value("BlockName").toString());
            EXPECT_EQ("432.0000 288.0000", attributes.value("BlockSize").toString());
            EXPECT_EQ("1.0000 0.0000 0.0000 1.0000 54.0000 36.0000", attributes.value("BlockTrf").toString());
            EXPECT_EQ("CutBlock", attributes.value("BlockType").toString());
            break;
        } else {
            xmlReader.readNext();
        }
    }
}

TEST_F(CutBlockTest, cutBlockToJdfWithChangedTrf)
{
    QString jdf;
    QXmlStreamWriter xmlWriter(&jdf);
    cutBlockUT->setTransformationMatrix(QTransform(-1.0, 1.0, 1.0, 0.0, 120.0, 240.5));
    cutBlockUT->toJdf(xmlWriter);
    xmlWriter.writeEndDocument();

    QXmlStreamReader xmlReader(jdf);
    EXPECT_FALSE(xmlReader.atEnd());

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "CutBlock" && xmlReader.isStartElement()) {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            EXPECT_EQ("A-1", attributes.value("BlockName").toString());
            EXPECT_EQ("432.0000 288.0000", attributes.value("BlockSize").toString());
            EXPECT_EQ("-1.0000 1.0000 1.0000 0.0000 120.0000 240.5000", attributes.value("BlockTrf").toString());
            EXPECT_EQ("CutBlock", attributes.value("BlockType").toString());
            break;
        } else {
            xmlReader.readNext();
        }
    }
}

TEST_F(CutBlockTest, moveBoundingRectIdentity)
{
    CutBlockSP cutBlock = CutBlock::create();
    cutBlock->setWidth(150.0);
    cutBlock->setHeight(100.0);
    cutBlock->setTransformationMatrix(QTransform(1.0, 0.0, 0.0, 1.0, 120.0, 240.5));
    EXPECT_EQ(QRectF(120.0, 240.5, 150.0, 100.0), cutBlock->boundingRect());
    cutBlock->moveBoundingRectTo(45.0, 30.0);
    EXPECT_EQ(QRectF(45.0, 30.0, 150.0, 100.0), cutBlock->boundingRect());
}

TEST_F(CutBlockTest, moveBoundingRectRotated)
{
    CutBlockSP cutBlock = CutBlock::create();
    cutBlock->setWidth(150.0);
    cutBlock->setHeight(100.0);
    cutBlock->setTransformationMatrix(QTransform(0.0, -1.0, 1.0, 0.0, 120.0, 240.5));
    EXPECT_EQ(QRectF(120.0, 90.5, 100.0, 150.0), cutBlock->boundingRect());
    cutBlock->moveBoundingRectTo(45.0, 30.0);
    EXPECT_EQ(QRectF(45.0, 30.0, 100.0, 150.0), cutBlock->boundingRect());
}
