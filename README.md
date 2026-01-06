# LRU Cache Implementation in C++

A high-performance Least Recently Used (LRU) Cache implementation using a combination of a hash map and a doubly linked list for O(1) time complexity operations.

## Overview

An LRU Cache is a data structure that stores a fixed number of items and evicts the least recently used item when the cache reaches its capacity. This implementation provides efficient caching with constant time complexity for both insertion and retrieval operations.

## Requirements

The LRU cache supports the following operations:

- **`put(key, value)`**: Insert a key-value pair into the cache. If the cache is at capacity, remove the least recently used item before inserting the new item.
- **`get(key)`**: Get the value associated with the given key. If the key exists in the cache, move it to the front of the cache (most recently used) and return its value. If the key does not exist, throw a runtime error.
- **Fixed Capacity**: The cache has a fixed capacity, specified during initialization.
- **Thread Safety**: The cache is designed for thread-safe concurrent access from multiple threads.
- **Efficiency**: Both `put` and `get` operations have O(1) time complexity.

## Architecture

### Classes and Components

#### Node (`DoublyLinkedList.hpp`)
The `Node` class represents a node in the doubly linked list, containing:
- `key`: The key of the cached item
- `value`: The value of the cached item
- `prev`: Reference to the previous node
- `next`: Reference to the next node

#### DoublyLinkedList (`DoublyLinkedList.hpp`)
A generic doubly linked list implementation that provides:
- `addToFront()`: Add a new node at the head of the list
- `moveToFront()`: Move an existing node to the head
- `removeNode()`: Remove a specific node from the list
- `removeLast()`: Remove and return the tail node (least recently used)
- `getHead()` / `getTail()`: Access the head and tail nodes

#### LRUCache (`LRUCache.hpp`)
The main cache class that implements LRU cache functionality using:
- A hash map (`unordered_map`) for O(1) key lookup
- A doubly linked list for maintaining access order

**Methods:**
- `get(key)`: Retrieves the value associated with a given key. If the key exists, it is moved to the head of the linked list (most recently used) and its value is returned. If the key does not exist, a `runtime_error` is thrown.
- `put(key, value)`: Inserts a key-value pair into the cache. If the key already exists, its value is updated, and the node is moved to the head. If the key does not exist and the cache is at capacity, the least recently used item (at the tail) is removed, and the new item is inserted at the head.
- `contains(key)`: Check if a key exists in the cache
- `getSize()`: Get the current number of items in the cache
- `isEmpty()`: Check if the cache is empty
- `clear()`: Remove all items from the cache
- `display()`: Print the current cache contents

#### LRUCacheDemo (`LRUCacheDemo.cpp`)
Demonstrates the usage of the LRU cache by:
- Creating an instance of `LRUCache` with a capacity of 3
- Performing various `put` and `get` operations
- Printing the results and cache state

## Usage

### Compilation

```bash
g++ LRUCacheDemo.cpp -o LRUCacheDemo
```

### Running

```bash
./LRUCacheDemo
```

### Example Code

```cpp
#include "LRUCache.hpp"
#include <string>

int main() {
    // Create LRU cache with capacity 3
    LRUCache<int, std::string> cache(3);
    
    // Add entries
    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");
    
    // Get a value (moves it to front)
    std::string value = cache.get(2);  // Returns "Two"
    
    // Adding a new entry when full evicts LRU item
    cache.put(4, "Four");  // Evicts key 1 (least recently used)
    
    // Update existing entry
    cache.put(2, "Two Updated");
    
    return 0;
}
```

## Time Complexity

| Operation | Time Complexity |
|-----------|-----------------|
| `get()`   | O(1)            |
| `put()`   | O(1)            |
| `contains()` | O(1)         |
| `clear()` | O(n)            |

## Space Complexity

O(n) where n is the cache capacity

## How It Works

1. **Hash Map**: Provides O(1) access to cache nodes by key
2. **Doubly Linked List**: Maintains the order of items by recency of use
   - **Head**: Most recently used item
   - **Tail**: Least recently used item
3. **On Access (`get`)**: The accessed node is moved to the head
4. **On Insert (`put`)**: 
   - If key exists: Update value and move to head
   - If key doesn't exist and cache is full: Remove tail node, then insert at head
   - If key doesn't exist and cache has space: Insert at head

## File Structure

```
LRU CACHE/
├── DoublyLinkedList.hpp   # Doubly linked list implementation
├── LRUCache.hpp           # LRU Cache implementation
├── LRUCacheDemo.cpp       # Demo/test program
└── README.md              # This file
```

## License

This project is open source and available for educational purposes.
