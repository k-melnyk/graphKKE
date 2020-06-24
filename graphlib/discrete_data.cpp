#include <vector>
#include <iostream>
#include <fstream>
#include "graph.h"
#include "graph_kernels.h"

int main() {
    size_t numOfNodes = 150;
    size_t numOfGraphs = 2000;
    std::ifstream dataFile ("/home/katerynam/work/data/artificial/prob_150_2k/data.txt");

    std::vector<GraphLib::Graph<>> vecOfGraphs;
    vecOfGraphs.reserve(numOfGraphs);

    std::vector<int> nodeLabels;
    for (size_t i = 1; i <= numOfNodes; ++i) {
        nodeLabels.push_back(static_cast<int>(i));
    }

    if (dataFile.is_open()) {
        for (size_t i = 0; i < numOfGraphs; ++i) {
            std::cout << "Loading of graph " << i << std::endl;
            std::vector<std::vector<size_t>> adjMatrix;
            size_t value;

            for (size_t row = 0; row < numOfNodes; ++row) {
                std::vector<size_t> currentRow;
                for (size_t col = 0; col < numOfNodes; ++col) {
                    dataFile >> value;
                    currentRow.push_back(value);
                }
                adjMatrix.push_back(currentRow);
            }

            GraphLib::Graph<> graph(adjMatrix);
            graph.AddNodeLabels(nodeLabels);
            vecOfGraphs.push_back(graph);
        }
        dataFile.close();
    }

//    std::fstream dataFileNodeLabels("/home/katerynam/work/data/colored_nodes/dynamic/node_labels.txt");

//    if (dataFileNodeLabels.is_open()) {
//        int value;
//        std::vector<int> currentNodeLabels;
//        currentNodeLabels.reserve(numOfNodes);

//        for (size_t i = 0; i < numOfGraphs; ++i) {
//            for (size_t j = 0; j < numOfNodes; ++j) {
//                dataFileNodeLabels >> value;
//                currentNodeLabels.push_back(value);
//            }
//            vecOfGraphs[i].AddNodeLabels(currentNodeLabels);
//            currentNodeLabels.clear();
//        }
//        dataFileNodeLabels.close();
//    }

    std::cout <<"Wl:"<<std::endl;
    auto start = std::chrono::system_clock::now();
    size_t numberOfIteration = 1;
    std::vector<std::vector<int>> resultWL;
    resultWL = GraphLib::WLSubtreeKernel(vecOfGraphs, numberOfIteration);
    auto end = std::chrono::system_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time of computing WL without threading" << int_ms.count() << std::endl;


    std::cout <<"Saving..."<<std::endl;
    std::ofstream dataFileOutput ("/home/katerynam/work/data/artificial/prob_150_2k/test");
    if (dataFileOutput.is_open()) {
        for (size_t row = 0; row < numOfGraphs; ++row) {
            for (size_t col = 0; col < numOfGraphs; ++col) {
                dataFileOutput << resultWL[row][col] << " ";
            }
            dataFileOutput << std::endl;
        }
        dataFileOutput.close();
    }
}

