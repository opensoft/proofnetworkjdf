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
#ifndef PROOF_XJDF_XJDFHELPER_H
#define PROOF_XJDF_XJDFHELPER_H

#include "proofseed/proofalgorithms.h"

#include "proofnetwork/xjdf/apihelper.h"
#include "proofnetwork/xjdf/data/xjdfdocument.h"
#include "proofnetwork/xjdf/proofnetworkxjdf_types.h"

#include <QVector>

namespace Proof {
namespace XJdf {

inline QVector<XJdfNodeSP> findNodes(const XJdfDocumentSP &job, const QString &type = QString())
{
    if (type.isEmpty())
        return job->findAllNodes([](const auto &) { return true; });
    return job->findAllNodes([type = type.toLower()](const XJdfNodeSP &node) -> bool {
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

inline QVector<XJdfNodeSP> findCuttingNodes(const XJdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("cutting"));
}

inline QVector<XJdfNodeSP> findFoldingNodes(const XJdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("folding"));
}

inline QVector<XJdfNodeSP> findBoxPackingNodes(const XJdfDocumentSP &job)
{
    return findNodes(job, QStringLiteral("boxpacking"));
}

template <typename Resource>
inline QVector<XJdfNodeSP> nodesWithLink(const QVector<XJdfNodeSP> &nodes, LinkUsage usage = LinkUsage::InputLink);

template <>
inline QVector<XJdfNodeSP> nodesWithLink<CuttingParams>(const QVector<XJdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const XJdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->cuttingParamsLink()->isDirty()
               && node->resourceLinkPool()->cuttingParamsLink()->usage() == usage;
    });
}

template <>
inline QVector<XJdfNodeSP> nodesWithLink<FoldingParams>(const QVector<XJdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const XJdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->foldingParamsLink()->isDirty()
               && node->resourceLinkPool()->foldingParamsLink()->usage() == usage;
    });
}

template <>
inline QVector<XJdfNodeSP> nodesWithLink<BoxPackingParams>(const QVector<XJdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const XJdfNodeSP &node) -> bool {
        return node->resourceLinkPool()->boxPackingParamsLink()->isDirty()
               && node->resourceLinkPool()->boxPackingParamsLink()->usage() == usage;
    });
}

template <>
inline QVector<XJdfNodeSP> nodesWithLink<Component>(const QVector<XJdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const XJdfNodeSP &node) -> bool {
        return algorithms::findIf(node->resourceLinkPool()->componentLinks(),
                                  [usage](const auto &link) { return link->usage() == usage; });
    });
}

template <>
inline QVector<XJdfNodeSP> nodesWithLink<Media>(const QVector<XJdfNodeSP> &nodes, LinkUsage usage)
{
    return algorithms::filter(nodes, [usage](const XJdfNodeSP &node) -> bool {
        return algorithms::findIf(node->resourceLinkPool()->mediaLinks(),
                                  [usage](const auto &link) { return link->usage() == usage; });
    });
}

inline QVector<XJdfNodeSP> probablyCuttingNodes(const XJdfDocumentSP &job)
{
    QVector<XJdfNodeSP> result;
    QSet<XJdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QVector<XJdfNodeSP> &nodes) {
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

inline QVector<XJdfNodeSP> probablyFoldingNodes(const XJdfDocumentSP &job)
{
    QVector<XJdfNodeSP> result;
    QSet<XJdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QVector<XJdfNodeSP> &nodes) {
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

inline QVector<XJdfNodeSP> probablyBoxPackingNodes(const XJdfDocumentSP &job)
{
    QVector<XJdfNodeSP> result;
    QSet<XJdfNodeSP> addedNodes;
    auto adder = [&result, &addedNodes](const QVector<XJdfNodeSP> &nodes) {
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

} // namespace XJdf
} // namespace Proof

#endif // PROOF_XJDF_XJDFHELPER_H
