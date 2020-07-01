#ifndef TREE_H
#define TREE_H

template <typename TYPE>
class Node {
public:
    virtual ~Node() {
        delete left;
        delete right;
    }
public:
    TYPE data;

    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
};


#endif // TREE_H
