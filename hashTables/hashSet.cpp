#include <cstddef>   // For size_t
#include <stdexcept>
#include <vector>
#include <list>
#include <iostream>
#include "hashSet.h"

// Hash function: computes an index for a given key
size_t HashSet::hashFunction(const int& value) const {
    return value % this->tableSize;
};

void HashSet::resizeUp() {
    size_t newSize = this->tableSize * 2; // Doubles the table size
    std::vector<std::list<int>> newTable(newSize);

    // Reinsert all elements in the new table
    for (const auto& bucket : this->table) {
        for (int value : bucket) {
            size_t newBucketId = value % newSize;
            newTable[newBucketId].push_back(value);
        }
    }

    size_t previousNumElements = this->numElements;
    this->table = std::move(newTable);
    this->tableSize = newSize;
    this->numElements = previousNumElements;
}

void HashSet::resizeDown() {
    size_t newSize = this->tableSize / 2; // Doubles the table size

    if (newSize < this->MIN_TABLE_SIZE) {
        newSize = this->MIN_TABLE_SIZE;
    }

    std::vector<std::list<int>> newTable(newSize);

    // Reinsert all elements in the new table
    for (const auto& bucket : this->table) {
        for (int value : bucket) {
            size_t newBucketId = value % newSize;
            newTable[newBucketId].push_back(value);
        }
    }

    size_t previousNumElements = this->numElements;
    this->table = std::move(newTable);
    this->tableSize = newSize;
    this->numElements = previousNumElements;
}

// Constructor: Initializes the hash table with a specified number of buckets (default: 101)
HashSet::HashSet(size_t size) : table(size), tableSize(size), numElements(0) { };


double HashSet::getLoadFactor() const {
    return static_cast<double>(this->numElements) / this->tableSize;
}

// insert: Inserts a key-value pair into the hash table
void HashSet::insert(const int& value) {
    if (this->containsValue(value)) {
        return;
    }

    if (this->getLoadFactor() > this->MAX_LOAD_FACTOR) {
        resizeUp();
    }
    size_t bucketId = hashFunction(value);
    this->table[bucketId].push_back(value);
    this->numElements++;
};

// remove: Removes all elements equal to the value parameter from the hash table
void HashSet::remove(const int& value) {
    if (!this->containsValue(value)) {
        return;
    }

    if (this->getLoadFactor() < this->MIN_LOAD_FACTOR) {
        resizeDown();
    }

    size_t bucketId = hashFunction(value);

    std::list<int>& bucket = this->table[bucketId];
    for (auto it = bucket.begin(); it != bucket.end();) {
        if (*it == value) {
            it = bucket.erase(it); // erase returns the next iterator
            this->numElements--;
            break;
        } else {
            it++;
        }
    }
};

// get: Retrieves a reference to the value associated with the given key.
// Throws an exception if the key is not found.
std::list<int>& HashSet::get(const int& key) {
    if (key < 0 || static_cast<size_t>(key) >= this->tableSize) {
        throw std::out_of_range("Key out of range");
    } else {
        return this->table[key];
    }
}

// contains: Returns true exists values given a key in the hash table, false otherwise.
bool HashSet::containsValue(const int& value) const {
    size_t bucketId = hashFunction(value);

    for (const auto& val : this->table[bucketId]) {
        if (val == value) {
            return true;
        }
    }
    return false;
};

// clear: Removes all key-value pairs from the hash table
void HashSet::clear() {
    for (auto &bucket : this->table) {
        bucket.clear();
    }
    this->table.clear();
    this->table.resize(tableSize);
    this->numElements = 0;
};

// getSize: Returns the number of elements (key-value pairs) in the hash table.
size_t HashSet::getSize() const {
    return this->numElements;
};

size_t HashSet::getTableSize() const {
    return this->table.size();
}

// print: Prints the contents of the hash table for debugging purposes.
void HashSet::print() const {
    for (size_t i = 0; i < this->table.size(); i++) {
        std::cout << "Bucket " << i << ": ";

        for (const auto &val : this->table[i]) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};