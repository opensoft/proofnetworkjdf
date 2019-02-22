// clazy:skip

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

        qmlWrapperUT = xjdfDocUT->toQmlWrapper();
    }

    void TearDown() override { delete qmlWrapperUT; }

protected:
    XJdfDocumentSP xjdfDocUT;
    XJdfDocumentQmlWrapper *qmlWrapperUT;
};

TEST_F(XJdfDocumentTest, qmlWrapperProperties)
{
    QStringList invalidProperties = findWrongChangedSignalsInQmlWrapper(qmlWrapperUT);
    EXPECT_EQ(0, invalidProperties.count()) << invalidProperties.join("\n").toLatin1().constData();
}

TEST_F(XJdfDocumentTest, malformedXJdf)
{
    
}

TEST_F(XJdfDocumentTest, fromXJdf)
{
    
}

