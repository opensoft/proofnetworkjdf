#ifndef PROOFNETWORKJDF_TYPES_H
#define PROOFNETWORKJDF_TYPES_H

#include "proofnetwork/proofnetwork_types.h"

#include <QSharedPointer>
#include <QWeakPointer>

namespace Proof {
namespace Jdf {

class JdfDocument;
typedef QSharedPointer<JdfDocument> JdfDocumentSP;
typedef QWeakPointer<JdfDocument> JdfDocumentWP;

class CuttingProcess;
typedef QSharedPointer<CuttingProcess> CuttingProcessSP;
typedef QWeakPointer<CuttingProcess> CuttingProcessWP;

class CutBlock;
typedef QSharedPointer<CutBlock> CutBlockSP;
typedef QWeakPointer<CutBlock> CutBlockWP;

class Media;
typedef QSharedPointer<Media> MediaSP;
typedef QWeakPointer<Media> MediaWP;

}
}

#endif // PROOFNETWORKJDF_TYPES_H
