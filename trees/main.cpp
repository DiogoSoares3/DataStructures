#include <iostream>
#include "AVLTree.h"


int main() {
    AVLTree<int> avl;

    // Test 1: Insertion
    std::cout << "Inserting elements: ";
    int elementsToInsert[] = {30, 20, 40, 10, 25, 35, 50, 5, 15, 27, 45, 55};
    for (int elem : elementsToInsert) {
        std::cout << elem << " ";
        avl.insert(elem);
    }
    std::cout << std::endl;

    // Display the AVL tree in-order after insertions
    std::cout << "In-order traversal after insertions: ";
    avl.printInOrder(avl.getRoot());
    std::cout << std::endl;

    // Test 2: Deletion
    std::cout << "Deleting elements: ";
    int elementsToDelete[] = {10, 20, 30};
    for (int elem : elementsToDelete) {
        std::cout << elem << " ";
        avl.remove(elem);
    }
    std::cout << std::endl;

    // Display the AVL tree in-order after deletions
    std::cout << "In-order traversal after deletions: ";
    avl.printInOrder(avl.getRoot());
    std::cout << std::endl;

    // Test 3: Edge Cases
    std::cout << "Testing edge cases..." << std::endl;

    // Attempt to insert duplicate elements
    std::cout << "Inserting duplicate element 25: ";
    avl.insert(25);
    avl.printInOrder(avl.getRoot());
    std::cout << std::endl;

    // Attempt to delete a non-existent element
    std::cout << "Deleting non-existent element 100: ";
    avl.remove(100);
    avl.printInOrder(avl.getRoot());
    std::cout << std::endl;

    // Test 4: Tree Balance Verification
    std::cout << "Verifying tree balance after operations..." << std::endl;
    // Implement a function to verify the balance of the tree if not already present
    std::cout << "Tree is balanced: " << std::boolalpha << avl.isBalanced(avl.getRoot()) << std::endl;

    // Test 5: Clear the Tree
    std::cout << "Clearing the entire tree." << std::endl;
    avl.clear(avl.getRoot());
    std::cout << "In-order traversal after clearing: ";
    avl.printInOrder(avl.getRoot());
    std::cout << std::endl;

    return 0;
}
