// clazy:skip

#include "proofnetwork/xjdf/data/xjdfdocument.h"

#include "gtest/proof/test_global.h"

#include <QFile>
#include <QSignalSpy>
#include <QXmlStreamReader>

using namespace Proof;
using namespace Proof::XJdf;
using testing::Test;

class XJdfDocumentTest : public Test
{
public:
    XJdfDocumentTest() {}

protected:
    void SetUp() override
    {
        QFile file(":/data/proposal.xjdf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        xjdfDocUT = XJdfDocument::fromXJdf(xml);
        ASSERT_TRUE(xjdfDocUT);
    }

    void TearDown() override {}

protected:
    XJdfDocumentSP xjdfDocUT;
};

TEST_F(XJdfDocumentTest, malformedXJdf)
{}

TEST_F(XJdfDocumentTest, fromXJdf)
{}
