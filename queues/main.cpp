#include <iostream>
#include "queue.h"

int main() {
    Queue q;

    std::cout << "Initial queue (should be empty):\n";
    q.print();
    std::cout << "Size: " << q.getSize() << "\n\n";

    // Test enqueue operations
    std::cout << "Enqueue 10, 20, 30:\n";
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.print();
    std::cout << "Size: " << q.getSize() << "\n";
    
    // The chain is stored from backNode (most recent) to frontNode (oldest).
    // Thus, the front element (oldest) is accessed via front(), which should be 10.
    std::cout << "Front element (should be 10): " << q.front() << "\n\n";

    // Test dequeue: remove one element (the front, oldest element)
    std::cout << "Dequeue one element (should remove 10):\n";
    q.dequeue();
    q.print();
    std::cout << "Size: " << q.getSize() << "\n";
    std::cout << "New front element (should be 20): " << q.front() << "\n\n";

    // Test additional enqueue operations
    std::cout << "Enqueue 40 and 50:\n";
    q.enqueue(40);
    q.enqueue(50);
    q.print();
    std::cout << "Size: " << q.getSize() << "\n";
    std::cout << "Front element (should still be 20): " << q.front() << "\n\n";

    // Dequeue all elements one by one
    std::cout << "Dequeue all elements:\n";
    while (!q.isEmpty()) {
        q.dequeue();
        q.print();
        std::cout << "Size: " << q.getSize() << "\n";
    }

    // Test clear on an empty queue (should not cause errors)
    std::cout << "\nTesting clear on empty queue:\n";
    q.clear();
    q.print();
    std::cout << "Final size after clear: " << q.getSize() << "\n";

    return 0;
}