#ifndef JDFCUTBLOCKQMLWRAPPER_H
#define JDFCUTBLOCKQMLWRAPPER_H

#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class CutBlockQmlWrapperPrivate;

class PROOF_NETWORK_JDF_EXPORT CutBlockQmlWrapper : public NetworkDataEntityQmlWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString blockName READ blockName CONSTANT)
    Q_PROPERTY(double width READ width CONSTANT)
    Q_PROPERTY(double height READ height CONSTANT)
    Q_PROPERTY(QString transformationMatrix READ transformationMatrix CONSTANT)
    Q_PROPERTY(Proof::Jdf::ApiHelper::BlockType blockType READ blockType NOTIFY blockTypeChanged)
    Q_DECLARE_PRIVATE(CutBlockQmlWrapper)
public:
    explicit CutBlockQmlWrapper(const CutBlockSP &cutBlock, QObject *parent = 0);
    ~CutBlockQmlWrapper();
    PROOF_NDE_WRAPPER_TOOLS(CutBlock)

    QString blockName() const;
    double width() const;
    double height() const;
    QString transformationMatrix() const;
    Proof::Jdf::ApiHelper::BlockType blockType() const;

signals:
    void blockNameChanged(const QString &arg);
    void widthChanged(double arg);
    void heightChanged(double arg);
    void transformationMatrixChanged(const QString &arg);
    void blockTypeChanged(Proof::Jdf::ApiHelper::BlockType arg);

protected:
    void setupEntity(const QSharedPointer<NetworkDataEntity> &old = QSharedPointer<NetworkDataEntity>()) override;
};

}
}

#endif // JDFCUTBLOCKQMLWRAPPER_H
