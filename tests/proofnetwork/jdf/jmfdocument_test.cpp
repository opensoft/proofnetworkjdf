// clazy:skip

#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/jmfdocument.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QDateTime>
#include <QDomDocument>
#include <QSignalSpy>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class JmfDocumentTest : public Test
{
public:
    JmfDocumentTest()
    {
    }
protected:
    void SetUp() override
    {
        QFile file(":/data/jmfdocument.jmf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        jmfDocumentUT = JmfDocument::fromJmf(xml);

        QFile file2(":/data/jmfdocument2.jmf");
        ASSERT_TRUE(file2.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml2(&file2);
        jmfDocumentUT2 = JmfDocument::fromJmf(xml2);
    }

    void TearDown() override
    {
    }

protected:
    JmfDocumentSP jmfDocumentUT;
    JmfDocumentSP jmfDocumentUT2;
};

TEST_F(JmfDocumentTest, fromJmf)
{
    EXPECT_EQ("Proof", jmfDocumentUT->senderId());
    EXPECT_EQ(QDateTime::fromString("2015-10-30T15:26:52+03:00", Qt::ISODate), jmfDocumentUT->timeStamp());
    EXPECT_EQ("1.4", jmfDocumentUT->version());
    EXPECT_EQ(0, jmfDocumentUT->messages().size());
}

TEST_F(JmfDocumentTest, toJmf)
{
    QString text = jmfDocumentUT->toJmf();
    QDomDocument doc;
    ASSERT_TRUE(doc.setContent(text));
    auto jmfs = doc.elementsByTagName("JMF");
    ASSERT_EQ(1, jmfs.size());
    auto jmf = jmfs.at(0).toElement();
    EXPECT_EQ("Proof", jmf.attribute("SenderID"));
    EXPECT_EQ("2015-10-30T15:26:52+03:00", jmf.attribute("TimeStamp"));
    EXPECT_EQ("1.4", jmf.attribute("Version"));
    EXPECT_EQ("http://www.CIP4.org/JDFSchema_1_1", jmf.attribute("xmlns"));
}

TEST_F(JmfDocumentTest, updateFrom)
{
    QList<QSignalSpy *> spies = spiesForObject(jmfDocumentUT.data());
    jmfDocumentUT->updateFrom(jmfDocumentUT2);

    for (QSignalSpy *spy: spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);

    EXPECT_EQ(jmfDocumentUT2->senderId(), jmfDocumentUT->senderId());
    EXPECT_EQ(jmfDocumentUT2->timeStamp(), jmfDocumentUT->timeStamp());
}
