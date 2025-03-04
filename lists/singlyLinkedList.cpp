#include <iostream>
#include <cstddef>    // For size_t
#include <stdexcept>  // For exceptions
#include "singlyLinkedList.h"


// Constructor for Node: initializes the node's data with the given value and next pointer to nullptr
Node::Node(int value) : data(value), next(nullptr) { }

// Constructor for SinglyLinkedList: initializes head and tail to nullptr and size to 0
SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) { }

// Destructor: Releases all allocated nodes in the list
SinglyLinkedList::~SinglyLinkedList() {
    Node* current = head;                // Start with the head node
    while (current != nullptr) {         // Loop until we reach the end of the list
        Node* nextNode = current->next;  // Save the pointer to the next node
        delete current;                  // Delete the current node, freeing its memory
        current = nextNode;              // Move to the next node in the list
    }
    head = nullptr;  // Set head to nullptr to indicate the list is now empty
    tail = nullptr;  // Set tail to nullptr as well
    size = 0;        // Reset size to 0
}

// push_front: Inserts an element at the beginning of the list
void SinglyLinkedList::push_front(int value) {
    Node* node = new Node(value);   // Dynamically allocate a new Node with the given value

    if (this->size > 0) {           // If the list already has elements
        node->next = this->head;    // Set the new node's next pointer to the current head
    } else {                        // If the list is empty
        this->tail = node;          // Set tail to the new node as it's the only element
    }

    this->head = node;              // Update head to point to the new node
    this->size++;
};

// push_back: Inserts an element at the end of the list
void SinglyLinkedList::push_back(int value) {
    Node* node = new Node(value);   // Dynamically allocate a new Node with the given value

    if (this->size > 0) {           // If the list is not empty
        this->tail->next = node;    // Link the current tail's next pointer to the new node
    } else {                        // If the list is empty
        this->head = node;          // Set head to the new node
    }

    this->tail = node;              // Update tail to point to the new node
    this->size++;
};

// insert: Inserts an element at the specified index (0-indexed)
// Throws an exception if the index is out of bounds.
void SinglyLinkedList::insert(size_t index, int value) {
    if (index > this->size | index < 0) {  // Check if index is greater than size or negative
        throw std::out_of_range("Index is out of bounds");  // Throw exception if index is invalid
    }

    Node* previousNode = nullptr;   // Pointer to keep track of the node before the insertion point
    Node* nextNode = this->head;    // Pointer to keep track of the node at the insertion point

    size_t i = 0;
    while (i < index) {                 // Traverse the list until reaching the specified index
        if (i == 0) {                   // Special handling for the first iteration
            previousNode = this->head;  // Set previousNode to head
            nextNode = nextNode->next;  // Move nextNode to the next element
        } else {
            previousNode = previousNode->next; // Advance previousNode one step
            nextNode = nextNode->next;         // Advance nextNode one step
        }
        i++;
    }

    Node* node = new Node(value);   // Dynamically allocate a new Node with the given value
    node->next = nextNode;          // Set new node's next pointer to the current node at the insertion point
    previousNode->next = node;      // Link previous node to the new node

    // Setting a new tail if the inserted element is the last one
    if (index == this->size) {
        this->tail = node;          // Update tail to the new node if inserting at the end
    }

    // Setting a new head if the inserted element is the first one
    if (index == 0) {
        this->head = node;          // Update head to the new node if inserting at the beginning
    }

    this->size++;
};

// pop_front: Removes the element at the beginning of the list
// Throws an exception if the list is empty.
void SinglyLinkedList::pop_front() {
    if (this->isEmpty()) {
        throw std::out_of_range("List is empty");
    }

    Node* tempNode = this->head;             // Store the current head in a temporary pointer
    this->head = this->head->next;           // Update head to point to the next node

    if (this->size == 1) {                   // If there was only one node in the list
        this->tail = nullptr;                // Set tail to nullptr since the list is now empty
    }

    this->size--;                          // Decrement the size of the list
    delete tempNode;                       // Delete the old head node to free memory
};

// pop_back: Removes the element at the end of the list
// Throws an exception if the list is empty.
void SinglyLinkedList::pop_back() {
    if (this->isEmpty()) {
        throw std::out_of_range("List is empty");
    }

    if (!this->head->next) {                 // If there is only one Node (head's next is nullptr)
        delete this->head;                   // Delete the only node in the list
        this->head = this->tail = nullptr;   // Set both head and tail to nullptr
        this->size--;                        // Decrement the size of the list
        return;                              // Exit the function
    }

    Node* currentNode = this->head;

    while (currentNode->next != this->tail) { // Traverse until currentNode->next is the tail
        currentNode = currentNode->next;     // Move to the next node
    }

    delete this->tail;                       // Delete the current tail node
    this->tail = currentNode;                // Update tail to be the current node (new last node)
    this->tail->next = nullptr;              // Set the new tail's next pointer to nullptr
    this->size--;
};

