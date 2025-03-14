#include <iostream>
#include "AVLTree.h"

// Constructor: Initializes the node with the given value and height 1 (leaf node)
template<typename T>
AVLTree<T>::Node::Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) { }

// Constructor: Initializes an empty AVL tree
template<typename T>
AVLTree<T>::AVLTree() {

};

// Destructor: Releases all nodes in the tree
template<typename T>
AVLTree<T>::~AVLTree() {

};

// Returns the height of a node (0 if the node is nullptr)
template<typename T>
int AVLTree<T>::height(Node* node) const {
    
};

// Computes the balance factor of a node (height of the left subtree - height of the right subtree)
template<typename T>
int AVLTree<T>::getBalance(Node* node) const {
    
};

// Performs a right rotation on the subtree rooted at 'y' and returns the new root
template<typename T>
AVLTree<T>::Node* AVLTree<T>::rightRotate(Node* y) {
    
};

// Performs a left rotation on the subtree rooted at 'x' and returns the new root
template<typename T>
AVLTree<T>::Node* AVLTree<T>::leftRotate(Node* x) {
    
};

// Recursive function to insert a value into the subtree rooted at 'node' and returns the new root of that subtree
template<typename T>
AVLTree<T>::Node* AVLTree<T>::insert(Node* node, const T& value) {
    
};

// Recursive function to remove a value from the subtree rooted at 'node' and returns the new root of that subtree
template<typename T>
AVLTree<T>::Node* AVLTree<T>::remove(Node* node, const T& value) {
    
};

// Finds the node with the minimum value in the subtree rooted at 'node'
template<typename T>
AVLTree<T>::Node* AVLTree<T>::minValueNode(Node* node) const {
    
};

// Clears the subtree rooted at 'node' (used by the destructor)
template<typename T>
void AVLTree<T>::clear(Node* node) {
    
};

// Prints the values of the subtree in order (used for debugging)
template<typename T>
void AVLTree<T>::printInOrder(Node* node) const {
    
};
