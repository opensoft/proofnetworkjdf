// clazy:skip

#include "proofnetwork/jdf/data/xjmfdocument.h"

#include "gtest/proof/test_global.h"

#include <QDateTime>
#include <QDomDocument>
#include <QFile>
#include <QSignalSpy>
#include <QXmlStreamReader>

using namespace Proof;
using namespace Proof::XJdf;
using testing::Test;

class XJmfDocumentTest : public Test
{
public:
    XJmfDocumentTest() {}

protected:
    void SetUp() override
    {
        QFile file(":/data/xjmfdocument.xjmf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        xjmfDocumentUT = XJmfDocument::fromJmf(xml);

        QFile file2(":/data/xjmfdocument2.xjmf");
        ASSERT_TRUE(file2.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml2(&file2);
        xjmfDocumentUT2 = XJmfDocument::fromJmf(xml2);
    }

    void TearDown() override {}

protected:
    XJmfDocumentSP xjmfDocumentUT;
    XJmfDocumentSP xjmfDocumentUT2;
};

TEST_F(XJmfDocumentTest, fromXJmf)
{
}

TEST_F(XJmfDocumentTest, toXJmf)
{
   
}

TEST_F(XJmfDocumentTest, updateFrom)
{
    
}
