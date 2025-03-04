#pragma once
#include <cstddef>    // For size_t
#include <stdexcept>  // For exceptions

// Node structure for the singly linked list
struct Node {
    int data;    // Data stored in the node
    Node* next;  // Pointer to the next node

    // Constructor for Node
    Node(int value); // Implementation to be provided in the .cpp file
};

// LinkedList class declaration
class SinglyLinkedList {
private:
    Node* head;   // Pointer to the first node in the list
    Node* tail;   // (Optional) Pointer to the last node for efficient push_back
    size_t size;  // Current number of elements in the list

public:
    // Constructor: Initializes an empty list
    SinglyLinkedList();

    // Destructor: Releases all allocated nodes
    ~SinglyLinkedList();

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

    // print: Traverses the list and prints each element
    void print() const;
};
