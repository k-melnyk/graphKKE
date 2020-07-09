#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <utility>
#include <cassert>
#include <map>

#include "graph.h"

template <typename TYPE_WEIGHT>
size_t MinDistance(const std::vector<TYPE_WEIGHT>& vectorOfDistances, const std::vector<bool>& checkedNodes) {
    int minElem = INT_MAX;
    size_t indexMinElement = 0;

    for (size_t i = 0; i < vectorOfDistances.size(); ++i) {
        if (!checkedNodes[i] && vectorOfDistances[i] <= minElem) {
            minElem = vectorOfDistances[i];
            indexMinElement = i;
        }
    }
    return indexMinElement;
}

template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
std::vector<TYPE_EDGE_WEIGHT> DijkstraAlgo(GraphLib::Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT> graph, size_t indexSourceNode) {
    const size_t numberOfNodes = graph.GetNumberOfNodes();

    std::vector<bool> checkedNodes(numberOfNodes, 0);
    std::vector<TYPE_EDGE_WEIGHT> distances(numberOfNodes, INT_MAX);

    distances[indexSourceNode] = 0;

    size_t i = 0;
    while (i < numberOfNodes) {
        size_t indexCurrentNode = MinDistance(distances, checkedNodes);
        checkedNodes[indexCurrentNode] = 1;
        const std::vector<size_t> &currentAdjList = graph.GetNodeNeighbors(indexCurrentNode);

        for (size_t i = 0; i < currentAdjList.size(); ++i) {
            TYPE_EDGE_WEIGHT invalidValue = graph.GetInvalidValue();
            TYPE_EDGE_WEIGHT weightEdge = graph.GetEdgeWeight(indexCurrentNode, currentAdjList[i]);
            if (weightEdge != invalidValue) {

                if (!checkedNodes[currentAdjList[i]] && distances[indexCurrentNode] + weightEdge < distances[currentAdjList[i]]) {
                    distances[currentAdjList[i]] = distances[indexCurrentNode] + weightEdge;
                }
            }
        }
        ++i;
    }
    return distances;
}

#endif // DIJKSTRA_H
