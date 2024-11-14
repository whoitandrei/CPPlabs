#include <iostream>
#include <string>

struct element {
    std::string key;
    std::string value;
};

class FlatMap {

private:
    element* map;
    std::size_t map_size;
    std::size_t capacity;

    void resize(short delta) {
        element* new_map = new element[map_size + delta];
        for (std::size_t i = 0; i < map_size; ++i) {
            new_map[i] = map[i];
        }
        delete[] map;
        map = new_map;
        capacity += delta;
    }

    std::size_t binarySearch(const std::string& key) const {
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

public:
    FlatMap() : map_size(0), capacity(0), map(nullptr) {}

    FlatMap(const FlatMap& other_map) : capacity(other_map.capacity), map_size(other_map.map_size) {
        map = new element[map_size];
        for (std::size_t i = 0; i < map_size; ++i) {
            map[i] = other_map.map[i];
        }
    }

    ~FlatMap() {
        map_size = 0;
        capacity = 0;
        delete[] map;
    }

    FlatMap& operator=(const FlatMap& other_map) {
        if (this != &other_map) {
            delete[] map;
            map_size = other_map.map_size;
            capacity = other_map.capacity;
            map = new element[map_size];
            for (std::size_t i = 0; i < map_size; ++i) {
                map[i] = other_map.map[i];
            }
        }
        return *this;
    }

    std::size_t size() const {
        return map_size;
    }

    std::string& operator[](const std::string& key) {
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
            map[index].value = "";
            ++map_size;
            return map[index].value;
        }
    }

    bool contains(const std::string& key) {
        std::size_t index = binarySearch(key);
        return index < map_size && map[index].key == key;
    }

    std::size_t erase(const std::string& key) {
        std::size_t index = binarySearch(key);
        if (index < map_size && map[index].key == key) {
            for (std::size_t i = index; i < map_size - 1; ++i) {
                map[i] = map[i + 1];
            }
            --map_size;
            //resize(-1); 
            return 1;
        }
        return 0;
    }

    void clear() {
        if (map != nullptr){
            delete[] map;
        }
        map = nullptr;
        map_size = 0;
    }

};

