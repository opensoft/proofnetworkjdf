#ifndef JDFCUTBLOCK_H
#define JDFCUTBLOCK_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/data/qmlwrappers/cutblockqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofcore/objectscache.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class CutBlockPrivate;
class PROOF_NETWORK_JDF_EXPORT CutBlock : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CutBlock)
public:

    QString id() const;
    bool available() const;
    QString blockName() const;
    double width() const;
    double height() const;
    QString transformationMatrix() const;

    void setAvailable(bool arg);
    void setBlockName(const QString &arg);
    void setWidth(double arg);
    void setHeight(double arg);
    void setId(const QString &arg);
    void setTransformationMatrix(const QString &arg);

    void updateFrom(const NetworkDataEntitySP &other) override;
    CutBlockQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static CutBlockSP create();

    static CutBlockSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);
    static CutBlockSP defaultObject();

signals:
    void availableChanged(bool arg);
    void blockNameChanged(const QString &arg);
    void widthChanged(double arg);
    void heightChanged(double arg);
    void idChanged(const QString &arg);
    void transformationMatrixChanged(const QString &arg);

protected:
    explicit CutBlock();

};

}
}

#endif // JDFCUTBLOCK_H
