#include "..\includes\FlatMap.h"

int main() {
    FlatMap<int, int> map;

    map[1] = 10;
    map[2] = 20;

    std::cout << "Size: " << map.size() << std::endl;

    for (auto element : map) {
        std::cout << element.key << ": " << element.value << std::endl;
    }

    map.erase(2);
    std::cout << "Size after erase: " << map.size() << std::endl;

    return 0;
}