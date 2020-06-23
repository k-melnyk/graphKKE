#ifndef RED_BLACK_T_H
#define RED_BLACK_T_H

#include "node.h"

namespace Trees {
    enum class NodeColor:char{red, black};

    template <typename TYPE>
    class NodeRB : public Node<TYPE> {
    public:
        ~NodeRB() {
            delete parent;
        }
    public:
        NodeColor color = NodeColor::black;
        NodeRB *parent = nullptr;
    };

    template <typename TYPE>
    class RedBlackTree {
    public:
        ~RedBlackTree();
        void InsertNode(TYPE newValueOfNode);
        NodeRB<TYPE>* GetRoot() const {
            return root;
        }
    private:
        void RotateRightRight(NodeRB<TYPE> *currentNode);
        void RotateLeftLeft(NodeRB<TYPE> *currentNode);
        void RotateLeft(NodeRB<TYPE> *currentNode);
        void RotateRight(NodeRB<TYPE> *currentNode);

        NodeRB<TYPE> *root = nullptr;
    };

    template <typename TYPE>
    RedBlackTree<TYPE>::~RedBlackTree() {
        delete root;
    }

    template <typename TYPE>
    void RedBlackTree<TYPE>::RotateLeftLeft(NodeRB<TYPE> *currentNode) {
        if (!currentNode) {
            return;
        }

        NodeRB<TYPE> *rightCurrentChild = currentNode->parent->right;
        NodeRB<TYPE> *currentParent = currentNode->parent;
        NodeRB<TYPE> *currentGrandParent = currentNode->parent->parent;
        NodeColor tmpColor = NodeColor::red;

        currentParent->right = currentGrandParent;
        currentGrandParent->left = rightCurrentChild;

        if (currentGrandParent->parent) {
            currentParent->parent = currentGrandParent->parent;
        }
        else {
            root = currentParent;
            currentParent->parent = nullptr;
        }
        currentGrandParent->parent = currentNode->parent;

        if (currentGrandParent->left) {
            currentGrandParent->left->parent = currentGrandParent;
        }

        tmpColor = currentParent->color;
        currentParent->color = currentGrandParent->color;
        currentGrandParent->color = tmpColor;
    }

    template <typename TYPE>
    void RedBlackTree<TYPE>::RotateRightRight(NodeRB<TYPE> *currentNode) {
        if (!currentNode) {
            return;
        }
        NodeRB<TYPE> *leftCurrentChild = currentNode->parent->left;
        NodeRB<TYPE> *currentParent = currentNode->parent;
        NodeRB<TYPE> *currentGrandParent = currentNode->parent->parent;
        NodeColor tmpColor = NodeColor::black;

        currentParent->left = currentGrandParent;
        currentGrandParent->right = leftCurrentChild;

        if (currentGrandParent->parent) {
            currentParent->parent = currentGrandParent->parent;
        }
        else {
            root = currentParent;
            currentParent->parent = nullptr;
        }
        currentGrandParent->parent = currentNode->parent;

        if (currentGrandParent->right) {
            currentGrandParent->right->parent = currentGrandParent;
        }

        tmpColor = currentParent->color;
        currentParent->color = currentGrandParent->color;
        currentGrandParent->color = tmpColor;
    }

    template <typename TYPE>
    void RedBlackTree<TYPE>::RotateLeft(NodeRB<TYPE> *currentNode) {
        if (!currentNode) {
            return;
        }
        NodeRB<TYPE> *currentParent = currentNode->parent;
        NodeRB<TYPE> *currentGrandParent = currentNode->parent->parent;
        NodeRB<TYPE> *leftCurrentChild = currentNode->left;

        currentNode->left = currentParent;
        currentParent->right = leftCurrentChild;

        currentNode->parent = currentGrandParent;
        currentParent->parent = currentNode;
        leftCurrentChild->parent = currentParent;
        if (currentParent->left) {
            currentParent->left->parent->parent = currentNode;
        }
    }

