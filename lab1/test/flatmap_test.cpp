#include <gtest/gtest.h>
#include "D:\NSU\prog\C++\labs\lab1\src\FlatMap.h"

// Тестирование конструктора по умолчанию
TEST(FlatMapTest, DefaultConstructor) {
    FlatMap map;
    EXPECT_EQ(map.size(), 0);
}

// Тестирование конструктора копирования
TEST(FlatMapTest, CopyConstructor) {
    FlatMap map1;
    map1["key1"] = "value1";
    map1["key2"] = "value2";

    FlatMap map2(map1);
    EXPECT_EQ(map2.size(), 2);
    EXPECT_EQ(map2["key1"], "value1");
    EXPECT_EQ(map2["key2"], "value2");
}

// Тестирование оператора присваивания
TEST(FlatMapTest, AssignmentOperator) {
    FlatMap map1;
    map1["key1"] = "value1";
    
    FlatMap map2;
    map2 = map1;
    EXPECT_EQ(map2.size(), 1);
    EXPECT_EQ(map2["key1"], "value1");
}

// Тестирование добавления элемента
TEST(FlatMapTest, AddElement) {
    FlatMap map;
    map["key1"] = "value1";
    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map["key1"], "value1");
}

// Тестирование добавления нескольких элементов
TEST(FlatMapTest, AddMultipleElements) {
    FlatMap map;
    map["key1"] = "value1";
    map["key2"] = "value2";
    EXPECT_EQ(map.size(), 2);
    EXPECT_EQ(map["key2"], "value2");
}

// Тестирование поиска существующего элемента
TEST(FlatMapTest, ContainsExistingKey) {
    FlatMap map;
    map["key1"] = "value1";
    EXPECT_TRUE(map.contains("key1"));
}

// Тестирование поиска несуществующего элемента
TEST(FlatMapTest, ContainsNonExistingKey) {
    FlatMap map;
    EXPECT_FALSE(map.contains("key1"));
}

// Тестирование удаления существующего элемента
TEST(FlatMapTest, EraseExistingKey) {
    FlatMap map;
    map["key1"] = "value1";
    EXPECT_EQ(map.erase("key1"), 1);
    EXPECT_EQ(map.size(), 0);
}

// Тестирование удаления несуществующего элемента
TEST(FlatMapTest, EraseNonExistingKey) {
    FlatMap map;
    map["key1"] = "value1";
    EXPECT_EQ(map.erase("key2"), 0);
}

// Тестирование очистки map
TEST(FlatMapTest, ClearMap) {
    FlatMap map;
    map["key1"] = "value1";
    map.clear();
    EXPECT_EQ(map.size(), 0);
}

// Тестирование добавления элемента с существующим ключом
TEST(FlatMapTest, AddExistingKey) {
    FlatMap map;
    map["key1"] = "value1";
    map["key1"] = "value2"; 
    EXPECT_EQ(map["key1"], "value2");
}

// Тестирование добавления элементов в разном порядке
TEST(FlatMapTest, AddElementsInReverseOrder) {
    FlatMap map;
    map["key2"] = "value2";
    map["key1"] = "value1"; 
    EXPECT_EQ(map.size(), 2);
    EXPECT_EQ(map["key1"], "value1");
    EXPECT_EQ(map["key2"], "value2");
}

TEST(FlatMapTest, AddElementsInOrder) {
    FlatMap map;
    map["key1"] = "value1";
    map["key2"] = "value2"; 
    EXPECT_EQ(map.size(), 2);
    EXPECT_EQ(map["key1"], "value1");
    EXPECT_EQ(map["key2"], "value2");
}

// Тестирование поиска по ключу, который не был добавлен
TEST(FlatMapTest, GetNonExistingKey) {
    FlatMap map;
    EXPECT_EQ(map["key1"], "");
}

// Тестирование добавления и получения значений с пробелами в ключах
TEST(FlatMapTest, AddKeyWithSpaces) {
    FlatMap map;
    map["key with spaces"] = "value1";
    EXPECT_EQ(map["key with spaces"], "value1");
}

// Тестирование добавления и получения значений с пустыми ключами
TEST(FlatMapTest, AddEmptyKey) {
    FlatMap map;
    map[""] = "value1"; 
    EXPECT_EQ(map[""], "value1");
}

// Тестирование добавления и получения значений с длинными ключами
TEST(FlatMapTest, AddLongKey) {
    FlatMap map;
    std::string long_key(1000, 'a'); 
    map[long_key] = "value1";
    EXPECT_EQ(map[long_key], "value1");
}


// Тестирование самоприсваивания
TEST(FlatMapTest, SelfAssignment) {
    FlatMap map;
    map["key1"] = "value1";
    map = map; // Проверяем, что самоприсваивание не вызывает ошибок        
    EXPECT_EQ(map.size(), 1);
}

// Тестирование работы с большим количеством элементов
TEST(FlatMapTest, LargeNumberOfElements) {
    FlatMap map;
    for (int i = 0; i < 1000; ++i) {
        map["key" + std::to_string(i)] = "value" + std::to_string(i);
    }
    EXPECT_EQ(map.size(), 1000);
    EXPECT_EQ(map["key777"], "value777");
}

// Тестирование работы с элементами, содержащими пробелы и специальные символы
TEST(FlatMapTest, AddKeyWithSpecialCharacters) {
    FlatMap map;
    map["key with spaces & special!@#"] = "value!@";
    EXPECT_EQ(map["key with spaces & special!@#"], "value!@");
}

// Тестирование работы с пустой map
TEST(FlatMapTest, EmptyMap) {
    FlatMap map;
    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.contains("key"));
}

// Тестирование работы с map после очистки
TEST(FlatMapTest, ClearAfterAdding) {
    FlatMap map;
    map["key1"] = "value1";
    map.clear();
    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.contains("key1"));
}

// Тестирование работы с map после удаления всех элементов
TEST(FlatMapTest, EraseAllElements) {
    FlatMap map;
    map["key1"] = "value1";
    map["key2"] = "value2";
    map.erase("key1");
    map.erase("key2");
    EXPECT_EQ(map.size(), 0);
}

