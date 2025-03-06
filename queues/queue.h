#pragma once
#include <stdexcept>  // For exceptions
#include <cstddef>    // For size_t

// Queue class implementing a FIFO data structure
class Queue {
private:
    // Internal node structure for the linked list implementation
    struct Node {
        int data;   // Data stored in the node
        Node* next; // Pointer to the next node
        // Node constructor
        Node(int value);
    };

    Node* frontNode; // Pointer to the front of the queue
    Node* backNode;  // Pointer to the back of the queue
    size_t size;     // Number of elements in the queue

public:
    // Constructor: Initializes an empty queue
    Queue();

    // Destructor: Frees all allocated memory
    ~Queue();

    // Enqueue: Adds an element to the back of the queue
    void enqueue(int value);

    // Dequeue: Removes the element from the front of the queue
    // Throws an exception if the queue is empty.
    void dequeue();

    // Front: Returns a reference to the front element of the queue
    // Throws an exception if the queue is empty.
    int& front();

    // isEmpty: Returns true if the queue is empty, false otherwise.
    bool isEmpty() const;

    // getSize: Returns the number of elements in the queue.
    size_t getSize() const;

    // clear: Removes all elements from the queue and frees memory
    void clear();

    // print: Traverses the queue and prints each element
    void print() const;
};
