#define _CRT_SECURE_NO_WARNINGS
#include "WAV.hpp"

WAV::WAV(std::string filepath) : filepath(filepath){}

WAV::~WAV() {}

bool WAV::checkChunk(const char* name, const char* expect){
    return std::strncmp(name, expect, 4) == 0;
}

void WAV::checkHeader (){
    if (!checkChunk(header.riff, "RIFF") || !checkChunk(header.format, "WAVE")) {
        throw std::runtime_error("Invalid WAV file format!\n");
    }
    if (header.audioFormat != 1) { // 1 соответствует PCM
        throw std::runtime_error("Unsupported audio type: not PCM.");
    }

    // Проверка количества каналов
    if (header.numChannels != 1) { // 1 канал для моно
        throw std::runtime_error("not mono canal.");
    }

    // Проверка разрядности
    if (header.bitsPerSample != 16) { // 16 бит
        throw std::runtime_error("not 16 bit per sample");
    }

    // Проверка частоты
    if (header.sampleRate != 44100) { // 44100 Гц
        throw std::runtime_error("not 44100 Hz");
    }
}

void WAV::readHeader(std::ifstream &file) {
    file.read(reinterpret_cast<char*>(&header), sizeof(header) - sizeof(unsigned long) - 4);
    
    int chunkSize;
    char chunkId[4];    
    while (file.read(chunkId, 4))
    {
        file.read(reinterpret_cast<char *>(&chunkSize), 4);
        if (checkChunk(chunkId, "data"))
        {
            const char* chunkId_ = "data"; 
            std::strncpy(header.subchunk2Id, chunkId_, sizeof(header.subchunk2Id));
            header.subchunk2Size = chunkSize;
            break;
        }
        else
        {
            file.seekg(chunkSize, std::ios::cur);
        }

        if (file.eof() || file.fail())
        {
            throw std::runtime_error("Cant find data chunk!\n");
            break;
        }
    }
}

void WAV::getFileData(){
    std::ifstream file(filepath, std::ios::binary);
    if (!file){
        throw std::runtime_error("cannot open file " + filepath);
    }

    readHeader(file);

    samples.resize(header.subchunk2Size / sizeof(short));
    file.read(reinterpret_cast<char *>(samples.data()), header.subchunk2Size);
    if (file.fail()){
        throw std::runtime_error("error reading samples from " + filepath);
    }
    file.close();
}

std::vector<short>& WAV::getSamples(){
    return samples;
}

WAV::WAVHEADER WAV::getHeader() {
    return header;
}

void WAV::copyHeader(WAV* inputWAV){
    this->header = inputWAV->header;
}

void WAV::writeOutputWAV(const std::string& filepath_){
    std::ofstream file(filepath_, std::ios::binary);
    if(!file){
        throw std::runtime_error("error open output file: " + filepath);
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(WAVHEADER));
    file.write(reinterpret_cast<const char *>(samples.data()), samples.size() * sizeof(short));
    file.close();
}