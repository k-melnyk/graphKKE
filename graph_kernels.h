#ifndef GRAPH_KERNELS_H
#define GRAPH_KERNELS_H

#include <vector>
#include <unordered_map>
#include <numeric>
#include <string>
#include <algorithm>
#include <set>
#include <thread>

#include "graph.h"
#include "utils.h"

namespace GraphLib {
    std::vector<std::string> GetNodeLabelsFromIndex(const std::set<size_t>& nodeIndices, const std::vector<std::string>& allNodeLabels) {
        std::vector<std::string> nodeNeighborsLabels;
        nodeNeighborsLabels.reserve(allNodeLabels.size());

        for (size_t index : nodeIndices) {
            nodeNeighborsLabels.push_back(allNodeLabels[index]);
        }
        
        return nodeNeighborsLabels;
    }


    void CountLabelsInGraph(const std::vector<std::vector<int>>& graphs, const std::unordered_map<std::string, int>& uniqueNodeLabels, size_t indBegin, size_t indEnd, std::vector<std::vector<int>>& countLabels) {
        std::vector<int> countUniqueLabels;
        countUniqueLabels.reserve(uniqueNodeLabels.size());

        for (size_t i = indBegin; i < indEnd; ++i) {
            const std::vector<int>& currentNodeLabels = graphs[i];

            for (auto& currentUniqueLabel : uniqueNodeLabels) {
                const int currectCount = static_cast<int>(count(currentNodeLabels.begin(), currentNodeLabels.end(), currentUniqueLabel.second));

                countUniqueLabels.push_back(currectCount);
            }

            countLabels[i] = countUniqueLabels;
            countUniqueLabels.clear();
        }
    }