// remove: Removes the element at the specified index (0-indexed)
// Throws an exception if the index is invalid.
void SinglyLinkedList::remove(size_t index) {
    if (index >= this->size) {    // Check if index is out of bounds (greater than or equal to size, or negative)
        throw std::out_of_range("Index is out of bounds");
    }

    Node* previousNode = nullptr;            // Pointer to keep track of the node before the one to remove
    Node* currentNode = this->head;            // Pointer to traverse the list and locate the node to remove

    size_t i = 0;
    while (i < index) {                      // Traverse until reaching the specified index
        if (i == 0) {                      // For the first iteration, set previousNode and update currentNode
            previousNode = this->head;     // previousNode is set to head
            currentNode = currentNode->next;  // Move currentNode to the next node
        } else {
            previousNode = previousNode->next;  // Advance previousNode one node
            currentNode = currentNode->next;    // Advance currentNode one node
        }
        i++;
    }

    if (!(index == 0 & this->size == 1)) {    // If the list does not have only one node at index 0
        previousNode->next = currentNode->next; // Link the previous node to the node after currentNode
    }
    delete currentNode;

    // Setting a new tail if the excluded element is the last one
    if (index == this->size-1) {             // If the removed node was the last element
        this->tail = previousNode;           // Update tail to the previous node
    }

    // Setting a new head if the excluded element is the first one
    if (index == 0) {                        // If the removed node was the first element
        this->head = previousNode;           // Update head to the new first node (which could be nullptr if list becomes empty)
    }

    this->size--;
};


// front: Returns a reference to the first element
// Throws an exception if the list is empty.
int& SinglyLinkedList::front() {
    if (this->isEmpty()) {
        throw std::out_of_range("List is empty");
    }

    return this->head->data;
};

// back: Returns a reference to the last element
// Throws an exception if the list is empty.
int& SinglyLinkedList::back() {
    if (this->isEmpty()) {
        throw std::out_of_range("List is empty");
    }

    return this->tail->data;
};

// getSize: Returns the current number of elements in the list
size_t SinglyLinkedList::getSize() const {
    return this->size;
};

// isEmpty: Checks if the list is empty
bool SinglyLinkedList::isEmpty() const {
    return !this->size;
};

// clear: Removes all elements from the list and frees memory
void SinglyLinkedList::clear() {
    this->~SinglyLinkedList();
};

// print: Traverses the list and prints each element
void SinglyLinkedList::print() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr)
            std::cout << " -> ";
        current = current->next;
    }
    std::cout << "\n";
}

// int main() {
//     SinglyLinkedList list;

//     std::cout << "Initial list (should be empty): ";
//     list.print();

//     list.push_front(10);
//     list.print();  // Expected: 10
//     list.pop_back();

//     // Test push_front
//     std::cout << "\nTesting push_front:" << std::endl;
//     list.push_front(10);
//     list.print();  // Expected: 10
//     list.push_front(20);
//     list.print();  // Expected: 20 -> 10
//     list.push_front(30);
//     list.print();  // ExpWected: 30 -> 20 -> 10

//     // Test push_back
//     std::cout << "\nTesting push_back:" << std::endl;
//     list.push_back(40);
//     list.print();  // Expected: 30 -> 20 -> 10 -> 40
//     list.push_back(50);
//     list.print();  // Expected: 30 -> 20 -> 10 -> 40 -> 50

//     // Test insert (inserting 25 at index 3)
//     std::cout << "\nTesting insert (insert 25 at index 3):" << std::endl;
//     list.insert(3, 25);
//     list.print();  // Expected: 30 -> 20 -> 10 -> 25 -> 40 -> 50

//     // Test remove (removing element at index 1)
//     std::cout << "\nTesting remove (remove element at index 1):" << std::endl;
//     list.remove(1);
//     list.print();  // Expected: 30 -> 10 -> 25 -> 40 -> 50

//     // Test pop_front
//     std::cout << "\nTesting pop_front:" << std::endl;
//     list.pop_front();
//     list.print();  // Expected: 10 -> 25 -> 40 -> 50

//     // Test pop_back
//     std::cout << "\nTesting pop_back:" << std::endl;
//     list.pop_back();
//     list.print();  // Expected: 10 -> 25 -> 40

//     // Test clear
//     std::cout << "\nTesting clear:" << std::endl;
//     list.clear();
//     list.print();  // Expected: (empty output)

//     return 0;
// }