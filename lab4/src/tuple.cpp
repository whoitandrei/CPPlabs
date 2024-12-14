#include "..\includes\tuple.h"


int main(){
    std::tuple<int, std::string, bool> test = {1, "abc", true};
    std::cout << test;
}