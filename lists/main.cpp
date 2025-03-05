#include <iostream>
#include "circularDoublyLinkedList.h"
#include "singlyLinkedList.h"

void testCircularDoublyLinkedList() {
    CircularDoublyLinkedList cdll;
    
    // Initial state: should be empty
    std::cout << "Initial list (should be empty):" << std::endl;
    cdll.print();
    std::cout << "Size: " << cdll.getSize() << "\n" << std::endl;
    
    // Test push_front: add elements to the beginning
    std::cout << "Testing push_front:" << std::endl;
    cdll.push_front(10);     // List: 10
    cdll.print();
    cdll.push_front(20);     // List: 20 -> 10
    cdll.print();
    cdll.push_front(30);     // List: 30 -> 20 -> 10
    cdll.print();
    std::cout << "Size after push_front: " << cdll.getSize() << "\n" << std::endl;
    
    // Test push_back: add elements to the end
    std::cout << "Testing push_back:" << std::endl;
    cdll.push_back(40);      // List: 30 -> 20 -> 10 -> 40
    cdll.print();
    cdll.push_back(50);      // List: 30 -> 20 -> 10 -> 40 -> 50
    cdll.print();
    std::cout << "Size after push_back: " << cdll.getSize() << "\n" << std::endl;
    
    // Test insert: insert elements at specific indices
    std::cout << "Testing insert:" << std::endl;
    // Insert at the beginning (index 0)
    cdll.insert(0, 5);       // List: 5 -> 30 -> 20 -> 10 -> 40 -> 50
    std::cout << "After inserting 5 at index 0:" << std::endl;
    cdll.print();
    
    // Insert in the middle (e.g., index 3)
    cdll.insert(3, 25);      // Expected List: 5 -> 30 -> 20 -> 25 -> 10 -> 40 -> 50
    std::cout << "After inserting 25 at index 3:" << std::endl;
    cdll.print();
    
    // Insert at the end (index equals size)
    cdll.insert(cdll.getSize(), 60);  // Expected to append 60 at the end
    std::cout << "After inserting 60 at the end:" << std::endl;
    cdll.print();
    std::cout << "Size after insert operations: " << cdll.getSize() << "\n" << std::endl;
    
    // Test pop_front: remove the first element
    std::cout << "Testing pop_front:" << std::endl;
    cdll.pop_front();        // Removes element at the beginning
    cdll.print();
    std::cout << "Size after pop_front: " << cdll.getSize() << "\n" << std::endl;
    
    // Test pop_back: remove the last element
    std::cout << "Testing pop_back:" << std::endl;
    cdll.pop_back();         // Removes element at the end
    cdll.print();
    std::cout << "Size after pop_back: " << cdll.getSize() << "\n" << std::endl;
    
    // Test remove: remove elements at specific indices
    std::cout << "Testing remove:" << std::endl;
    // Remove element at index 2
    cdll.remove(2);          // Remove the element at index 2
    std::cout << "After removing element at index 2:" << std::endl;
    cdll.print();
    std::cout << "Size after removal: " << cdll.getSize() << "\n" << std::endl;
    
    // Remove element at index 0 (head)
    cdll.remove(0);          // Remove the head element
    std::cout << "After removing element at index 0:" << std::endl;
    cdll.print();
    std::cout << "Size after removal: " << cdll.getSize() << "\n" << std::endl;
    
    // Remove element at last index
    cdll.remove(cdll.getSize() - 1);  // Remove the last element
    std::cout << "After removing the last element:" << std::endl;
    cdll.print();
    std::cout << "Size after removal: " << cdll.getSize() << "\n" << std::endl;
    
    // Test front() and back() to access first and last elements
    std::cout << "Testing front() and back():" << std::endl;
    std::cout << "Front element: " << cdll.front() << std::endl;
    std::cout << "Back element: " << cdll.back() << "\n" << std::endl;
    
    // Test clear: remove all elements from the list
    std::cout << "Testing clear():" << std::endl;
    cdll.clear();
    cdll.print();   // Should print an empty list
    std::cout << "Size after clear: " << cdll.getSize() << std::endl;
    std::cout << "List is empty? " << (cdll.isEmpty() ? "Yes" : "No") << std::endl;
}

void testSinglyLinkedList() {
    SinglyLinkedList list;

    std::cout << "Initial list (should be empty): ";
    list.print();

    list.push_front(10);
    list.print();  // Expected: 10
    list.pop_back();

    // Test push_front
    std::cout << "\nTesting push_front:" << std::endl;
    list.push_front(10);
    list.print();  // Expected: 10
    list.push_front(20);
    list.print();  // Expected: 20 -> 10
    list.push_front(30);
    list.print();  // ExpWected: 30 -> 20 -> 10

    // Test push_back
    std::cout << "\nTesting push_back:" << std::endl;
    list.push_back(40);
    list.print();  // Expected: 30 -> 20 -> 10 -> 40
    list.push_back(50);
    list.print();  // Expected: 30 -> 20 -> 10 -> 40 -> 50

    // Test insert (inserting 25 at index 3)
    std::cout << "\nTesting insert (insert 25 at index 3):" << std::endl;
    list.insert(3, 25);
    list.print();  // Expected: 30 -> 20 -> 10 -> 25 -> 40 -> 50

    // Test remove (removing element at index 1)
    std::cout << "\nTesting remove (remove element at index 1):" << std::endl;
    list.remove(1);
    list.print();  // Expected: 30 -> 10 -> 25 -> 40 -> 50

    // Test pop_front
    std::cout << "\nTesting pop_front:" << std::endl;
    list.pop_front();
    list.print();  // Expected: 10 -> 25 -> 40 -> 50

    // Test pop_back
    std::cout << "\nTesting pop_back:" << std::endl;
    list.pop_back();
    list.print();  // Expected: 10 -> 25 -> 40

    // Test clear
    std::cout << "\nTesting clear:" << std::endl;
    list.clear();
    list.print();  // Expected: (empty output)
}

int main() {
    std::cout << "----------Testing Singly Linked List--------------\n" << std::endl;
    testSinglyLinkedList();
    std::cout << "\n++++++++++++++++++++++++++++++++++\n" << std::endl;
    std::cout << "----------Testing Circular Doubly Linked List--------------\n" << std::endl;
    testCircularDoublyLinkedList();
    return 0;
}