    template <typename TYPE>
    void RedBlackTree<TYPE>::RotateRight(NodeRB<TYPE> *currentNode) {
        if (!currentNode) {
            return;
        }
        NodeRB<TYPE> *currentParent = currentNode->parent;
        NodeRB<TYPE> *currentGrandParent = currentNode->parent->parent;
        NodeRB<TYPE> *rightCurrentChild = currentNode->right;

        currentNode->right = currentParent;
        currentParent->left = rightCurrentChild;

        currentNode->parent = currentGrandParent;
        currentParent->parent = currentNode;
        rightCurrentChild->parent = currentParent;
        if (currentParent->right) {
            currentParent->right->parent->parent = currentNode;
        }
    }

    template <typename TYPE>
    void RedBlackTree<TYPE>::InsertNode(TYPE newValueOfNode) {
        NodeRB<TYPE> *currentNode = root;
        NodeRB<TYPE> *parent_node = currentNode;

        if (!root) {
            root = new NodeRB<TYPE>();
            root->parent = nullptr;
            root->data = newValueOfNode;
            root->color = NodeColor::black;
        }

        while (currentNode) {
            if (newValueOfNode > currentNode->data) {
                if (!currentNode->right) {
                    currentNode->right = new NodeRB<TYPE>();
                    currentNode->right->parent = parent_node;
                    currentNode->right->data = newValueOfNode;
                    currentNode->right->color = NodeColor::red;
                    currentNode = currentNode->right;
                    break;
                }
                else {
                    parent_node = currentNode->right;
                    currentNode = currentNode->right;
                }
            }
            else {
                if (!currentNode->left) {
                    currentNode->left = new NodeRB<TYPE>();
                    currentNode->left->parent = parent_node;
                    currentNode->left->data = newValueOfNode;
                    currentNode->left->color = NodeColor::red;
                    currentNode = currentNode->left;
                    break;
                }
                else {
                    parent_node = currentNode->left;
                    currentNode = currentNode->left;
                }
            }
        }

        if (currentNode) {
            NodeRB<TYPE> *uncleNode = nullptr;

            while (currentNode != root && currentNode->parent->color != NodeColor::black) {
                if (currentNode->parent->parent->left == currentNode->parent) {
                    uncleNode = currentNode->parent->parent->right;
                }
                else {
                    uncleNode = currentNode->parent->parent->left;
                }

                if (uncleNode && uncleNode->color == NodeColor::red) {
                    currentNode->parent->color = NodeColor::black;
                    uncleNode->color = NodeColor::black;
                    currentNode->parent->parent->color = NodeColor::red;

                    if (currentNode->parent->parent == root) {
                        currentNode = root;
                        currentNode->color = NodeColor::black;
                    }
                    else {
                        currentNode = currentNode->parent->parent;
                    }
                }
                else {
                    if (currentNode->parent->data <= currentNode->parent->parent->data) {
                        if (currentNode->data > currentNode->parent->data) {
                            RotateLeft(currentNode);
                        }
                        RotateLeftLeft(currentNode);
                    }
                    else {
                        if (currentNode->data <= currentNode->parent->data) {
                            RotateRight(currentNode);
                        }
                        RotateRightRight(currentNode);
                    }

                    if (currentNode->parent->data < currentNode->parent->parent->data && currentNode->data < currentNode->parent->data) {
                        RotateLeftLeft(currentNode);
                    }
                    else if (currentNode->parent->data < currentNode->parent->parent->data && currentNode->data > currentNode->parent->data) {
                        RotateLeft(currentNode);
                        RotateLeftLeft(currentNode);
                    }
                    else if (currentNode->parent->data > currentNode->parent->parent->data && currentNode->data > currentNode->parent->data) {
                       RotateRightRight(currentNode);
                    }
                    else {
                        RotateRight(currentNode);
                        RotateRightRight(currentNode);
                    }
                }

                if (currentNode == root) {
                    break;
                }
            }
        }
    }
}


#endif // RED_BLACK_T_H
