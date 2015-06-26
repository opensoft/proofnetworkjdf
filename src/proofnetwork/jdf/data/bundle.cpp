#include "bundle.h"

#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class BundlePrivate : NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(Bundle)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    ApiHelper::BundleType bundleType = ApiHelper::BundleType::BoxBundle;
    int totalAmount = 0;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

ApiHelper::BundleType Bundle::bundleType() const
{
    Q_D(const Bundle);
    return d->bundleType;
}

int Bundle::totalAmount() const
{
    Q_D(const Bundle);
    return d->totalAmount;
}

void Bundle::setBundleType(ApiHelper::BundleType arg)
{
    Q_D(Bundle);
    if (d->bundleType != arg) {
        d->bundleType = arg;
        emit bundleTypeChanged(arg);
    }
}

void Bundle::setTotalAmount(int arg)
{
    Q_D(Bundle);
    if (d->totalAmount != arg) {
        d->totalAmount = arg;
        emit totalAmountChanged(arg);
    }
}

BundleQmlWrapper *Bundle::toQmlWrapper(QObject *parent) const
{
    Q_D(const Bundle);
    BundleSP castedSelf = qSharedPointerCast<Bundle>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new BundleQmlWrapper(castedSelf, parent);
}

BundleSP Bundle::create()
{
    BundleSP result(new Bundle());
    makeWeakSelf(result);
    return result;
}

BundleSP Bundle::fromJdf(QXmlStreamReader &xmlReader)
{
    BundleSP bundle = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Bundle" && xmlReader.isStartElement() && ! bundle->isFetched()) {
            bundle->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            bundle->setBundleType(ApiHelper::bundleTypeFromString(attributes.value("BundleType").toString()));
            bundle->setTotalAmount(attributes.value("TotalAmount").toInt());
        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return bundle;
}

void Bundle::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Bundle);
    jdfWriter.writeStartElement("Bundle");
    jdfWriter.writeAttribute("BundleType", ApiHelper::bundleTypeToString(d->bundleType));
    jdfWriter.writeAttribute("TotalAmount", QString::number(d->totalAmount));
    jdfWriter.writeEndElement();
}

Bundle::Bundle()
    : NetworkDataEntity(*new BundlePrivate)
{
}

void BundlePrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(Bundle);
    BundleSP castedOther = qSharedPointerCast<Bundle>(other);
    q->setBundleType(castedOther->bundleType());
    q->setTotalAmount(castedOther->totalAmount());

    NetworkDataEntityPrivate::updateFrom(other);
}

