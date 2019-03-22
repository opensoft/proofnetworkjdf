#ifndef XJDF_INTENT_H
#define XJDF_INTENT_H

#include "xjdfabstractnode.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

namespace Proof {
namespace XJdf {

class IntentPrivate;
class PROOF_NETWORK_XJDF_EXPORT Intent : public XJdfAbstractNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Intent)
public:
    Intent(const Intent &) = delete;
    Intent &operator=(const XJdfAbstractNode &) = delete;
    Intent(XJdfAbstractNode &&) = delete;
    Intent &operator=(Intent &&) = delete;
    ~Intent() = default;

    QString name() const;
    void setName(const QString &arg);

    bool fillFromXJdf(QXmlStreamReader &xjdfReader) override;
    void readAttributesFromXJdf(QXmlStreamReader &xjdfReader) override;
    void toXJdf(QXmlStreamWriter &xjdfWriter, bool writeEnd = false) const override;
    static IntentSP fromXJdf(QXmlStreamReader &xjdfReader);

signals:
    void nameChanged(const QString &name);

protected:
    Intent();
    explicit Intent(IntentPrivate &dd);
    void updateSelf(const NetworkDataEntitySP &other) override;

    static void addResourceCreator(const QString &name, std::function<IntentSP(QXmlStreamReader &)> &&creator);
    static std::function<IntentSP(QXmlStreamReader &)> &resourceCreator(const QString &name);
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_INTENT_H
