#include "Converter.hpp"
#define SAMPLE_RATE 44100


Mute::Mute(DATA::COMMAND *cmd) : cmd(cmd){}

void Mute::apply(WAV& file){
    auto& sample = file.getSamples();
    size_t sampleSize = sample.size();

    startSample = cmd->start * SAMPLE_RATE;
    endSample = cmd->end * SAMPLE_RATE;
    
    for (size_t i = startSample; i < endSample && i < sampleSize; ++i){
        sample[i] = 0;
    }
    std::cout << "applied mute command. duration: " << cmd->start << " " << cmd->end << std::endl;
}


Mix::Mix(std::string secondFilePath , DATA::COMMAND *cmd) : secondFilePath(secondFilePath), cmd(cmd) {}

void Mix::apply(WAV& file){
    WAV secondFile(secondFilePath);
    secondFile.getFileData();

    startSample = cmd->start * SAMPLE_RATE;
    endSample = cmd->end * SAMPLE_RATE;

    auto& mainSample = file.getSamples();
    const auto& secondSample = secondFile.getSamples();

    for (size_t i = startSample; i < endSample && i < secondSample.size() && i < mainSample.size(); ++i){
        mainSample[i] = (mainSample[i] + secondSample[i]) / 2;
    }
    std::cout << "applied mix command with file: " << secondFilePath << "; duration: " << cmd->start << " " << cmd->end << std::endl;
}

Random::Random(DATA::COMMAND *cmd) : cmd(cmd){}

void Random::apply(WAV& file){
    auto& sample = file.getSamples();
    size_t sampleSize = sample.size();
    startSample = cmd->start * SAMPLE_RATE;
    endSample = cmd->end * SAMPLE_RATE;
    
    std::random_device rd; 
    std::mt19937 gen(rd()); 

    short min = SHRT_MIN; 
    short max = SHRT_MAX;  

    std::uniform_int_distribution<short> dist(min, max);

    for (size_t i = startSample; i < endSample && i < sampleSize; ++i){
        sample[i] = dist(gen);
    }
    std::cout << "applied random command. duration: " << cmd->start << " " <<  cmd->end << std::endl;
}
