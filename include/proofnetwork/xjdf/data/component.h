#ifndef XJDF_COMPONENT_H
#define XJDF_COMPONENT_H

#include "resource.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class ComponentPrivate;
class PROOF_NETWORK_XJDF_EXPORT Component : public Resource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Component)
public:
    Component(const Component &) = delete;
    Component &operator=(const XJdfAbstractNode &) = delete;
    Component(XJdfAbstractNode &&) = delete;
    Component &operator=(Component &&) = delete;
    ~Component() = default;

    static ComponentSP create();

    MediaSP mediaRef() const;
    double width() const;
    double height() const;
    double thickness() const;

    void setMediaRef(const MediaSP &arg);
    void setWidth(double arg);
    void setHeight(double arg);
    void setThickness(double arg);

    static ComponentSP fromXJdf(QXmlStreamReader &xjdfReader);
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;

signals:
    void mediaRefChanged(const MediaSP &arg);
    void widthChanged(double arg);
    void heightChanged(double arg);
    void thicknessChanged(double arg);

protected:
    Component();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_COMPONENT_H
