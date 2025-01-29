#include <unordered_map>
#include <list>
#include <iostream>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList; // {key, value}
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap;

public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }
        
        // Mueve al frente (más reciente)
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        return cacheMap[key]->second;
    }
    
    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key]->second = value;
            return;
        }
        
        if (cacheList.size() == capacity) {
            int lruKey = cacheList.back().first;
            cacheMap.erase(lruKey);
            cacheList.pop_back();
        }
        
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }
};

int main() {
    LRUCache lru(2);
    lru.put(1, 10);
    lru.put(2, 20);
    std::cout << lru.get(1) << "\n";
    lru.put(3, 30);
    std::cout << lru.get(2) << "\n";
    lru.put(4, 40);
    std::cout << lru.get(1) << "\n";
    std::cout << lru.get(3) << "\n";
    std::cout << lru.get(4) << "\n";
    return 0;
}
