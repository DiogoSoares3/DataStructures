#include <iostream>
#include <stdexcept>
#include "dynamicArray.h"

// Default Constructor
DynamicArray::DynamicArray() : data(nullptr), size(0) { }

// Destructor to deallocate memory
DynamicArray::~DynamicArray() {
    delete[] data;
};

// Private function to resize the array to newCapacity
void DynamicArray::resize(size_t newCapacity) {
    int* newData = new int[newCapacity];

    // Copy existing elements to the new array
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    // Free old memory and update the data pointer
    delete[] data;
    data = newData;
};

// Function to add an element at the end
void DynamicArray::push_back(int value) {
    resize(this->size+1);             // Resizes to a new capacity
    this->data[this->size++] = value; // Assigns a new value to the new allocated space at the same time that updates the size (using size++)
};

// Function to remove the last element
void DynamicArray::pop_back() {
    if (this->size == 0) {
        throw std::out_of_range("Array is empty");
    }
    resize(this->size--); // Resizes to a new capacity at the same time that updates the size (using size--)
};

// Function to include an element on a specific index
void DynamicArray::insert(size_t index, int value) {
    if (index > this->size) { // Not using '<=' because the index can be the sequence of last index of the DynamicArray
        throw std::out_of_range("Index out of range");
    }

    resize(this->size+1);
    this->size++;

    for (size_t i = this->size; i > index; i--) {
        this->data[i] = this->data[i-1]; // Moving the elements to the right
    }

    this->data[index] = value;
};

// Function to exclude an element on a specific index
void DynamicArray::erase(size_t index) {
    if (index >= this->size) {
        throw std::out_of_range("Index out of range");
    }

    for (size_t i = index; i < this->size-1; i++) {
        this->data[i] = this->data[i+1]; // Moving the elements to the left
    }

    resize(this->size--);
};

// Access to elements by index (no limit check)
int& DynamicArray::operator[](size_t index) {
    if(index >= this->size) {
        throw std::out_of_range("Index out of range");
    }
    return this->data[index];
};

// Function to obtain the current size
size_t DynamicArray::getSize() const {
    return this->size;
};
