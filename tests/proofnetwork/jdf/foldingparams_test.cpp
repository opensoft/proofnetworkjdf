#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/foldingparams.h"

#include <QXmlStreamReader>
#include <QSignalSpy>
#include <QFile>
#include <QDebug>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class FoldingParamsTest: public Test
{
public:
    FoldingParamsTest()
    {
    }

protected:
    void SetUp() override
    {
        QFile file1(":/data/foldingparams.jdf");
        ASSERT_TRUE(file1.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml1(&file1);
        foldingParams1 = FoldingParams::fromJdf(xml1);
        ASSERT_TRUE(foldingParams1 != nullptr);

        QFile file2(":/data/foldingparams2.jdf");
        ASSERT_TRUE(file2.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml2(&file2);
        foldingParams2 = FoldingParams::fromJdf(xml2);
        ASSERT_TRUE(foldingParams2 != nullptr);

        qmlWrapper = foldingParams1->toQmlWrapper();
        ASSERT_TRUE(qmlWrapper != nullptr);
    }

    void TearDown() override
    {
        delete qmlWrapper;
    }

protected:
    FoldingParamsSP foldingParams1;
    FoldingParamsSP foldingParams2;
    FoldingParamsQmlWrapper *qmlWrapper;
};

TEST_F(FoldingParamsTest, fromJdf)
{
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());
    EXPECT_EQ("F12-14", foldingParams2->foldCatalog());
}

TEST_F(FoldingParamsTest, setFoldCatalog)
{
    foldingParams1->setFoldCatalog("");
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("aasdf");
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("12-4");
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("F0-0");
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("F00-00");
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("F101-101");
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("F3-1");
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("FA-B");
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("F64-X");
    EXPECT_EQ("F64-X", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("F16-14");
    EXPECT_EQ("F16-14", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("F6-8");
    EXPECT_EQ("F6-8", foldingParams1->foldCatalog());

    foldingParams1->setFoldCatalog("F64-2");
    EXPECT_EQ("F64-2", foldingParams1->foldCatalog());

}

TEST_F(FoldingParamsTest, updateFrom)
{
    QList<QSignalSpy *> spies = spiesForObject(foldingParams1.data());
    QList<QSignalSpy *> qmlspies = spiesForObject(qmlWrapper);

    foldingParams1->updateFrom(foldingParams2);

    for (QSignalSpy *spy: qmlspies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    for (QSignalSpy *spy: spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);
    spies.clear();
    qDeleteAll(qmlspies);
    qmlspies.clear();

    EXPECT_EQ(foldingParams1->foldCatalog(), foldingParams2->foldCatalog());
}

TEST_F(FoldingParamsTest, foldingParamsToJdf)
{
    QString jdf;
    QXmlStreamWriter xmlWriter(&jdf);
    foldingParams1->toJdf(xmlWriter);
    xmlWriter.writeEndDocument();

    QXmlStreamReader xmlReader(jdf);
    EXPECT_FALSE(xmlReader.atEnd());

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "FoldingParams" && xmlReader.isStartElement()) {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            EXPECT_EQ(attributes.value("FoldCatalog").toString(), "F6-1");
            break;
        } else {
            xmlReader.readNext();
        }
    }
}
