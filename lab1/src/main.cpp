#include <memory>
#include "FlatMap.h"


int main() {
    FlatMap map;
    /*std::cout << student["key"] << std::endl;
    student["first_name"] = "Ivan";
    student["last_name"] = "Petrov";
    student["university"] = "NSU";
    student["department"] = "FIT";
    student["group"] = "...";
    student["first_name"] = "Egor";
    */
    int n;
    std::cout << "how many values do you want to add: ";
    std::cin >> n;
    std::cin.ignore();
    std::cout << "input format - key value splitted by space: [key] [val]\n\n";

    for (int i = 0; i < n; ++i){
        std::string key;
        std::string val;

        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input); 
       
        if (iss >> key >> val) {
            map[key] = val;
        } else {
            std::cout << "error: input two strings splitted by space. this string is not added to [map]" << std::endl;
            i--;
        }
    }

    int m;
    std::cout << "how many values you want to print: ";
    std::cin >> m;
    std::cin.ignore();
    std::cout << std::endl;

    for (int i = 0; i < m; ++i){
        std::string key;
        std::getline(std::cin, key);
        
        if (map.contains(key)){
            std::cout << key << " : " << map[key] << std::endl <<std::endl;
        }
        else {
            std::cout << "this (" << key << ") key doesn't exist! try another." << std::endl;
        }
    }

    return 0;
}