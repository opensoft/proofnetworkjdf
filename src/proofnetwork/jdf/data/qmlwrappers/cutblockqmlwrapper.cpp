#include "cutblockqmlwrapper.h"

#include "proofnetwork/jdf/data/cutblock.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {
class CutBlockQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(CutBlockQmlWrapper)
};

}
}

using namespace Proof;
using namespace Proof::Jdf;

CutBlockQmlWrapper::CutBlockQmlWrapper(const CutBlockSP &cutBlock, QObject *parent)
    : NetworkDataEntityQmlWrapper(cutBlock, *new CutBlockQmlWrapperPrivate, parent)
{
    setupEntity();
}

CutBlockQmlWrapper::~CutBlockQmlWrapper()
{
}

PROOF_NDE_WRAPPER_TOOLS_IMPL(CutBlock)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, bool, available)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, QString, blockName)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, double, width)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, double, height)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(CutBlock, QString, transformationMatrix)

void CutBlockQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(CutBlockQmlWrapper);
    CutBlockSP cutBlock = d->entity<CutBlock>();
    Q_ASSERT(cutBlock);

    connect(cutBlock.data(), &CutBlock::availableChanged,
            this, &CutBlockQmlWrapper::availableChanged);
    connect(cutBlock.data(), &CutBlock::blockNameChanged,
            this, &CutBlockQmlWrapper::blockNameChanged);
    connect(cutBlock.data(), &CutBlock::widthChanged,
            this, &CutBlockQmlWrapper::widthChanged);
    connect(cutBlock.data(), &CutBlock::heightChanged,
            this, &CutBlockQmlWrapper::heightChanged);
    connect(cutBlock.data(), &CutBlock::idChanged,
            this, &CutBlockQmlWrapper::idChanged);
    connect(cutBlock.data(), &CutBlock::transformationMatrixChanged,
            this, &CutBlockQmlWrapper::transformationMatrixChanged);

    CutBlockSP oldCutBlock = qSharedPointerCast<CutBlock>(old);
    if (oldCutBlock) {
        if (cutBlock->id() != oldCutBlock->id())
            emit idChanged(cutBlock->id());
        if (cutBlock->available() != oldCutBlock->available())
            emit availableChanged(cutBlock->available());
        if (cutBlock->blockName() != oldCutBlock->blockName())
            emit blockNameChanged(cutBlock->blockName());
        if (cutBlock->width() != oldCutBlock->width())
            emit widthChanged(cutBlock->width());
        if (cutBlock->height() != oldCutBlock->height())
            emit heightChanged(cutBlock->height());
        if (cutBlock->transformationMatrix() != oldCutBlock->transformationMatrix())
            emit transformationMatrixChanged(cutBlock->transformationMatrix());
    }

}
