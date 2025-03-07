#pragma once
#include <stdexcept>  // For exceptions
#include <cstddef>    // For size_t

// Stack class implementing a LIFO data structure
class Stack {
private:
    // Internal node structure for the stack implementation
    struct Node {
        int data;   // Data stored in the node
        Node* prev; // Pointer to the previous node
        // Node constructor
        Node(int value);
    };

    Node* topNode;  // Pointer to the first node of the stack
    size_t size;     // Number of elements in the stack

public:
    // Constructor: Initializes an empty stack
    Stack();

    // Destructor: Frees all allocated memory
    ~Stack();

    // push: Adds an element to the front of the stack
    void push(int value);

    // pop: Removes the element from the top of the stack
    // Throws an exception if the stack is empty.
    void pop();

    // top: Returns a reference to the top element of the stack
    // Throws an exception if the stack is empty.
    int& top();

    // isEmpty: Returns true if the stack is empty, false otherwise.
    bool isEmpty() const;

    // getSize: Returns the number of elements in the stack.
    size_t getSize() const;

    // clear: Removes all elements from the stack and frees memory
    void clear();

    // print: Traverses the stack and prints each element
    void print() const;
};
