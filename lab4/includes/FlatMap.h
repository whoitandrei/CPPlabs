#include <string>
#include <iostream>

template <class Key, class Value>
class FlatMap {
private:
    struct Element {
        Key key;
        Value value;
    };

    Element* map;      
    std::size_t map_size;  
    std::size_t capacity;  

    void resize(short delta);
    std::size_t binarySearch(const Key& key) const;

public:
    FlatMap() : map(nullptr), map_size(0), capacity(0) {}
    FlatMap(const FlatMap& other_map);
    ~FlatMap();
    FlatMap& operator=(const FlatMap& other_map);
    std::size_t size() const;
    Value& operator[](const Key& key);
    bool contains(const Key& key);
    std::size_t erase(const Key& key);
    void clear();

    class iterator {
    private:
        Element* ptr;
    public:
        iterator(Element* p) : ptr(p) {}
        iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        Element& operator*() const { return *ptr; }
    };

    iterator begin() { return iterator(map); }
    iterator end() { return iterator(map + map_size); }
};



template <class Key, class Value>
void FlatMap<Key, Value>::resize(short delta) {
    Element* new_map = new Element[map_size + delta];
    for (std::size_t i = 0; i < map_size; ++i) {
        new_map[i] = map[i];
    }
    delete[] map;
    map = new_map;
    capacity += delta;
}

template <class Key, class Value>
std::size_t FlatMap<Key, Value>::binarySearch(const Key& key) const {
    std::size_t left = 0;
    std::size_t right = map_size;
    while (left < right) {
        std::size_t mid = left + (right - left) / 2;
        if (map[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

template <class Key, class Value>
FlatMap<Key, Value>::FlatMap(const FlatMap& other_map) : capacity(other_map.capacity), map_size(other_map.map_size) {
    map = new Element[map_size];
    for (std::size_t i = 0; i < map_size; ++i) {
        map[i] = other_map.map[i];
    }
}

template <class Key, class Value>
FlatMap<Key, Value>::~FlatMap() {
    delete[] map;
}

template <class Key, class Value>
FlatMap<Key, Value>& FlatMap<Key, Value>::operator=(const FlatMap& other_map) {
    if (this != &other_map) {
        delete[] map;
        map_size = other_map.map_size;
        capacity = other_map.capacity;
        map = new Element[map_size];
        for (std::size_t i = 0; i < map_size; ++i) {
            map[i] = other_map.map[i];
        }
    }
    return *this;
}

template <class Key, class Value>
std::size_t FlatMap<Key, Value>::size() const {
    return map_size;
}

template <class Key, class Value>
Value& FlatMap<Key, Value>::operator[](const Key& key) {
    std::size_t index = binarySearch(key);
    if (index < map_size && map[index].key == key) {
        return map[index].value;
    } else {
        if (map_size == capacity)
            resize(1);
        for (std::size_t i = map_size; i > index; --i) {
            map[i] = map[i - 1];
        }
        map[index].key = key;
        map[index].value = Value();
        ++map_size;
        return map[index].value;
    }
}

template <class Key, class Value>
bool FlatMap<Key, Value>::contains(const Key& key) {
    std::size_t index = binarySearch(key);
    return index < map_size && map[index].key == key;
}

template <class Key, class Value>
std::size_t FlatMap<Key, Value>::erase(const Key& key) {
    std::size_t index = binarySearch(key);
    if (index < map_size && map[index].key == key) {
        for (std::size_t i = index; i < map_size - 1; ++i) {
            map[i] = map[i + 1];
        }
        --map_size;
        return 1;
    }
    return 0;
}

template <class Key, class Value>
void FlatMap<Key, Value>::clear() {
    delete[] map;
    map = nullptr;
    map_size = 0;
}
