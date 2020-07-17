#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <queue>
#include <stack>
#include <cassert>
#include <iostream>

#include "node.h"

namespace Trees {
    template<typename TYPE>
    class BinaryTree {
        public:
            ~BinaryTree();
            Node<TYPE>* GetRoot() const {
                return m_root;
            }
            void InsertNode(TYPE newValueOfNode);
            Node<TYPE>* FindNode(TYPE newValueOfNode);
            void DeleteNode(TYPE newValueOfNode);
            void PrintTree();

        private:
            Node<TYPE> *m_root = nullptr;
    };

    template <typename TYPE>
    BinaryTree<TYPE>::~BinaryTree() {
        delete m_root;
    }

    template <typename TYPE>
    void BinaryTree<TYPE>::InsertNode(TYPE newValueOfNode) {
        Node<TYPE> *currentNode = m_root;

        if (!m_root) {
            m_root = new Node<TYPE>();
            m_root->data = newValueOfNode;
            return;
        }

        while (currentNode) {
            if (newValueOfNode > currentNode->data) {
                if (!currentNode->right) {
                    currentNode->right = new Node<TYPE>();
                    currentNode->right->data = newValueOfNode;
                    break;
                }
                else {
                    currentNode = currentNode->right;
                }
            }
            else {
                if (!currentNode->left) {
                    currentNode->left = new Node<TYPE>();
                    currentNode->left->data = newValueOfNode;
                    break;
                }
                else {
                    currentNode = currentNode->left;
                }
            }
        }
    }

    template <typename TYPE>
    Node<TYPE>* BinaryTree<TYPE>::FindNode(TYPE newValueOfNode) {
        Node<TYPE> *currentNode = m_root;

        if (!currentNode) {
            std::cout<< "There are no vertices in the tree to be found." <<std::endl;
        }

        while (currentNode) {
            if (newValueOfNode == currentNode->data) {
                return currentNode;
            }
            else if (newValueOfNode > currentNode->data) {
                currentNode = currentNode->right;
            }
            else {
                currentNode = currentNode->left;
            }
        }
        if (!currentNode) {
            std::cout << "There is no vertex with the value " << newValueOfNode << " in the tree." << std::endl;
        }
        return nullptr;
    }

    template <typename TYPE>
    void BinaryTree<TYPE>::DeleteNode(TYPE newValueOfNode) {
        Node<TYPE> *currentNode = m_root;
        Node<TYPE> *parentNode = nullptr;

        if (!currentNode) {
            std::cout<< "There are no vertices in the tree to be deleted." <<std::endl;
        }

        while (currentNode->data != newValueOfNode) {
            parentNode = currentNode;

            if (newValueOfNode > currentNode->data) {
                currentNode = currentNode->right;
            }
            else if (newValueOfNode < currentNode->data) {
                currentNode = currentNode->left;
            }
        }

        if (newValueOfNode != currentNode->data) {
            std::cout << "There is no vertex with the value " << newValueOfNode << " in the tree." << std::endl;
            return;
        }

        if (!currentNode->right && !currentNode->left) {
            if (parentNode && newValueOfNode == parentNode->left->data) {
                parentNode->left = nullptr;
            }
            else {
                parentNode->right = nullptr;
            }
        }
        else if (!currentNode->right && currentNode->left) {
            if (currentNode->left->data > parentNode->data) {
                parentNode->right = currentNode->left;
            }
            else {
                parentNode->left = currentNode->left;
            }
            currentNode->left = nullptr;
        }
        else if (currentNode->right && !currentNode->left) {
            if (currentNode->right->data > parentNode->data) {
                parentNode->right = currentNode->right;
            }
            else {
                parentNode->left = currentNode->right;
            }
            currentNode->right = nullptr;
        }
        else {
            Node<TYPE> *minNode = currentNode->right;
            Node<TYPE> *pNode = currentNode;

            while (minNode->left) {
                pNode = minNode;
                minNode = minNode->left;
            }

            if (minNode->right) {
                pNode->left = minNode->right;
            }

            minNode->left = currentNode->left;
            currentNode->left = nullptr;

            minNode->right = currentNode->right;
            currentNode->right = nullptr;

            if (minNode->data > parentNode->data) {
                parentNode->right = minNode;
            }
            else {
                parentNode->left = minNode;
            }
        }

        delete currentNode;
    }
}


#endif

