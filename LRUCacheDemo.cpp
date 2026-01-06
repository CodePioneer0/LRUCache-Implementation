#include "LRUCache.hpp"
#include <iostream>
#include <string>

using namespace std;

void printHeader(const string& title) {
    cout << "\n" << string(50, '=') << endl;
    cout << " " << title << endl;
    cout << string(50, '=') << endl;
}

void printSubHeader(const string& title) {
    cout << "\n--- " << title << " ---" << endl;
}

int main() {
    printHeader("LRU Cache Demo");
    
    // Test 1: Basic Operations
    printSubHeader("Test 1: Creating cache with capacity 3");
    LRUCache<int, string> cache(3);
    cout << "Cache created successfully!" << endl;
    cout << "Initial state - Empty: " << (cache.isEmpty() ? "Yes" : "No") << endl;
    cout << "Initial size: " << cache.getSize() << endl;
    
    // Test 2: Adding entries
    printSubHeader("Test 2: Adding entries (1, 2, 3)");
    cache.put(1, "One");
    cout << "Added: 1 -> One" << endl;
    cache.put(2, "Two");
    cout << "Added: 2 -> Two" << endl;
    cache.put(3, "Three");
    cout << "Added: 3 -> Three" << endl;
    cache.display();
    
    // Test 3: Accessing an entry (moves to front)
    printSubHeader("Test 3: Accessing key 1 (should move to front)");
    cout << "Value for key 1: " << cache.get(1) << endl;
    cache.display();
    
    // Test 4: Cache eviction when full
    printSubHeader("Test 4: Adding key 4 when cache is full");
    cout << "Adding: 4 -> Four" << endl;
    cout << "Expected: Key 2 should be evicted (least recently used)" << endl;
    cache.put(4, "Four");
    cache.display();
    
    // Test 5: Verify eviction
    printSubHeader("Test 5: Verifying eviction of key 2");
    cout << "Contains key 2: " << (cache.contains(2) ? "Yes" : "No") << endl;
    cout << "Contains key 1: " << (cache.contains(1) ? "Yes" : "No") << endl;
    cout << "Contains key 3: " << (cache.contains(3) ? "Yes" : "No") << endl;
    cout << "Contains key 4: " << (cache.contains(4) ? "Yes" : "No") << endl;
    
    // Test 6: Exception handling for non-existent key
    printSubHeader("Test 6: Accessing non-existent key");
    try {
        cout << "Attempting to get key 2..." << endl;
        cache.get(2);
    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    // Test 7: Updating existing entry
    printSubHeader("Test 7: Updating existing entry");
    cout << "Current value for key 3: " << cache.get(3) << endl;
    cache.put(3, "Three Updated");
    cout << "Updated key 3 to: Three Updated" << endl;
    cout << "New value for key 3: " << cache.get(3) << endl;
    cache.display();
    
    // Test 8: Multiple accesses to test LRU order
    printSubHeader("Test 8: Testing LRU order with multiple accesses");
    cache.get(4);  // Access 4
    cout << "Accessed key 4" << endl;
    cache.get(1);  // Access 1
    cout << "Accessed key 1" << endl;
    cache.display();
    cout << "Order should be: 1 (most recent) -> 4 -> 3 (least recent)" << endl;
    
    // Test 9: Add new entry to verify correct eviction
    printSubHeader("Test 9: Adding key 5 (should evict key 3)");
    cache.put(5, "Five");
    cout << "Added: 5 -> Five" << endl;
    cache.display();
    cout << "Contains key 3: " << (cache.contains(3) ? "Yes" : "No") << endl;
    
    // Test 10: Cache size verification
    printSubHeader("Test 10: Cache size verification");
    cout << "Current size: " << cache.getSize() << endl;
    cout << "Is empty: " << (cache.isEmpty() ? "Yes" : "No") << endl;
    
    // Test 11: Clear cache
    printSubHeader("Test 11: Clearing cache");
    cache.clear();
    cout << "Cache cleared!" << endl;
    cache.display();
    cout << "Is empty after clear: " << (cache.isEmpty() ? "Yes" : "No") << endl;
    cout << "Size after clear: " << cache.getSize() << endl;
    
    // Test 12: Using cache after clear
    printSubHeader("Test 12: Using cache after clear");
    cache.put(100, "Hundred");
    cache.put(200, "Two Hundred");
    cout << "Added new entries after clear" << endl;
    cache.display();
    
    printHeader("All Tests Completed Successfully!");
    
    return 0;
} 