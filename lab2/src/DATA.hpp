#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include "consoleColor.hpp"

class DATA
{
public:
    struct COMMAND
    {
        std::string name;
        int filenum;
        int start;
        int end;
    };

    DATA(int argc, char** argv);
    ~DATA();
    void readTodo();
    const std::vector<std::string> getInputFiles() const;
    const std::string getOutputFile();
    const std::string getTodoFile();
    const std::vector<COMMAND> getCommands();

private:
    std::vector<std::string> inputFilesPathes;
    std::string outputFilePath;
    std::string todoFilePath;
    std::vector<COMMAND> commands;
    int argc;
    char** argv;

    void checkInputArguments();

};


