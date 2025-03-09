#pragma once
#include <cstddef>   // For size_t
#include <stdexcept>
#include <vector>
#include <list>
#include <utility>   // For std::pair

// Templated HashTable class for generic key-value pairs
class HashSet {
private:
    // Each bucket is a list of key-value pairs
    std::vector<std::list<int>> table;
    size_t tableSize;     // Number of buckets
    size_t numElements;   // Total number of key-value pairs stored
    const double MAX_LOAD_FACTOR = 0.7;
    const double MIN_LOAD_FACTOR = 0.3;
    const size_t MIN_TABLE_SIZE = 5;

    // Hash function: computes an index for a given key
    size_t hashFunction(const int& value) const;

    void resizeUp();
    void resizeDown();

public:
    // Constructor: Initializes the hash table with a specified number of buckets (default: 101)
    explicit HashSet(size_t size = 101);

    // Destructor: Clears the hash table and frees all resources
    ~HashSet() = default;

    double getLoadFactor() const;

    // insert: Inserts a key-value pair into the hash table
    void insert(const int& value);

    // remove: Removes the key-value pair associated with the given key from the hash table
    void remove(const int& value);

    // get: Retrieves a reference to the value associated with the given key.
    // Throws an exception if the key is not found.
    std::list<int>& get(const int& key);

    // contains: Returns true if the key exists in the hash table, false otherwise.
    bool containsValue(const int& value) const;

    // clear: Removes all key-value pairs from the hash table
    void clear();

    // getSize: Returns the number of elements (key-value pairs) in the hash table.
    size_t getSize() const;

    size_t getTableSize() const;

    // print: Prints the contents of the hash table for debugging purposes.
    void print() const;
};
