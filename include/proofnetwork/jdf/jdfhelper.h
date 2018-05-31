#ifndef PROOF_JDF_JDFHELPER_H
#define PROOF_JDF_JDFHELPER_H

#include "proofcore/proofalgorithms.h"

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/boxpackingparams.h"
#include "proofnetwork/jdf/data/boxpackingparamslink.h"
#include "proofnetwork/jdf/data/component.h"
#include "proofnetwork/jdf/data/componentlink.h"
#include "proofnetwork/jdf/data/cuttingparams.h"
#include "proofnetwork/jdf/data/cuttingparamslink.h"
#include "proofnetwork/jdf/data/foldingparams.h"
#include "proofnetwork/jdf/data/foldingparamslink.h"
#include "proofnetwork/jdf/data/jdfdocument.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/resourcelinkpool.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QList>

namespace Proof {
namespace Jdf {

inline QList<JdfNodeSP> findNodes(const JdfDocumentSP &job, const QString &type = QString(""))
{
    if (type.isEmpty()) {
        return job->findAllNodes([](const auto &) { return true; });
    } else {
        return job->findAllNodes([type = type.toLower()](const JdfNodeSP &node) -> bool {
            auto loweredType = node->type().toLower();
            if (loweredType == type)
                return true;
            if (loweredType == QLatin1String("processgroup") || loweredType == QLatin1String("combined"))
                return algorithms::findIf(node->types(),
                                          [type](const auto &t) { return !t.compare(type, Qt::CaseInsensitive); })
                    .count();
            return false;
        });
    }
}

inline QList<JdfNodeSP> findCuttingNodes(const JdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("cutting"));
}

inline QList<JdfNodeSP> findFoldingNodes(const JdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("folding"));
}

inline QList<JdfNodeSP> findBoxPackingNodes(const JdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("boxpacking"));
}

template <typename Resource>
inline QList<JdfNodeSP> nodesWithLink(const QList<JdfNodeSP> &nodes, LinkUsage usage = LinkUsage::InputLink);

template <>
inline QList<JdfNodeSP> nodesWithLink<CuttingParams>(const QList<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->cuttingParamsLink()->isDirty()
               && node->resourceLinkPool()->cuttingParamsLink()->usage() == usage;
    });
}

template <>
inline QList<JdfNodeSP> nodesWithLink<FoldingParams>(const QList<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->foldingParamsLink()->isDirty()
               && node->resourceLinkPool()->foldingParamsLink()->usage() == usage;
    });
}

template <>
inline QList<JdfNodeSP> nodesWithLink<BoxPackingParams>(const QList<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->boxPackingParamsLink()->isDirty()
               && node->resourceLinkPool()->boxPackingParamsLink()->usage() == usage;
    });
}

template <>
inline QList<JdfNodeSP> nodesWithLink<Component>(const QList<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return algorithms::findIf(node->resourceLinkPool()->componentLinks(),
                                  [usage](const auto &link) { return link->usage() == usage; });
    });
}

template <>
inline QList<JdfNodeSP> nodesWithLink<Media>(const QList<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return algorithms::findIf(node->resourceLinkPool()->mediaLinks(),
                                  [usage](const auto &link) { return link->usage() == usage; });
    });
}

inline QList<JdfNodeSP> probablyCuttingNodes(const JdfDocumentSP &job)
{
    QList<JdfNodeSP> result;
    QSet<JdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QList<JdfNodeSP> &nodes) {
        for (const auto &node : nodes) {
            if (addedNodes.contains(node))
                continue;
            addedNodes << node;
            result << node;
        }
    };
    const auto cuttingNodes = findCuttingNodes(job);
    adder(nodesWithLink<CuttingParams>(cuttingNodes));
    adder(cuttingNodes);
    adder(nodesWithLink<CuttingParams>(findNodes(job)));
    return result;
}

inline QList<JdfNodeSP> probablyFoldingNodes(const JdfDocumentSP &job)
{
    QList<JdfNodeSP> result;
    QSet<JdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QList<JdfNodeSP> &nodes) {
        for (const auto &node : nodes) {
            if (addedNodes.contains(node))
                continue;
            addedNodes << node;
            result << node;
        }
    };
    const auto foldingNodes = findFoldingNodes(job);
    adder(nodesWithLink<FoldingParams>(foldingNodes));
    adder(foldingNodes);
    adder(nodesWithLink<FoldingParams>(findNodes(job)));
    return result;
}

inline QList<JdfNodeSP> probablyBoxPackingNodes(const JdfDocumentSP &job)
{
    QList<JdfNodeSP> result;
    QSet<JdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QList<JdfNodeSP> &nodes) {
        for (const auto &node : nodes) {
            if (addedNodes.contains(node))
                continue;
            addedNodes << node;
            result << node;
        }
    };
    const auto boxPackingNodes = findBoxPackingNodes(job);
    adder(nodesWithLink<BoxPackingParams>(boxPackingNodes));
    adder(boxPackingNodes);
    adder(nodesWithLink<BoxPackingParams>(findNodes(job)));
    return result;
}

} // namespace Jdf
} // namespace Proof

#endif // PROOF_JDF_JDFHELPER_H
