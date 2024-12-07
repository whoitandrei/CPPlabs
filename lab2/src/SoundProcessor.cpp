#include "SoundProcessor.hpp"


static std::unique_ptr<Converter> createConverter(DATA::COMMAND* cmd, DATA* data) {
        if (cmd->name == "mute") {
            return std::make_unique<Mute>(cmd);
        } else if (cmd->name == "mix") {
            return std::make_unique<Mix>(data->getInputFiles()[cmd->filenum-1], cmd);
        } else if (cmd->name == "random") {
            return std::make_unique<Random>(cmd);
        }
        return nullptr; 
}

SoundProcessor::SoundProcessor(DATA* data) : data(data){}
SoundProcessor::~SoundProcessor() {}

void SoundProcessor::process(){
    WAV mainFile(data->getInputFiles()[0]);
    mainFile.getFileData();

    for (auto cmd : data->getCommands()){
        std::unique_ptr<Converter> converter = createConverter(&cmd, data);
        if (converter) {
            converter->apply(mainFile);
        } else {
            std::cerr << "Unknown command type: " << cmd.name << std::endl;
        }
    }

    mainFile.writeOutputWAV(data->getOutputFile());
}

