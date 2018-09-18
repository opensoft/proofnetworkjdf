/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef PROOF_JDF_JDFHELPER_H
#define PROOF_JDF_JDFHELPER_H

#include "proofseed/proofalgorithms.h"

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

#include <QVector>

namespace Proof {
namespace Jdf {

inline QVector<JdfNodeSP> findNodes(const JdfDocumentSP &job, const QString &type = QString())
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

inline QVector<JdfNodeSP> findCuttingNodes(const JdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("cutting"));
}

inline QVector<JdfNodeSP> findFoldingNodes(const JdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("folding"));
}

inline QVector<JdfNodeSP> findBoxPackingNodes(const JdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("boxpacking"));
}

template <typename Resource>
inline QVector<JdfNodeSP> nodesWithLink(const QVector<JdfNodeSP> &nodes, LinkUsage usage = LinkUsage::InputLink);

template <>
inline QVector<JdfNodeSP> nodesWithLink<CuttingParams>(const QVector<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->cuttingParamsLink()->isDirty()
               && node->resourceLinkPool()->cuttingParamsLink()->usage() == usage;
    });
}

template <>
inline QVector<JdfNodeSP> nodesWithLink<FoldingParams>(const QVector<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->foldingParamsLink()->isDirty()
               && node->resourceLinkPool()->foldingParamsLink()->usage() == usage;
    });
}

template <>
inline QVector<JdfNodeSP> nodesWithLink<BoxPackingParams>(const QVector<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->boxPackingParamsLink()->isDirty()
               && node->resourceLinkPool()->boxPackingParamsLink()->usage() == usage;
    });
}

template <>
inline QVector<JdfNodeSP> nodesWithLink<Component>(const QVector<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return algorithms::findIf(node->resourceLinkPool()->componentLinks(),
                                  [usage](const auto &link) { return link->usage() == usage; });
    });
}

template <>
inline QVector<JdfNodeSP> nodesWithLink<Media>(const QVector<JdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const JdfNodeSP &node) -> bool {
        return algorithms::findIf(node->resourceLinkPool()->mediaLinks(),
                                  [usage](const auto &link) { return link->usage() == usage; });
    });
}

inline QVector<JdfNodeSP> probablyCuttingNodes(const JdfDocumentSP &job)
{
    QVector<JdfNodeSP> result;
    QSet<JdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QVector<JdfNodeSP> &nodes) {
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

inline QVector<JdfNodeSP> probablyFoldingNodes(const JdfDocumentSP &job)
{
    QVector<JdfNodeSP> result;
    QSet<JdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QVector<JdfNodeSP> &nodes) {
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

inline QVector<JdfNodeSP> probablyBoxPackingNodes(const JdfDocumentSP &job)
{
    QVector<JdfNodeSP> result;
    QSet<JdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QVector<JdfNodeSP> &nodes) {
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
