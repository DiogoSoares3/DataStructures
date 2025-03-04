#pragma once
#include <stdexcept>
#include <cstddef>  // For size_t

class DynamicArray {
private:
    int* data;         // Pointer to the array of elements
    size_t size;       // Current number of stored elements

    // Function to set a new capacity for our DynamicArray
    void resize(size_t newCapacity);

public:
    // Default Constructor
    DynamicArray();

    // Destructor to deallocate memory
    ~DynamicArray();

    // Function to add an element at the end
    void push_back(int value);

    // Function to remove the last element
    void pop_back();

    // Function to insert an element at a specific index
    void insert(size_t index, int value);

    // Function to erase an element at a specific index
    void erase(size_t index);

    // Overloaded operator[] for element access (with range check)
    int& operator[](size_t index);

    // Function to obtain the current size
    size_t getSize() const;
};
