# Linked Lists Implementation in C++

This repository provides educational implementations of two fundamental linked list data structures in C++: the **Singly Linked List** and the **Circular Doubly Linked List**. These implementations demonstrate core data structure concepts such as dynamic memory allocation, pointer manipulation, and efficient insertion/deletion operations. They serve as building blocks for more advanced data structures and algorithms.

---

## Table of Contents

1. [Overview](#overview)
2. [Singly Linked List](#singly-linked-list)
    - [Classes and Attributes](#classes-and-attributes-in-singly-linked-list)
    - [Key Methods](#key-methods-in-singly-linked-list)
3. [Circular Doubly Linked List](#circular-doubly-linked-list)
    - [Classes and Attributes](#classes-and-attributes-in-circular-doubly-linked-list)
    - [Key Methods](#key-methods-in-circular-doubly-linked-list)
4. [Usage and Compilation](#usage-and-compilation)
5. [Conclusion](#conclusion)

---

## Overview

Linked lists are dynamic data structures where elements (nodes) are stored in non-contiguous memory locations. Each node typically contains data and a pointer (or pointers) linking it to other nodes. Unlike static arrays, linked lists can grow or shrink at runtime, making them ideal for situations where the number of elements changes frequently.

In this project, we implement two versions of linked lists:
- A **Singly Linked List**, where each node points only to the next node.
- A **Circular Doubly Linked List**, where each node has pointers to both the next and previous nodes, and the list is circular (i.e., the last node links back to the first, and the first node's previous pointer links to the last).

---

## Singly Linked List

### Classes and Attributes in Singly Linked List

- **`Node`**
  - **Attributes:**
    - `data`: Stores the value of the node.
    - `next`: Pointer to the next node in the list.
  - **Constructor:**  
    Initializes a new node with a given value and sets the `next` pointer to `nullptr`.

- **`SinglyLinkedList`**
  - **Attributes:**
    - `head`: Points to the first node in the list.
    - `tail`: Points to the last node in the list.
    - `size`: Keeps track of the number of nodes in the list.
  - **Destructor:**  
    Traverses the list and deletes all nodes to free memory.
    
### Key Methods in Singly Linked List

- **`push_front(int value)`**  
  Inserts a new node at the beginning of the list.

- **`push_back(int value)`**  
  Appends a new node at the end of the list.

- **`insert(size_t index, int value)`**  
  Inserts a new node at the specified index (0-indexed).  
  *Note:* Traverses the list until the specified index is reached.

- **`pop_front()`**  
  Removes the node at the beginning of the list, properly deallocating its memory.

- **`pop_back()`**  
  Removes the node at the end of the list.  
  *Note:* If only one node exists, it resets both `head` and `tail` to `nullptr`.

- **`remove(size_t index)`**  
  Removes the node at the specified index and updates pointers to maintain list integrity.

- **Accessors:**  
  - `front()`: Returns the first element.
  - `back()`: Returns the last element.
  - `getSize()`: Returns the current number of nodes.
  - `isEmpty()`: Checks if the list is empty.

- **`clear()`**  
  Deletes all nodes and resets the list to an empty state.

- **`print()`**  
  Traverses and prints the elements of the list for debugging purposes.

---

## Circular Doubly Linked List

### Classes and Attributes in Circular Doubly Linked List

- **`DNode`**
  - **Attributes:**
    - `data`: Stores the node's value.
    - `next`: Pointer to the next node.
    - `prev`: Pointer to the previous node.
  - **Constructor:**  
    Initializes the node with the given value and sets both pointers (`next` and `prev`) to `nullptr`.

- **`CircularDoublyLinkedList`**
  - **Attributes:**
    - `head`: Points to the first node of the circular list.  
      *Note:* In a circular list, the last node's `next` points back to `head` and `head->prev` points to the last node.
    - `size`: Represents the number of nodes in the list.
  - **Destructor:**  
    Uses a `do/while` loop to traverse the circular list and delete each node, ensuring that the entire list is freed correctly.

### Key Methods in Circular Doubly Linked List

- **`push_front(int value)`**  
  Inserts a new node at the beginning of the list.  
  *Updates:* Adjusts both `next` and `prev` pointers.  
  *Special Case:* If the list is empty, the new node's `next` and `prev` pointers reference itself.

- **`push_back(int value)`**  
  Inserts a new node at the end of the list.  
  *Updates:* Similar to `push_front` but maintains the tail as the last node (accessible via `head->prev`).

- **`insert(size_t index, int value)`**  
  Inserts a new node at the specified index (0-indexed).  
  *Note:* Traverses the list using two pointers to locate the correct insertion point and updates the surrounding nodes’ pointers accordingly.

- **`pop_front()`**  
  Removes the first node of the list, updating the head and the tail’s `next`/`prev` pointers to maintain circularity.

- **`pop_back()`**  
  Removes the last node (i.e., the node pointed to by `head->prev`), ensuring the list remains circular.

- **`remove(size_t index)`**  
  Removes the node at the specified index.  
  *Important:* If the removed node is the head, updates the head pointer to the next node.

- **Accessors:**  
  - `front()`: Returns the first element.
  - `back()`: Returns the last element.
  - `getSize()`: Returns the current number of nodes.
  - `isEmpty()`: Checks if the list is empty.

- **`clear()`**  
  Deletes all nodes from the list, using the destructor to free memory.

- **`print()`**  
  Traverses the circular list (using a `do/while` loop) and prints each node’s data to visualize the list structure.

---

## Usage and Compilation

To compile the code, you can combine multiple C++ source files into one executable. For example, if your files are `main.cpp`, `SinglyLinkedList.cpp`, and `CircularDoublyLinkedList.cpp`, compile them using:

```bash
g++ -std=c++11 main.cpp singlyLinkedList.cpp circularDoublyLinkedList.cpp -o linkedLists
```

This command compiles all source files and produces an executable named `linkedLists`

## Conclusion

This project provides two implementations of linked lists in C++:

- A **Singly Linked List** which offers a straightforward, linear data structure.
- A **Circular Doubly Linked List** which supports bidirectional traversal and a circular structure, ideal for applications like round-robin scheduling.

Both implementations include standard operations such as insertion, deletion, and traversal. Understanding these implementations helps in mastering dynamic data structures and preparing for more complex algorithmic challenges.
