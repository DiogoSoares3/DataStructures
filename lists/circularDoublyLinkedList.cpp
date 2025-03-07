#include <cstddef>    // For size_t
#include <stdexcept>
#include <iostream>
#include "circularDoublyLinkedList.h"

// Constructor: initializes node data and sets pointers to nullptr
DNode::DNode(int value) : data(value), next(nullptr), prev(nullptr) { };

// Constructor: Initializes an empty circular doubly linked list
CircularDoublyLinkedList::CircularDoublyLinkedList() : head(nullptr), size(0) { };

// Destructor: Releases all allocated nodes
CircularDoublyLinkedList::~CircularDoublyLinkedList() {
    if (this->head != nullptr) {
        DNode* current = this->head;
        do {
            DNode* nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != this->head);
    }
    this->head = nullptr;
    this->size = 0;
};

// push_front: Inserts an element at the beginning of the circular doubly linked list
void CircularDoublyLinkedList::push_front(int value) {
    DNode* newNode = new DNode(value);

    if (this->size > 0) {                             // If the list is not empty
        this->head->prev->next = newNode;             // Set the current tail's next to point to the new node
        newNode->prev = this->head->prev;             // Set the new node's previous pointer to the current tail
        newNode->next = this->head;                   // Set the new node's next pointer to the current head
        this->head->prev = newNode;                   // Update the current head's previous pointer to the new node
        this->head = newNode;                         // Update head to be the new node (new beginning of the list)
    } else {                                          // If the list is empty
        this->head = newNode;                         // Set head to the new node
        this->head->prev = newNode;                   // In a single-node circular list, previous points to itself
        this->head->next = this->head->prev;          // Next also points to itself (circularity)
    }
    this->size++;
};

// push_back: Inserts an element at the end of the circular doubly linked list
void CircularDoublyLinkedList::push_back(int value) {
    DNode* newNode = new DNode(value);

    if (this->size > 0) {                             // If the list is not empty
        this->head->prev->next = newNode;             // Set the current tail's next pointer (head->prev is the tail) to the new node
        newNode->prev = this->head->prev;             // Set the new node's previous pointer to the current tail
        newNode->next = this->head;                   // Set the new node's next pointer to the head, maintaining circularity
        this->head->prev = newNode;                   // Update the head's previous pointer to the new node, making it the new tail
    } else {                                          // If the list is empty
        this->head = newNode;                         // Set head to the new node
        this->head->prev = newNode;                   // Previous pointer of the single node points to itself
        this->head->next = this->head->prev;          // Next pointer also points to itself, ensuring circularity
    }
    this->size++;
};

// insert: Inserts an element at the specified index (0-indexed)
// Throws an exception if the index is out of bounds.
void CircularDoublyLinkedList::insert(size_t index, int value) {
    DNode* newNode = new DNode(value);         // Create a new node with the given value

    if (this->size > 0) {                        // If the list is not empty
        DNode* previousNode = this->head->prev;  // Initialize previousNode as the current tail (head->prev)
        DNode* nextNode = this->head;            // Initialize nextNode as the current head

        size_t i = 0;                          // Start an index counter
        while (i < index) {                      // Traverse until reaching the insertion index
            previousNode = previousNode->next; // Move previousNode forward by one
            nextNode = nextNode->next;         // Move nextNode forward by one
            i++;                               // Increment the counter
        }

        previousNode->next = newNode;          // Link the previous node's next to the new node
        newNode->prev = previousNode;          // Set new node's previous pointer to previousNode
        newNode->next = nextNode;              // Link new node's next pointer to nextNode
        nextNode->prev = newNode;              // Update nextNode's previous pointer to the new node

        if (index == 0) {                      // If the element is inserted at the beginning
            this->head = newNode;              // Update the head pointer to the new node
        }
    } else {                                     // If the list is empty
        this->head = newNode;                    // Set head to the new node
        this->head->prev = newNode;              // The new node's previous pointer points to itself
        this->head->next = this->head->prev;       // The new node's next pointer also points to itself (circular link)
    }
    this->size++;                                // Increment the size of the list
};

