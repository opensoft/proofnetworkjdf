#include "bundle.h"

#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class BundlePrivate : NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(Bundle)

    ApiHelper::BundleType bundleType = ApiHelper::Box;
};

ApiHelper::BundleType Bundle::bundleType() const
{
    Q_D(const Bundle);
    return d->bundleType;
}

void Bundle::setBundleType(ApiHelper::BundleType arg)
{
    Q_D(Bundle);
    if (d->bundleType != arg) {
        d->bundleType = arg;
        emit bundleTypeChanged(arg);
    }
}

void Bundle::updateFrom(const NetworkDataEntitySP &other)
{
    BundleSP castedOther = qSharedPointerCast<Bundle>(other);
    setBundleType(castedOther->bundleType());

    NetworkDataEntity::updateFrom(other);
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
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

BundleSP Bundle::fromJdf(QXmlStreamReader &xmlReader)
{
    BundleSP result = create();
    result->setFetched(true);

    if (xmlReader.name() == "Bundle") {
        QXmlStreamAttributes attributes = xmlReader.attributes();
        result->setBundleType(ApiHelper::bundleTypeFromString(attributes.value("BundleType").toString()));
    }

    return result;
}

void Bundle::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Bundle);
    jdfWriter.writeAttribute("BundleType", ApiHelper::bundleTypeToString(d->bundleType));
}

BundleSP Bundle::defaultObject()
{
    static BundleSP entity = create();
    return entity;
}

Bundle::Bundle()
    : NetworkDataEntity(*new BundlePrivate)
{
}

} // namespace Jdf
} // namespace Proof
