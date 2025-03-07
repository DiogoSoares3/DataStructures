#include <iostream>
#include "stack.h"

int main() {
    Stack stack;

    // Test initial state
    std::cout << "Initial stack (should be empty):\n";
    stack.print();
    std::cout << "Size: " << stack.getSize() << "\n\n";

    // Test push
    std::cout << "Pushing elements: 10, 20, 30\n";
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.print(); // Expected: 30 <- 20 <- 10
    std::cout << "Size: " << stack.getSize() << "\n\n";

    // Test top
    std::cout << "Top element (should be 30): " << stack.top() << "\n\n";

    // Test pop
    std::cout << "Popping one element...\n";
    stack.pop();
    stack.print(); // Expected: 20 <- 10
    std::cout << "Size: " << stack.getSize() << "\n";
    std::cout << "Top element (should be 20): " << stack.top() << "\n\n";

    // Popping all the elements
    std::cout << "Popping  all the elements...\n";
    stack.print();
    stack.pop();
    stack.pop();
    stack.print();
    std::cout << "Size: " << stack.getSize() << "\n";

    // Test push again
    std::cout << "Pushing element: 40\n";
    stack.push(40);
    stack.print(); // Expected: 40
    std::cout << "Size: " << stack.getSize() << "\n\n";

    // Test clear
    std::cout << "Clearing the stack...\n";
    stack.clear();
    stack.print(); // Expected: (empty output)
    std::cout << "Size after clear: " << stack.getSize() << "\n";

    return 0;
}