#include "gtest/test_global.h"

#include "proofnetwork/jdf/jdfhelper.h"

#include <QXmlStreamReader>
#include <QSignalSpy>
#include <QFile>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class JdfHelpersTest: public Test
{
public:
    JdfHelpersTest()
    {
    }

protected:
    void SetUp() override
    {
        QFile file(":/data/jdfhelpers.jdf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        jdfDocUT = JdfDocument::fromJdf(xml);
        ASSERT_TRUE(jdfDocUT);
    }

    void TearDown() override
    {
    }

protected:
    JdfDocumentSP jdfDocUT;
};

TEST_F(JdfHelpersTest, findAllNodes)
{
    const auto nodes = findNodes(jdfDocUT);
    const QStringList ids = {"root", "cutting_node3", "cutting_node2",
                             "cutting_and_folding_node1", "folding_node3", "folding_node2",
                             "folding_and_boxpacking_node1", "boxpacking_node3", "boxpacking_node2"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, findCuttingNodes)
{
    const auto nodes = findCuttingNodes(jdfDocUT);
    const QStringList ids = {"cutting_node2", "cutting_and_folding_node1"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, findFoldingNodes)
{
    const auto nodes = findFoldingNodes(jdfDocUT);
    const QStringList ids = {"cutting_and_folding_node1", "folding_node2", "folding_and_boxpacking_node1"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, findBoxPackingNodes)
{
    const auto nodes = findBoxPackingNodes(jdfDocUT);
    const QStringList ids = {"folding_and_boxpacking_node1", "boxpacking_node2"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, nodesWithCuttingParamsLink)
{
    const auto nodes = nodesWithLink<CuttingParams>(findNodes(jdfDocUT));
    const QStringList ids = {"cutting_node3", "cutting_and_folding_node1"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, nodesWithFoldingParamsLink)
{
    const auto nodes = nodesWithLink<FoldingParams>(findNodes(jdfDocUT));
    const QStringList ids = {"cutting_and_folding_node1", "folding_node3", "folding_and_boxpacking_node1"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, nodesWithBoxPackingParamsLink)
{
    const auto nodes = nodesWithLink<BoxPackingParams>(findNodes(jdfDocUT));
    const QStringList ids = {"folding_and_boxpacking_node1", "boxpacking_node3"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, nodesWithInputComponentLink)
{
    const auto nodes = nodesWithLink<Component>(findNodes(jdfDocUT));
    const QStringList ids = {"cutting_and_folding_node1"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, nodesWithOutputComponentLink)
{
    const auto nodes = nodesWithLink<Component>(findNodes(jdfDocUT), LinkUsage::OutputLink);
    const QStringList ids = {"cutting_node2"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, nodesWithMediaLink)
{
    const auto nodes = nodesWithLink<Media>(findNodes(jdfDocUT));
    const QStringList ids = {"cutting_node3", "cutting_node2"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}


TEST_F(JdfHelpersTest, probablyCuttingNodes)
{
    const auto nodes = probablyCuttingNodes(jdfDocUT);
    const QStringList ids = {"cutting_and_folding_node1", "cutting_node2", "cutting_node3"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, probablyFoldingNodes)
{
    const auto nodes = probablyFoldingNodes(jdfDocUT);
    const QStringList ids = {"cutting_and_folding_node1", "folding_and_boxpacking_node1", "folding_node2", "folding_node3"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}

TEST_F(JdfHelpersTest, probablyBoxPackingNodes)
{
    const auto nodes = probablyBoxPackingNodes(jdfDocUT);
    const QStringList ids = {"folding_and_boxpacking_node1", "boxpacking_node2", "boxpacking_node3"};
    ASSERT_EQ(ids.count(), nodes.count()) << Proof::algorithms::map(nodes, [](const auto &n){return n->id();}, QStringList()).join(", ").toStdString();
    for (int i = 0; i < nodes.count(); ++i)
        EXPECT_EQ(ids[i], nodes[i]->id());
}
