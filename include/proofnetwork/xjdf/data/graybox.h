#ifndef XJDF_GRAYBOX_H
#define XJDF_GRAYBOX_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class GrayBoxPrivate;
class PROOF_NETWORK_XJDF_EXPORT GrayBox : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GrayBox)
public:
    GrayBox(const GrayBox &) = delete;
    GrayBox &operator=(const GrayBox &) = delete;
    GrayBox(GrayBox &&) = delete;
    GrayBox &operator=(GrayBox &&) = delete;
    ~GrayBox() = default;

    QVector<ProcessType> types() const;
    QVector<ResourceSetSP> resourceSets() const;
    void setTypes(const QVector<ProcessType> &arg);
    void setResourceSets(const QVector<ResourceSetSP> &arg);
    void addResourceSet(const ResourceSetSP &arg);

    bool fillFromXJdf(QXmlStreamReader &reader) override;
    void readAttributesFromXJdf(QXmlStreamReader &reader) override;
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void typesChanged(const QVector<Proof::XJdf::ProcessType> &arg);
    void resourceSetsChanged(const QVector<Proof::XJdf::ResourceSetSP> &arg);

protected:
    explicit GrayBox();
    explicit GrayBox(GrayBoxPrivate &dd);
    void updateSelf(const NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_GRAYBOX_H
