#include <stdexcept>  // For exceptions
#include <cstddef>    // For size_t
#include <iostream>
#include "queue.h"

// Constructor: Initializes an empty node
Queue::Node::Node(int value) : data(value), next(nullptr) {};

// Constructor: Initializes an empty queue
Queue::Queue() : frontNode(nullptr), backNode(nullptr), size(0) {};

// Destructor: Frees all allocated memory
Queue::~Queue() {
    Node* current = this->backNode;      // Start with the backNode node
    while (current != nullptr) {         // Loop until we reach the end of the queue
        Node* nextNode = current->next;  // Save the pointer to the next node
        delete current;                  // Delete the current node, freeing its memory
        current = nextNode;              // Move to the next node in the queue
    }
    this->backNode = nullptr;   // Set head to nullptr to indicate the queue is now empty
    this->frontNode = nullptr;  // Set tail to nullptr as well
    this->size = 0;             // Reset size to 0
};

// Enqueue: Adds an element to the back of the queue
void Queue::enqueue(int value) {
    Node* newNode = new Node(value);

    if (this->size > 0) {
        // New node's next points to the current backNode.
        newNode->next = this->backNode;
        // Update backNode to be the new node.
        this->backNode = newNode;
    } else {
        // For the first node, both frontNode and backNode point to newNode.
        this->frontNode = newNode;
        this->backNode = newNode;
    }

    this->size++;
};

// Dequeue: Removes the element from the front of the queue
// Throws an exception if the queue is empty.
void Queue::dequeue() {
    if (this->isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }

    Node* tempNode = this->frontNode;
    Node* previousNode = nullptr;

    if (this->size > 1) {
        size_t i = 0;

        // Traverse the chain from backNode to locate the node before frontNode.
        while (i < this->size-1) {
            if (i == 0){
                previousNode = this->backNode;
            } else {
                previousNode = previousNode->next;
            }
            i++;
        }
        // previousNode is the node immediately before frontNode.
        this->frontNode = previousNode;
        previousNode->next = nullptr;
    } else {
        // If only one element, reset both pointers.
        this->frontNode = nullptr;
        this->backNode = nullptr;
    }

    delete tempNode;
    this->size--;
};

// Front: Returns a reference to the front element of the queue
// Throws an exception if the queue is empty.
int& Queue::front() {
    if (this->isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }

    return this->frontNode->data;
};

// isEmpty: Returns true if the queue is empty, false otherwise.
bool Queue::isEmpty() const {
    return !this->size;
};

// getSize: Returns the number of elements in the queue.
size_t Queue::getSize() const {
    return this->size;
};

// clear: Removes all elements from the list and frees memory
void Queue::clear() {
    this->~Queue();
};

// print: Traverses the queue and prints each element
void Queue::print() const {
    Node* current = this->backNode;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr)
            std::cout << " -> ";
        current = current->next;
    }
    std::cout << "\n";
};
