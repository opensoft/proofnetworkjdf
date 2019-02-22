// clazy:skip

#include "proofnetwork/jdf/xjdfhelper.h"

#include "gtest/proof/test_global.h"

#include <QFile>
#include <QXmlStreamReader>

using namespace Proof;
using namespace Proof::XJdf;
using testing::Test;

class XJdfHelpersTest : public Test
{
public:
    XJdfHelpersTest() {}

protected:
    void SetUp() override
    {
        QFile file(":/data/xjdfhelpers.xjdf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        xjdfDocUT = XJdfDocument::fromXJdf(xml);
        ASSERT_TRUE(xjdfDocUT);
    }

    void TearDown() override {}

protected:
    JdfDocumentSP xjdfDocUT;
};

TEST_F(JdfHelpersTest, findAllNodes)
{
    const auto nodes = findNodes(xjdfDocUT);
    
}
