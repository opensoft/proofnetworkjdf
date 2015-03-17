#include "data/abstractresource.h"
#include "data/abstractphysicalresource.h"
#include "data/cutblock.h"
#include "data/cuttingparams.h"
#include "data/cuttingprocess.h"
#include "data/media.h"
#include "data/component.h"
#include "data/bundle.h"
#include "data/jdfdocument.h"

#include "proofnetworkjdf_global.h"

Q_LOGGING_CATEGORY(proofNetworkJdfDataLog, "proof.network.jdf.data")

__attribute__((constructor))
static void libraryInit()
{
    qRegisterMetaType<Proof::Jdf::AbstractResourceQmlWrapper *>("Proof::Jdf::AbstractResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::AbstractPhysicalResourceQmlWrapper *>("Proof::Jdf::AbstractPhysicalResourceQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfDocument *>("Proof::Jdf::JdfDocument *");
    qRegisterMetaType<Proof::Jdf::CuttingProcessQmlWrapper *>("Proof::Jdf::CuttingProcessQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::CuttingParamsQmlWrapper *>("Proof::Jdf::CuttingParamsQmlWrapper *");
    qRegisterMetaType<QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>>("QQmlListProperty<Proof::Jdf::CutBlockQmlWrapper>");
    qRegisterMetaType<Proof::Jdf::MediaQmlWrapper *>("Proof::Jdf::MediaQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentQmlWrapper *>("Proof::Jdf::ComponentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::ComponentQmlWrapper *>("Proof::Jdf::ComponentQmlWrapper *");
    qRegisterMetaType<Proof::Jdf::JdfDocumentSP>("Proof::Jdf::JdfDocumentSP");
    qRegisterMetaType<Proof::Jdf::JdfDocumentWP>("Proof::Jdf::JdfDocumentWP");
    qRegisterMetaType<Proof::Jdf::CuttingProcessSP>("Proof::Jdf::CuttingProcessSP");
    qRegisterMetaType<Proof::Jdf::CuttingProcessWP>("Proof::Jdf::CuttingProcessWP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsSP>("Proof::Jdf::CuttingParamsSP");
    qRegisterMetaType<Proof::Jdf::CuttingParamsWP>("Proof::Jdf::CuttingParamsWP");
    qRegisterMetaType<Proof::Jdf::CutBlockSP>("Proof::Jdf::CutBlockSP");
    qRegisterMetaType<Proof::Jdf::CutBlockWP>("Proof::Jdf::CutBlockWP");
    qRegisterMetaType<Proof::Jdf::MediaSP>("Proof::Jdf::MediaSP");
    qRegisterMetaType<Proof::Jdf::MediaWP>("Proof::Jdf::MediaWP");
    qRegisterMetaType<Proof::Jdf::ComponentSP>("Proof::Jdf::ComponentSP");
    qRegisterMetaType<Proof::Jdf::ComponentWP>("Proof::Jdf::ComponentWP");
    qRegisterMetaType<Proof::Jdf::BundleSP>("Proof::Jdf::BundleSP");
    qRegisterMetaType<Proof::Jdf::BundleWP>("Proof::Jdf::BundleWP");
}
