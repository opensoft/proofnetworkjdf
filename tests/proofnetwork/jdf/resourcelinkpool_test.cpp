// clazy:skip

#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/qmlwrappers/resourcelinkpoolqmlwrapper.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"

#include "gtest/test_global.h"

#include <QDebug>
#include <QFile>
#include <QSignalSpy>
#include <QXmlStreamReader>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;
using testing::TestWithParam;

class ResourceLinkPoolTest : public Test
{
public:
    ResourceLinkPoolTest() {}

protected:
    void SetUp() override
    {
        QFile file1(":/data/resourcelinkpool.jdf");
        ASSERT_TRUE(file1.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml1(&file1);

        linkPool1 = ResourceLinkPool::fromJdf(xml1);
        ASSERT_TRUE(linkPool1);
        EXPECT_EQ(true, linkPool1->isFetched());

        QFile file2(":/data/resourcelinkpool2.jdf");
        ASSERT_TRUE(file2.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml2(&file2);

        linkPool2 = ResourceLinkPool::fromJdf(xml2);
        ASSERT_TRUE(linkPool2);

        qmlWrapperUT = linkPool1->toQmlWrapper();
        ASSERT_TRUE(qmlWrapperUT != nullptr);
    }

    void TearDown() override { delete qmlWrapperUT; }

protected:
    ResourceLinkPoolSP linkPool1;
    ResourceLinkPoolSP linkPool2;
    ResourceLinkPoolQmlWrapper *qmlWrapperUT;
};

TEST_F(ResourceLinkPoolTest, qmlWrapperProperties)
{
    QStringList invalidProperties = findWrongChangedSignalsInQmlWrapper(qmlWrapperUT);
    EXPECT_EQ(0, invalidProperties.count()) << invalidProperties.join("\n").toLatin1().constData();
}

TEST_F(ResourceLinkPoolTest, fromJdf)
{
    EXPECT_EQ(LinkUsage::InputLink, linkPool1->cuttingParamsLink()->usage());
    EXPECT_EQ("CPM_0000", linkPool1->cuttingParamsLink()->rRef());

    ASSERT_EQ(1, linkPool1->mediaLinks().count());
    EXPECT_EQ(LinkUsage::InputLink, linkPool1->mediaLinks().first()->usage());
    EXPECT_EQ("PAP_0000", linkPool1->mediaLinks().first()->rRef());

    ASSERT_EQ(3, linkPool1->componentLinks().count());
    EXPECT_EQ(LinkUsage::InputLink, linkPool1->componentLinks().at(0)->usage());
    EXPECT_EQ("COMP_0000", linkPool1->componentLinks().at(0)->rRef());
    EXPECT_EQ(LinkUsage::OutputLink, linkPool1->componentLinks().at(1)->usage());
    EXPECT_EQ("A_OUT", linkPool1->componentLinks().at(1)->rRef());
    EXPECT_EQ(LinkUsage::OutputLink, linkPool1->componentLinks().at(2)->usage());
    EXPECT_EQ("B_OUT", linkPool1->componentLinks().at(2)->rRef());

    EXPECT_EQ(LinkUsage::InputLink, linkPool2->cuttingParamsLink()->usage());
    EXPECT_EQ("061106-00002_1_CutPara00001", linkPool2->cuttingParamsLink()->rRef());

    ASSERT_EQ(2, linkPool2->componentLinks().count());
    EXPECT_EQ(LinkUsage::InputLink, linkPool2->componentLinks().at(0)->usage());
    EXPECT_EQ("061106-00002_1_Comp00001", linkPool2->componentLinks().at(0)->rRef());
    EXPECT_EQ(LinkUsage::OutputLink, linkPool2->componentLinks().at(1)->usage());
    EXPECT_EQ("061106-00002_1_Comp00002", linkPool2->componentLinks().at(1)->rRef());
}

TEST_F(ResourceLinkPoolTest, updateFrom)
{
    QVector<QSignalSpy *> spies = spiesForObject(linkPool1.data());
    QVector<QSignalSpy *> qmlspies = spiesForObject(qmlWrapperUT);

    linkPool1->updateFrom(linkPool2);

    for (QSignalSpy *spy : qmlspies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    for (QSignalSpy *spy : spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);
    spies.clear();
    qDeleteAll(qmlspies);
    qmlspies.clear();

    EXPECT_EQ(linkPool1->mediaLinks().count(), linkPool2->mediaLinks().count());
    EXPECT_EQ(linkPool1->componentLinks().count(), linkPool2->componentLinks().count());
}

TEST_F(ResourceLinkPoolTest, toJdf)
{
    QString jdf;
    QXmlStreamWriter xmlWriter(&jdf);
    linkPool1->toJdf(xmlWriter);
    xmlWriter.writeEndDocument();

    QXmlStreamReader reader(jdf);
    EXPECT_FALSE(reader.atEnd());

    int componentCount = 0;
    bool hasResourceLinkPool = false;
    bool hasMediaLink = false;
    bool hasCuttingParamsLink = false;
    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.isStartElement()) {
            if (reader.name() == "ResourceLinkPool") {
                hasResourceLinkPool = true;
            } else if (reader.name() == "MediaLink") {
                hasMediaLink = true;
                MediaLinkSP media = MediaLink::fromJdf(reader);
                ASSERT_TRUE(media);
                EXPECT_EQ("PAP_0000", media->rRef());
                EXPECT_EQ(LinkUsage::InputLink, media->usage());
            } else if (reader.name() == "CuttingParamsLink") {
                hasCuttingParamsLink = true;
                CuttingParamsLinkSP cutting = CuttingParamsLink::fromJdf(reader);
                ASSERT_TRUE(cutting);
                EXPECT_EQ("CPM_0000", cutting->rRef());
                EXPECT_EQ(LinkUsage::InputLink, cutting->usage());
            } else if (reader.name() == "ComponentLink") {
                componentCount++;
            }
        }
        reader.readNext();
    }
    EXPECT_EQ(true, hasResourceLinkPool);
    EXPECT_EQ(true, hasMediaLink);
    EXPECT_EQ(true, hasCuttingParamsLink);
    EXPECT_EQ(3, componentCount);
}
