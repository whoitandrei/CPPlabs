#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

class WAV
{
private:
    struct WAVHEADER {
        char riff[4];
        unsigned long chunkSize;
        char format[4];
        char subchunk1Id[4];
        unsigned long subchunk1Size;
        unsigned short audioFormat;
        unsigned short numChannels;
        unsigned long sampleRate;
        unsigned long byteRate;
        unsigned short blockAlign;
        unsigned short bitsPerSample;
        char subchunk2Id[4];
        unsigned long subchunk2Size;
    };

    std::string filepath;
    std::vector<short> samples;
    WAVHEADER header;
    bool checkChunk(const char* name, const char* expect);
    void checkHeader ();
    void readHeader(std::ifstream &file);
   
public:
    WAV(std::string filepath);
    virtual ~WAV();
    void getFileData();
    std::vector<short>& getSamples();
    WAVHEADER getHeader();
    void copyHeader(WAV* inputWAV);
    void writeOutputWAV(const std::string& filepath);
};


