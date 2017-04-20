#ifndef PROOF_JDF_COMPONENT_H
#define PROOF_JDF_COMPONENT_H

#include "proofnetwork/jdf/data/abstractphysicalresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofcore/objectscache.h"
#include "proofnetwork/jdf/data/qmlwrappers/componentqmlwrapper.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

using JdfComponentDataKey = QPair<QString, QString>;

class ComponentPrivate;
class PROOF_NETWORK_JDF_EXPORT Component : public AbstractPhysicalResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Component)
public:
    ComponentType componentType() const;
    ProductType productType() const;
    QString productTypeDetails() const;
    double width() const;
    double height() const;
    double length() const;
    BundleSP bundle() const;
    QList<CutBlockSP> cutBlocks() const;
    QList<ComponentSP> parts() const;

    void setComponentType(ComponentType arg);
    void setProductType(ProductType arg);
    void setProductTypeDetails(const QString &arg);
    void setWidth(double arg);
    void setHeight(double arg);
    void setLength(double arg);
    void setBundle(const BundleSP &arg);
    QList<CutBlockSP> updateCutBlocks(const QList<CutBlockSP> &arg);
    QList<ComponentSP> updateParts(const QList<ComponentSP> &arg);
    void addPart(const ComponentSP &arg);

    ComponentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static ComponentSP create(const QString &id = QString());

    static ComponentSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    ComponentLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

signals:
    void componentTypeChanged(Proof::Jdf::ComponentType arg);
    void productTypeChanged(Proof::Jdf::ProductType arg);
    void productTypeDetailsChanged(const QString &arg);
    void widthChanged(double arg);
    void heightChanged(double arg);
    void lengthChanged(double arg);
    void bundleChanged(const Proof::Jdf::BundleSP &bundle);
    void cutBlocksChanged();
    void partsChanged();

protected:
    explicit Component(const QString &id);

};

PROOF_NETWORK_JDF_EXPORT ObjectsCache<JdfComponentDataKey, Component> &componentsCache();

}
}

#endif // PROOF_JDF_COMPONENT_H
