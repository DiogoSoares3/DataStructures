# Dynamic Array in C++

This Data Structure repository contains an educational implementation of a dynamic array in C++. It demonstrates fundamental concepts of dynamic memory allocation, pointer manipulation, and the implementation of basic methods for managing arrays at runtime. While this implementation resizes the array on every operation (which is not optimal for performance), it illustrates the principles behind dynamic arrays and serves as a foundation for more advanced data structures and algorithms.

## What Is a Dynamic Array?

A dynamic array is a data structure that allows you to store elements in a contiguous block of memory whose capacity can be adjusted at runtime. Unlike a static array, where the size is fixed at compile time, a dynamic array can grow or shrink as elements are added or removed. This flexibility is essential when the number of elements is not known in advance or may vary over time.

### Dynamic Memory Allocation

In this implementation, memory allocation and deallocation are managed manually using the `new[]` and `delete[]` operators:

- **Allocation**: When the `resize(size_t newCapacity)` function is called, a new block of memory is allocated to hold exactly `newCapacity` elements of type `int`.

- **Data Copy**: Existing elements are copied from the old array to the new array using a loop that iterates over the currently stored elements.

- **Deallocation**: After copying, the old memory block is deallocated using `delete[]`, and the pointer `data` is updated to point to the new block.

This approach ensures that the array always has the exact size required to store its elements, although, in practical applications, dynamic arrays (like `std::vector`) typically reserve extra capacity to minimize frequent reallocations.

## Class Methods

1. **`push_back(int value)`**
- Purpose: Adds a new element to the end of the array.

- How It Works:
    - Calls `resize` to increase the array's capacity by one, which involves reallocating and copying the existing elements.
    - Inserts the new value at the end of the array.
    - Increments the `size` variable to reflect the new number of elements.

- Note: Resizing the array on every insertion is instructional but not ideal for performance. Real-world dynamic arrays usually increase capacity exponentially.

2. **`pop_back()`**

- Purpose: Removes the last element from the array.

- How It Works:
    - Checks whether the array is empty.
    - Decrements the `size` variable.
    - Calls `resize` to adjust the array's capacity to the new size.

- Note: Like push_back, this method resizes the array on every removal, which is not the most efficient strategy but helps demonstrate dynamic memory management.

3. **`insert(size_t index, int value)`**

- Purpose: Inserts a new element at a specific position in the array.

- How It Works:
    - Validates that the provided index is within acceptable bounds (the index can equal `size` for appending at the end).
    - Calls `resize` to increase the capacity by one.
    - Shifts existing elements to the right from the specified index to make room for the new element. For example:
    ```cpp
    for (size_t i = this->size; i > index; i--) {
        this->data[i] = this->data[i - 1];
    }
    ```
    - Inserts the new value at the desired position and increments the `size`.

4. **`erase(size_t index)`**

- Purpose: Removes the element at a specific index from the array.

- How It Works:
    - Validates that the index is within the array's current bounds.
    - Shifts elements to the left starting from the index, effectively overwriting the element to be removed:
    ```cpp
    for (size_t i = index; i < this->size - 1; i++) {
        this->data[i] = this->data[i + 1];
    }
    ```
    - Decrements the `size` and calls `resize` to adjust the array's capacity to the new number of elements.

5. **`operator[](size_t index)`**

- Purpose: Provides array-like access to elements using the subscript operator (e.g., `arr[i]`).

- How It Works:
    - Checks if the index is within valid bounds.
    - Returns a reference to the element at the specified index, allowing both reading and writing.

- Usage Example:
    ```cpp
    DynamicArray arr;
    arr.push_back(10);
    std::cout << arr[0]; // Accesses the first element
    ```
6. **`getSize() const`**

- Purpose: Returns the current number of elements stored in the array.

- How It Works:
    - Declared as a `const` member function to guarantee that it does not modify the state of the object.
    - Simply returns the `size` variable.

## Final Considerations

- **Efficiency vs. Educational Value**:
This implementation is intended to clarify the basic concepts of dynamic memory allocation and array manipulation in C++. In production code, dynamic arrays typically grow exponentially (e.g., doubling capacity) to minimize the number of reallocations, as implemented by `std::vector`.

- **Error Handling**:
The implementation uses exceptions (e.g., `std::out_of_range`) to handle invalid index accesses, which enhances the safety and robustness of the data structure.

- **Building Blocks for Advanced Structures**:
Understanding how a dynamic array works is essential for developing more complex data structures such as linked lists, stacks, queues, and eventually, structures used in graph algorithms. 