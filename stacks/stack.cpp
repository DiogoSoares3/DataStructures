#include <stdexcept>  // For exceptions
#include <cstddef>    // For size_t
#include <iostream>
#include "stack.h"


// Constructor: Initializes an empty node
Stack::Node::Node(int value) : data(value), prev(nullptr) { };

// Constructor: Initializes an empty queue
Stack::Stack() : topNode(nullptr), size(0) { };

// Destructor: Frees all allocated memory
Stack::~Stack() {
    Node* current = this->topNode;
    while (current != nullptr) {
        Node* previousNode = current->prev;
        delete current;
        current = previousNode;
    }
    this->topNode = nullptr;
    this->size = 0;
};

// push: Adds an element to the front of the stack
void Stack::push(int value) {
    Node* newNode = new Node(value);

    if (this->isEmpty()) {
        this->topNode = newNode; // When the stack is empty, newNode becomes the top.
    } else {
        newNode->prev = this->topNode; // Set newNode's prev pointer to the current top node.
        this->topNode = newNode; // Update topNode to point to the new node.
    }

    this->size++;
};

// pop: Removes the element from the top of the stack
// Throws an exception if the stack is empty.
void Stack::pop() {
    if (this->isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }

    // Getting the topNode for deletion
    Node* tempNode = this->topNode;
    if (this->size > 1) {
        this->topNode = this->topNode->prev; // Set topNode to its previous node.
    } else {
        this->topNode = nullptr; // If there is only one element, set topNode to nullptr.
    }

    delete tempNode;
    this->size--;
};

// top: Returns a reference to the top element of the stack
// Throws an exception if the stack is empty.
int& Stack::top() {
    if (this->isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }

    return this->topNode->data;
};

// isEmpty: Returns true if the stack is empty, false otherwise.
bool Stack::isEmpty() const {
    return !this->size;
};

// getSize: Returns the number of elements in the stack.
size_t Stack::getSize() const {
    return this->size;
};

// clear: Removes all elements from the stack and frees memory
void Stack::clear() {
    this->~Stack();
};

// print: Traverses the stack and prints each element
void Stack::print() const {
    Node* current = this->topNode;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->prev != nullptr)
            std::cout << " <- ";
        current = current->prev;
    }
    std::cout << "\n";
};
