# Hash Tables in C++

This project contains two implementations of hash tables in C++:

- **HashSet:** Stores unique values (in this example, integers).
- **HashMap:** Stores key-value pairs, functioning as a dictionary.

Both implementations use vectors of lists (called "buckets") to handle collisions and employ a resizing policy based on the load factor to maintain optimal performance.

---

## 1. What Are Hash Tables?

A **hash table** is an advanced data structure that provides an efficient mapping from keys to values using a hash function. Here are some in-depth aspects:

- **Fundamental Concept:**  
  A hash table leverages a hash function to compute an index into an array of buckets or slots, from which the desired value can be quickly retrieved. The hash function converts the key into an integer that is then mapped to a valid index using a modulus operation with the table size.

- **Collision Handling:**  
  When different keys produce the same hash index—a situation known as a collision—hash tables must have a strategy to manage them. Two common approaches are:
  - **Chaining:**  
    Each bucket is implemented as a linked list (or similar structure) that holds all entries mapping to that index. This project uses chaining, allowing multiple entries in the same bucket.
  - **Open Addressing:**  
    All entries are stored within the array itself, and collisions are resolved by probing for an alternative slot (using linear, quadratic, or double hashing).  
    *Note:* Open addressing is not used in this project but is a viable alternative in other contexts.

- **Performance Characteristics:**  
  With a well-designed hash function and proper resizing:
  - **Average Case:** Operations such as insertion, deletion, and search have an expected time complexity of O(1).
  - **Worst Case:** In extreme scenarios (e.g., many collisions), performance may degrade to O(n), though this is rare when using a good hash function and dynamic resizing.

- **Applications in Modern Computing:**  
  Hash tables are critical in various domains, including compiler design (symbol tables), databases (indexing), networking (routing tables), and many high-performance applications where rapid data retrieval is essential.

---

## 2. Use Cases

Hash tables are highly versatile and form the backbone of many real-world applications. Their fast access times and efficient data management make them ideal for a wide array of scenarios:

- **HashSet:**
  - **Purpose:**  
    To store a collection of unique elements by ensuring no duplicates are present.
  - **Common Applications:**
    - **Data Deduplication:**  
      Quickly eliminating duplicate values from large datasets.
    - **Membership Testing:**  
      Efficiently checking whether an element exists within a collection, useful in spell checkers, security systems (e.g., checking for compromised passwords), and more.
    - **Set Operations:**  
      Enabling mathematical operations like union, intersection, and difference between sets, which is fundamental in various algorithms.
    - **Real-Time Processing:**  
      Often used in systems that require immediate verification of unique identifiers, such as user session tracking or streaming data analysis.

- **HashMap:**
  - **Purpose:**  
    To provide a mapping from keys to values, allowing for quick and efficient retrieval of information.
  - **Common Applications:**
    - **Caching:**  
      Storing results of expensive computations or frequently accessed data to speed up retrieval times in web servers, database systems, and application backends.
    - **Symbol Tables:**  
      Widely used in compilers and interpreters to associate variable names with memory addresses or values.
    - **Configuration Management:**  
      Managing configuration settings where each key represents a configuration parameter and its corresponding value.
    - **Dynamic Data Management:**  
      Supporting algorithms that require frequent updates and lookups, such as those used in graph algorithms, real-time analytics, or even artificial intelligence applications.
    - **Database Indexing:**  
      Providing fast lookups for database records, which is crucial for performance in large-scale data storage systems.

---

## 3. Key Methods and Features

### Common Methods

- **`hashFunction`:**  
  Computes the index (bucket) for a given value or key. Typically, the modulus operator (e.g., `value % tableSize`) is used to determine the position in the table.

- **Resizing Policy:**  
  To maintain performance, hash tables are resized based on the **load factor**:
  - **Load Factor:**  
    Load factor is equal the number of elements divided by the hash table size.
  - **`resizeUp`:**  
    If the load factor exceeds a maximum limit (`MAX_LOAD_FACTOR`), the table size is doubled. All elements are rehashed into the new structure.
  - **`resizeDown`:**  
    If the load factor drops below a minimum limit (`MIN_LOAD_FACTOR`), the table is shrunk (usually by half), respecting a minimum table size (`MIN_TABLE_SIZE`).

