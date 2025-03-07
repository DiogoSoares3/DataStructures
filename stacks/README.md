# Stack Implementation in C++

This repository contains an educational implementation of a **Stack** data structure in C++. The stack is implemented using a linked list and follows the **Last-In, First-Out (LIFO)** principle. In a stack, the last element added is the first one to be removed. This behavior is essential for many algorithmic processes and applications.

---

## What is a Stack?

A **stack** is a linear data structure that operates on the **LIFO** (Last-In, First-Out) principle. It supports two primary operations:

- **Push:** Add an element to the top of the stack.
- **Pop:** Remove the element from the top of the stack.

Additional operations typically include:
- **Top:** Retrieve the top element without removing it.
- **isEmpty:** Check if the stack is empty.
- **getSize:** Determine the number of elements in the stack.
- **Clear:** Remove all elements from the stack.

---

## Real-World Applications of Stacks

Stacks play a vital role in various aspects of computing, including:
- **Function Call Management:** The call stack is used to manage function calls, local variables, and control flow.
- **Expression Evaluation:** Stacks are used in parsing and evaluating expressions (e.g., converting infix to postfix notation).
- **Undo Mechanisms:** Applications like text editors use stacks to implement undo functionality.
- **Depth-First Search (DFS):** Stacks facilitate DFS in graph algorithms.
- **Backtracking:** Many algorithms, such as puzzle solvers or recursive solutions, use stacks to store state information.

Understanding and implementing a stack is fundamental to mastering more complex data structures and algorithms.

---

## Implementation Details

The stack in this project is implemented using a linked list. Below is an overview of the key components:

### Classes and Attributes

- **`Node` (nested within `Stack`):**  
  - **Attributes:**  
    - `data`: Holds the integer value stored in the node.  
    - `prev`: Pointer to the previous node in the stack.  
  - **Constructor:**  
    Initializes the node with a given value and sets `prev` to `nullptr`.

- **`Stack`:**  
  - **Attributes:**  
    - `topNode`: Points to the top element of the stack (the last pushed element).  
    - `size`: Tracks the number of elements in the stack.
  - **Key Methods:**  
    - **`push(int value)`**: Adds an element to the top of the stack.  
    - **`pop()`**: Removes the top element from the stack. Throws an exception if the stack is empty.  
    - **`top()`**: Returns a reference to the top element without removing it.  
    - **`isEmpty()`**: Checks if the stack is empty.  
    - **`getSize()`**: Returns the number of elements in the stack.  
    - **`clear()`**: Removes all elements from the stack, freeing memory.  
    - **`print()`**: Traverses the stack and prints its elements (useful for debugging).

---

## Compilation Instructions

To compile the project, ensure you have the following files in your repository:
- `Stack.h` – Contains the class definition and method prototypes.
- `Stack.cpp` – Contains the implementation of the Stack methods.
- `main.cpp` – Contains a test suite to verify the functionality of the Stack.

You can compile these files together using `g++`. For example:

```bash
g++ -std=c++11 main.cpp stack.cpp -o stack
```

This command will produce an executable named `stack`. Run the executable to test the stack operations and observe the output from the `print()` method.

## Conclusion

The stack is a fundamental data structure with wide-ranging applications in computing, from managing function calls to enabling efficient backtracking and expression evaluation. This repository’s implementation in C++ provides a practical example of how stacks work, how to manipulate them, and their importance in solving algorithmic problems.