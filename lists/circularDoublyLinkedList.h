#pragma once
#include <cstddef>    // For size_t
#include <stdexcept>
#include <iostream>

// Node structure for the circular doubly linked list
struct DNode {
    int data;        // Data stored in the node
    DNode* next;     // Pointer to the next node
    DNode* prev;     // Pointer to the previous node

    // Constructor: initializes node data and sets pointers to nullptr
    DNode(int value);
};

// Circular Doubly Linked List class declaration
class CircularDoublyLinkedList {
private:
    DNode* head;     // Pointer to the head of the list
    size_t size;     // Current number of elements in the list

public:
    // Constructor: Initializes an empty circular doubly linked list
    CircularDoublyLinkedList();

    // Destructor: Releases all allocated nodes
    ~CircularDoublyLinkedList();

    // push_front: Inserts an element at the beginning of the list
    void push_front(int value);

    // push_back: Inserts an element at the end of the list
    void push_back(int value);

    // insert: Inserts an element at the specified index (0-indexed)
    // Throws an exception if the index is out of bounds.
    void insert(size_t index, int value);

    // pop_front: Removes the element at the beginning of the list
    // Throws an exception if the list is empty.
    void pop_front();

    // pop_back: Removes the element at the end of the list
    // Throws an exception if the list is empty.
    void pop_back();

    // remove: Removes the element at the specified index (0-indexed)
    // Throws an exception if the index is invalid.
    void remove(size_t index);

    // front: Returns a reference to the first element
    // Throws an exception if the list is empty.
    int& front();

    // back: Returns a reference to the last element
    // Throws an exception if the list is empty.
    int& back();

    // getSize: Returns the current number of elements in the list
    size_t getSize() const;

    // isEmpty: Checks if the list is empty
    bool isEmpty() const;

    // clear: Removes all elements from the list and frees memory
    void clear();

    // print: Traverses the list and prints its elements (for debugging/testing)
    void print() const;
};
