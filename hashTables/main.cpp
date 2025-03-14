#include <iostream>
#include "hashSet.h"
#include "hashMap.h"

int main() {
    // Testing Hash Set:
    std::cout << "\n\n--- Testing HashMap ---" << std::endl;

    HashSet mySet(5);

    std::cout << "Initial table:" << std::endl;
    mySet.print();
    std::cout << "Initial table size: " << mySet.getSize() << std::endl;
    std::cout << "Initial load factor: " << mySet.getLoadFactor() << std::endl << std::endl;

    for (int i = 1; i <= 10; i++) {
        mySet.insert(i * 10);  // Insert 10, 20, 30, ..., 100
    }

    std::cout << "After inserting 10 values:" << std::endl;
    mySet.print();
    std::cout << "Table size: " << mySet.getSize() << std::endl;
    std::cout << "Load factor: " << mySet.getLoadFactor() << std::endl << std::endl;

    for (int i = 11; i <= 20; i++) {
        mySet.insert(i * 10);  // Insert 110, 120, ..., 200
    }

    std::cout << "After inserting additional 10 values:" << std::endl;
    mySet.print();
    std::cout << "Table size (num elements): " << mySet.getSize() << std::endl;
    std::cout << "Load factor: " << mySet.getLoadFactor() << std::endl;
    std::cout << "Current bucket count (tableSize): " << mySet.getTableSize() << std::endl << std::endl;

    std::cout << "Removing value 50:" << std::endl;
    mySet.remove(50);
    mySet.print();
    std::cout << "Load factor: " << mySet.getLoadFactor() << std::endl << std::endl;

    std::cout << "Clearing the hash set:" << std::endl;
    mySet.clear();
    mySet.print();
    std::cout << "Final table size: " << mySet.getSize() << std::endl;

    // --------------------- Begin HashMap Tests ---------------------
    std::cout << "\n\n--- Testing HashMap ---" << std::endl;
    
    // Create a HashMap with initial bucket count 5
    HashMap<int, std::string> myMap(5);
    
    std::cout << "\nInitial HashMap:" << std::endl;
    myMap.print();
    std::cout << "Initial number of elements: " << myMap.getSize() << std::endl;
    std::cout << "Initial load factor: " << myMap.getLoadFactor() << std::endl << std::endl;
    
    // Insert some key-value pairs into the HashMap
    myMap.insert(1, "One");
    myMap.insert(2, "Two");
    myMap.insert(3, "Three");
    myMap.insert(4, "Four");
    myMap.insert(5, "Five");
    
    std::cout << "After inserting 5 key-value pairs:" << std::endl;
    myMap.print();
    std::cout << "Number of elements: " << myMap.getSize() << std::endl;
    std::cout << "Load factor: " << myMap.getLoadFactor() << std::endl << std::endl;
    
    // Test search functionality
    std::cout << "Testing search function:" << std::endl;
    if (myMap.contains(3)) {
        std::cout << "Key 3 found with value: " << myMap.get(3) << std::endl;
    } else {
        std::cout << "Key 3 not found." << std::endl;
    }
    
    // Remove a key and test the removal
    std::cout << "\nRemoving key 2:" << std::endl;
    myMap.remove(2);
    myMap.print();
    std::cout << "Number of elements: " << myMap.getSize() << std::endl;
    std::cout << "Load factor: " << myMap.getLoadFactor() << std::endl << std::endl;
    
    // Insert additional key-value pairs to potentially trigger a resize
    for (int i = 6; i <= 10; i++) {
        myMap.insert(i, "Number " + std::to_string(i));
    }
    
    std::cout << "After inserting additional key-value pairs:" << std::endl;
    myMap.print();
    std::cout << "Number of elements: " << myMap.getSize() << std::endl;
    std::cout << "Load factor: " << myMap.getLoadFactor() << std::endl;
    std::cout << "Current bucket count: " << myMap.getTableSize() << std::endl << std::endl;
    
    // Clear the HashMap and display the final state
    std::cout << "Clearing the hash map:" << std::endl;
    myMap.clear();
    myMap.print();
    std::cout << "Final number of elements: " << myMap.getSize() << std::endl;
    
    return 0;
}