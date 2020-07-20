#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <stdio.h>

#include "utils.h"

namespace GraphLib {

    template <typename TYPE_EDGE_WEIGHT=int>
    class Edge {
    public:
        void AddEdgeWeight(size_t indexNode1, size_t indexNode2, TYPE_EDGE_WEIGHT weight) {
            m_indexOfNode1 = indexNode1;
            m_indexOfNode2 = indexNode2;
            m_weight = weight;
        }

        std::pair<size_t, size_t> GetNodeIndeces() {
            const std::pair<size_t, size_t> nodeIndeces = {m_indexOfNode1, m_indexOfNode2};

            return nodeIndeces;
        }

        TYPE_EDGE_WEIGHT GetWeight() {
            return m_weight;
        }

    private:
        size_t m_indexOfNode1;
        size_t m_indexOfNode2;

        TYPE_EDGE_WEIGHT m_weight;
    };

    template <typename TYPE_NODE_LABELS=int, typename TYPE_EDGE_WEIGHT=int>
    class Graph {
    public:
        Graph() = default;
        Graph(const Graph& graph) noexcept;
        Graph(Graph&& graphs) noexcept;
        Graph(size_t numOfNodes);
        Graph(const std::vector<std::vector<size_t>>& adjMatrix);
        Graph(const std::vector<std::pair<size_t, size_t>>& vectorOfEdges, size_t numberOfNodes);

        Graph& operator=(Graph&& graph) noexcept;
        Graph& operator=(const Graph& graph) noexcept;

        void AddEdge(size_t sourceNodeINdex, size_t destNodeIndex);
        void AddNodeLabels(const std::vector<TYPE_NODE_LABELS> vectorOfNodeLabels);
        void AddEdgeWeight(std::pair<size_t, size_t> pairOfNodes, TYPE_EDGE_WEIGHT weight);

        size_t GetNumberOfNodes() const;
        std::vector<std::vector<int>> GetAdjMatrix() const;

        const std::set<size_t>& GetNodeNeighbors(size_t indexOfNode) const;
        const std::vector<TYPE_NODE_LABELS>& GetNodeLabels() const;
        TYPE_EDGE_WEIGHT GetEdgeWeight(size_t indexOfNode1, size_t indexOfNode2) const;
        std::vector<std::pair<size_t, size_t>> GetVectorOfEdges() const;

    protected:
        size_t m_numberOfNodes;
        std::unordered_map<size_t, std::set<size_t>> m_adjList;

