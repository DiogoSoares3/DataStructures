#include <iostream>
#include "hashSet.h"

int main() {
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
    
    return 0;
}