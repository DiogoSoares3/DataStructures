# AVL Tree Implementation in C++

This repository contains an implementation of an AVL tree in C++. An AVL tree is a self-balancing binary search tree (BST) that maintains its height to ensure efficient operations. It was named after its inventors, Adelson-Velsky and Landis, who introduced it in 1962.

## What is an AVL Tree?

An AVL tree is a type of binary search tree where the heights of the left and right subtrees of every node differ by at most one. This property, known as the AVL balance condition, ensures that the tree remains approximately balanced. When the balance condition is violated due to insertions or deletions, the tree performs rotations to restore balance.

### Key Properties

- **Binary Search Tree Property**: For each node, all elements in the left subtree are less than the node’s value, and all elements in the right subtree are greater.
- **Balance Factor**: The balance factor of a node is the height of its left subtree minus the height of its right subtree. In an AVL tree, this must always be -1, 0, or 1.

## Purpose of an AVL Tree

The primary purpose of an AVL tree is to provide efficient data storage and retrieval operations. By maintaining balance, AVL trees prevent the worst-case scenarios of a skewed binary search tree, ensuring that operations such as search, insertion, and deletion are performed in O(log n) time.

### Advantages

- **Efficient Operations**: Search, insertion, and deletion operations have a time complexity of O(log n) due to the balanced structure.
- **Self-Balancing**: The tree automatically adjusts itself after modifications to maintain balance, ensuring consistent performance.
- **Predictable Performance**: Unlike unbalanced BSTs, AVL trees guarantee logarithmic time complexity for key operations.

### Disadvantages

- **Complex Implementation**: The self-balancing mechanism requires additional logic for rotations and balance factor calculations, making it more complex than a basic BST.
- **Overhead**: Balancing operations introduce computational overhead, particularly in scenarios with frequent insertions and deletions.
- **Not Optimal for All Scenarios**: For static datasets with frequent searches, other data structures like hash tables may be more efficient.

## Real-World Applications

AVL trees are used in applications requiring efficient dynamic data management. Some examples include:

- **Database Indexing**: AVL trees index database records for fast search, insertion, and deletion.
- **Memory Management**: Operating systems use AVL trees to manage memory allocation and deallocation.
- **File Systems**: AVL trees help maintain directory structures and file metadata.
- **Language Processing**: Compilers and interpreters use AVL trees for symbol tables to look up variables and functions efficiently.
- **Network Routing**: AVL trees can manage routing tables to determine optimal data packet paths.

## Implementation Overview

The AVL tree is implemented as a template class `AVLTree<T>`, allowing it to store elements of any comparable data type `T`. The implementation includes:

- **Node Structure**: A private nested structure for tree nodes, containing the data, pointers to left and right children, and the node’s height.
- **Rotation Methods**: Private methods for left and right rotations to maintain balance.
- **Insertion and Deletion**: Public methods to insert and remove elements while preserving the AVL balance property.
- **Helper Methods**: Private and public methods to support operations like height calculation, balance factor computation, and tree traversal.

### Class Structure

Here is the class declaration for the implementation:

```cpp
template<typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        Node(const T& value);
    };
    Node* root;
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* recInsert(Node* node, const T& value);
    Node* recRemove(Node* node, const T& value);
    Node* minValueNode(Node* node) const;
public:
    AVLTree();
    ~AVLTree();
    int height(Node* node) const;
    int getBalance(Node* node) const;
    void insert(const T& value);
    void remove(const T& value);
    void clear(Node* node);
    void printInOrder(Node* node) const;
    Node* getRoot() const;
    bool isBalanced(Node* node);
};
```
## Method Explanations

Below is a detailed explanation of each method in the `AVLTree` implementation.

### Private Methods

#### `Node::Node(const T& value)`

- **Purpose**: Constructor for the `Node` structure.
- **Functionality**: Initializes a new node with the given `value`, sets `left` and `right` pointers to `nullptr`, and assigns a height of 1 (as a new node is a leaf).

#### `Node* rightRotate(Node* y)`