- **`clear`:**  
  Removes all elements from the table by clearing each bucket and resetting counters.

- **`print`:**  
  A debugging method that displays the content of each bucket, making it easier to visualize the distribution of elements.

---

### HashSet

**Description:**  
Implements a set of unique values (in this example, integers). The internal structure uses a `std::vector<std::list<int>>` to store the elements and manage collisions.

**Key Methods:**

- **`hashFunction(const int& value)`:**  
  Calculates the index for the value using `value % tableSize`.

- **`insert(const int& value)`:**  
  - Checks if the value is already present using `containsValue`.
  - If the load factor exceeds `MAX_LOAD_FACTOR`, it calls `resizeUp` to double the table size.
  - Inserts the value into the calculated bucket and increments the element counter.

- **`remove(const int& value)`:**  
  - Checks if the value exists; if it does, it removes it from the corresponding bucket.
  - If the load factor falls below `MIN_LOAD_FACTOR`, it calls `resizeDown` to reduce the table size.
  - Updates the element counter by removing the found value.

- **`containsValue(const int& value)`:**  
  Iterates through the bucket determined by the hash function and returns `true` if the value is found, or `false` otherwise.

- **`getLoadFactor()`:**  
  Returns the ratio of the number of elements to the table size, allowing a decision on whether to resize.

- **Additional Methods:**  
  Methods such as `clear()`, `getSize()`, and `print()` help to clear the table, return the number of elements, and display the buckets, respectively.

---

### HashMap

**Description:**  
Implements a key-value mapping using a `std::vector<std::list<std::pair<KeyType, ValueType>>>`. This structure is ideal for associating data (value) with identifiers (key).

**Key Methods:**

- **`hashFunction(const KeyType& key)`:**  
  Computes the bucket index for a key using `static_cast<size_t>(key) % tableSize`.

- **`insert(const KeyType& key, const ValueType& value)`:**  
  - Checks if the key already exists using `contains`.
  - If the load factor exceeds `MAX_LOAD_FACTOR`, it performs a `resizeUp`.
  - Inserts the pair (key, value) into the appropriate bucket and increments the element count.

- **`remove(const KeyType& key)`:**  
  - Finds the corresponding bucket for the key and removes the found pair.
  - If the load factor falls below `MIN_LOAD_FACTOR`, it calls `resizeDown`.
  - Updates the element counter.

- **`get(const KeyType& key)`:**  
  Iterates through the bucket and returns a reference to the value associated with the key. If the key is not found, it throws an exception (`std::out_of_range`).

- **`contains(const KeyType& key)`:**  
  Checks if the key exists in the calculated bucket and returns `true` or `false`.

- **Additional Methods:**  
  Functions like `getLoadFactor()`, `clear()`, `getSize()`, and `print()` provide support for monitoring table usage, clearing data, and displaying content.

---

## 4. Resizing Policy with Load Factor

The **resizing policy** aims to maintain the hash table's optimal performance:

- **When to Increase Size (`resizeUp`):**  
  If the load factor (number of elements divided by table size) exceeds a maximum limit (`MAX_LOAD_FACTOR`), the table is resized to a larger size (usually doubled). This reduces collisions and improves the efficiency of search and insertion operations.

- **When to Decrease Size (`resizeDown`):**  
  If the load factor falls below a minimum limit (`MIN_LOAD_FACTOR`), the table is shrunk (typically halved) to free memory, without dropping below a predefined minimum size (`MIN_TABLE_SIZE`).

This strategy ensures that the hash table remains balanced between memory usage and performance, dynamically adapting as the number of elements changes.

---

## 5. Conclusion

Hash tables are essential data structures for applications requiring quick and efficient access to elements.  
- **HashSet** is ideal for maintaining a set of unique elements and performing rapid existence checks.  
- **HashMap** offers a practical way to associate keys with values, simplifying the implementation of dictionaries, caches, and mapping systems.

The implementations presented demonstrate how to use hash functions, handle collisions with buckets, and apply resizing policies based on the load factor to optimize performance. These techniques are widely used in algorithms, databases, cache systems, and many other areas of computing.
