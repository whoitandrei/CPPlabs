#include "DATA.hpp"

DATA::DATA(int argc, char** argv) : argc(argc), argv(argv) {
    checkInputArguments();
    for (int i = 1; i < argc - 2; ++i) {
        if (strncmp(argv[i] + strlen(argv[i]) - 4, ".wav", 4) != 0){
            throw std::runtime_error("not .wav file: " + (std::string)argv[i]);
        }
        inputFilesPathes.push_back(argv[i]);
    }
    outputFilePath = argv[argc - 2];
    todoFilePath = argv[argc - 1];
}
DATA::~DATA() {}

void DATA::readTodo(){
    std::ifstream file(todoFilePath);
    if (!file){
        throw std::runtime_error("error opening todo file" + todoFilePath);
    }

    std::string line;
    size_t lineCount = 1;
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        COMMAND cmd;
        cmd.name = command;
        setConsoleColor(6,0);

        if (command == "mute"){
            int start, end;
            if (iss >> start >> end){
                if (start < 0){
                    std::cout << "in mute command detected negative start second " << start<< "\nwill be applied from 0 second" << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl << std::endl;
                    start = 0;
                }
                if (start < end){
                    cmd.start = start;
                    cmd.end = end;
                    commands.push_back(cmd);
                }
                else {
                    std::cerr << "invalid arguments for mute " << start << end << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
                }
            }
            else {
                std::cerr << "cannot read values for mute command!\ncommand will be not applied " << std::endl;
                std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
            }

        }
        else if (command == "mix"){
            int filenum, start, end;
            if (iss >> filenum >> start >> end){
                if (filenum < 1 || filenum > inputFilesPathes.size()){
                    std::cerr << "invalid number of file for mix command: " << filenum << "\nthis command will be not applied\n";
                    std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
                    continue; 
                }
                if (start < 0){
                    std::cout << "in mix command detected negative start second " << start<< "\nwill be applied from 0 second" << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
                    start = 0;
                }
                if (start < end){
                    cmd.filenum = filenum;
                    cmd.start = start;
                    cmd.end = end;
                    commands.push_back(cmd);
                }
                else {
                    std::cerr << "invalid arguments for mix " << filenum << " " <<start << " " << end << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
                }
            }
            else {
                std::cerr << "cannot read values for mix command!\ncommand will be not applied" << std::endl;
                std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
            }
        }
        else if (command == "random"){
            int start, end;
            if (iss >> start >> end){
                if (start < 0){
                    std::cout << "in random command detected negative start second " << start<< "\nwill be applied from 0 second" << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
                    start = 0;
                }
                if (start < end){
                    cmd.start = start;
                    cmd.end = end;
                    commands.push_back(cmd);
                }
                else {
                    std::cerr << "invalid arguments for random " << start << " " << end << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
                }
            }
            else {
                std::cerr << "cannot read values for random command!\ncommand will be not applied" << std::endl;
                std::cout << "warning on line: " << lineCount << std::endl<< std::endl;
            }
        }
        else {
            std::cout << "\nexeption on line: " << lineCount << std::endl;
            throw std::runtime_error("unknown command " + command);// + " on line: " + (const char*)lineCount);
        }
        lineCount++;
    }
    resetConsoleColor();
    file.close();
}

void DATA::checkInputArguments(){
    for (int i = 1; i < argc; ++i)
    {
        if (!std::strcmp(argv[i], "-h")){
            throw std::logic_error("this program [SoundProcessor.exe] modifies the input wav file according to the commands written in the input file with .txt extension\n\n \
            commands that can be used (in file write without []):\nmute [n] [m] - to mute audio from n second to m second\nmix [filenum] [n] [m] - to mix audio with filenum file (filenum type int) from n sec to m sec\nrandom [n] [m] - fill interval from n to m second with random value of samples\n\n \
            syntax of using utilite:\nSoundProcessor.exe <WAV Files pathes... (min 1 file)> <output WAV File path> <todo file path (commands)>\n\n \
            Colors: \nwhite - good way of program\nred - fatal errors\nyellow - warnings\n\ngood luck to you :^)\nby Andrei Zverev 23206");
            
        }
    }
    if (argc < 4){
        throw std::runtime_error("need at least 3 arguments!");
    }
}

const std::vector<std::string> DATA::getInputFiles(){
    return inputFilesPathes;
}
const std::string DATA::getOutputFile(){
    return outputFilePath;
}
const std::string DATA::getTodoFile(){
    return todoFilePath;
}

const std::vector<DATA::COMMAND> DATA::getCommands(){
    return commands;
}