// pop_front: Removes the element at the beginning of the list
// Throws an exception if the list is empty.
void CircularDoublyLinkedList::pop_front() {
    if (this->isEmpty()) {                                 // Check if the list is empty
        throw std::out_of_range("List is empty");         // Throw an exception if there are no nodes to remove
    }

    DNode* tempNode = this->head;                          // Save the current head node in a temporary pointer

    if (this->size > 1) {                                  // If the list has more than one element
        this->head->prev->next = this->head->next;         // Set the tail's next pointer (head->prev is the tail) to the second node
        this->head->next->prev = this->head->prev;         // Set the second node's previous pointer to the tail
        this->head = this->head->next;                     // Update head to the second node (new first node)
    } else {                                               // If there is only one element in the list
        this->head = nullptr;                              // Set head to nullptr (list becomes empty)
    }

    this->size--;                                        // Decrement the size of the list
    delete tempNode;                                     // Free the memory allocated for the old head node
};

// pop_back: Removes the element at the end of the list
// Throws an exception if the list is empty.
void CircularDoublyLinkedList::pop_back() {
    if (this->isEmpty()) {                                 // Check if the list is empty
        throw std::out_of_range("List is empty");         // Throw an exception if there are no nodes to remove
    }

    DNode* tempNode = this->head->prev;                    // Save the tail node (head->prev) in a temporary pointer

    if (this->size > 1) {                                  // If the list has more than one element
        tempNode->prev->next = tempNode->next;             // Update the node before the tail: its next pointer is set to head (since tail->next is head)
        tempNode->next->prev = tempNode->prev;             // Update head's previous pointer to be the node before the tail
    } else {                                               // If there is only one element in the list
        this->head = nullptr;                              // Set head to nullptr (list becomes empty)
    }

    this->size--;                                        // Decrement the size of the list
    delete tempNode;                                     // Free the memory allocated for the removed tail node
};

// remove: Removes the element at the specified index (0-indexed)
// Throws an exception if the index is invalid.
void CircularDoublyLinkedList::remove(size_t index) {
    if (index >= this->size) {  
        throw std::out_of_range("Index is out of bounds");
    }

    // Initialize previousNode to the tail and currentNode to the head.
    DNode* previousNode = this->head->prev;  
    DNode* currentNode = this->head;

    if (this->size > 1) {  
        size_t i = 0;
        // Traverse the list until reaching the node at the specified index.
        while (i < index) {
            previousNode = previousNode->next;
            currentNode = currentNode->next;
            i++;
        }

        // Update the links to bypass currentNode.
        previousNode->next = currentNode->next;
        currentNode->next->prev = previousNode;
        
        // If the removed node is the head (index == 0), update the head pointer.
        if (index == 0) {
            this->head = currentNode->next;
        }
    } else {
        // If there is only one node in the list, set head to nullptr.
        this->head = nullptr;
    }

    this->size--;
    delete currentNode;  // Free the memory of the removed node.
};

// front: Returns a reference to the first element
// Throws an exception if the list is empty.
int& CircularDoublyLinkedList::front() {
    if (this->isEmpty()) {
        throw std::out_of_range("List is empty");
    }

    return this->head->data;
};

// back: Returns a reference to the last element
// Throws an exception if the list is empty.
int& CircularDoublyLinkedList::back() {
    if (this->isEmpty()) {
        throw std::out_of_range("List is empty");
    }

    return this->head->prev->data;
};

// getSize: Returns the current number of elements in the list
size_t CircularDoublyLinkedList::getSize() const {
    return this->size;
};

// isEmpty: Checks if the list is empty
bool CircularDoublyLinkedList::isEmpty() const {
    return !this->size;
};

// clear: Removes all elements from the list and frees memory
void CircularDoublyLinkedList::clear() {
    this->~CircularDoublyLinkedList();
};

void CircularDoublyLinkedList::print() const {
    // If the list is empty, output a message and return
    if (head == nullptr) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    // Start from the head node
    DNode* current = head;
    
    // Use a do-while loop to traverse the circular list exactly once
    do {
        std::cout << current->data;           // Print the data of the current node
        current = current->next;              // Move to the next node
        // If we haven't returned to head, print the arrow separator
        if (current != head) {
            std::cout << " -> ";
        }
    } while (current != head);

    std::cout << "\n";
};
