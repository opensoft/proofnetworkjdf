#ifndef XJDF_MEDIA_H
#define XJDF_MEDIA_H

#include "resource.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class MediaPrivate;
class PROOF_NETWORK_XJDF_EXPORT Media : public Resource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Media)
public:
    Media(const Media &) = delete;
    Media &operator=(const Media &) = delete;
    Media(Media &&) = delete;
    Media &operator=(Media &&) = delete;
    ~Media() = default;

    double width() const;
    double height() const;
    double thickness() const;

    void setWidth(double arg);
    void setHeight(double arg);
    void setThickness(double arg);

    static MediaSP create(const QString &id = QString());

    static MediaSP fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document = XJdfDocumentSP());
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;

signals:
    void widthChanged(double arg);
    void heightChanged(double arg);
    void thicknessChanged(double arg);

protected:
    explicit Media(const QString &id);
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_MEDIA_H
