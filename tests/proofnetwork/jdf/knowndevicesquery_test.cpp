#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/jmfdocument.h"
#include "proofnetwork/jdf/data/knowndevicesquery.h"
#include "proofnetwork/jdf/data/devicefilter.h"
#include "proofnetwork/jdf/apihelper.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QDateTime>
#include <QSignalSpy>
#include <QDomDocument>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class KnownDevicesQueryTest : public Test
{
public:
    KnownDevicesQueryTest()
    {
    }
protected:
    void SetUp() override
    {
        QFile file(":/data/knowndevicesquery.jmf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        jmfDocumentUT = JmfDocument::fromJmf(xml);

        QFile file2(":/data/knowndevicesquery2.jmf");
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

TEST_F(KnownDevicesQueryTest, fromJmf)
{
    EXPECT_EQ("MIS System", jmfDocumentUT->senderId());
    EXPECT_EQ(QDateTime::fromString("2006-04-19T14:48:12-07:00", Qt::ISODate), jmfDocumentUT->timeStamp());
    ASSERT_EQ(1, jmfDocumentUT->messages().size());
    KnownDevicesQuerySP knownDevices = qSharedPointerObjectCast<KnownDevicesQuery>(jmfDocumentUT->messages().at(0));
    ASSERT_FALSE(knownDevices.isNull());
    EXPECT_EQ("misb41feececf78250c", knownDevices->id());
    ASSERT_FALSE(knownDevices->deviceFilter().isNull());
    EXPECT_EQ(ApiHelper::DeviceFilterDetails::BriefDeviceFilterDetails, knownDevices->deviceFilter()->details());
}

TEST_F(KnownDevicesQueryTest, updateFrom)
{
    ASSERT_EQ(1, jmfDocumentUT->messages().size());
    KnownDevicesQuerySP knownDevices = qSharedPointerObjectCast<KnownDevicesQuery>(jmfDocumentUT->messages().at(0));
    ASSERT_FALSE(knownDevices.isNull());
    ASSERT_EQ(1, jmfDocumentUT2->messages().size());
    KnownDevicesQuerySP knownDevices2 = qSharedPointerObjectCast<KnownDevicesQuery>(jmfDocumentUT2->messages().at(0));
    ASSERT_FALSE(knownDevices2.isNull());
    QList<QSignalSpy *> spies = spiesForObject(knownDevices.data());

    knownDevices->updateFrom(knownDevices2);

    for (QSignalSpy *spy: spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);

    EXPECT_EQ(knownDevices2->id(), knownDevices->id());
    EXPECT_EQ(knownDevices2->deviceFilter(), knownDevices->deviceFilter());
}

TEST_F(KnownDevicesQueryTest, toJmf)
{
    QString text = jmfDocumentUT->toJmf();
    QDomDocument doc;
    ASSERT_TRUE(doc.setContent(text));
    auto jmfs = doc.elementsByTagName("JMF");
    ASSERT_EQ(1, jmfs.size());
    auto queries = jmfs.at(0).toElement().elementsByTagName("Query");
    ASSERT_EQ(1, queries.size());
    auto query = queries.at(0).toElement();
    EXPECT_EQ("misb41feececf78250c", query.attribute("ID"));
    EXPECT_EQ("KnownDevices", query.attribute("Type"));
    auto filters = query.elementsByTagName("DeviceFilter");
    ASSERT_EQ(1, filters.size());
    auto filter = filters.at(0).toElement();
    EXPECT_EQ("Brief", filter.attribute("DeviceDetails"));
}
