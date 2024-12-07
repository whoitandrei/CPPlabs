#include <iostream>
#include <stdexcept>
#include <cstring>
#include <Windows.h>
#include "DATA.hpp"
#include "SoundProcessor.hpp"


int main(int argc, char** argv){
    try {
        DATA data(argc, argv);
        data.readTodo();
        SoundProcessor processor(&data);
        processor.process();
        std::cout << "\nall good!\npath of result file: .\\" << data.getOutputFile() << std::endl;
    }
    catch(const std::runtime_error& e){
        setConsoleColor(12,0);
        std::cerr << "fatal error: " << e.what() << std::endl;
        resetConsoleColor();
        std::cerr << "type -h to get more info" << std::endl;
        return 1;
    }
    catch (const std::logic_error& e){
        std::cerr << e.what() << std::endl;
        return 0;
    }
    
    return 0;
}