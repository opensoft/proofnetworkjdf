#ifndef PROOFNETWORKJDF_TYPES_H
#define PROOFNETWORKJDF_TYPES_H

#include "proofnetwork/proofnetwork_types.h"

#include <QSharedPointer>
#include <QWeakPointer>

namespace Proof {
namespace Jdf {

class AbstractResource;
typedef QSharedPointer<AbstractResource> AbstractResourceSP;
typedef QWeakPointer<AbstractResource> AbstractResourceWP;

class AbstractPhysicalResource;
typedef QSharedPointer<AbstractPhysicalResource> AbstractPhysicalResourceSP;
typedef QWeakPointer<AbstractPhysicalResource> AbstractPhysicalResourceWP;

class JdfDocument;
typedef QSharedPointer<JdfDocument> JdfDocumentSP;
typedef QWeakPointer<JdfDocument> JdfDocumentWP;

class ResourcePool;
typedef QSharedPointer<ResourcePool> ResourcePoolSP;
typedef QWeakPointer<ResourcePool> ResourcePoolWP;

class CuttingParams;
typedef QSharedPointer<CuttingParams> CuttingParamsSP;
typedef QWeakPointer<CuttingParams> CuttingParamsWP;

class CutBlock;
typedef QSharedPointer<CutBlock> CutBlockSP;
typedef QWeakPointer<CutBlock> CutBlockWP;

class Media;
typedef QSharedPointer<Media> MediaSP;
typedef QWeakPointer<Media> MediaWP;

class LaminatingIntent;
typedef QSharedPointer<LaminatingIntent> LaminatingIntentSP;
typedef QWeakPointer<LaminatingIntent> LaminatingIntentWP;

class Component;
typedef QSharedPointer<Component> ComponentSP;
typedef QWeakPointer<Component> ComponentWP;

class Bundle;
typedef QSharedPointer<Bundle> BundleSP;
typedef QWeakPointer<Bundle> BundleWP;

class FoldingParams;
typedef QSharedPointer<FoldingParams> FoldingParamsSP;
typedef QSharedPointer<FoldingParams> FoldingParamsWP;

}
}

#endif // PROOFNETWORKJDF_TYPES_H
