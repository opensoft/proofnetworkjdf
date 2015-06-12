#include "data/abstractresource.h"
#include "data/abstractphysicalresource.h"
#include "data/cutblock.h"
#include "data/cuttingparams.h"
#include "data/foldingparams.h"
#include "data/resourcepool.h"
#include "data/media.h"
#include "data/laminatingintent.h"
#include "data/component.h"
#include "data/bundle.h"
#include "data/jdfdocument.h"

#include "data/cuttingparamslink.h"
#include "data/foldingparamslink.h"
#include "data/medialink.h"
#include "data/laminatingintentlink.h"
#include "data/componentlink.h"
#include "data/resourcelinkpool.h"

#include "proofnetworkjdf_global.h"

Q_LOGGING_CATEGORY(proofNetworkJdfDataLog, "proof.network.jdf.data")

__attribute__((constructor))
static void libraryInit()
{
    qRegisterMetaType<Proof::Jdf::AbstractResourceQmlWrapper *>("Proof::Jdf::AbstractResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractPhysicalResourceQmlWrapper *>("Proof::Jdf::AbstractPhysicalResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfDocument *>("Proof::Jdf::JdfDocument *");

    qRegisterMetaType<Proof::Jdf::ResourcePoolQmlWrapper *>("Proof::Jdf::ResourcePoolQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CuttingParamsQmlWrapper *>("Proof::Jdf::CuttingParamsQmlWrapper *");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>>("QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>>("QQmlListProperty<Proof::Jdf::JdfNodeQmlWrapper>");
    qRegisterMetaType<Proof::Jdf::MediaQmlWrapper *>("Proof::Jdf::MediaQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentQmlWrapper *>("Proof::Jdf::LaminatingIntentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentQmlWrapper *>("Proof::Jdf::ComponentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::FoldingParamsQmlWrapper *>("Proof::Jdf::FoldingParamsQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentQmlWrapper *>("Proof::Jdf::ComponentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfNodeQmlWrapper *>("Proof::Jdf::JdfNodeQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfDocumentQmlWrapper *>("Proof::Jdf::JdfDocumentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfNodeSP>("Proof::Jdf::JdfNodeSP");
    qRegisterMetaType<Proof::Jdf::JdfNodeWP>("Proof::Jdf::JdfNodeWP");

    qRegisterMetaType<Proof::Jdf::ResourceLinkPoolQmlWrapper *>("Proof::Jdf::ResourceLinkPoolQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkQmlWrapper *>("Proof::Jdf::CuttingParamsLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::MediaLinkQmlWrapper *>("Proof::Jdf::MediaLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkQmlWrapper *>("Proof::Jdf::LaminatingIntentLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentLinkQmlWrapper *>("Proof::Jdf::ComponentLinkQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkQmlWrapper *>("Proof::Jdf::FoldingParamsLinkQmlWrapper *");

    qRegisterMetaType<Proof::Jdf::JdfDocumentSP>("Proof::Jdf::JdfDocumentSP");
    qRegisterMetaType<Proof::Jdf::JdfDocumentWP>("Proof::Jdf::JdfDocumentWP");
    qRegisterMetaType<Proof::Jdf::ResourcePoolSP>("Proof::Jdf::ResourcePoolSP");
    qRegisterMetaType<Proof::Jdf::ResourcePoolWP>("Proof::Jdf::ResourcePoolWP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsSP>("Proof::Jdf::CuttingParamsSP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsWP>("Proof::Jdf::CuttingParamsWP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsSP>("Proof::Jdf::FoldingParamsSP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsWP>("Proof::Jdf::FoldingParamsWP");
    qRegisterMetaType<Proof::Jdf::CutBlockSP>("Proof::Jdf::CutBlockSP");
    qRegisterMetaType<Proof::Jdf::CutBlockWP>("Proof::Jdf::CutBlockWP");
    qRegisterMetaType<Proof::Jdf::MediaSP>("Proof::Jdf::MediaSP");
    qRegisterMetaType<Proof::Jdf::MediaWP>("Proof::Jdf::MediaWP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentSP>("Proof::Jdf::LaminatingIntentSP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentWP>("Proof::Jdf::LaminatingIntentWP");
    qRegisterMetaType<Proof::Jdf::ComponentSP>("Proof::Jdf::ComponentSP");
    qRegisterMetaType<Proof::Jdf::ComponentWP>("Proof::Jdf::ComponentWP");
    qRegisterMetaType<Proof::Jdf::BundleSP>("Proof::Jdf::BundleSP");
    qRegisterMetaType<Proof::Jdf::BundleWP>("Proof::Jdf::BundleWP");

    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkSP>("Proof::Jdf::CuttingParamsLinkSP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsLinkWP>("Proof::Jdf::CuttingParamsLinkWP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkSP>("Proof::Jdf::FoldingParamsLinkSP");
    qRegisterMetaType<Proof::Jdf::FoldingParamsLinkWP>("Proof::Jdf::FoldingParamsLinkWP");
    qRegisterMetaType<Proof::Jdf::MediaLinkSP>("Proof::Jdf::MediaLinkSP");
    qRegisterMetaType<Proof::Jdf::MediaLinkWP>("Proof::Jdf::MediaLinkWP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkSP>("Proof::Jdf::LaminatingIntentLinkSP");
    qRegisterMetaType<Proof::Jdf::LaminatingIntentLinkWP>("Proof::Jdf::LaminatingIntentLinkWP");
    qRegisterMetaType<Proof::Jdf::ComponentLinkSP>("Proof::Jdf::ComponentLinkSP");
    qRegisterMetaType<Proof::Jdf::ComponentLinkWP>("Proof::Jdf::ComponentLinkWP");

    qRegisterMetaType<Proof::Jdf::ApiHelper::ResourceStatus>("Proof::Jdf::ApiHelper::ResourceStatus");
    qRegisterMetaType<Proof::Jdf::ApiHelper::ResourceClass>("Proof::Jdf::ApiHelper::ResourceClass");
    qRegisterMetaType<Proof::Jdf::ApiHelper::CoatingType>("Proof::Jdf::ApiHelper::CoatingType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::MediaUnit>("Proof::Jdf::ApiHelper::MediaUnit");
    qRegisterMetaType<Proof::Jdf::ApiHelper::LaminatingSurface>("Proof::Jdf::ApiHelper::LaminatingSurface");
    qRegisterMetaType<Proof::Jdf::ApiHelper::BundleType>("Proof::Jdf::ApiHelper::BundleType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::ComponentType>("Proof::Jdf::ApiHelper::ComponentType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::PartIdKeysType>("Proof::Jdf::ApiHelper::PartIdKeysType");
    qRegisterMetaType<Proof::Jdf::ApiHelper::ProcessUsage>("Proof::Jdf::ApiHelper::ProcessUsage");
    qRegisterMetaType<Proof::Jdf::ApiHelper::Usage>("Proof::Jdf::ApiHelper::Usage");
    qRegisterMetaType<Proof::Jdf::ApiHelper::BlockType>("Proof::Jdf::ApiHelper::BlockType");
}
