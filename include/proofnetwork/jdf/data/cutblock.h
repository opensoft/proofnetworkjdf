#ifndef JDFCUTBLOCK_H
#define JDFCUTBLOCK_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/data/qmlwrappers/cutblockqmlwrapper.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofcore/objectscache.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

using JdfCutBlockDataKey = QPair<QString, QString>;

class CutBlockPrivate;
class PROOF_NETWORK_JDF_EXPORT CutBlock : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CutBlock)
public:
    QString blockName() const;
    double width() const;
    double height() const;
    double x() const;
    double y() const;
    double rotation() const;
    QString transformationMatrix() const;
    ApiHelper::BlockType blockType() const;

    void setBlockName(const QString &arg);
    void setWidth(double arg);
    void setHeight(double arg);
    void setX(double arg);
    void setY(double arg);
    void setRotation(double arg);
    void setTransformationMatrix(const QString &arg);
    void setTransformationMatrix(double x, double y, double rotation);
    void setBlockType(ApiHelper::BlockType arg);

    CutBlockQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static CutBlockSP create(const QString &blockName = QString());

    static CutBlockSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void blockNameChanged(const QString &arg);
    void widthChanged(double arg);
    void heightChanged(double arg);
    void xChanged(double arg);
    void yChanged(double arg);
    void rotationChanged(double arg);
    void transformationMatrixChanged(const QString &arg);
    void blockTypeChanged(Proof::Jdf::ApiHelper::BlockType arg);

protected:
    explicit CutBlock(const QString &blockName = QString());

};

PROOF_NETWORK_JDF_EXPORT ObjectsCache<JdfCutBlockDataKey, CutBlock> &cutBlockCache();

}
}

#endif // JDFCUTBLOCK_H
