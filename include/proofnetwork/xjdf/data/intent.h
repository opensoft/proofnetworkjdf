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
    Intent &operator=(const Intent &) = delete;
    Intent(Intent &&) = delete;
    Intent &operator=(Intent &&) = delete;
    ~Intent() = default;

    QString name() const;
    void setName(const QString &arg);

    bool fillFromXJdf(QXmlStreamReader &reader) override;
    void readAttributesFromXJdf(QXmlStreamReader &reader) override;
    void toXJdf(QXmlStreamWriter &writer, bool writeEnd = false) const override;
    static IntentSP fromXJdf(QXmlStreamReader &reader, const XJdfDocumentSP &document = XJdfDocumentSP());

    template <class T>
    inline static void registerIntentCreator(const QString &name)
    {
        addIntentCreator(name, [](QXmlStreamReader &reader, const XJdfDocumentSP &document) -> IntentSP {
            return qSharedPointerCast<Intent>(T::fromXJdf(reader, document));
        });
    }

signals:
    void nameChanged(const QString &name);

protected:
    explicit Intent();
    explicit Intent(IntentPrivate &dd);
    void updateSelf(const NetworkDataEntitySP &other) override;
    static void addIntentCreator(const QString &name,
                                 std::function<IntentSP(QXmlStreamReader &, const XJdfDocumentSP &)> &&creator);
    static std::function<IntentSP(QXmlStreamReader &, const XJdfDocumentSP &)> &intentCreator(const QString &name);
};

} // namespace XJdf
} // namespace Proof

#endif // XJDF_INTENT_H
