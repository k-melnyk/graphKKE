#include <iostream>
#include <vector>
#include <cstdio>
#include <random>

#include "binarytree.h"
#include "red_black_t.h"
#include "DfsBfs.h"
#include "graph.h"
#include "dijkstra.h"
#include "graph_kernels.h"
#include "node2vec.h"
#include "utils.h"

void TestDFS() {
    std::vector<int> resultBFS;
    std::vector<int> resultDFS;

    Trees::BinaryTree<int> binaryTree;

    binaryTree.InsertNode(4);
    binaryTree.InsertNode(2);
    binaryTree.InsertNode(5);
    binaryTree.InsertNode(1);
    binaryTree.InsertNode(3);

    resultBFS = Trees::BFS<Trees::BinaryTree<int>, int>(binaryTree); // 4 2 5 1 3
    resultDFS = Trees::DFS<Trees::BinaryTree<int>, int>(binaryTree); // 4 2 1 3 5

    for(size_t i = 0; i < resultBFS.size(); ++i) {
        std::cout << "BFS: " << resultBFS[i] << std::endl;
    }

    for(size_t i = 0; i < resultDFS.size(); ++i) {
        std::cout << "DFS: " << resultDFS[i] << std::endl;
    }
}

//void TestWeightedGraph() {
//    GraphLib::Graph<float> graph(5);

//    graph.AddEdge(0, 1);
//    graph.AddEdge(0, 3);
//    graph.AddEdge(0, 4);
//    graph.AddEdge(1, 2);
//    graph.AddEdge(1, 3);
//    graph.AddEdge(2, 4);
//    graph.AddEdge(2, 3);

//    graph.PrintGraph();

//    // Weighted graph test
//    GraphLib::Graph<float> weightedGraph(5);

//    weightedGraph.AddEdgeWeighted(0, 1, 0.5f);
//    weightedGraph.AddEdgeWeighted(0, 3, 0.1f);
//    weightedGraph.AddEdgeWeighted(0, 4, 0.2f);
//    weightedGraph.AddEdgeWeighted(1, 2, 0.3f);
//    weightedGraph.AddEdgeWeighted(1, 3, 0.4f);
//    weightedGraph.AddEdgeWeighted(2, 4, 0.2f);
//    weightedGraph.AddEdgeWeighted(2, 3, 0.7f);

//    weightedGraph.PrintGraph();
//}

//void TestDijkstra() {
//    GraphLib::Graph<int> weightedGraphDijkstra(9);

//    weightedGraphDijkstra.AddEdgeWeighted(0, 1, 4);
//    weightedGraphDijkstra.AddEdgeWeighted(1, 2, 8);
//    weightedGraphDijkstra.AddEdgeWeighted(2, 3, 7);
//    weightedGraphDijkstra.AddEdgeWeighted(3, 4, 9);
//    weightedGraphDijkstra.AddEdgeWeighted(4, 5, 10);
//    weightedGraphDijkstra.AddEdgeWeighted(5, 6, 2);
//    weightedGraphDijkstra.AddEdgeWeighted(6, 7, 1);
//    weightedGraphDijkstra.AddEdgeWeighted(0, 7, 8);
//    weightedGraphDijkstra.AddEdgeWeighted(7, 8, 7);
//    weightedGraphDijkstra.AddEdgeWeighted(6, 8, 6);
//    weightedGraphDijkstra.AddEdgeWeighted(2, 8, 2);
//    weightedGraphDijkstra.AddEdgeWeighted(2, 5, 4);
//    weightedGraphDijkstra.AddEdgeWeighted(3, 5, 14);

//    weightedGraphDijkstra.PrintGraph();

//    std::vector<int> distances;
//    distances = DijkstraAlgo<GraphLib::Graph<int>, int>(weightedGraphDijkstra, 0);

//    printf("Vertex \t\t Distance from Source\n");
//    for(size_t i = 0; i < distances.size(); ++i) {
//        printf("%d \t\t %d\n", static_cast<int>(i), distances[i]);
//    }
//}

void TestWLKernel() {
    std::vector<std::pair<size_t, size_t>> listOfEdges1 = {{0, 2}, {1, 2}, {2, 3}, {2, 5}, {3, 4}, {3, 5}, {4, 5}};

    GraphLib::Graph<> graph1(listOfEdges1, 6);
//    graph1.AddEdge(0, 2);
//    graph1.AddEdge(1, 2);
//    graph1.AddEdge(2, 3);
//    graph1.AddEdge(2, 5);
//    graph1.AddEdge(3, 4);
//    graph1.AddEdge(3, 5);
//    graph1.AddEdge(4, 5);

    std::vector<int> nodeLabels1 = {1,1,4, 5,2,3};
    graph1.AddNodeLabels(nodeLabels1);

    std::vector<std::pair<size_t, size_t>> listOfEdges2 = {{0,1}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}, {4, 5}};
    GraphLib::Graph<> graph2(listOfEdges2, 6);
