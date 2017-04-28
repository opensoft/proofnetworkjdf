// clazy:skip

#include "gtest/test_global.h"

#include "proofnetwork/jdf/data/jmfdocument.h"
#include "proofnetwork/jdf/data/knowndevicesresponse.h"
#include "proofnetwork/jdf/data/deviceinfo.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QDateTime>
#include <QDomDocument>
#include <QSignalSpy>

using namespace Proof;
using namespace Proof::Jdf;
using testing::Test;

class KnownDevicesResponseTest : public Test
{
public:
    KnownDevicesResponseTest()
    {
    }
protected:
    void SetUp() override
    {
        QFile file(":/data/knowndevicesresponse.jmf");
        ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QXmlStreamReader xml(&file);
        jmfDocumentUT = JmfDocument::fromJmf(xml);

        QFile file2(":/data/knowndevicesresponse2.jmf");
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

TEST_F(KnownDevicesResponseTest, fromJmf)
{
    EXPECT_EQ("HPIN150-SM1", jmfDocumentUT->senderId());
    EXPECT_EQ(QDateTime::fromString("2015-10-29T10:50:30-04:00", Qt::ISODate), jmfDocumentUT->timeStamp());
    ASSERT_EQ(1, jmfDocumentUT->messages().size());
    auto knownDevices = qSharedPointerObjectCast<KnownDevicesResponse>(jmfDocumentUT->messages().at(0));
    ASSERT_FALSE(knownDevices.isNull());
    EXPECT_EQ("Rmisb41feececf78250c", knownDevices->id());
    auto devices = knownDevices->deviceInfos();
    ASSERT_EQ(2, devices.size());
    auto first = devices.at(0);
    EXPECT_EQ("10.1.0.159", first->deviceId());
    EXPECT_EQ(DeviceStatus::IdleDeviceStatus, first->status());
    EXPECT_EQ(DeviceCondition::OkDeviceCondition, first->condition());
    auto second = devices.at(1);
    EXPECT_EQ("10.1.0.158", second->deviceId());
    EXPECT_EQ(DeviceStatus::IdleDeviceStatus, second->status());
    EXPECT_EQ(DeviceCondition::OkDeviceCondition, second->condition());
}

TEST_F(KnownDevicesResponseTest, toJmf)
{
    QString text = jmfDocumentUT->toJmf();
    QDomDocument doc;
    ASSERT_TRUE(doc.setContent(text));
    auto jmfs = doc.elementsByTagName("JMF");
    ASSERT_EQ(1, jmfs.size());
    auto responses = jmfs.at(0).toElement().elementsByTagName("Response");
    ASSERT_EQ(1, responses.size());
    auto deviceLists = responses.at(0).toElement().elementsByTagName("DeviceList");
    ASSERT_EQ(1, deviceLists.size());
    auto deviceInfos = deviceLists.at(0).toElement().elementsByTagName("DeviceInfo");
    ASSERT_EQ(2, deviceInfos.size());
    auto first = deviceInfos.at(0).toElement();
    EXPECT_EQ("10.1.0.159", first.attribute("DeviceID"));
    EXPECT_EQ("Idle", first.attribute("DeviceStatus"));
    EXPECT_EQ("OK", first.attribute("DeviceCondition"));
    auto second = deviceInfos.at(1).toElement();
    EXPECT_EQ("10.1.0.158", second.attribute("DeviceID"));
    EXPECT_EQ("Idle", second.attribute("DeviceStatus"));
    EXPECT_EQ("OK", second.attribute("DeviceCondition"));
}

TEST_F(KnownDevicesResponseTest, updateFrom)
{
    ASSERT_EQ(1, jmfDocumentUT->messages().size());
    auto knownDevices = qSharedPointerObjectCast<KnownDevicesResponse>(jmfDocumentUT->messages().at(0));
    ASSERT_FALSE(knownDevices.isNull());
    ASSERT_EQ(1, jmfDocumentUT2->messages().size());
    auto knownDevices2 = qSharedPointerObjectCast<KnownDevicesResponse>(jmfDocumentUT2->messages().at(0));
    ASSERT_FALSE(knownDevices2.isNull());

    QList<QSignalSpy *> spies = spiesForObject(knownDevices.data());

    knownDevices->updateFrom(knownDevices2);

    for (QSignalSpy *spy: spies)
        EXPECT_EQ(1, spy->count()) << spy->signal().constData();

    qDeleteAll(spies);
}
