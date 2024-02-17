#include <iostream>
#include <list>
#include <vector>

// Hash table class
template<typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
private:
    // Define the bucket type as a list of key-value pairs
    using Bucket = std::list<std::pair<Key, Value>>;
    // Vector of buckets to store the hash table
    std::vector<Bucket> table;
    // Hash function object
    Hash hashFunc;
    // Number of buckets in the hash table
    size_t numBuckets;

public:
    // Constructor with specified number of buckets
    HashTable(size_t size = 10) : numBuckets(size), table(size) {}

    // Function to insert a key-value pair into the hash table
    void insert(const Key& key, const Value& value) {
        // Calculate hash value
        size_t hashValue = hashFunc(key);
        // Map hash value to the index of the bucket
        size_t index = hashValue % numBuckets;
        // Search for the key in the bucket
        for (auto& kvp : table[index]) {
            if (kvp.first == key) {
                // Key already exists, update its value
                kvp.second = value;
                return;
            }
        }
        // Key doesn't exist, insert new key-value pair
        table[index].emplace_back(key, value);
    }

    // Function to retrieve the value associated with a key
    Value get(const Key& key) {
        // Calculate hash value
        size_t hashValue = hashFunc(key);
        // Map hash value to the index of the bucket
        size_t index = hashValue % numBuckets;
        // Search for the key in the bucket
        for (const auto& kvp : table[index]) {
            if (kvp.first == key) {
                // Key found, return its value
                return kvp.second;
            }
        }
        // Key not found, return a default-constructed value
        // Note: This may not be ideal for all value types
        // You may want to throw an exception or return a special value indicating absence
        return Value();
    }

    // Function to remove a key-value pair from the hash table
    void remove(const Key& key) {
        // Calculate hash value
        size_t hashValue = hashFunc(key);
        // Map hash value to the index of the bucket
        size_t index = hashValue % numBuckets;
        // Search for the key in the bucket
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                // Key found, erase it from the bucket
                bucket.erase(it);
                return;
            }
        }
    }
};

int main() {
    // Example usage
    HashTable<std::string, int> ht;
    ht.insert("apple", 10);
    ht.insert("banana", 20);

    std::cout << "Value for key 'apple': " << ht.get("apple") << std::endl;
    std::cout << "Value for key 'banana': " << ht.get("banana") << std::endl;

    ht.remove("apple");

    std::cout << "Value for key 'apple' after removal: " << ht.get("apple") << std::endl;

    return 0;
}
