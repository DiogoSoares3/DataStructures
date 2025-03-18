#include <iostream>
#include "AVLTree.h"


template class AVLTree<int>;

// Constructor: Initializes the node with the given value and height 1 (leaf node)
template<typename T>
AVLTree<T>::Node::Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) { } 

// Performs a right rotation on the subtree rooted at 'y' and returns the new root
template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::rightRotate(Node* y) {
    Node* newRightNode = y;
    y = y->left;
    newRightNode->left = y->right;
    y->right = newRightNode;

    newRightNode->height = 1 + std::max(
        this->height(newRightNode->left), 
        this->height(newRightNode->right)
    );
    y->height = 1 + std::max(
        this->height(y->left), 
        this->height(y->right)
    );

    return y;
}

// Performs a left rotation on the subtree rooted at 'x' and returns the new root
template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::leftRotate(Node* x) {
    Node* newLeftNode = x;
    x = x->right;
    newLeftNode->right = x->left;
    x->left = newLeftNode;

    newLeftNode->height = 1 + std::max(
        this->height(newLeftNode->left), 
        this->height(newLeftNode->right)
    );
    x->height = 1 + std::max(
        this->height(x->left), 
        this->height(x->right)
    );

    return x;
}

// Recursive function to insert a value into the subtree rooted at 'node' and returns the new root of that subtree
template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::recInsert(Node* node, const T& value) {
    if (!node) {
        return new Node(value);
    }

    if (value > node->data) {
        node->right = this->recInsert(node->right, value);
    } else if (value < node->data) {
        node->left = this->recInsert(node->left, value);
    } else {
        return node;  // Duplicates not allowed
    }

    // Update height of the node.
    node->height = 1 + std::max(
        this->height(node->left), 
        this->height(node->right)
    );

    int balance = this->getBalance(node);

    // Left Left Case
    if (balance > 1 && value < node->left->data)
        return rightRotate(node);
    
    // Right Right Case
    if (balance < -1 && value > node->right->data)
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;  // Return the final updated root
}

// Recursive function to remove a value from the subtree rooted at 'node' and returns the new root of that subtree
template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::recRemove(Node* node, const T& value) {
    if (!node) return nullptr; // Base case: If node not found, return null

    if (value > node->data) {
        node->right = this->recRemove(node->right, value);
    } else if (value < node->data) {
        node->left = this->recRemove(node->left, value);
    } else {  // If the value is what we are looking for
        // Node with one or no child
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp; // Return non-null child (if exists) or nullptr (if the node doesn't have childs)
        }

        // Node with two children: Find inorder successor (the smaller number at the right subtree)
        Node* temp = this->minValueNode(node->right);
        node->data = temp->data; // Replaces the data of the node to be "deleted" with the value of the inorder successor
        node->right = this->recRemove(node->right, temp->data); // Delete inorder successor
    }

    node->height = 1 + std::max(
        this->height(node->left), 
        this->height(node->right)
    );

    // If the tree have only one node after the deletion, return the unique node
    if (!node) return node;

    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // LR Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RR Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // RL Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Return the final updated root
}

// Finds the node with the minimum value in the subtree rooted at 'node'
template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::minValueNode(Node* node) const {
    Node* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

// Constructor: Initializes an empty AVL tree
template<typename T>
AVLTree<T>::AVLTree() : root(nullptr) { }

// Destructor: Releases all nodes in the tree
template<typename T>
AVLTree<T>::~AVLTree() {
    this->clear(this->root);
}

// Returns the height of a node (0 if the node is nullptr)
template<typename T>
int AVLTree<T>::height(Node* node) const {
    return (node == nullptr) ? 0 : node->height;
}

// Computes the balance factor of a node (height of the left subtree - height of the right subtree)
// This function only works if the Tree is balanced
template<typename T>
int AVLTree<T>::getBalance(Node* node) const {
    if (!node) return 0;
    return this->height(node->left) - this->height(node->right);
}

// Inserts a value into the AVL tree
template<typename T>
void AVLTree<T>::insert(const T& value) {
    this->root = this->recInsert(this->root, value);
    return;
}

// Removes a value from the AVL tree
template<typename T>
void AVLTree<T>::remove(const T& value) {
    this->root = this->recRemove(this->root, value);
    return;
}

// Clears the subtree rooted at 'node'
template<typename T>
void AVLTree<T>::clear(Node* node) {
    if (node == nullptr) return; // Base case: If node is null, return

    this->clear(node->left);   // Recursively delete the left subtree
    this->clear(node->right);  // Recursively delete the right subtree

    delete node; // Free the current node
    this->root = nullptr;
}

// Prints the values of the subtree in order (left-root-right)
template<typename T>
void AVLTree<T>::printInOrder(Node* node) const {
    if (!node) return;
    
    printInOrder(node->left);  // Visit left subtree
    std::cout << node->data << " ";  // Print current node
    printInOrder(node->right); // Visit right subtree
}

// Return the root node of the AVL Tree instance
template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::getRoot() const {
    return this->root;
}

// Return 0 if the tree is not balanced, return 1 if it is
template<typename T>
bool AVLTree<T>::isBalanced(Node* node) {
    return (this->getBalance(node) <= 1 && this->getBalance(node) >= -1) ? true : false;
}
