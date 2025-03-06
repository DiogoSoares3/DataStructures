# Queue Data Structure in C++

This repository provides an educational implementation of a **Queue** in C++. A queue is a linear data structure that follows the **First-In, First-Out (FIFO)** principle, meaning that the first element added to the queue is the first one to be removed. This README explains what a queue is, how it works, its real-world applications, and details about the C++ code implementation with compilation instructions.

---

## What is a Queue?

A **queue** is an abstract data type that operates in a FIFO manner. In a queue, elements are added (enqueued) at one end and removed (dequeued) from the other. The two main operations are:

- **Enqueue:** Insert an element at the back of the queue.
- **Dequeue:** Remove an element from the front of the queue.

Because of this behavior, queues are used to simulate real-world scenarios like people waiting in line, scheduling tasks, or buffering data.

---

## How Does a Queue Work (FIFO)?

The **FIFO** (First-In, First-Out) principle ensures that the element that has been in the queue the longest is processed first. For example, consider a line at a bank: the first customer to join the line is the first one to be served. In a queue implementation:
- **Enqueue:** When an element is enqueued, it is added at the "back" of the queue.
- **Dequeue:** When an element is dequeued, it is removed from the "front" of the queue.

---

## Real-World Applications of Queues

Queues are widely used in many applications, including:
- **Task Scheduling:** Operating systems use queues to schedule processes (e.g., CPU scheduling).
- **Print Spooling:** Print jobs are queued so that the printer processes them in order.
- **Breadth-First Search (BFS):** Graph traversal algorithms use queues to visit nodes in a FIFO order.
- **Customer Service Systems:** Simulate service lines where customers are served in the order they arrive.
- **Networking:** Packets are queued for processing in routers and switches.

---

## C++ Queue Implementation

The queue in this implementation is based on a linked list where:
- The **`frontNode`** always represents the front (oldest element) and its `next` pointer is `nullptr`.
- The **`backNode`** represents the back (most recently enqueued element).
- The queue maintains a size counter to track the number of elements.

### Key Methods

- **`enqueue(int value)`**  
  Adds an element to the back of the queue. If the queue is empty, both `frontNode` and `backNode` are set to the new node.

- **`dequeue()`**  
  Removes the element from the front of the queue. It traverses the queue from `backNode` to update the `frontNode` pointer and then deletes the old front node.

- **`front()`**  
  Returns a reference to the front element (oldest element). Throws an exception if the queue is empty.

- **`isEmpty()`**  
  Checks if the queue is empty.

- **`getSize()`**  
  Returns the number of elements in the queue.

- **`clear()`**  
  Removes all elements from the queue and frees memory.

- **`print()`**  
  Traverses the queue from the back to the front and prints each element, which is useful for debugging.

### Code Files

- **`queue.h`** – Contains the class definition and method prototypes.
- **`queue.cpp`** – Contains the implementation of the Queue methods.
- **`main.cpp`** – Contains a test suite to verify the functionality of the Queue implementation.

---

## Compilation Instructions

To compile the code, ensure that `queue.h`, `queue.cpp`, and `main.cpp` are in the same directory. Then use the following command with `g++`:

```bash
g++ -std=c++11 main.cpp queue.cpp -o queue
```

This command compiles all the source files and produces an executable named `queue`.

## Conclusion

This project demonstrates a fundamental implementation of a queue in C++ using a queue. By following the FIFO principle, the queue is ideal for real-world applications such as process scheduling, BFS in graph algorithms, and buffering tasks in networking.