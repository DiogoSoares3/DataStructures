#include <cstddef>    // For size_t
#include <stdexcept>
#include <iostream>
#include "circularDoublyLinkedList.h"

// Constructor: initializes node data and sets pointers to nullptr
DNode::DNode(int value) {

};

// Constructor: Initializes an empty circular doubly linked list
CircularDoublyLinkedList::CircularDoublyLinkedList() {

};

// Destructor: Releases all allocated nodes
CircularDoublyLinkedList::~CircularDoublyLinkedList() {
    
};

// push_front: Inserts an element at the beginning of the list
void CircularDoublyLinkedList::push_front(int value) {
    
};

// push_back: Inserts an element at the end of the list
void CircularDoublyLinkedList::push_back(int value) {
    
};

// insert: Inserts an element at the specified index (0-indexed)
// Throws an exception if the index is out of bounds.
void CircularDoublyLinkedList::insert(size_t index, int value) {
    
};

// pop_front: Removes the element at the beginning of the list
// Throws an exception if the list is empty.
void CircularDoublyLinkedList::pop_front() {
    
};

// pop_back: Removes the element at the end of the list
// Throws an exception if the list is empty.
void CircularDoublyLinkedList::pop_back() {
    
};

// remove: Removes the element at the specified index (0-indexed)
// Throws an exception if the index is invalid.
void CircularDoublyLinkedList::remove(size_t index) {
    
};

// front: Returns a reference to the first element
// Throws an exception if the list is empty.
int& CircularDoublyLinkedList::front() {
    
};

// back: Returns a reference to the last element
// Throws an exception if the list is empty.
int& CircularDoublyLinkedList::back() {
    
};

// getSize: Returns the current number of elements in the list
size_t CircularDoublyLinkedList::getSize() const {
    
};

// isEmpty: Checks if the list is empty
bool CircularDoublyLinkedList::isEmpty() const {
    
};

// clear: Removes all elements from the list and frees memory
void CircularDoublyLinkedList::clear() {
    
};

// print: Traverses the list and prints its elements (for debugging/testing)
void CircularDoublyLinkedList::print() const {

};