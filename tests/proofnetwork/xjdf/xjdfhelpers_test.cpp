// clazy:skip

#include "proofnetwork/xjdf/data/cutblock.h"
#include "proofnetwork/xjdf/data/cuttingparams.h"
#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/xjdfhelper.h"

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
        documentUT = Document::fromFile(":/data/proposal.xjdf");
        ASSERT_TRUE(documentUT);
    }

    void TearDown() override {}

protected:
    DocumentSP documentUT;
};

TEST_F(XJdfHelpersTest, flipCutBlocksVertically)
{
    const auto cuttingParamsList = documentUT->findResources<CuttingParams>(
        [](const auto &cuttingParams) { return !cuttingParams->cutBlocks().isEmpty(); });
    ASSERT_FALSE(cuttingParamsList.isEmpty());

    const auto cutBlocks = algorithms::filter(cuttingParamsList.first()->cutBlocks(),
                                              [](const auto &cutBlock) { return cutBlock->blockName() == "Block_1"; });
    ASSERT_FALSE(cutBlocks.isEmpty());
    const auto cutBlock = cutBlocks.first();
    EXPECT_EQ(1, cutBlock->x());
    EXPECT_EQ(1.1, cutBlock->y());
    EXPECT_EQ(400, cutBlock->width());
    EXPECT_EQ(300, cutBlock->height());

    flipCutBlocksVertically(documentUT);

    EXPECT_EQ(1, cutBlock->x());
    EXPECT_EQ(698.9, cutBlock->y());
    EXPECT_EQ(400, cutBlock->width());
    EXPECT_EQ(300, cutBlock->height());
}
