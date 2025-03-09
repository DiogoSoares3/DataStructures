#include <utility>   // For std::pair
#include <stdexcept>
#include <vector>
#include <list>
#include <iostream>
#include "hashMap.h"

template<typename KeyType, typename ValueType>
size_t HashMap< KeyType, ValueType>::hashFunction(const KeyType& key) const {
    return static_cast<size_t>(key) % tableSize;
}

template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::resizeUp() {
    size_t newSize = tableSize * 2;
    std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(newSize);

    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            size_t newBucketId = static_cast<size_t>(pair.first) % newSize;
            newTable[newBucketId].push_back(pair);
        }
    }
    table = std::move(newTable);
    tableSize = newSize;
}

template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::resizeDown() {
    size_t newSize = tableSize / 2;
    if (newSize < MIN_TABLE_SIZE) {
        newSize = MIN_TABLE_SIZE;
    }
    std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(newSize);

    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            size_t newBucketId = static_cast<size_t>(pair.first) % newSize;
            newTable[newBucketId].push_back(pair);
        }
    }
    table = std::move(newTable);
    tableSize = newSize;
}

template<typename KeyType, typename ValueType>
HashMap< KeyType, ValueType>::HashMap(size_t size = 101) : table(size), tableSize(size), numElements(0) { }

template<typename KeyType, typename ValueType>
HashMap< KeyType, ValueType>::~HashMap() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    table.clear();
    numElements = 0;
}

template<typename KeyType, typename ValueType>
double HashMap< KeyType, ValueType>::getLoadFactor() const {
    return static_cast<double>(numElements) / tableSize;
}

template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    if (contains(key)) return;

    if (getLoadFactor() > MAX_LOAD_FACTOR) {
        resizeUp();
    }
    size_t bucketId = hashFunction(key);
    table[bucketId].push_back(std::make_pair(key, value));
    numElements++;
}

template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::remove(const KeyType& key) {
    if (!contains(key)) return;

    size_t bucketId = hashFunction(key);
    auto& bucket = table[bucketId];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            numElements--;
            break;
        }
    }
    if (getLoadFactor() < MIN_LOAD_FACTOR) {
        resizeDown();
    }
}

template<typename KeyType, typename ValueType>
ValueType& HashMap< KeyType, ValueType>::get(const KeyType& key) {
    size_t bucketId = hashFunction(key);
    for (auto& pair : table[bucketId]) {
        if (pair.first == key)
            return pair.second;
    }
    throw std::out_of_range("Key not found");
}

template<typename KeyType, typename ValueType>
bool HashMap< KeyType, ValueType>::contains(const KeyType& key) const {
    size_t bucketId = hashFunction(key);
    for (const auto& pair : table[bucketId]) {
        if (pair.first == key)
            return true;
    }
    return false;
}

template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::clear() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    table.clear();
    table.resize(tableSize);
    numElements = 0;
}

template<typename KeyType, typename ValueType>
size_t HashMap< KeyType, ValueType>::getSize() const {
    return numElements;
}

template<typename KeyType, typename ValueType>
void HashMap< KeyType, ValueType>::print() const {
    for (size_t i = 0; i < table.size(); i++) {
        std::cout << "Bucket " << i << ": ";
        for (const auto& pair : table[i]) {
            std::cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        std::cout << std::endl;
    }
}