//    graph2.AddEdge(0, 1);
//    graph2.AddEdge(1, 2);
//    graph2.AddEdge(1, 3);
//    graph2.AddEdge(1, 4);
//    graph2.AddEdge(2, 3);
//    graph2.AddEdge(3, 4);
//    graph2.AddEdge(4, 5);

    std::vector<int> nodeLabels2 = {1,4,2,5,3,2};
    graph2.AddNodeLabels(nodeLabels2);

    std::vector<std::pair<size_t, size_t>> listOfEdges3 = {{0, 2}, {1, 2}, {2, 3}, {2, 5}, {3, 4}, {3, 5}, {4, 5}};

    GraphLib::Graph<> graph3(listOfEdges3, 6);
//    graph1.AddEdge(0, 2);
//    graph1.AddEdge(1, 2);
//    graph1.AddEdge(2, 3);
//    graph1.AddEdge(2, 5);
//    graph1.AddEdge(3, 4);
//    graph1.AddEdge(3, 5);
//    graph1.AddEdge(4, 5);

    std::vector<int> nodeLabels3 = {1,1,4, 5,2,3};
    graph3.AddNodeLabels(nodeLabels3);

    std::vector<std::pair<size_t, size_t>> listOfEdges4 = {{0,1}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}, {4, 5}};
    GraphLib::Graph<> graph4(listOfEdges4, 6);
//    graph2.AddEdge(0, 1);
//    graph2.AddEdge(1, 2);
//    graph2.AddEdge(1, 3);
//    graph2.AddEdge(1, 4);
//    graph2.AddEdge(2, 3);
//    graph2.AddEdge(3, 4);
//    graph2.AddEdge(4, 5);

    std::vector<int> nodeLabels4 = {1,4,2,5,3,2};
    graph4.AddNodeLabels(nodeLabels4);

    std::vector<std::vector<int>> adjMatrix;
    adjMatrix = graph1.GetAdjMatrix();

    std::vector<GraphLib::Graph<>> vectorOfGraphs = {graph1, graph2, graph3, graph4};
    size_t numberOfIteration = 1;
    std::vector<std::vector<int>> resultWL;
    resultWL = GraphLib::WLSubtreeKernel(vectorOfGraphs, numberOfIteration);

    int a = 0;
}

void TestNode2Vec() {
    size_t numberOutcomes = 5;
    std::default_random_engine generator;
    std::gamma_distribution<double> distribution(1, 1);
    std::vector<double> gammaDistr;
    gammaDistr.reserve(numberOutcomes);

    double sum = 0;
    for (size_t i = 0; i < numberOutcomes; ++i) {
        double variable = distribution(generator);
        gammaDistr.push_back(variable);
        sum += variable;
    }

    std::vector<double> dirichletDistr;
    dirichletDistr.reserve(numberOutcomes);

    for (size_t i = 0; i < numberOutcomes; ++i) {
        double value = gammaDistr[i] / sum;
        dirichletDistr.push_back(value);
    }

    size_t N = 1000;
    std::vector<size_t> J(numberOutcomes);
    std::vector<double> q(numberOutcomes);
    std::vector<size_t> X;

    AliasSetup(dirichletDistr, J, q);
    X = AliasDraw(N, J, q);
}

void TestAdjMatrix() {
    std::vector<std::vector<size_t>> adjMatrix(4);
    adjMatrix[0] = {0,1,0,0};
    adjMatrix[1] = {1,0,1,1};
    adjMatrix[2] = {1,0,0,1};
    adjMatrix[3] = {0,1,1,0};

    GraphLib::Graph<> graph(adjMatrix);

    GraphLib::Graph<int, int> graph1(4);
    graph1.AddEdge(0, 1);
    graph1.AddEdge(1, 2);
    graph1.AddEdge(1, 3);
    graph1.AddEdge(2, 3);

    std::vector<std::pair<size_t, size_t>> edgeVec(4);
    edgeVec[0] = std::make_pair(0, 1);
    edgeVec[1] = std::make_pair(1, 2);
    edgeVec[2] = std::make_pair(1, 3);
    edgeVec[3] = std::make_pair(2, 3);

    GraphLib::Graph<> graph2(edgeVec, 4);

    std::vector<std::pair<size_t, size_t>> vectorOfEdges = graph.GetVectorOfEdges();
}

void TestEdgeWeight() {
    std::vector<std::vector<size_t>> adjMatrix(4);
    adjMatrix[0] = {0,1,0,0};
    adjMatrix[1] = {1,0,1,1};
    adjMatrix[2] = {1,0,0,1};
    adjMatrix[3] = {0,1,1,0};

    GraphLib::Graph<> graph(adjMatrix);

    std::unordered_map<size_t, std::pair<size_t, int>> edgeWeight;
    edgeWeight.emplace(0, std::make_pair(1, 5));
    edgeWeight.emplace(1, std::make_pair(2, 7));
    edgeWeight.emplace(1, std::make_pair(3, 4));

    graph.AddEdgeWeight(std::make_pair(0, 1), 5);
    graph.AddEdgeWeight(std::make_pair(1, 2), 7);
    graph.AddEdgeWeight(std::make_pair(3, 1), 4);


    int a = 2 ;
}

int main() {
    TestWLKernel();
    return 0;
}
