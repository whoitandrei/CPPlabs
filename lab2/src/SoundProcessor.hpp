#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "DATA.hpp"
#include "WAV.hpp"
#include "Converter.hpp"

class ConverterFactory {
public:
    static std::unique_ptr<Converter> createConverter(DATA::COMMAND cmd, DATA* data);
};

class SoundProcessor
{
private:
    DATA* data;

public:
    SoundProcessor(DATA* data);
    virtual ~SoundProcessor();
    void process();

};

