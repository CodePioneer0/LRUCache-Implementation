#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include "DoublyLinkedList.hpp"

using namespace std;

template<typename K, typename V>
class LRUCache {
private:
    int capacity;
    DoublyLinkedList<K,V> dll;
    unordered_map<K, Node<K,V>*> cache;

public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    V get(K key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            throw runtime_error("Key not found");
        }
        
        Node<K,V>* node = it->second;
        dll.moveToFront(node);
        return node->value;
    }
    
    void put(K key, V value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            // Key exists, update value and move to front
            Node<K,V>* node = it->second;
            node->value = value;
            dll.moveToFront(node);
        } else {
            // Key doesn't exist, add new entry
            if (cache.size() >= capacity) {
                // Remove least recently used item
                Node<K,V>* lastNode = dll.getTail();
                cache.erase(lastNode->key);
                dll.removeNode(lastNode);
            }
            
            // Add new item to front
            Node<K,V>* newNode = dll.addToFront(key, value);
            cache[key] = newNode;
        }
    }
    
    bool contains(K key) const {
        return cache.find(key) != cache.end();
    }
    
    int getSize() const {
        return cache.size();
    }
    
    bool isEmpty() const {
        return cache.empty();
    }
    
    void clear() {
        while (!dll.isEmpty()) {
            Node<K,V>* node = dll.removeLast();
            cache.erase(node->key);
            delete node;
        }
    }
    
    void display() const {
        cout << "\nLRU Cache Contents:" << endl;
        Node<K,V>* current = dll.getHead();
        while (current) {
            cout << current->key << " -> " << current->value << endl;
            current = current->next;
        }
        cout << "Cache size: " << cache.size() << "/" << capacity << endl;
    }
};

#endif 