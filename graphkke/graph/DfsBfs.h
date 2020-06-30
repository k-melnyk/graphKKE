#ifndef DFS_BSF_H
#define DFS_BFS_H

#include "binarytree.h"
#include "graph.h"

namespace Trees {

    template <typename TYPE_TREE, typename TYPE>
    std::vector<TYPE> DFS(const TYPE_TREE& tree) {
        std::vector<TYPE> dfsVector;
        std::stack<Node<TYPE>*> nodes;

        nodes.push(tree.GetRoot());

        Node<TYPE>* currentNode = nullptr;
        while (!nodes.empty()) {
            currentNode = nodes.top();
            dfsVector.push_back(currentNode->data);
            nodes.pop();

            if (currentNode->right) {
                nodes.push(currentNode->right);
            }
            if (currentNode->left) {
                nodes.push(currentNode->left);
            }
        }

        return dfsVector;
    }

    template <typename TYPE_TREE, typename TYPE>
    std::vector<TYPE> BFS(const TYPE_TREE& tree) {
        std::vector<TYPE> bfsVector;
        std::queue<Node<TYPE>*> nodes;

        nodes.push(tree.GetRoot());

        Node<TYPE>* currentNode = nullptr;
        while (!nodes.empty()) {
            currentNode = nodes.front();
            bfsVector.push_back(currentNode->data);
            nodes.pop();

            if (currentNode->left) {
                nodes.push(currentNode->left);
            }
            if (currentNode->right) {
                nodes.push(currentNode->right);
            }
        }

        return bfsVector;
    }

    template<typename TYPE>
    void CheckIfInRange(const Node<TYPE>* currentNode, TYPE leftBorder, TYPE rightBorder, const std::vector<TYPE>& nodeInList) {
        if (currentNode->data >= leftBorder && currentNode->data <= rightBorder) {
            nodeInList.push_back(currentNode->data);
            if (currentNode->right) {
                CheckIfInRange(currentNode->right, currentNode->data, rightBorder, nodeInList);
            }
            if (currentNode->left) {
                CheckIfInRange(currentNode->left, leftBorder, currentNode->data, nodeInList);
            }
        }
        else if (currentNode->data < leftBorder) {
            if (currentNode->right) {
                CheckIfInRange(currentNode->right, leftBorder, rightBorder, nodeInList);
            }
        }
        else if (currentNode->data > rightBorder) {
            if (currentNode->left) {
                CheckIfInRange(currentNode->left, leftBorder, rightBorder, nodeInList);
            }
        }
    }

    template<typename TYPE>
    std::vector<TYPE> SearchInRange(const BinaryTree<TYPE>& tree, int leftBorder, int rightBorder) {
        std::vector<TYPE> nodeInList;
        Node<TYPE> *currentNode = tree.get_root();
        CheckIfInRange(currentNode, leftBorder, rightBorder, nodeInList);
        return nodeInList;
    }
}

namespace GraphLib {

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    std::vector<size_t> BFS(const Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>& graph, size_t indexSourceNode) {
        std::vector<size_t> bfsVector;
        std::queue<size_t> queueNodes;
        std::vector<bool> checkedNodes(graph.GetNumberOfNodes(), false);
        size_t currentNode = 0;

        queueNodes.push(indexSourceNode);
        checkedNodes[indexSourceNode] = true;

        while (!queueNodes.empty()) {
            currentNode = queueNodes.front();
            bfsVector.push_back(currentNode);
            queueNodes.pop();

            const std::vector<size_t>& neighborsOfCurrNode = graph.GetNodeNeighbors(currentNode);
            for (size_t i = 0; i < neighborsOfCurrNode.size(); ++i) {
                if (!checkedNodes[neighborsOfCurrNode[i]]) {
                   queueNodes.push(neighborsOfCurrNode[i]);
                   checkedNodes[neighborsOfCurrNode[i]] = true;
                }
            }
        }

        return bfsVector;
    }

    template <typename TYPE_NODE_LABELS, typename TYPE_EDGE_WEIGHT>
    std::vector<size_t> DFS(const Graph<TYPE_NODE_LABELS, TYPE_EDGE_WEIGHT>& graph, size_t indexSourceNode) {
        std::vector<size_t> dfsVector;
        std::stack<size_t> stackNodes;
        std::vector<bool> checkedNodes(graph.GetNumberOfNodes(), false);
        size_t currentNode = 0;

        stackNodes.push(indexSourceNode);
        checkedNodes[indexSourceNode] = true;

        while (!stackNodes.empty()) {
            currentNode = stackNodes.top();
            dfsVector.push_back(currentNode);
            stackNodes.pop();

            const std::vector<size_t>& neighborsOfCurrNode = graph.GetNodeNeighbors(currentNode);
            for (size_t i = 0; i < neighborsOfCurrNode.size(); ++i) {
                if (!checkedNodes[neighborsOfCurrNode[i]]) {
                    stackNodes.push(neighborsOfCurrNode[i]);
                    checkedNodes[neighborsOfCurrNode[i]] = true;
                }
            }
        }

        return dfsVector;
    }
}

#endif // DFS_BFS_H
