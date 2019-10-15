#include "proofnetwork/xjdf/xjdfhelper.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/document.h"
#include "proofnetwork/xjdf/data/resourceset.h"
#include <proofnetwork/xjdf/data/component.h>
#include <proofnetwork/xjdf/data/cutblock.h>
#include <proofnetwork/xjdf/data/cuttingparams.h>
#include <proofnetwork/xjdf/data/media.h>

#include <QTransform>

namespace Proof {
namespace XJdf {

void flipCutBlocksVertically(const DocumentSP &document)
{
    if (!document || !document->isDirty()) {
        qCCritical(proofNetworkXJdfDataLog) << "Job doesn't flip. XJDF document not valid.";
        return;
    }

    double height = 0.0;
    const auto mediaList = document->findResources<Media>([](const auto &media) {
        return media->type() == MediaType::Paper && media->width() > 0.0 && media->height() > 0.0;
    });
    for (const auto &media : mediaList)
        height = std::max(height, media->height());

    const auto inputComponentResourceSets = algorithms::filter(document->resourceSets(), [](const auto &resourceSet) {
        return resourceSet->usage() == UsageType::Input && !resourceSet->template resourcesByType<Component>().isEmpty();
    });

    for (const auto &resourceSet : inputComponentResourceSets) {
        const auto components = resourceSet->resourcesByType<Component>();
        for (const auto &component : components)
            height = std::max(height, component->height());
    }

    if (qFuzzyIsNull(height)) {
        qCCritical(proofNetworkXJdfDataLog) << "Job doesn't flip. Dimentions not found.";
        return;
    }

    const auto cuttingParamsList = document->findResources<Proof::XJdf::CuttingParams>();
    for (const auto &cuttingParams : cuttingParamsList) {
        int rotation = Proof::XJdf::resourceRotateToInt(cuttingParams->orientation());
        cuttingParams->setOrientation(Proof::XJdf::ResourceOrientation::Rotate0Orientation);
        const auto cutBlocks = cuttingParams->cutBlocks();
        for (const auto &cutBlock : cutBlocks) {
            QRectF rect = QTransform(1, 0, 0, -1, 0, height)
                              .translate(cutBlock->x(), cutBlock->y())
                              .rotate(rotation)
                              .mapRect(QRectF(0, 0, cutBlock->width(), cutBlock->height()));

            cutBlock->setX(rect.x());
            cutBlock->setY(rect.y());
            cutBlock->setWidth(rect.width());
            cutBlock->setHeight(rect.height());
        }
    }
    qCDebug(proofNetworkXJdfDataLog) << "Job flipped";
}

} // namespace XJdf
} // namespace Proof