        std::vector<TYPE_NODE_LABELS> m_nodeLabels;
        std::vector<Edge<TYPE_EDGE_WEIGHT>> m_edgeWeights;
    };

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::Graph(size_t numOfNodes) : m_numberOfNodes(numOfNodes) {
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::Graph(const Graph& graph) noexcept : m_numberOfNodes(graph.m_numberOfNodes),
                                                                           m_adjList(graph.m_adjList),
                                                                           m_nodeLabels(graph.m_nodeLabels),
                                                                           m_edgeWeights(graph.m_edgeWeights) {
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::Graph(Graph&& graph) noexcept : m_numberOfNodes(graph.m_numberOfNodes),
                                                                      m_adjList(graph.m_adjList),
                                                                      m_nodeLabels(graph.m_nodeLabels),
                                                                      m_edgeWeights(graph.m_edgeWeights) {
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>& Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::operator=(const Graph& graph) noexcept {
        if (this == &graph) return *this;

        m_numberOfNodes = graph.m_numberOfNodes;
        m_adjList = std::move(graph.m_adjList);
        m_nodeLabels = std::move(graph.m_nodeLabels);
        m_edgeWeights = std::move(graph.m_edgeWeights);
        return *this;
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>& Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::operator=(Graph&& graph) noexcept{
        if (this == &graph) return *this;

        m_numberOfNodes = graph.m_numberOfNodes;
        m_adjList = std::move(graph.m_adjList);
        m_nodeLabels = std::move(graph.m_nodeLabels);
        m_edgeWeights = std::move(graph.m_edgeWeights);
        return *this;
    }


    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::Graph(const std::vector<std::vector<size_t>>& adjMatrix) : m_numberOfNodes(adjMatrix.size()) {
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            std::set<size_t> nodeNeighbors;
            for (size_t j = 0; j < adjMatrix.size(); ++j) {
                if (adjMatrix[i][j]) {
                    nodeNeighbors.insert(j);
                }
            }
            m_adjList.emplace(i, nodeNeighbors);
        }
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::Graph(const std::vector<std::pair<size_t, size_t>>& vectorOfEdges, size_t numberOfNodes) : m_numberOfNodes(numberOfNodes) {
        for (size_t i = 0; i < numberOfNodes; ++i) {
            m_adjList.emplace(i, std::set<size_t>());
        }

        for (auto& pair : vectorOfEdges) {
            AddEdge(pair.first, pair.second);
            AddEdge(pair.second, pair.first);
        }
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    void Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::AddEdge(size_t sourceNodeIndex, size_t destNodeIndex) {
        m_adjList.at(sourceNodeIndex).insert(destNodeIndex);
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    void Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::AddNodeLabels(const std::vector<TYPE_NODE_LABELS> vectorOfNodeLabels) {
        for (size_t i = 0; i < vectorOfNodeLabels.size(); ++i) {
            m_nodeLabels.push_back(vectorOfNodeLabels[i]);
        }
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    void Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::AddEdgeWeight(std::pair<size_t, size_t> pairOfNodes, TYPE_EDGE_WEIGHT weight) {
        Edge<TYPE_EDGE_WEIGHT> edge1;
        Edge<TYPE_EDGE_WEIGHT> edge2;

        size_t indexNode1 = pairOfNodes.first;
        size_t indexNode2 = pairOfNodes.second;

        edge1.AddEdgeWeight(indexNode1, indexNode2, weight);
        edge2.AddEdgeWeight(indexNode2, indexNode1, weight);

        m_edgeWeights.push_back(edge1);
        m_edgeWeights.push_back(edge2);
    }


    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    size_t Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::GetNumberOfNodes() const {
        return m_numberOfNodes;
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    const std::vector<TYPE_NODE_LABELS>& Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::GetNodeLabels() const {
        return m_nodeLabels;
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    const std::set<size_t>& Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::GetNodeNeighbors(size_t indexOfNode) const {
        auto it = m_adjList.find(indexOfNode);
        if (it != m_adjList.end()) {
            return it->second;
        }
        else {
            const static std::set<size_t> empty_result;
            return empty_result;
        }
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    std::vector<std::pair<size_t, size_t>> Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::GetVectorOfEdges() const {
        std::vector<std::pair<size_t, size_t>> vectorOfEdges;

        std::vector<bool> flagsSourceNodes(m_numberOfNodes, false);

        for (size_t i = 0; i < m_numberOfNodes; ++i) {
            const std::set<size_t>& currentAdjList = GetNodeNeighbors(i);

            if (!currentAdjList.empty()) {
                for (auto& node : currentAdjList) {
                    if (!flagsSourceNodes[node]) {
                        vectorOfEdges.push_back(std::make_pair(i, node));
                    }
                }
                flagsSourceNodes[i] = true;
            }
        }

        return vectorOfEdges;
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    std::vector<std::vector<int>> Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::GetAdjMatrix() const {
        std::vector<std::vector<int>> adjMatrix;
        adjMatrix.reserve(m_numberOfNodes);

        for (size_t i = 0; i < m_numberOfNodes; ++i) {
            std::vector<int> rows(m_numberOfNodes, 0);
            adjMatrix.push_back(rows);
        }

        for (auto& pair : m_adjList) {
            for (auto& neighbors : pair.second) {
                adjMatrix[pair.first][neighbors] = 1;
            }
        }

        return adjMatrix;
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    TYPE_EDGE_WEIGHT Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>::GetEdgeWeight(size_t indexOfNode1, size_t indexOfNode2) const {
        for (size_t i = 0; i < m_edgeWeights.size(); ++i) {
            Edge<TYPE_EDGE_WEIGHT> currentEdge = m_edgeWeights[i];
            std::pair<size_t, size_t> pairOfNodes = currentEdge.GetNodeIndeces();

            if (pairOfNodes.first == indexOfNode1 && pairOfNodes.second == indexOfNode2) {
                return currentEdge.GetWeight();
                break;
            }

            if (pairOfNodes.first == indexOfNode2 && pairOfNodes.second == indexOfNode1) {
                return currentEdge.GetWeight();
                break;
            }
        }
        return 0;
    }
}

#endif // GRAPH_H
