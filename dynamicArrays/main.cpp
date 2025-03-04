#include <iostream>
#include "dynamicArray.h"

int main() {
    try {
        DynamicArray arr;

        // Test push_back
        arr.push_back(10);
        arr.push_back(20);
        arr.push_back(30);

        std::cout << "After push_back: ";
        for (size_t i = 0; i < arr.getSize(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";

        // Test insert: Insert 15 at index 1
        arr.insert(1, 15);
        std::cout << "After insert (15 at index 1): ";
        for (size_t i = 0; i < arr.getSize(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";

        // Test erase: Remove element at index 2
        arr.erase(2);
        std::cout << "After erase (element at index 2): ";
        for (size_t i = 0; i < arr.getSize(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";

        // Test pop_back
        arr.pop_back();
        std::cout << "After pop_back: ";
        for (size_t i = 0; i < arr.getSize(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";

    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }

    return 0;
}