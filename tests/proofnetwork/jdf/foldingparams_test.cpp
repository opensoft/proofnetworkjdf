// clazy:skip

#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/foldingparams.h"

#include <QXmlStreamReader>
#include <QSignalSpy>
#include <QFile>
#include <QDebug>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;
using testing::TestWithParam;
using std::tuple;

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

        qmlWrapperUT = foldingParams1->toQmlWrapper();
        ASSERT_TRUE(qmlWrapperUT != nullptr);
    }

    void TearDown() override
    {
        delete qmlWrapperUT;
    }

protected:
    FoldingParamsSP foldingParams1;
    FoldingParamsSP foldingParams2;
    FoldingParamsQmlWrapper *qmlWrapperUT;
};

TEST_F(FoldingParamsTest, qmlWrapperProperties)
{
    QStringList invalidProperties = findWrongChangedSignalsInQmlWrapper(qmlWrapperUT);
    EXPECT_EQ(0, invalidProperties.count()) << invalidProperties.join("\n").toLatin1().constData();
}

TEST_F(FoldingParamsTest, fromJdf)
{
    EXPECT_EQ("F6-1", foldingParams1->foldCatalog());
    EXPECT_EQ("F12-14", foldingParams2->foldCatalog());
}

TEST_F(FoldingParamsTest, updateFrom)
{
    QList<QSignalSpy *> spies = spiesForObject(foldingParams1.data());
    QList<QSignalSpy *> qmlspies = spiesForObject(qmlWrapperUT);

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

class FoldingParamsFoldCatalogTest : public TestWithParam<tuple<QString, QString>>
{
public:
    FoldingParamsFoldCatalogTest()
    {
    }
protected:
    void SetUp() override
    {
        QFile file(":/data/foldingparams.jdf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        foldingParams = FoldingParams::fromJdf(xml);
        ASSERT_TRUE(foldingParams != nullptr);
    }
protected:
    FoldingParamsSP foldingParams;
};

TEST_P(FoldingParamsFoldCatalogTest, foldCatalogTest)
{
    QString expected = std::get<0>(GetParam());
    QString value = std::get<1>(GetParam());

    foldingParams->setFoldCatalog(value);
    QString real = foldingParams->foldCatalog();
    EXPECT_EQ(expected, real);
}

INSTANTIATE_TEST_CASE_P(FoldingParamsFoldCatalogTestParameters,
                        FoldingParamsFoldCatalogTest,
                        testing::Values(tuple<QString, QString>("", ""),
                                        tuple<QString, QString>("", "aasdf"),
                                        tuple<QString, QString>("", "12-4"),
                                        tuple<QString, QString>("", "F0-0"),
                                        tuple<QString, QString>("", "F00-00"),
                                        tuple<QString, QString>("", "F101-101"),
                                        tuple<QString, QString>("", "F3-1"),
                                        tuple<QString, QString>("", "FA-B"),
                                        tuple<QString, QString>("F64-X", "F64-X"),
                                        tuple<QString, QString>("F16-14", "F16-14"),
                                        tuple<QString, QString>("F6-8", "F6-8"),
                                        tuple<QString, QString>("F64-2", "F64-2"))
                        );
