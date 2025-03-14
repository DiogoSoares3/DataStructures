#include <utility>   // For std::pair
#include <stdexcept>
#include <vector>
#include <list>
#include <iostream>
#include "hashMap.h"

template class HashMap<int, std::string>;

// Computes the bucket index for a given key.
template<typename KeyType, typename ValueType>
size_t HashMap< KeyType, ValueType>::hashFunction(const KeyType& key) const {
    return static_cast<size_t>(key) % this->tableSize;
}

// Doubles the table size and rehashes all elements.
template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::resizeUp() {
    size_t newSize = this->tableSize * 2;
    std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(newSize);

    // Rehash each element into the new table.
    for (const auto& bucket : this->table) {
        for (const auto& pair : bucket) {
            size_t newBucketId = static_cast<size_t>(pair.first) % newSize;
            newTable[newBucketId].push_back(pair);
        }
    }
    this->table = std::move(newTable);
    this->tableSize = newSize;
}

// Halves the table size (not below MIN_TABLE_SIZE) and rehashes all elements.
template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::resizeDown() {
    size_t newSize = this->tableSize / 2;
    if (newSize < MIN_TABLE_SIZE) {
        newSize = MIN_TABLE_SIZE;
    }
    std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(newSize);

    // Rehash each element into the new table.
    for (const auto& bucket : this->table) {
        for (const auto& pair : bucket) {
            size_t newBucketId = static_cast<size_t>(pair.first) % newSize;
            newTable[newBucketId].push_back(pair);
        }
    }
    this->table = std::move(newTable);
    this->tableSize = newSize;
}

// Constructor initializes the hash map with a given table size.
template<typename KeyType, typename ValueType>
HashMap< KeyType, ValueType>::HashMap(size_t size) : table(size), tableSize(size), numElements(0) { }

// Destructor clears all buckets and resets the table.
template<typename KeyType, typename ValueType>
HashMap< KeyType, ValueType>::~HashMap() {
    for (auto& bucket : this->table) {
        bucket.clear();
    }
    this->table.clear();
    this->numElements = 0;
}

// Returns the current load factor (elements/table size).
template<typename KeyType, typename ValueType>
double HashMap< KeyType, ValueType>::getLoadFactor() const {
    return static_cast<double>(this->numElements) / this->tableSize;
}

// Inserts a new key-value pair; resizes table if load factor exceeds maximum.
template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    if (contains(key)) return;

    if (getLoadFactor() > MAX_LOAD_FACTOR) {
        resizeUp();
    }
    size_t bucketId = hashFunction(key);
    this->table[bucketId].push_back(std::make_pair(key, value));
    this->numElements++;
}

// Removes the key-value pair associated with the given key.
template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::remove(const KeyType& key) {
    if (!contains(key)) return;

    size_t bucketId = hashFunction(key);
    auto& bucket = this->table[bucketId];
    for (auto it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            bucket.erase(it);
            this->numElements--;
            break;
        }
    }
    if (getLoadFactor() < MIN_LOAD_FACTOR) {
        resizeDown();
    }
}

// Returns a reference to the value for the given key; throws if not found.
template<typename KeyType, typename ValueType>
ValueType& HashMap< KeyType, ValueType>::get(const KeyType& key) {
    size_t bucketId = hashFunction(key);
    for (auto& pair : this->table[bucketId]) {
        if (pair.first == key)
            return pair.second;
    }
    throw std::out_of_range("Key not found");
}

// Checks if the key exists in the map.
template<typename KeyType, typename ValueType>
bool HashMap< KeyType, ValueType>::contains(const KeyType& key) const {
    size_t bucketId = hashFunction(key);

    for (const auto& pair : this->table[bucketId]) {
        if (pair.first == key)
            return true;
    }
    return false;
}

// Clears all elements from the hash map and resets the table.
template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::clear() {
    for (auto& bucket : this->table) {
        bucket.clear();
    }
    this->table.clear();
    this->table.resize(tableSize);
    this->numElements = 0;
}

// Returns the number of key-value pairs stored.
template<typename KeyType, typename ValueType>
size_t HashMap< KeyType, ValueType>::getSize() const {
    return this->numElements;
}

// Returns the current number of buckets in the table.
template<typename KeyType, typename ValueType>
size_t HashMap< KeyType, ValueType>::getTableSize() const {
    return this->table.size();
}

// Prints the content of each bucket for debugging.
template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::print() const {
    for (size_t i = 0; i < this->table.size(); i++) {
        std::cout << "Bucket " << i << ": ";
        for (const auto& pair : this->table[i]) {
            std::cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        std::cout << std::endl;
    }
}