    void ComputeInnerProduct(const std::vector<std::vector<int>>& countLabels, size_t numberOfRowsBegin,  size_t numberOfRowsEnd, std::vector<std::vector<int>>& kernelMatrix) {
        for (size_t i = numberOfRowsBegin; i < numberOfRowsEnd; ++i) {
            std::cout << "Computing kernel for vector: " << i <<std::endl;

            for (size_t j = 0; j < countLabels.size(); ++j) {
                const int dotProduct = std::inner_product(countLabels[i].begin(), countLabels[i].end(), countLabels[j].begin(), 0);
                if (i == j) {
                    kernelMatrix[i][j] = dotProduct;
                }
                else {
                    kernelMatrix[i][j] += dotProduct;
                }
            }
        }
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    std::vector<std::vector<int>> WLSubtreeKernel(const std::vector<Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>>& vectorOfGraph, size_t numberOfIteration) {
        const size_t numberOfGraphs = vectorOfGraph.size();
        std::vector<std::vector<std::string>> currentNodeLabels;
        currentNodeLabels.reserve(numberOfGraphs);

        std::vector<std::vector<std::string>> allGraphNodeLabels(numberOfGraphs);
        std::vector<std::string> uniqueLabels;

        for (size_t i = 0; i < numberOfGraphs; ++i) {
            const std::vector<TYPE_NODE_LABELS>& oldNodeLabels = vectorOfGraph[i].GetNodeLabels();

            std::vector<std::string> newStringLabels;
            newStringLabels.reserve(oldNodeLabels.size());

            for (size_t j = 0; j < oldNodeLabels.size(); ++j) {
                newStringLabels.push_back(std::to_string(oldNodeLabels[j]));
            }

            allGraphNodeLabels[i].insert(allGraphNodeLabels[i].end(), newStringLabels.begin(), newStringLabels.end());
            uniqueLabels.insert(uniqueLabels.end(), newStringLabels.begin(), newStringLabels.end());

            currentNodeLabels.push_back(newStringLabels);
        }

        size_t iter = 0;
        while (iter != numberOfIteration) {
            for (size_t indexOfGraph = 0; indexOfGraph < numberOfGraphs; ++indexOfGraph) {
                std::cout << "Preprocess labels: " << indexOfGraph << std::endl;
                std::vector<std::string> newNodeLabels;

                size_t currentNumberOfNodes = vectorOfGraph[indexOfGraph].GetNumberOfNodes();
                newNodeLabels.reserve(currentNumberOfNodes);
                for (size_t i = 0; i < currentNumberOfNodes; ++i) {
                    const std::set<size_t>& currentNeighbors = vectorOfGraph[indexOfGraph].GetNodeNeighbors(i);
                    std::vector<std::string> nodeNeighborLabel;
                    nodeNeighborLabel.reserve(currentNeighbors.size());

                    if (!currentNeighbors.empty()) {
                        nodeNeighborLabel = GetNodeLabelsFromIndex(currentNeighbors, currentNodeLabels[indexOfGraph]);

                        if (nodeNeighborLabel.size() > 1) {
                            std::sort(nodeNeighborLabel.begin(), nodeNeighborLabel.end());
                        }
                    }

                    std::string nodeLabelsString = currentNodeLabels[indexOfGraph][i];
                    for (size_t j = 0; j < nodeNeighborLabel.size(); ++j) {
                        nodeLabelsString += nodeNeighborLabel[j];
                    }

                    newNodeLabels.push_back(nodeLabelsString);
                }

                currentNodeLabels[indexOfGraph] = newNodeLabels;

                allGraphNodeLabels[indexOfGraph].insert(allGraphNodeLabels[indexOfGraph].end(), newNodeLabels.begin(), newNodeLabels.end());
                uniqueLabels.insert(uniqueLabels.end(), newNodeLabels.begin(), newNodeLabels.end());
            }
            ++iter;
        }

        UniqueValuesInVector(uniqueLabels);

        std::unordered_map<std::string, int> hashLabels;
        std::vector<std::vector<int>> graphLabelsInt;
        graphLabelsInt.resize(numberOfGraphs);

        for (size_t i = 0; i < uniqueLabels.size(); ++i) {
            hashLabels.emplace(uniqueLabels[i], i);
        }

        for (size_t i = 0; i < numberOfGraphs; ++i) {
            for (size_t j = 0; j < allGraphNodeLabels[i].size(); ++j) {
                graphLabelsInt[i].reserve(allGraphNodeLabels[i].size());

                auto search = hashLabels.find(allGraphNodeLabels[i][j]);

                if (search != hashLabels.end()) {
                    graphLabelsInt[i].push_back(search->second);
                }
            }
        }
        std::cout << "Count labels..." << std::endl;

        std::vector<std::vector<int>> countLabels;
        countLabels.resize(numberOfGraphs, std::vector<int>());

        std::vector<std::thread> threads;
        const size_t numberOfThreads = std::thread::hardware_concurrency();
        const size_t step = static_cast<size_t>(graphLabelsInt.size() / numberOfThreads);
        threads.reserve(numberOfThreads);

        if (step != 0) {
            for (size_t i = 0; i < numberOfThreads; ++i) {
                std::cout << "Threading...." << std::endl;

                if (i != numberOfThreads - 1) {
                    std::thread currentThread(CountLabelsInGraph, std::ref(graphLabelsInt), std::ref(hashLabels), step * i , step * (i + 1), std::ref(countLabels));
                    threads.push_back(std::move(currentThread));
                }
                else {
                    std::thread currentThread(CountLabelsInGraph, std::ref(graphLabelsInt), std::ref(hashLabels), step * i, graphLabelsInt.size(), std::ref(countLabels));
                    threads.push_back(std::move(currentThread));
                }
            }

            for (size_t i = 0; i < numberOfThreads; ++i) {
                threads[i].join();
            }
        }
        else {
            CountLabelsInGraph(graphLabelsInt, hashLabels, 0, graphLabelsInt.size(), countLabels);
        }

        threads.clear();

        std::vector<std::vector<int>> kernelMatrix(numberOfGraphs, std::vector<int>(numberOfGraphs, 0));

        if (step != 0) {
            for (size_t i = 0; i < numberOfThreads; ++i) {
                std::cout << "Threading inner product...." << std::endl;

                if (i != numberOfThreads - 1) {
                    std::thread currentThread(ComputeInnerProduct, std::ref(countLabels), step * i, step * (i + 1), std::ref(kernelMatrix));
                    threads.push_back(std::move(currentThread));
                }
                else {
                    std::thread currentThread(ComputeInnerProduct, std::ref(countLabels), step * i, countLabels.size(), std::ref(kernelMatrix));
                    threads.push_back(std::move(currentThread));
                }
            }

            for (size_t i = 0; i < numberOfThreads; ++i) {
                threads[i].join();
            }
        }
        else {
            ComputeInnerProduct(countLabels, 0, countLabels.size(), kernelMatrix);
        }

        return kernelMatrix;
    }
}

#endif // GRAPH_KERNELS_H