- **Purpose**: Performs a right rotation on the subtree rooted at `y`.
- **Functionality**: Balances the tree when the left subtree is taller. Reassigns pointers and updates heights of affected nodes, returning the new root (`y->left`).

#### `Node* leftRotate(Node* x)`

- **Purpose**: Performs a left rotation on the subtree rooted at `x`.
- **Functionality**: Balances the tree when the right subtree is taller. Reassigns pointers and updates heights, returning the new root (`x->right`).

#### `Node* recInsert(Node* node, const T& value)`

- **Purpose**: Recursively inserts a value into the subtree rooted at `node`.
- **Functionality**:
  - If `node` is `nullptr`, creates a new node with `value`.
  - Recursively inserts into the left or right subtree based on `value` comparison.
  - Updates the node’s height and checks the balance factor.
  - Performs rotations (LL, LR, RR, RL cases) if the balance factor exceeds ±1.
  - Returns the updated subtree root.

#### `Node* recRemove(Node* node, const T& value)`

- **Purpose**: Recursively removes a value from the subtree rooted at `node`.
- **Functionality**:
  - If `node` is `nullptr`, returns `nullptr`.
  - Recursively searches for `value` in the left or right subtree.
  - Upon finding the node:
    - No children or one child: Deletes the node and returns the child (or `nullptr`).
    - Two children: Replaces the node’s data with the inorder successor’s value, then deletes the successor.
  - Updates heights and performs rotations if needed (LL, LR, RR, RL cases).
  - Returns the updated subtree root.

#### `Node* minValueNode(Node* node) const`

- **Purpose**: Finds the node with the minimum value in the subtree rooted at `node`.
- **Functionality**: Traverses the leftmost path to locate the smallest value, used during deletion of nodes with two children.

### Public Methods

#### `AVLTree()`

- **Purpose**: Constructor for the `AVLTree` class.
- **Functionality**: Initializes an empty tree by setting `root` to `nullptr`.

#### `~AVLTree()`

- **Purpose**: Destructor for the `AVLTree` class.
- **Functionality**: Calls `clear(root)` to delete all nodes and free memory.

#### `int height(Node* node) const`

- **Purpose**: Returns the height of a given node.
- **Functionality**: If `node` is `nullptr`, returns 0; otherwise, returns the node’s `height`.

#### `int getBalance(Node* node) const`

- **Purpose**: Computes the balance factor of a node.
- **Functionality**: Returns the difference between the heights of the left and right subtrees (`height(left) - height(right)`).

#### `void insert(const T& value)`

- **Purpose**: Inserts a value into the AVL tree.
- **Functionality**: Calls `recInsert(root, value)` to perform the insertion and updates the `root` if necessary.

#### `void remove(const T& value)`

- **Purpose**: Removes a value from the AVL tree.
- **Functionality**: Calls `recRemove(root, value)` to perform the deletion and updates the `root` if necessary.

#### `void clear(Node* node)`

- **Purpose**: Recursively deletes all nodes in the subtree rooted at `node`.
- **Functionality**: Traverses the tree in post-order (left, right, root) to delete nodes and free memory.

#### `void printInOrder(Node* node) const`

- **Purpose**: Prints the values of the subtree rooted at `node` in order.
- **Functionality**: Performs an in-order traversal (left, root, right) to print node values, useful for debugging or displaying the tree’s contents.

#### `Node* getRoot() const`

- **Purpose**: Returns the root node of the tree.
- **Functionality**: Provides access to the root for external operations or inspections.

#### `bool isBalanced(Node* node)`

- **Purpose**: Checks if the subtree rooted at `node` is balanced.
- **Functionality**: Determines if the balance factor is within the AVL constraints (-1, 0, 1).

## Conclusion
This AVL tree implementation provides a robust and efficient way to manage dynamic datasets with guaranteed logarithmic time complexity for key operations. While it is more complex than a basic binary search tree, the self-balancing property ensures consistent performance, making it suitable for applications where data is frequently modified.

For further details on the implementation, refer to the source code and comments provided in the header and implementation files.