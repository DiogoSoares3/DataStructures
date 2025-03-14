#pragma once
#include <iostream>

template<typename T>
class AVLTree {
private:
    // AVL Tree Node structure
    struct Node {
        T data;         // Value stored in the node
        Node* left;     // Pointer to the left subtree
        Node* right;    // Pointer to the right subtree
        int height;     // Height of the node (needed for balancing)

        // Constructor: Initializes the node with the given value and height 1 (leaf node)
        Node(const T& value);
    };

    Node* root; // Pointer to the root of the AVL tree

public:
    // Constructor: Initializes an empty AVL tree
    AVLTree();

    // Destructor: Releases all nodes in the tree
    ~AVLTree();

    // Returns the height of a node (0 if the node is nullptr)
    int height(Node* node) const;

    // Computes the balance factor of a node (height of the left subtree - height of the right subtree)
    int getBalance(Node* node) const;

    // Performs a right rotation on the subtree rooted at 'y' and returns the new root
    Node* rightRotate(Node* y);

    // Performs a left rotation on the subtree rooted at 'x' and returns the new root
    Node* leftRotate(Node* x);

    // Recursive function to insert a value into the subtree rooted at 'node' and returns the new root of that subtree
    Node* insert(Node* node, const T& value);

    // Recursive function to remove a value from the subtree rooted at 'node' and returns the new root of that subtree
    Node* remove(Node* node, const T& value);

    // Searches for a value in the tree. Returns true if found, false otherwise.
    bool search(const T& value) const;

    // Finds the node with the minimum value in the subtree rooted at 'node'
    Node* minValueNode(Node* node) const;

    // Clears the subtree rooted at 'node' (used by the destructor)
    void clear(Node* node);

    // Prints the values of the subtree in order (used for debugging)
    void printInOrder(Node* node) const;
};