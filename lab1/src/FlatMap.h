#pragma once 
#include <iostream>
#include <string>
#include <sstream>

// ничего нет в глоб области видимости , реализация должна быть в cpp , че такое виртуальная функция и зачем нужен виртуальный деструктор

class FlatMap {
private:
    struct element { 
        std::string key;
        std::string value;
    };

    element* map;
    std::size_t map_size;
    std::size_t capacity;

    void resize(short delta);
    std::size_t binarySearch(const std::string& key) const;

public:
    FlatMap() : map_size(0), capacity(0), map(nullptr) {}
    FlatMap(const FlatMap& other_map);
    virtual ~FlatMap();
    FlatMap& operator=(const FlatMap& other_map);
    std::size_t size() const;
    std::string& operator[](const std::string& key);
    bool contains(const std::string& key);
    std::size_t erase(const std::string& key);
    void clear();
};

class A : public FlatMap {
public:
    ~A() override {};
};