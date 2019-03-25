#ifndef XJDF_RESOURCE_H
#define XJDF_RESOURCE_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class ResourcePrivate;
class PROOF_NETWORK_XJDF_EXPORT Resource : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Resource)
public:
    Resource(const Resource &) = delete;
    Resource &operator=(const XJdfAbstractNode &) = delete;
    Resource(XJdfAbstractNode &&) = delete;
    Resource &operator=(Resource &&) = delete;
    ~Resource() = default;

    QString id() const;
    ResourceOrientation orientation() const;
    QVector<PartSP> parts() const;
    AmountPoolSP amountPool() const;

    void setId(const QString &arg);
    void setOrientation(ResourceOrientation arg);
    void setParts(const QVector<PartSP> &arg);
    void setAmountPool(const AmountPoolSP &arg);

    bool fillFromXJdf(QXmlStreamReader &xjdfReader) override;
    void readAttributesFromXJdf(QXmlStreamReader &xjdfReader) override;
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;
    static ResourceSP fromXJdf(QXmlStreamReader &xjdfReader);

    template <class T>
    inline static void registerResourceCreator(const QString &name)
    {
        addResourceCreator(name, [](QXmlStreamReader &xjdfReader) -> ResourceSP {
            return qSharedPointerCast<Resource>(T::fromXJdf(xjdfReader));
        });
    }

signals:
    void idChanged(const QString &arg);
    void orientationChanged(ResourceOrientation arg);
    void partsChanged(const QVector<PartSP> &arg);
    void amountPoolChanged(const AmountPoolSP &arg);

protected:
    Resource(const QString &id = QString());
    explicit Resource(ResourcePrivate &dd, const QString &id = QString());
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
    static void addResourceCreator(const QString &name, std::function<ResourceSP(QXmlStreamReader &)> &&creator);

    static std::function<ResourceSP(QXmlStreamReader &)> &resourceCreator(const QString &name);
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_RESOURCE_H
