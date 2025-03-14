#pragma once
#include <utility>   // For std::pair
#include <stdexcept>
#include <vector>
#include <list>
#include <iostream>


template<typename KeyType, typename ValueType>
class HashMap {
private:
    std::vector<std::list<std::pair<KeyType, ValueType>>> table;
    size_t tableSize;
    size_t numElements;

    const double MAX_LOAD_FACTOR = 0.7;
    const double MIN_LOAD_FACTOR = 0.3;
    const size_t MIN_TABLE_SIZE = 5;

    size_t hashFunction(const KeyType& key) const;

    void resizeUp();

    void resizeDown();

public:
    explicit HashMap(size_t size = 101);

    ~HashMap();

    double getLoadFactor() const;

    void insert(const KeyType& key, const ValueType& value);

    void remove(const KeyType& key);

    ValueType& get(const KeyType& key);

    bool contains(const KeyType& key) const;

    void clear();

    size_t getSize() const;

    size_t getTableSize() const;

    void print() const;
};